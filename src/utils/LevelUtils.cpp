#include "LevelUtils.hpp"

int getLevelDifficulty(GJGameLevel* level) {
    if (!level) return static_cast<int>(GJDifficulty::NA);
    if (level->m_autoLevel) return static_cast<int>(GJDifficulty::Auto);
    if (level->m_ratings == 0) return static_cast<int>(GJDifficulty::NA);

    if (level->m_demon.value() > 0) {
        switch (level->m_demonDifficulty) {
        case 3: return static_cast<int>(GJDifficulty::DemonEasy);
        case 4: return static_cast<int>(GJDifficulty::DemonMedium);
        case 5: return static_cast<int>(GJDifficulty::DemonInsane);
        case 6: return static_cast<int>(GJDifficulty::DemonExtreme);
        default: return static_cast<int>(GJDifficulty::Demon);
        }
    }

    if (level->m_ratings != 0) {
        int difficulty = level->m_ratingsSum / level->m_ratings;

        switch (difficulty) {
        case 1: return static_cast<int>(GJDifficulty::Easy);
        case 2: return static_cast<int>(GJDifficulty::Normal);
        case 3: return static_cast<int>(GJDifficulty::Hard);
        case 4: return static_cast<int>(GJDifficulty::Harder);
        case 5: return static_cast<int>(GJDifficulty::Insane);
        default: return static_cast<int>(GJDifficulty::NA);
        }
	}

	return static_cast<int>(GJDifficulty::NA);
}

bool isLevelComplete(GJGameLevel* level) {
    return level->getNormalPercent() == 100;
}