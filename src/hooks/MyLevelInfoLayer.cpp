#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "../shared/LevelData.hpp"
#include "../utils/LevelData.cpp"
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/FLAlertLayer.hpp>

LevelStats data;

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;
		data = loadData(level);
		
		auto myInfoBtn = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
			this,
			menu_selector(MyLevelInfoLayer::myoninfoBtn)
		);
		
		auto menu = this->getChildByID("other-menu");
		auto infoBtn = menu->getChildByID("info-button");

		myInfoBtn->setPosition(infoBtn->getPosition());
		infoBtn->getParent()->addChild(myInfoBtn);
		infoBtn->setVisible(false);
		return true;
	}

	void myoninfoBtn(CCObject*) {
		std::string title = std::string(m_level->m_levelName);
		FLAlertLayer::create(title.c_str(), dataText(m_level, data), "OK")->show();
		
		auto currentScene = CCDirector::sharedDirector()->getRunningScene();
		if (!currentScene) return;
		
		auto fltLayer = currentScene->getChildByID("FLAlertLayer");
		if (!fltLayer) return;
		
		auto layer = fltLayer->getChildByID("main-layer");
		if (!layer) return;
		
		auto flMenu = layer->getChildByID("main-menu");
		if (!flMenu) return;
		
		auto infoBtn = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
			this, 
			menu_selector(LevelInfoLayer::onLevelInfo)
		);

		infoBtn->setPosition(ccp(125, -5));
		flMenu->addChild(infoBtn);
		layer->updateLayout();
	}
};