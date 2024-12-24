#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "../shared/LevelData.hpp"
#include "../utils/LevelData.cpp"
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <chrono>

LevelStats data;

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;
		log::info("------------------------------init------------------------------");
		data = loadData(level);
		
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

							+ "<cl>First Practice Run</c>: " + std::to_string(data.first_practice) + "\n"
							+ "<cb>Best Practice Run</c>: " + std::to_string(data.best_practice) + "\n\n"
								
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