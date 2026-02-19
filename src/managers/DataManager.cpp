#include "DataManager.hpp"
#include <Geode/utils/file.hpp>
#include <filesystem>
#include <cvolton.level-id-api/include/EditorIDs.hpp>
#include <Geode/Geode.hpp>
#include <string>

using namespace geode::prelude;

std::string DataManager::levelKey(GJGameLevel* level) {
    if (!level) return "";

    if (level->m_levelType == GJLevelType::Editor)
        return std::to_string(EditorIDs::getID(level)) + "-editor";

    auto base = std::to_string(level->m_levelID.value());

    if (level->m_levelType == GJLevelType::Main)
        return base + "-local";

    if (level->m_dailyID > 0)
        return base + "-daily";

    if (level->m_gauntletLevel)
        return base + "-gauntlet";

    return base + "-saved";
}

LevelStats DataManager::load(GJGameLevel* level) {
    if (!level)
        return StatsManager::getBaseData();

    auto key = levelKey(level);
    auto path = Mod::get()->getSaveDir() / "levels" / (key + ".json");

    if (!std::filesystem::exists(path))
        return loadLegacy(level);

    auto content = file::readString(path);
    if (!content)
        return StatsManager::getBaseData();

    auto parsed = matjson::parse(content.unwrap());
    if (!parsed)
        return StatsManager::getBaseData();

    auto result = parsed.unwrap().as<LevelStats>();
    return result ? result.unwrap() : StatsManager::getBaseData();
}

LevelStats DataManager::save(GJGameLevel* level, const LevelStats& data) {
    if (!level) return data;

    auto key = levelKey(level);
    auto dir = Mod::get()->getSaveDir() / "levels";
    std::filesystem::create_directories(dir);

    auto path = dir / (key + ".json");

    matjson::Value json = data;
    auto result = file::writeString(path, json.dump());

    return data;
}

LevelStats DataManager::loadLegacy(GJGameLevel* level) {
    if (!level)
        return StatsManager::getBaseData();

    auto keyModern = levelKey(level);
    auto keyDefault = std::to_string(level->m_levelID.value());

    std::string key =
        Mod::get()->hasSavedValue(keyModern)
        ? keyModern
        : keyDefault;

    if (!Mod::get()->hasSavedValue(key))
        return StatsManager::getBaseData();

    auto legacy = Mod::get()->getSavedValue<LegacyStats>(key);

    LevelStats result = StatsManager::getBaseData();
    StatsManager::mapLegacyData(legacy, result);

    return save(level, result);
}