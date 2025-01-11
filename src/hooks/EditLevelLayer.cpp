#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include "../shared/LevelData.hpp"

class $modify(MyEditLevelLayer, EditLevelLayer){
    bool init(GJGameLevel * level){
        if (!EditLevelLayer::init(level)) return false;
        data = loadData(level);

        auto myInfoBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
            this,
            menu_selector(MyEditLevelLayer::myoninfoBtn));

        auto infoBtn = this->getChildByIDRecursive("info-button");

        if(infoBtn != nullptr){
            myInfoBtn->setPosition(infoBtn->getPosition());
            infoBtn->getParent()->addChild(myInfoBtn);
            infoBtn->setVisible(false);
        }
        return true;
    }


    // ik this is awkward
    void myoninfoBtn(CCObject *)
    {
        std::string title = std::string(m_level->m_levelName);

        FLAlertLayer::create(title.c_str(), dataText(m_level, data), "OK")->show();
        CCScene* currentScene = CCDirector::sharedDirector()->getRunningScene();

        if (currentScene)
        {
            auto fltLayer = currentScene->getChildByID("FLAlertLayer");
			auto layer = fltLayer->getChildByID("main-layer");
			auto flMenu = layer->getChildByID("main-menu");
            auto infoBtn = CCMenuItemSpriteExtra::create(
                CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
                this, menu_selector(EditLevelLayer::onLevelInfo));

            infoBtn->setPosition(ccp(125, -5));
            flMenu->addChild(infoBtn);
            layer->updateLayout();
        }
    }
};