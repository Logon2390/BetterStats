#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include "../shared/LevelData.hpp"
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;
		data = loadData(level);
		
		auto sprite = CircleButtonSprite::create(CCSprite::create("test.png"_spr), CircleBaseColor::Blue, CircleBaseSize::Tiny);
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
		std::string title = std::string(m_level->m_levelName);
		FLAlertLayer::create(title.c_str(), dataText(m_level, data), "OK")->show();
		
		CCScene* currentScene = CCDirector::sharedDirector()->getRunningScene();
		if (currentScene){
			auto fltLayer = currentScene->getChildByID("FLAlertLayer");
            auto layer = fltLayer->getChildByID("main-layer");
            auto flMenu = layer->getChildByID("main-menu");
            auto infoBtn = CCMenuItemSpriteExtra::create(
                CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
                this, menu_selector(LevelInfoLayer::onLevelInfo));

            infoBtn->setPosition(ccp(125, -5));
            flMenu->addChild(infoBtn);
            layer->updateLayout();
		}
	}
};