#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "../shared/LevelData.hpp"
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include "MyPopup.cpp"

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;
		levelStats = loadData(level);

		auto sprite = CircleButtonSprite::create(CCSprite::createWithSpriteFrameName("test.png"_spr), CircleBaseColor::Blue, CircleBaseSize::Tiny);
		auto statsBtn = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(MyLevelInfoLayer::myoninfoBtn));
		statsBtn->setID("stats-button"_spr);

		auto menu = this->getChildByID("other-menu");
		if(menu != nullptr){
			auto infoBtn = menu->getChildByID("info-button");
			statsBtn->setPosition(infoBtn->getPosition());
			infoBtn->getParent()->addChild(statsBtn);
			infoBtn->setVisible(false);
			menu->updateLayout();
		}
 
		return true;
	}

	void myoninfoBtn(CCObject*) {
		MyPopup::create(m_level, m_difficultySprite, levelStats)->show();
	}
};