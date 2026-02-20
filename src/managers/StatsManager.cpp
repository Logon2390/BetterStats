#include "StatsManager.hpp"
#include "../utils/Formatters.hpp"

using namespace geode::prelude;

LevelStats StatsManager::levelData{};

LevelStats& StatsManager::setLevelData(const LevelStats& data) {
    StatsManager::levelData = data;
	return StatsManager::levelData;
}

LevelStats& StatsManager::getLevelData() {
    return levelData;
}

void StatsManager::mapLegacyData(const LegacyStats& legacy) 
{
    levelData.practice_stats.attempts = legacy.p_attempts;
    levelData.practice_stats.first_practice.attempts = legacy.first_practice;
    levelData.practice_stats.best_practice.attempts = legacy.best_practice;
    levelData.time_played = legacy.time_played;
}

int StatsManager::getNormalAttempts(const int attempts)
{
	return attempts - levelData.practice_stats.attempts;
}

int StatsManager::getPracticeAttempts()
{
	return levelData.practice_stats.attempts;
}

std::string StatsManager::getTimePlayed()
{
	return formatDuration(levelData.time_played);
}

std::string StatsManager::getPracticeTimePlayed()
{
	return formatDuration(levelData.practice_stats.time_played);
}

int StatsManager::getPracticeRunsCount()
{
    return levelData.practice_stats.practice_count;
}

int64_t StatsManager::getCurrentDate()
{
	return getCurrentTimestamp();
}

std::string StatsManager::getLastPlayed(const bool isLevelComplete)
{
	bool isDataUnavailable = levelData.last_play_date == 0;

    if (!isLevelComplete && isDataUnavailable) return "-";
	return isDataUnavailable ? "unknow" : formatRelativeTime(levelData.last_play_date);
}

std::string StatsManager::getCompleteDate(const bool isLevelComplete)
{
    bool isDataUnavailable = levelData.completed_date == 0;

    if (!isLevelComplete && isDataUnavailable) return "-";
	return  isDataUnavailable ? "unknow" : formatDate(levelData.completed_date);
}

PracticeRunStats StatsManager::getFirstPractice()
{
	return levelData.practice_stats.first_practice;
}

PracticeRunStats StatsManager::getBestPractice()
{
	return levelData.practice_stats.best_practice;
}

PracticeRunStats StatsManager::getLastPractice()
{
	return levelData.practice_stats.last_practice;
}

/* returns the better of the two runs, prioritizing attempts, then checkpoints, then time played */
PracticeRunStats StatsManager::comparePracticeRuns(const PracticeRunStats& run1, const PracticeRunStats& run2)
{
    if (run1.attempts != run2.attempts)
        return (run1.attempts < run2.attempts) ? run1 : run2;

    if (run1.checkpoints != run2.checkpoints)
        return (run1.checkpoints < run2.checkpoints) ? run1 : run2;

    return (run1.time_played < run2.time_played) ? run1 : run2;
}

void StatsManager::registerDeath(int percent) {
    if (percent >= 0 && percent < 100) {
        levelData.deathsPerPercent[percent]++;
    }
}