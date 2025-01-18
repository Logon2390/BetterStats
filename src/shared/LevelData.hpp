#pragma once

#include <Geode/Geode.hpp>
#include <matjson.hpp>
#include <matjson/stl_serialize.hpp>
#include <fmt/format.h>

using namespace geode::prelude;

struct LegacyData {
    int p_attempts;
    int first_practice;
    int best_practice;
    double time_played;
};
typedef struct LegacyData LegacyStats;

struct PracticeRun {
    int attempts;
    int checkpoints;
    double time_played;
};
typedef struct PracticeRun PracticeRunStats;

struct PracticeData {
    int attempts;
    int practice_count;
    double time_played;
    std::string last_practice_date;
    PracticeRunStats first_practice;
    PracticeRunStats best_practice;
    PracticeRunStats last_practice;
};
typedef struct PracticeData PracticeStats;

struct LevelData {
    int attempts;
    std::string completed_date;
    std::string download_date;
    std::string last_play_date;
    PracticeStats practice_stats;
    double time_played;
};
typedef struct LevelData LevelStats;

extern LevelStats data;
extern LegacyStats legacy_data;
extern bool load_legacy_data;

LevelStats getBaseData();
LevelStats loadData(GJGameLevel* level);
std::string dataText(GJGameLevel* level, const LevelStats& data);
std::string levelValue(GJGameLevel* level);
void saveData(GJGameLevel* level, const LevelStats& data);
void loadLegacyData(LevelStats& data);

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

        if(value.contains("p_attempts")){
            GEODE_UNWRAP_INTO(legacy_data.p_attempts, value["p_attempts"].asInt());
            GEODE_UNWRAP_INTO(legacy_data.first_practice, value["first_practice"].asInt());
            GEODE_UNWRAP_INTO(legacy_data.best_practice, value["best_practice"].asInt());
            GEODE_UNWRAP_INTO(legacy_data.time_played, value["time_played"].asDouble());
            load_legacy_data = true;
        }

        GEODE_UNWRAP_INTO(data.attempts, value["attempts"].asInt());
        GEODE_UNWRAP_INTO(data.completed_date, value["completed_date"].asString());
        GEODE_UNWRAP_INTO(data.download_date, value["download_date"].asString());
        GEODE_UNWRAP_INTO(data.last_play_date, value["last_play_date"].asString());
        GEODE_UNWRAP_INTO(data.practice_stats, value["practice_stats"].as<PracticeStats>());
        GEODE_UNWRAP_INTO(data.time_played, value["time_played"].asDouble());
        return geode::Ok(data);
    }
    
    static matjson::Value toJson(const LevelStats& value) {
        return matjson::makeObject({
            {"attempts", value.attempts},
            {"completed_date", value.completed_date},
            {"download_date", value.download_date},
            {"last_play_date", value.last_play_date},
            {"practice_stats", value.practice_stats},
            {"time_played", value.time_played}
        });
    }
};


