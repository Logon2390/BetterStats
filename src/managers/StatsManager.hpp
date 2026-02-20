#pragma once

#include <Geode/Geode.hpp>
#include <Geode/binding/GJGameLevel.hpp>
#include <string>
#include <array>

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
    std::array<int, 100> deathsPerPercent{};
    double time_played{};
};
using LevelStats = LevelData;


class StatsManager {
private:
    static LevelStats levelData;

public:
    static LevelStats& getLevelData();
    static LevelStats& setLevelData(const LevelStats& data);
    static void mapLegacyData(const LegacyStats& legacy);
    static int getNormalAttempts(const int totalAttempts);
    static int getPracticeAttempts();
    static int getPracticeRunsCount();
    static std::string getTimePlayed();
    static std::string getPracticeTimePlayed();
    static std::string getLastPlayed(const bool isLevelComplete);
    static std::string getCompleteDate(const bool isLevelComplete);
    static int64_t getCurrentDate();
	static PracticeRunStats getFirstPractice();
	static PracticeRunStats getBestPractice();
	static PracticeRunStats getLastPractice();
	static PracticeRunStats comparePracticeRuns(const PracticeRunStats& run1, const PracticeRunStats& run2);
    static void registerDeath(int percent);
};