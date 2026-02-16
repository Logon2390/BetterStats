#include <Geode/Geode.hpp>
#include <string>
#include <chrono>
#include <filesystem>

using namespace geode::prelude;

#include "../shared/LevelData.hpp"
#include <cvolton.level-id-api/include/EditorIDs.hpp>
#include <Geode/utils/file.hpp>
#include <matjson.hpp>

PracticeRunStats praticeData = {
    .attempts = 0,
    .checkpoints = 0,
    .time_played = 0
};

PracticeStats practiceStats = {
    .attempts = 0,
    .practice_count = 0,
    .time_played = 0,
    .last_practice_date = "",
    .first_practice = praticeData,
    .best_practice = praticeData,
    .last_practice = praticeData
};

LevelStats levelStats = {
    .completed_date = "",
    .download_date = "",
    .last_play_date = "",
    .practice_stats = practiceStats,
    .time_played = 0
};

LevelStats getBaseData(){
    return LevelStats{
        .completed_date = "",
        .download_date = "",
        .last_play_date = "",
        .practice_stats = practiceStats,
        .time_played = 0
    };
}

std::string dataText(GJGameLevel* level, const LevelStats& data)
{
    std::chrono::duration<double> duration(data.time_played);
    std::chrono::hours hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    duration -= hours;
    std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;
    std::chrono::seconds secs = std::chrono::duration_cast<std::chrono::seconds>(duration);

    std::string infoText = "<cg>Total Attempts</c>: " + std::to_string(level->m_attempts.value()) + "\n" 
                        + "<cy>Normal Attempts</c>: " + std::to_string(level->m_attempts.value() - data.practice_stats.attempts) + "\n" 
                        + "<cc>Practice Attempts</c>: " + std::to_string(data.practice_stats.attempts) + "\n" 
                        + "<cj>Jumps</c>: " + std::to_string(level->m_jumps.value()) + "\n\n"

                        + "<cl>First Practice Run</c>: " + std::to_string(data.practice_stats.first_practice.attempts) + "\n" 
                        + "<cb>Best Practice Run</c>: " + std::to_string(data.practice_stats.best_practice.attempts) + "\n\n"

                        + "<cp>Time Played</c>: " + (hours.count() == 0 ? "" : std::to_string(hours.count()) + "h ") 
                        + (minutes.count() == 0 ? "" : std::to_string(minutes.count()) + "m ") 
                        + std::to_string(secs.count()) + "s";
    return infoText;
}

std::string levelValue(GJGameLevel* level)
{
    std::string value = "";

    if (level->m_levelType == GJLevelType::Editor)
    {
        value += std::to_string(EditorIDs::getID(level));
        value += "-editor";
        return value;
    }
    else
    {
        value += std::to_string(level->m_levelID.value());

        if (level->m_levelType == GJLevelType::Main)
            return value + "-local";

        if (level->m_dailyID > 0)
            return value + "-daily";

        if (level->m_gauntletLevel)
            return value + "-gauntlet";

        return value + "-saved";
    }
}

void mapLegacyData(const LegacyStats& legacyLevel, LevelStats& outData)
{
    outData.practice_stats.attempts = legacyLevel.p_attempts;
    outData.practice_stats.first_practice.attempts = legacyLevel.first_practice;
    outData.practice_stats.best_practice.attempts = legacyLevel.best_practice;
    outData.time_played = legacyLevel.time_played;
}

LevelStats loadLegacyData(GJGameLevel* level)
{
    if (!level) return getBaseData();

    auto keyDefault = std::to_string(level->m_levelID.value());
    auto keyModern = levelValue(level);

    LegacyStats legacyLevel{};
    std::string key = Mod::get()->hasSavedValue(keyModern) ? keyModern : keyDefault;

    if (!Mod::get()->hasSavedValue(key)) return getBaseData();

    legacyLevel = Mod::get()->getSavedValue<LegacyStats>(key);
    LevelStats result = getBaseData();
    mapLegacyData(legacyLevel, result);

    return result;
}

LevelStats loadData(GJGameLevel* level) 
{
    if (!level) return getBaseData();

    std::string levelID = levelValue(level);
    auto levelsDir = Mod::get()->getSaveDir() / "levels";
    auto path = levelsDir / (levelID + ".json");

    if (std::filesystem::exists(path)) 
    {
        auto content = file::readString(path);
        if (!content) return getBaseData();

        auto parsed = matjson::parse(content.unwrap());
        if (!parsed) return getBaseData();

        auto result = parsed.unwrap().as<LevelStats>();
        return result.unwrap();
    }
    else
    {
        auto data = loadLegacyData(level);
        return saveData(level, data);   
    }

	return getBaseData();
}


LevelStats saveData(GJGameLevel* level, const LevelStats& data) {
    std::string levelID = levelValue(level);

    auto levelsDir = Mod::get()->getSaveDir() / "levels";
    auto path = levelsDir / (levelID + ".json");

    matjson::Value json = data;
    auto result = file::writeString(path, json.dump());

	return data;
}