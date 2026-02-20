#include "DataManager.hpp"
#include <Geode/utils/file.hpp>
#include <filesystem>
#include <cvolton.level-id-api/include/EditorIDs.hpp>
#include <Geode/Geode.hpp>
#include <string>
#include "StatsManager.hpp"
#include <Geode/loader/Log.hpp>

using namespace geode::prelude;

std::filesystem::path DataManager::levelFilePath{};

std::filesystem::path DataManager::getSaveDir() {
    return Mod::get()->getSaveDir() / "levels";
}

std::filesystem::path DataManager::setLevelPath(const std::string& key) {
    levelFilePath = getSaveDir() / (key + ".json");
	return levelFilePath;
}

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

bool DataManager::load(GJGameLevel* level) {
    if (!level) return false;

	auto path = setLevelPath(levelKey(level));

    if (!std::filesystem::exists(path)) {
		StatsManager::setLevelData({}); //reset loaded data to avoid showing wrong stats
		loadLegacy(level); //try loading legacy data if exists, otherwise default data will be used
        return true;       
    }

    auto content = file::readString(path);
    if (!content) return false;

    auto parsed = matjson::parse(content.unwrap());
    if (!parsed) return false;

    auto result = parsed.unwrap().as<LevelStats>();

    if (result.isOk()) {
        StatsManager::setLevelData(result.unwrap());
        return true;
    }

    return false;
}

bool DataManager::save() {
    matjson::Value json = StatsManager::getLevelData();
    auto result = file::writeString(levelFilePath, json.dump());
    return result.isOk();
}

bool DataManager::loadLegacy(GJGameLevel* level) {
    if (!level) return false;

    auto keyModern = levelKey(level);
    auto keyDefault = std::to_string(level->m_levelID.value());

    std::string key =
        Mod::get()->hasSavedValue(keyModern)
        ? keyModern
        : keyDefault;

    if (!Mod::get()->hasSavedValue(key)) return false;

    auto legacy = Mod::get()->getSavedValue<LegacyStats>(key);
    StatsManager::mapLegacyData(legacy);
    return true;
}