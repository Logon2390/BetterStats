#include <Geode/Geode.hpp>
#include <string>
#include <iostream>
#include <chrono>

using namespace geode::prelude;

#include "../shared/LevelData.hpp"
#include <cvolton.level-id-api/include/EditorIDs.hpp>

LevelStats data;

LevelStats getBaseData()
{
    return LevelStats{
        .attempts = 0,
        .p_attempts = 0,
        .first_practice = 0,
        .best_practice = 0,
        .time_played = 0};
}

std::string dataText(GJGameLevel* const& level, LevelStats data)
{
    std::chrono::duration<double> duration(data.time_played);
    std::chrono::hours hours = duration_cast<std::chrono::hours>(duration);
    duration -= hours;
    std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;
    std::chrono::seconds secs = duration_cast<std::chrono::seconds>(duration);

    std::string infoText = "<cg>Total Attempts</c>: " + std::to_string(level->m_attempts) + "\n" 
                        + "<cy>Normal Attempts</c>: " + std::to_string(level->m_attempts - data.p_attempts) + "\n" 
                        + "<cc>Practice Attempts</c>: " + std::to_string(data.p_attempts) + "\n" 
                        + "<cj>Jumps</c>: " + std::to_string(level->m_jumps) + "\n\n"

                        + "<cl>First Practice Run</c>: " + std::to_string(data.first_practice) + "\n" 
                        + "<cb>Best Practice Run</c>: " + std::to_string(data.best_practice) + "\n\n"

                        + "<cp>Time Played</c>: " + (hours.count() == 0 ? "" : std::to_string(hours.count()) + "h ") 
                        + (minutes.count() == 0 ? "" : std::to_string(minutes.count()) + "m ") 
                        + std::to_string(secs.count()) + "s";
    return infoText;
}

std::string levelValue(GJGameLevel* const& level)
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

LevelStats loadData(GJGameLevel* const& level)
{
    if(level == nullptr) return getBaseData();
    if (!Mod::get()->hasSavedValue(levelValue(level)))
    {
        if (Mod::get()->hasSavedValue(std::to_string(level->m_levelID.value())))
        {
            LevelStats data = Mod::get()->getSavedValue<LevelStats>(std::to_string(level->m_levelID.value()));
            Mod::get()->setSavedValue(levelValue(level), data);
            Mod::get()->saveData();
            return data;
        }
        else
        {
            return Mod::get()->setSavedValue(levelValue(level), getBaseData());
        }
    }
    return Mod::get()->getSavedValue<LevelStats>(levelValue(level));
}

void saveData(GJGameLevel* const& level, LevelStats data)
{
    Mod::get()->setSavedValue(levelValue(level), data);
    Mod::get()->saveData();
}