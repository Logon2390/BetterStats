#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/PlayLayer.hpp>
#include "../managers/DataManager.hpp"
#include "../managers/StatsManager.hpp"

class $modify(PlayLayer){

	struct Fields {
		LevelStats levelStats{};
		PracticeRunStats bestPracticeRun{};
		PracticeRunStats currentPracticeRun{};
		double attemptTime = 0;
		double practiceAttemptTime = 0;
		int practiceAttempts = 1;
		int practiceRunsCompleted = 0;
		bool practice = false;
		bool validPracticeRun = false;
		bool savePracticeData = false;
		bool isPracticeMode = false;
	};

	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects){
		if(!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
		m_fields->levelStats = DataManager::load(level);
		m_fields->practice = m_isPracticeMode;
		m_fields->isPracticeMode = m_isPracticeMode;
		return true;
	}

	void levelComplete(){
		if(m_fields->isPracticeMode && m_fields->validPracticeRun){
			m_fields->savePracticeData = true;
			m_fields->practiceRunsCompleted++;
			m_fields->currentPracticeRun.time_played += m_fields->practiceAttemptTime;
			m_fields->bestPracticeRun = m_fields->bestPracticeRun.attempts == 0  ? 
				m_fields->currentPracticeRun : StatsManager::comparePracticeRuns(m_fields->currentPracticeRun, m_fields->bestPracticeRun);
		}

		if (!m_fields->isPracticeMode && m_fields->levelStats.completed_date == 0) {
			m_fields->levelStats.completed_date = StatsManager::getCurrentDate();
		}

		if (m_fields->levelStats.practice_stats.first_practice.attempts == 0) {
			m_fields->levelStats.practice_stats.first_practice = m_fields->currentPracticeRun;
		}

		PlayLayer::levelComplete();
	}

	void togglePracticeMode(bool PracticeMode){
		m_fields->currentPracticeRun = PracticeRunStats{1, 0, 0};
		m_fields->practice = true;
		m_fields->isPracticeMode = !m_fields->isPracticeMode;
		m_fields->validPracticeRun = !m_isPracticeMode && m_attemptTime <= 3;
		PlayLayer::togglePracticeMode(PracticeMode);
	}

	void updateAttempts(){
		if(m_isPracticeMode) {
			m_fields->practiceAttempts++;
			m_fields->currentPracticeRun.attempts++;
			//m_fields->currentPracticeRun++;
		}
		PlayLayer::updateAttempts();
	}

	void resetLevel(){
		m_fields->attemptTime += this->m_attemptTime;
		m_fields->practiceAttemptTime += (m_fields->isPracticeMode) ? this->m_attemptTime : 0;
		m_fields->validPracticeRun = m_fields->validPracticeRun
			|| (m_isPracticeMode && m_checkpointArray->count() == 0);
		PlayLayer::resetLevel();
	}

	CheckpointObject* createCheckpoint(){
		if (m_fields->isPracticeMode) {
			m_fields->currentPracticeRun.checkpoints++;
		}

		return PlayLayer::createCheckpoint();
	}

	void onQuit(){
		auto levelStats = m_fields->levelStats;
		m_fields->attemptTime += this->m_attemptTime;
		m_fields->practiceAttemptTime += (m_fields->isPracticeMode) ? this->m_attemptTime : 0;
		levelStats.time_played += m_fields->attemptTime;
		levelStats.practice_stats.time_played += m_fields->practiceAttemptTime;
		levelStats.last_play_date = StatsManager::getCurrentDate();

		if(m_fields->practice){
			levelStats.practice_stats.attempts += m_fields->practiceAttempts;
			if(m_fields->savePracticeData){
				levelStats.practice_stats.practice_count += m_fields->practiceRunsCompleted;
				levelStats.practice_stats.last_practice = m_fields->currentPracticeRun;
				levelStats.practice_stats.best_practice = levelStats.practice_stats.best_practice.attempts == 0 ? 
					m_fields->bestPracticeRun : StatsManager::comparePracticeRuns(m_fields->bestPracticeRun, levelStats.practice_stats.best_practice);
			}
		}
		m_fields->attemptTime = 0;
		m_fields->practiceAttemptTime = 0;

		DataManager::save(m_level, levelStats);
		PlayLayer::onQuit();
	}
};