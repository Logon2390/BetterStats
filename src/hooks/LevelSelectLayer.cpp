#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelSelectLayer.hpp>
#include "../managers/DataManager.hpp"
#include <Geode/binding/FLAlertLayer.hpp>
#include "../ui/StatsPopup.cpp"
#include <array>

class $modify(MyLevelSelectLayer, LevelSelectLayer) {

    struct Fields {
        std::array<GJGameLevel*, 3> levels = { nullptr, nullptr, nullptr };
        int page = 1;
    };

    bool init(int page) {
        if (!LevelSelectLayer::init(page)) return false;

        auto sprite = CircleButtonSprite::create(CCSprite::createWithSpriteFrameName("icon.png"_spr), CircleBaseColor::Blue, CircleBaseSize::Tiny);
		auto statsBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(MyLevelSelectLayer::onStatsPopup));
		statsBtn->setID("betterStats-button"_spr);
		statsBtn->setPosition({ -30.f, 0.f });

        auto menu = this->getChildByIDRecursive("info-menu");
        if(menu != nullptr) {
            menu->addChild(statsBtn);
        }
        return true;
    }

    virtual void updatePageWithObject(CCObject* object1, CCObject* object2) {
        LevelSelectLayer::updatePageWithObject(object1, object2);
        GJGameLevel* level = static_cast<GJGameLevel*>(object2);

        m_fields->levels.at(m_fields->page) = level;
        m_fields->page = (m_fields->page + 1) % m_fields->levels.size();
    }
    
    void onStatsPopup(CCObject *level)
    {
        GJGameLevel* currentLevel = m_fields->levels.at(1);
        
        if(currentLevel != nullptr)
        {
            bool load = DataManager::load(currentLevel);

            if (load) 
            {
                int difficulty = static_cast<int>(currentLevel->m_difficulty);
                auto dificultySprite = GJDifficultySprite::create(difficulty, GJDifficultyName::Short);
                StatsPopup::create(currentLevel, dificultySprite)->show();
            }
            else 
            {
				FLAlertLayer::create("?", "This is not a level. What were you expecting to see here ._. ?", "OK")->show();

            }
        }
    }
};

