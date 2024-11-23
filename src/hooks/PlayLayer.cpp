#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "../Shared/LevelData.hpp"
#include <Geode/modify/PlayLayer.hpp>

double attemptTime = 0;
int practiceAttempts = 0;
int currentPracticeRun = 0;
int bestPracticeRun = 0;
bool practice = false;
bool validPracticeRun = false;
bool savePracticeData = false;

class $modify(PlayLayer){
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects){
		if(!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
		practiceAttempts = 1;
		bestPracticeRun = 0;
		practice = m_isPracticeMode;
		practice = false;
		savePracticeData = false;
		return true;
	}

	void levelComplete(){
		if(m_isPracticeMode && validPracticeRun){
			savePracticeData = true;
			bestPracticeRun = currentPracticeRun <= bestPracticeRun || bestPracticeRun == 0 ? 
				currentPracticeRun : bestPracticeRun;
		}
		PlayLayer::levelComplete();
	}

	void togglePracticeMode(bool practiceMode){
		currentPracticeRun = 1;
		practice = true;
		validPracticeRun = !m_isPracticeMode && m_attemptTime <= 3;
		PlayLayer::togglePracticeMode(practiceMode);
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
		validPracticeRun = validPracticeRun 
			|| (m_isPracticeMode && m_checkpointArray->count() == 0);
		PlayLayer::resetLevel();
	}

	void onQuit(){
		attemptTime += this->m_attemptTime;
		data.attempts = m_level->m_attempts;
		data.time_played += attemptTime;

		if(practice){
			data.p_attempts += practiceAttempts;
			if(savePracticeData){
				data.first_practice = data.first_practice == 0 ? bestPracticeRun : data.first_practice;
				data.best_practice = bestPracticeRun <= data.best_practice || data.best_practice == 0 ? 
					bestPracticeRun : data.best_practice;
			}
		}
		attemptTime = 0;

		Mod::get()->setSavedValue(std::to_string(m_level->m_levelID), data);
		Mod::get()->saveData();
		PlayLayer::onQuit();
	}
};