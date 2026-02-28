#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
#include "../managers/DataManager.hpp"
#include "../ui/StatsPopup.cpp"

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;
		DataManager::load(level);

		auto sprite = CircleButtonSprite::create(CCSprite::createWithSpriteFrameName("icon.png"_spr), CircleBaseColor::Blue , CircleBaseSize::Tiny);
		auto statsBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(MyLevelInfoLayer::onStatsPopup));
		statsBtn->setID("betterStats-button"_spr);
		statsBtn->setPosition({ 30.f, 0.f });

		auto menu = this->getChildByID("other-menu");
		if(menu != nullptr){
			auto favBtn = menu->getChildByID("favorite-button");
			favBtn->setPosition({ 60.f, 0.f }); //re-position the favorite button to make room for the stats button
			menu->addChild(statsBtn);
		}
		return true;
	}

	void onStatsPopup(CCObject*) {
		StatsPopup::create(m_level, m_difficultySprite)->show();
	}
};