#pragma once

#include <Geode/Geode.hpp>
#include <matjson.hpp>
#include <matjson/stl_serialize.hpp>

using namespace geode::prelude;

struct LevelData {
    int attempts;
    int p_attempts;
    int first_practice;
    int best_practice;
    double time_played;
};
typedef struct LevelData LevelStats;

template <>
struct matjson::Serialize<LevelStats> {
    static geode::Result<LevelStats> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(int attempts, value["attempts"].asInt());
		GEODE_UNWRAP_INTO(int p_attempts, value["p_attempts"].asInt());
		GEODE_UNWRAP_INTO(int first_practice, value["first_practice"].asInt());
		GEODE_UNWRAP_INTO(int best_practice, value["best_practice"].asInt());
		GEODE_UNWRAP_INTO(double time_played, value["time_played"].asDouble());
		return geode::Ok(LevelStats { attempts, p_attempts, first_practice, best_practice, time_played });
    }
    static matjson::Value toJson(const LevelStats& value) {
        return matjson::makeObject({
			{"attempts", value.attempts},
			{"p_attempts", value.p_attempts},
			{"first_practice", value.first_practice},
			{"best_practice", value.best_practice},
			{"time_played", value.time_played}
        });
    }
};

extern LevelStats data;

