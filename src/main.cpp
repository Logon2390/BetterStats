#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <matjson/stl_serialize.hpp>
#include <matjson.hpp>
#include <chrono>

struct LevelStats {
	int attempts;
	int p_attempts;
	int first_practice;
	int best_practice;
	double time_played;
};

template<>
struct matjson::Serialize<LevelStats> {
    static LevelStats from_json(const matjson::Value& value) {
        return LevelStats {
            .attempts = value["attempts"].as_int(),
			.p_attempts = value["p_attempts"].as_int(),
			.first_practice = value["first_practice"].as_int(),
			.best_practice = value["best_practice"].as_int(),
			.time_played = value["time_played"].as_double()
        };
    }

    static matjson::Value to_json(LevelStats const& value) {
        auto obj = matjson::Object();
			obj["attempts"] = value.attempts;
			obj["p_attempts"] = value.p_attempts;
			obj["first_practice"] = value.first_practice;
			obj["best_practice"] = value.best_practice;
			obj["time_played"] = value.time_played;
        return obj;
    }

	static bool is_json(Value const& value) {
		return value.is_object();
	}
};

LevelStats data;
double attemptTime = 0;
int practiceAttempts = 0;
int currentPracticeRun = 0;
int bestPracticeRun = 0;
bool practice = false;
bool validPracticeRun = false;

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;

		if(!Mod::get()->hasSavedValue(std::to_string(m_level->m_levelID))) {
			data = Mod::get()->setSavedValue(
				std::to_string(m_level->m_levelID), 
				LevelStats { 
					.attempts = m_level->m_attempts,
					.p_attempts = 0, 
					.first_practice = 0, 
					.best_practice = 0, 
					.time_played = 0 });
					Mod::get()->saveData();
		}else{
			data = Mod::get()->getSavedValue<LevelStats>(std::to_string(m_level->m_levelID));
		}

		auto myInfoBtn = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
			this,
			menu_selector(MyLevelInfoLayer::myoninfoBtn)
		);
		
		auto menu = this->getChildByID("other-menu");
		auto infoBtn = menu->getChildByID("info-button");

		myInfoBtn->setPosition(infoBtn->getPosition());
		infoBtn->getParent()->addChild(myInfoBtn);
		infoBtn->getParent()->removeChild(infoBtn);

		myInfoBtn->setID("my-button"_spr);
		return true;
	}

	void myoninfoBtn(CCObject*) {

		std::chrono::duration<double> duration(data.time_played);
		std::chrono::hours hours = duration_cast<std::chrono::hours>(duration);
		duration -= hours;
		std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
		duration -= minutes;
    	std::chrono::seconds secs = duration_cast<std::chrono::seconds>(duration);
		
		std::string title = std::string(m_level->m_levelName);

		std::string infoText = "<cg>Total Attempts</c>: " + std::to_string(m_level->m_attempts) + "\n" 
							+ "<cy>Normal Attempts</c>: " + std::to_string(m_level->m_attempts - data.p_attempts) + "\n"
							+ "<cc>Practice Attempts</c>: " + std::to_string(data.p_attempts) + "\n"
							+ "<cj>Jumps</c>: " + std::to_string(m_level->m_jumps) + "\n\n"

							+ "First Practice Run: " + std::to_string(data.first_practice) + "\n"
							+ "Best Practice Run: " + std::to_string(data.best_practice) + "\n\n"
								
							+"<cp>Time Played</c>: " 
								+ (hours.count() == 0 ? "" : std::to_string(hours.count()) + "h ") 
								+ (minutes.count() == 0 ? "" : std::to_string(minutes.count()) + "m ") 
								+ std::to_string(secs.count()) + "s";

		FLAlertLayer::create(title.c_str(), infoText, "OK")->show();
		CCScene* currentScene = CCDirector::sharedDirector()->getRunningScene();
		
		if (currentScene) 
		{
			auto fltLayer = currentScene->getChildByID("FLAlertLayer");
			auto layer = fltLayer->getChildByID("main-layer");
			auto flMenu = layer->getChildByID("main-menu");
			auto infoBtn = CCMenuItemSpriteExtra::create(
				CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
				this, menu_selector(LevelInfoLayer::onLevelInfo));

			infoBtn->setPosition(ccp(125, -5));
			flMenu->addChild(infoBtn);
			layer->updateLayout();
		}
	}
};

class $modify(PlayLayer){
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects){
		if(!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
		practiceAttempts = 1;
		bestPracticeRun = 0;
		practice = m_isPracticeMode;
		return true;
	}

	void levelComplete(){
		if(m_isPracticeMode && validPracticeRun){
			bestPracticeRun = 
				currentPracticeRun <= bestPracticeRun || bestPracticeRun == 0 ? 
				currentPracticeRun : bestPracticeRun;
		}
		PlayLayer::levelComplete();
	}

	void togglePracticeMode(bool practiceMode){
		currentPracticeRun = 1;
		practice = true;
		validPracticeRun = !m_isPracticeMode && m_attemptTime <= 3;
	}

	void updateAttempts(){
		if(m_isPracticeMode) {
			practiceAttempts++;
			currentPracticeRun++;
		}
		PlayLayer::updateAttempts();
	}

	void resetLevel(){
		attemptTime += this->m_attemptTime;
		
		if (m_isPracticeMode && m_checkpointArray->count() == 0){
			validPracticeRun = true; 
			log::info("valid practice run []");
		}
		PlayLayer::resetLevel();
	}

/*
	void resetLevelFromStart(){
		validPracticeRun = !m_isPracticeMode?
		PlayLayer::resetLevelFromStart();
	}
	*/

	void onQuit(){
		attemptTime += this->m_attemptTime;
		data.attempts = m_level->m_attempts;
		data.time_played += attemptTime;

		if(practice){
			data.p_attempts += practiceAttempts;
			data.first_practice = data.first_practice == 0 ? bestPracticeRun : data.first_practice;
			if(validPracticeRun){
				data.best_practice = 
				bestPracticeRun <= data.best_practice || data.best_practice == 0 ? 
				bestPracticeRun : data.best_practice;
			}
		}
		attemptTime = 0;

		Mod::get()->setSavedValue(std::to_string(m_level->m_levelID), data);
		Mod::get()->saveData();
		PlayLayer::onQuit();
	}
};