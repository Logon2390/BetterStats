#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "../shared/LevelData.hpp"
#include <Geode/modify/PlayLayer.hpp>

double attemptTime = 0;
int practiceAttempts = 0;
int currentPracticeRun = 0;
int bestPracticeRun = 0;
bool practice = false;
bool validPracticeRun = false;
bool savePracticeData = false;
bool isPracticeMode = false;

class $modify(PlayLayer){
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects){
		if(!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
		practiceAttempts = 1;
		bestPracticeRun = 1;
		practice = m_isPracticeMode;
		isPracticeMode = m_isPracticeMode;
		practice = false;
		savePracticeData = false;
		return true;
	}

	void levelComplete(){
		if(isPracticeMode && validPracticeRun){
			savePracticeData = true;
			bestPracticeRun = bestPracticeRun == 1 || currentPracticeRun <= bestPracticeRun ? 
				currentPracticeRun : bestPracticeRun;
		}
		PlayLayer::levelComplete();
	}

	void togglePracticeMode(bool PracticeMode){
		currentPracticeRun = 1;
		practice = true;
		isPracticeMode = !isPracticeMode;
		validPracticeRun = !m_isPracticeMode && m_attemptTime <= 3;
		PlayLayer::togglePracticeMode(PracticeMode);
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
		data.attempts = m_level->m_attempts.value();
		data.time_played += attemptTime;

		if(practice){
			data.practice_stats.attempts += practiceAttempts;
			if(savePracticeData){
				data.practice_stats.first_practice.attempts = data.practice_stats.first_practice.attempts == 0 ? bestPracticeRun : data.practice_stats.first_practice.attempts;
				data.practice_stats.best_practice.attempts = bestPracticeRun <= data.practice_stats.best_practice.attempts || data.practice_stats.best_practice.attempts == 0 ? 
					bestPracticeRun : data.practice_stats.best_practice.attempts;
			}
		}
		attemptTime = 0;

		saveData(m_level, data);
		PlayLayer::onQuit();
	}
};