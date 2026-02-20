#pragma once

#include <Geode/Geode.hpp>
#include <Geode/binding/GJGameLevel.hpp>
#include <matjson.hpp>
#include <array>
#include "StatsManager.hpp"
#include <Geode/Enums.hpp>

using namespace geode::prelude;

template <>
struct matjson::Serialize<PracticeRunStats> {
    static geode::Result<PracticeRunStats> fromJson(const matjson::Value& value) {
        PracticeRunStats data;
        GEODE_UNWRAP_INTO(data.attempts, value["attempts"].asInt());
        GEODE_UNWRAP_INTO(data.checkpoints, value["checkpoints"].asInt());
        GEODE_UNWRAP_INTO(data.time_played, value["time_played"].asDouble());
        return geode::Ok(data);
    }

    static matjson::Value toJson(const PracticeRunStats& value) {
        return matjson::makeObject({
            {"attempts", value.attempts},
            {"checkpoints", value.checkpoints},
            {"time_played", value.time_played}
            });
    }
};

template <>
struct matjson::Serialize<PracticeStats> {
    static geode::Result<PracticeStats> fromJson(const matjson::Value& value) {
        PracticeStats data;
        GEODE_UNWRAP_INTO(data.attempts, value["attempts"].asInt());
        GEODE_UNWRAP_INTO(data.practice_count, value["practice_count"].asInt());
        GEODE_UNWRAP_INTO(data.time_played, value["time_played"].asDouble());
        GEODE_UNWRAP_INTO(data.last_practice_date, value["last_practice_date"].asString());
        GEODE_UNWRAP_INTO(data.first_practice, value["first_practice"].as<PracticeRunStats>());
        GEODE_UNWRAP_INTO(data.best_practice, value["best_practice"].as<PracticeRunStats>());
        GEODE_UNWRAP_INTO(data.last_practice, value["last_practice"].as<PracticeRunStats>());
        return geode::Ok(data);
    }

    static matjson::Value toJson(const PracticeStats& value) {
        return matjson::makeObject({
            {"attempts", value.attempts},
            {"practice_count", value.practice_count},
            {"time_played", value.time_played},
            {"last_practice_date", value.last_practice_date},
            {"first_practice", value.first_practice},
            {"best_practice", value.best_practice},
            {"last_practice", value.last_practice}
            });
    }
};

template <>
struct matjson::Serialize<LevelStats> {
    static geode::Result<LevelStats> fromJson(const matjson::Value& value) {
        LevelStats data;
        GEODE_UNWRAP_INTO(data.completed_date, value["completed_date"].as<int64_t>());
        GEODE_UNWRAP_INTO(data.last_play_date, value["last_play_date"].as<int64_t>());
        GEODE_UNWRAP_INTO(data.practice_stats, value["practice_stats"].as<PracticeStats>());
        GEODE_UNWRAP_INTO(data.time_played, value["time_played"].asDouble());
		GEODE_UNWRAP_INTO(data.deathsPerPercent, value["deathsPerPercent"].as<std::array<int, 100>>());
        return geode::Ok(data);
    }

    static matjson::Value toJson(const LevelStats& value) {
        return matjson::makeObject({
            {"completed_date", value.completed_date},
            {"last_play_date", value.last_play_date},
            {"practice_stats", value.practice_stats},
            {"time_played", value.time_played},
            { "deathsPerPercent", value.deathsPerPercent}
            });
    }
};

template <>
struct matjson::Serialize<LegacyStats> {
    static geode::Result<LegacyStats> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(int p_attempts, value["p_attempts"].asInt());
        GEODE_UNWRAP_INTO(int first_practice, value["first_practice"].asInt());
        GEODE_UNWRAP_INTO(int best_practice, value["best_practice"].asInt());
        GEODE_UNWRAP_INTO(double time_played, value["time_played"].asDouble());
        return geode::Ok(LegacyStats{ p_attempts, first_practice, best_practice, time_played });
    }

    static matjson::Value toJson(const LegacyStats& value) {
        return matjson::makeObject({
            {"p_attempts", value.p_attempts},
            {"first_practice", value.first_practice},
            {"best_practice", value.best_practice},
            {"time_played", value.time_played},
            });
    }
};

class DataManager {
public:
    static bool load(GJGameLevel* level);
    static bool save();

private:
    static std::filesystem::path getSaveDir();
	static std::filesystem::path levelFilePath;
    static std::filesystem::path setLevelPath(const std::string& key);
    static bool loadLegacy(GJGameLevel* level);
    static std::string levelKey(GJGameLevel* level);
};