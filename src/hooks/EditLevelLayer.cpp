#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include "../managers/DataManager.hpp"
#include "../managers/StatsManager.hpp"
#include "../ui/StatsPopup.cpp"

class $modify(MyEditLevelLayer, EditLevelLayer){

    struct Fields {
        LevelStats levelStats{};
    };

    bool init(GJGameLevel * level){
        if (!EditLevelLayer::init(level)) return false;
        m_fields->levelStats = DataManager::load(level);

        auto sprite = CircleButtonSprite::create(CCSprite::create("test.png"_spr), CircleBaseColor::Blue, CircleBaseSize::Tiny);
		auto statsBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(MyEditLevelLayer::onStatsPopup));
        statsBtn->setID("betterStats-button"_spr);
		statsBtn->setPosition({ 30, 0 });

        auto menu = this->getChildByIDRecursive("info-button-menu");
        if(menu != nullptr){
            menu->addChild(statsBtn);
			menu->updateLayout();
        }
        return true;
    }


    void onStatsPopup(CCObject *)
    {
		auto dificultySprite = GJDifficultySprite::create(0, GJDifficultyName::Short);
		StatsPopup::create(m_level, dificultySprite, m_fields->levelStats)->show();
    }
};