#pragma once

#include <Geode/Geode.hpp>
#include <Geode/binding/GJGameLevel.hpp>
#include <string>
#include <Geode/utils/timer.hpp>

using namespace geode::prelude;

struct LegacyData {
    int p_attempts{};
    int first_practice{};
    int best_practice{};
    double time_played{};
};
using LegacyStats = LegacyData;

struct PracticeRun {
    int attempts{};
    int checkpoints{};
    double time_played{};
};
using PracticeRunStats = PracticeRun;

struct PracticeData {
    int attempts{};
    int practice_count{};
    double time_played{};
    std::string last_practice_date{};
    PracticeRunStats first_practice{};
    PracticeRunStats best_practice{};
    PracticeRunStats last_practice{};
};
using PracticeStats = PracticeData;

struct LevelData {
    int64_t completed_date{};
    int64_t last_play_date{};
    PracticeStats practice_stats{};
    double time_played{};
};
using LevelStats = LevelData;


class StatsManager {
public:
    static LevelStats getBaseData();
    static void mapLegacyData(const LegacyStats& legacy, LevelStats& outData);
    static int getNormalAttempts(GJGameLevel* level, const LevelStats& data);
    static int getPracticeAttempts(const LevelStats& data);
    static int getPracticeRunsCount(const LevelStats& data);
    static std::string getTimePlayed(const LevelStats& data);
    static std::string getPracticeTimePlayed(const LevelStats& data);
    static std::string getLastPlayed(const LevelStats& data);
    static std::string getCompleteDate(const LevelStats& data);
    static int64_t getCurrentDate();
	static PracticeRunStats getFirstPractice(const LevelStats& data);
	static PracticeRunStats getBestPractice(const LevelStats& data);
	static PracticeRunStats getLastPractice(const LevelStats& data);
	static PracticeRunStats comparePracticeRuns(const PracticeRunStats& run1, const PracticeRunStats& run2);
};