#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include "../managers/StatsManager.hpp"
#include "../managers/DataManager.hpp"
#include "../ui/StatsPopup.cpp"

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
	struct Fields {
		LevelStats levelStats{};
	};
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;
		  m_fields->levelStats = DataManager::load(level);

		auto sprite = CircleButtonSprite::create(CCSprite::createWithSpriteFrameName("icon.png"_spr), CircleBaseColor::Blue , CircleBaseSize::Tiny);
		auto statsBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(MyLevelInfoLayer::onStatsPopup));
		statsBtn->setID("betterStats-button"_spr);
		statsBtn->setPosition({ 30, 0 });

		auto menu = this->getChildByID("other-menu");
		if(menu != nullptr){
			auto favBtn = menu->getChildByID("favorite-button");
			favBtn->setPosition({ 60, 0 }); //re-position the favorite button to make room for the stats button
			menu->addChild(statsBtn);
			menu->updateLayout();
		}
 
		return true;
	}

	void onStatsPopup(CCObject*) {
		StatsPopup::create(m_level, m_difficultySprite, m_fields->levelStats)->show();
	}
};