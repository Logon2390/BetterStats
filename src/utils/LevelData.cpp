#include <Geode/Geode.hpp>
#include <string>
#include <iostream>
#include <chrono>

using namespace geode::prelude;

#include "../shared/LevelData.hpp"
#include <cvolton.level-id-api/include/EditorIDs.hpp>

bool load_legacy_data = false;

LegacyStats legacy_data = {
    .p_attempts = 0,
    .first_practice = 0,
    .best_practice = 0,
    .time_played = 0
};

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

LevelStats data = {
    .attempts = 0,
    .completed_date = "",
    .download_date = "",
    .last_play_date = "",
    .practice_stats = practiceStats,
    .time_played = 0
};

LevelStats getBaseData(){
    return LevelStats{
        .attempts = 0,
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

        if (level->m_levelType == GJLevelType::Local)
            return value + "-local";

        if (level->m_dailyID > 0)
            return value + "-daily";

        if (level->m_gauntletLevel)
            return value + "-gauntlet";

        return value + "-saved";
    }
}

void loadLegacyData(LevelStats& data)
{
    data.practice_stats.attempts = legacy_data.p_attempts;
    data.practice_stats.first_practice.attempts = legacy_data.first_practice;
    data.practice_stats.best_practice.attempts = legacy_data.best_practice;
    data.time_played = legacy_data.time_played;
    load_legacy_data = false;
}

LevelStats loadData(GJGameLevel* level)
{
    if(level == nullptr) return getBaseData();
    if (!Mod::get()->hasSavedValue(levelValue(level)))
    {
        if (Mod::get()->hasSavedValue(std::to_string(level->m_levelID)))
        {
            LevelStats data = Mod::get()->getSavedValue<LevelStats>(std::to_string(level->m_levelID.value()));
            if (load_legacy_data) loadLegacyData(data);

            Mod::get()->setSavedValue(levelValue(level), data);
            Mod::get()->saveData();
            return data;
        }
        else
        {
            return Mod::get()->setSavedValue(levelValue(level), getBaseData());
        }
    }

    LevelStats data = Mod::get()->getSavedValue<LevelStats>(levelValue(level));
    if (load_legacy_data) loadLegacyData(data);
    return data;
}

void saveData(GJGameLevel* level, const LevelStats& data)
{
    Mod::get()->setSavedValue(levelValue(level), data);
    Mod::get()->saveData();
}