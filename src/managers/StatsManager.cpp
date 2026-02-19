#include "StatsManager.hpp"
#include "../utils/Formatters.hpp"

using namespace geode::prelude;

LevelStats StatsManager::getBaseData() 
{
    return LevelStats{};
}

void StatsManager::mapLegacyData(const LegacyStats& legacy, LevelStats& outData) 
{
    outData.practice_stats.attempts = legacy.p_attempts;
    outData.practice_stats.first_practice.attempts = legacy.first_practice;
    outData.practice_stats.best_practice.attempts = legacy.best_practice;
    outData.time_played = legacy.time_played;
}

int StatsManager::getNormalAttempts(GJGameLevel* level, const LevelStats& data)
{
	return level->m_attempts.value() - data.practice_stats.attempts;
}

int StatsManager::getPracticeAttempts(const LevelStats& data)
{
	return data.practice_stats.attempts;
}

std::string StatsManager::getTimePlayed(const LevelStats& data)
{
	return formatDuration(data.time_played);
}

std::string StatsManager::getPracticeTimePlayed(const LevelStats& data)
{
	return formatDuration(data.practice_stats.time_played);
}

int StatsManager::getPracticeRunsCount(const LevelStats& data)
{
    return data.practice_stats.practice_count;
}

int64_t StatsManager::getCurrentDate()
{
	return getCurrentTimestamp();
}

std::string StatsManager::getLastPlayed(const LevelStats& data)
{
	return data.last_play_date == 0 ? "unknow" : formatRelativeTime(data.last_play_date);
}

std::string StatsManager::getCompleteDate(const LevelStats& data)
{
	return data.completed_date == 0 ? "unknow" : formatDate(data.completed_date);
}

PracticeRunStats StatsManager::getFirstPractice(const LevelStats& data)
{
	return data.practice_stats.first_practice;
}

PracticeRunStats StatsManager::getBestPractice(const LevelStats& data)
{
	return data.practice_stats.best_practice;
}

PracticeRunStats StatsManager::getLastPractice(const LevelStats& data)
{
	return data.practice_stats.last_practice;
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