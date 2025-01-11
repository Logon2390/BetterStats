#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include "../shared/LevelData.hpp"
#include <array>


std::array<GJGameLevel*, 3> levels = {nullptr, nullptr, nullptr};
int page = 1;

class $modify(MyLevelSelectLayer, LevelSelectLayer) {
    bool init(int page) {
        if (!LevelSelectLayer::init(page)) return false;
        data = loadData(levels[2]);

        auto myInfoBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
            this,
            menu_selector(MyLevelSelectLayer::myoninfoBtn));

        auto infoBtn = this->getChildByIDRecursive("info-button");

        if(infoBtn != nullptr) {
            myInfoBtn->setPosition(infoBtn->getPosition());
            infoBtn->getParent()->addChild(myInfoBtn);
            infoBtn->setVisible(false);
        }
        return true;
    }

    virtual void updatePageWithObject(CCObject* object1, CCObject* object2) {
        LevelSelectLayer::updatePageWithObject(object1, object2);
        GJGameLevel*  level = static_cast<GJGameLevel*>(object2);

        levels.at(page) = level;
        page = (page + 1) % levels.size();
    }
    
    void myoninfoBtn(CCObject *level)
    {
        GJGameLevel* currentLevel = levels.at(1);
        
        if(currentLevel != nullptr)
        {
            data = loadData(currentLevel);

            std::string title = std::string(currentLevel->m_levelName);
            FLAlertLayer::create(title.c_str(), dataText(currentLevel, data), "OK")->show();
            CCScene* currentScene = CCDirector::sharedDirector()->getRunningScene();

            if (currentScene)
            {
                auto fltLayer = currentScene->getChildByID("FLAlertLayer");
                auto layer = fltLayer->getChildByID("main-layer");
                auto flMenu = layer->getChildByID("main-menu");
                auto infoBtn = CCMenuItemSpriteExtra::create(
                    CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
                    this, menu_selector(LevelSelectLayer::onInfo));

                infoBtn->setPosition(ccp(125, -5));
                flMenu->addChild(infoBtn);
                layer->updateLayout();
            }

        }else{
            LevelSelectLayer::onInfo(level);
        }
    }
};

