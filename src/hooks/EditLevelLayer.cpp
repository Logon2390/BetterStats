#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditLevelLayer.hpp>
#include "../managers/DataManager.hpp"
#include "../ui/StatsPopup.cpp"

class $modify(MyEditLevelLayer, EditLevelLayer){
    bool init(GJGameLevel * level){
        if (!EditLevelLayer::init(level)) return false;
        DataManager::load(level);

        auto sprite = CircleButtonSprite::create(CCSprite::createWithSpriteFrameName("icon.png"_spr), CircleBaseColor::Blue, CircleBaseSize::Tiny);
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
		StatsPopup::create(m_level, dificultySprite)->show();
    }
};
