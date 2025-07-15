#include <Geode/Geode.hpp>
#include "../shared/LevelData.hpp"

using namespace geode::prelude;

class MyPopup : public geode::Popup<std::string const &, LevelStats const &>
{
protected:
    bool setup(std::string const &title, LevelStats const &data)
    {
        // @geode-ignore(unknown-resource)
        const char *cornerSpriteName = "rewardCorner_001.png";          // @geode-ignore(unknown-resource)
        const char *timeSpriteName = "GJ_timeIcon_001.png";             // @geode-ignore(unknown-resource)
        const char *accuracySpriteName = "pathIcon_09_001.png";         // @geode-ignore(unknown-resource)
        const char *difficultySpriteName = "difficulty_06_btn_001.png"; // @geode-ignore(unknown-resource)
        const char *ratingSpriteName = "GJ_featuredCoin_001.png";       // @geode-ignore(unknown-resource)
        const char *playIconName = "GJ_playBtn2_001.png";               // @geode-ignore(unknown-resource)
        const char *infoIconName = "GJ_infoIcon_001.png";               // @geode-ignore(unknown-resource)
        const char *checkPointSpriteName = "checkpoint_01_001.png";     // @geode-ignore(unknown-resource)
        const char *backgroundName = "square02b_001.png";               // @geode-ignore(unknown-resource)
        const char *goldFontName = "goldFont.fnt";                      // @geode-ignore(unknown-resource)
        const char *bigFontName = "bigFont.fnt";                        // @geode-ignore(unknown-resource)

        CCSprite *cornerSprite = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChild(cornerSprite);
        cornerSprite->setScale(1.0f);
        cornerSprite->setPosition(ccp(25, 25));

        CCSprite *cornerSprite2 = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChild(cornerSprite2);
        cornerSprite2->setScale(1.0f);
        cornerSprite2->setPosition(ccp(25, 235));
        cornerSprite2->setRotation(90.f);

        CCSprite *cornerSprite3 = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChild(cornerSprite3);
        cornerSprite3->setScale(1.0f);
        cornerSprite3->setPosition(ccp(415, 25));
        cornerSprite3->setRotation(270.f);

        CCSprite *cornerSprite4 = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChild(cornerSprite4);
        cornerSprite4->setScale(1.0f);
        cornerSprite4->setPosition(ccp(415, 235));
        cornerSprite4->setRotation(180.f);

        CCScale9Sprite *statsBG = cocos2d::extension::CCScale9Sprite::create(backgroundName, {0.0f, 0.0f, 80.0f, 80.0f});
        m_mainLayer->addChild(statsBG, 1);
        statsBG->setContentSize({200, 85});
        statsBG->setColor({130, 64, 33});
        statsBG->setPosition(ccp(123, 148));

        CCScale9Sprite *practiceRunsBG = cocos2d::extension::CCScale9Sprite::create(backgroundName, {0.0f, 0.0f, 80.0f, 80.0f});
        m_mainLayer->addChild(practiceRunsBG, 1);
        practiceRunsBG->setContentSize({200, 65});
        practiceRunsBG->setColor({130, 64, 33});
        practiceRunsBG->setPosition(ccp(123, 65));
        practiceRunsBG->setID("practiceRunsBG"_spr);

        CCScale9Sprite *completionBG = cocos2d::extension::CCScale9Sprite::create(backgroundName, {0.0f, 0.0f, 80.0f, 80.0f});
        m_mainLayer->addChild(completionBG, 1);
        completionBG->setContentSize({200, 85});
        completionBG->setColor({130, 64, 33});
        completionBG->setPosition(ccp(123, 148));
        completionBG->setID("completionBG"_spr);

        CCScale9Sprite *downloadBG = cocos2d::extension::CCScale9Sprite::create(backgroundName, {0.0f, 0.0f, 80.0f, 80.0f});
        m_mainLayer->addChild(downloadBG, 1);
        downloadBG->setContentSize({200, 85});
        downloadBG->setColor({130, 64, 33});
        downloadBG->setPosition(ccp(123, 148));
        downloadBG->setID("downloadBG"_spr);

        CCScale9Sprite *lastBG = cocos2d::extension::CCScale9Sprite::create(backgroundName, {0.0f, 0.0f, 80.0f, 80.0f});
        m_mainLayer->addChild(downloadBG, 1);
        downloadBG->setContentSize({200, 85});
        downloadBG->setColor({130, 64, 33});
        downloadBG->setPosition(ccp(123, 148));
        downloadBG->setID("downloadBG"_spr);

        CCMenu *titleMenu = CCMenu::create();
        m_mainLayer->addChild(titleMenu);
        titleMenu->setLayout(RowLayout::create());
        titleMenu->setPosition(ccp(350.0f, 393.0f));

        CCLabelBMFont *titleLabel = CCLabelBMFont::create(title.c_str(), goldFontName);
        titleMenu->addChild(titleLabel);
        titleLabel->setScale(0.7f);
        titleLabel->setAnchorPoint(ccp(0, 0.5f));

        CCSprite *accuracySprite = CCSprite::createWithSpriteFrameName(accuracySpriteName);
        accuracySprite->setScale(0.5f);

        CCSprite *accuracySpriteSelected = CCSprite::createWithSpriteFrameName(accuracySpriteName);
        accuracySpriteSelected->setScale(0.5f);

        CCMenuItemSpriteExtra *accuracyBtn = CCMenuItemSpriteExtra::create(
            accuracySprite,
            accuracySpriteSelected,
            this, menu_selector(MyPopup::onAccuracyBtn));

        titleMenu->addChild(accuracyBtn);
        accuracyBtn->setPosition(ccp(titleLabel->getPositionX() + titleLabel->getScaledContentWidth() + 15, titleLabel->getPositionY()));

        CCLabelBMFont *accuracyLabel = CCLabelBMFont::create("69", bigFontName);
        titleMenu->addChild(accuracyLabel);
        accuracyLabel->setScale(0.25f);
        accuracyLabel->setPosition(ccp(accuracyBtn->getPositionX(), accuracyBtn->getPositionY()));

        CCSprite *ratingSprite = CCSprite::createWithSpriteFrameName(ratingSpriteName);
        m_mainLayer->addChildAtPosition(ratingSprite, Anchor::Top, ccp(-175.0f, -40.0f));
        ratingSprite->setScale(0.9f);

        CCSprite *difficultySprite = CCSprite::createWithSpriteFrameName(difficultySpriteName);
        m_mainLayer->addChildAtPosition(difficultySprite, Anchor::Top, ccp(-175.0f, -40.0f));
        difficultySprite->setScale(0.9f);

        CCSprite *timeSprite = CCSprite::createWithSpriteFrameName(timeSpriteName);
        m_mainLayer->addChild(timeSprite);
        timeSprite->setScale(0.4f);
        timeSprite->setPosition(ccp(73, 217));

        CCLabelBMFont *timeLabel = CCLabelBMFont::create(("Time Played: " + std::to_string(data.time_played)).c_str(), bigFontName);
        m_mainLayer->addChild(timeLabel);
        timeLabel->setScale(0.3f);
        timeLabel->setAnchorPoint(ccp(0, 0.5f));
        timeLabel->setPosition(ccp(timeSprite->getPositionX() + 5, timeSprite->getPositionY() + 1));

        CCSprite *playIcon = CCSprite::createWithSpriteFrameName(playIconName);
        m_mainLayer->addChildAtPosition(playIcon, Anchor::Top, ccp(-192, -80));
        playIcon->setScale(0.18f);
        playIcon->setZOrder(2);

        CCLabelBMFont *statsSubtitle = CCLabelBMFont::create("Stats", goldFontName);
        m_mainLayer->addChild(statsSubtitle, 2);
        statsSubtitle->setScale(0.6f);
        statsSubtitle->setAnchorPoint(ccp(0, 0.5f));
        statsSubtitle->setPosition(ccp(playIcon->getPositionX() + 17, playIcon->getPositionY()));

        CCLabelBMFont *attemptsLabel = CCLabelBMFont::create(("Total Attempts: " + std::to_string(data.attempts)).c_str(), bigFontName);
        m_mainLayer->addChildAtPosition(attemptsLabel, Anchor::Center, ccp(-192, 35));
        attemptsLabel->setScale(0.4f);
        attemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        attemptsLabel->setZOrder(2);

        const int normalAttempts = data.attempts - data.practice_stats.attempts;
        CCLabelBMFont *normalLabel = CCLabelBMFont::create(("Normal Attempts: " + std::to_string(normalAttempts)).c_str(), bigFontName);
        m_mainLayer->addChildAtPosition(normalLabel, Anchor::Center, ccp(-192, 20));
        normalLabel->setScale(0.4f);
        normalLabel->setAnchorPoint(ccp(0, 0.5f));
        normalLabel->setZOrder(2);

        CCLabelBMFont *practiceLabel = CCLabelBMFont::create(("Practice Attempts: " + std::to_string(data.practice_stats.attempts)).c_str(), bigFontName);
        m_mainLayer->addChildAtPosition(practiceLabel, Anchor::Center, ccp(-192, 5));
        practiceLabel->setScale(0.4f);
        practiceLabel->setAnchorPoint(ccp(0, 0.5f));
        practiceLabel->setZOrder(2);

        CCLabelBMFont *jumpsLabel = CCLabelBMFont::create("Jumps: 100", bigFontName);
        m_mainLayer->addChildAtPosition(jumpsLabel, Anchor::Center, ccp(-192, -10));
        jumpsLabel->setScale(0.4f);
        jumpsLabel->setAnchorPoint(ccp(0, 0.5f));
        jumpsLabel->setZOrder(2);

        CCLabelBMFont *bestPracticeSubtitle = CCLabelBMFont::create("Best Practice Run", goldFontName);
        m_mainLayer->addChildAtPosition(bestPracticeSubtitle, Anchor::Center, ccp(-192, -45));
        bestPracticeSubtitle->setScale(0.6f);
        bestPracticeSubtitle->setAnchorPoint(ccp(0, 0.5f));
        bestPracticeSubtitle->setZOrder(2);

        CCLabelBMFont *bestPracticeAttemptsLabel = CCLabelBMFont::create("Attempts: 100", bigFontName);
        m_mainLayer->addChild(bestPracticeAttemptsLabel, 2);
        bestPracticeAttemptsLabel->setScale(0.3f);
        bestPracticeAttemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        bestPracticeAttemptsLabel->setZOrder(2);
        bestPracticeAttemptsLabel->setPosition(ccp(bestPracticeSubtitle->getPositionX(), bestPracticeSubtitle->getPositionY() - 12));

        CCSprite *timeSprite2 = CCSprite::createWithSpriteFrameName(timeSpriteName);
        m_mainLayer->addChild(timeSprite2, 2);
        timeSprite2->setScale(0.3f);
        timeSprite2->setPosition(ccp(bestPracticeAttemptsLabel->getPositionX() + bestPracticeAttemptsLabel->getScaledContentWidth() + 5, bestPracticeAttemptsLabel->getPositionY() - 1));

        CCLabelBMFont *bestPracticeTimeLabel = CCLabelBMFont::create("1h 40m", bigFontName);
        m_mainLayer->addChild(bestPracticeTimeLabel, 2);
        bestPracticeTimeLabel->setScale(0.3f);
        bestPracticeTimeLabel->setAnchorPoint(ccp(0, 0.5f));
        bestPracticeTimeLabel->setPosition(ccp(timeSprite2->getPositionX() + 4, timeSprite2->getPositionY()));

        CCSprite *checkPointSprite = CCSprite::createWithSpriteFrameName(checkPointSpriteName);
        m_mainLayer->addChild(checkPointSprite, 2);
        checkPointSprite->setScale(0.3f);
        checkPointSprite->setPosition(ccp(bestPracticeTimeLabel->getPositionX() + bestPracticeTimeLabel->getScaledContentWidth() + 5, bestPracticeTimeLabel->getPositionY()));

        CCLabelBMFont *bestPracticeCheckpointsLabel = CCLabelBMFont::create("100", bigFontName);
        m_mainLayer->addChild(bestPracticeCheckpointsLabel, 2);
        bestPracticeCheckpointsLabel->setScale(0.3f);
        bestPracticeCheckpointsLabel->setAnchorPoint(ccp(0, 0.5f));
        bestPracticeCheckpointsLabel->setPosition(ccp(checkPointSprite->getPositionX() + 4, checkPointSprite->getPositionY()));

        CCLabelBMFont *firstPracticeSubtitle = CCLabelBMFont::create("First Practice Run", goldFontName);
        m_mainLayer->addChildAtPosition(firstPracticeSubtitle, Anchor::Center, ccp(-192, -72));
        firstPracticeSubtitle->setScale(0.6f);
        firstPracticeSubtitle->setAnchorPoint(ccp(0, 0.5f));
        firstPracticeSubtitle->setZOrder(2);

        CCLabelBMFont *firstPracticeAttemptsLabel = CCLabelBMFont::create("Attempts: 100", bigFontName);
        m_mainLayer->addChild(firstPracticeAttemptsLabel, 2);
        firstPracticeAttemptsLabel->setScale(0.3f);
        firstPracticeAttemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        firstPracticeAttemptsLabel->setPosition(ccp(firstPracticeSubtitle->getPositionX(), firstPracticeSubtitle->getPositionY() - 12));

        CCSprite *timeSprite3 = CCSprite::createWithSpriteFrameName(timeSpriteName);
        m_mainLayer->addChild(timeSprite3, 2);
        timeSprite3->setScale(0.3f);
        timeSprite3->setPosition(ccp(firstPracticeAttemptsLabel->getPositionX() + firstPracticeAttemptsLabel->getScaledContentWidth() + 5, firstPracticeAttemptsLabel->getPositionY() - 1));

        CCLabelBMFont *firstPracticeTimeLabel = CCLabelBMFont::create("1h 20m", bigFontName);
        m_mainLayer->addChild(firstPracticeTimeLabel, 2);
        firstPracticeTimeLabel->setScale(0.3f);
        firstPracticeTimeLabel->setAnchorPoint(ccp(0, 0.5f));
        firstPracticeTimeLabel->setPosition(ccp(timeSprite3->getPositionX() + 4, timeSprite3->getPositionY()));

        CCSprite *checkPointSprite2 = CCSprite::createWithSpriteFrameName(checkPointSpriteName);
        m_mainLayer->addChild(checkPointSprite2, 2);
        checkPointSprite2->setScale(0.3f);
        checkPointSprite2->setPosition(ccp(firstPracticeTimeLabel->getPositionX() + firstPracticeTimeLabel->getScaledContentWidth() + 5, firstPracticeTimeLabel->getPositionY()));

        CCLabelBMFont *firstPracticeCheckpointsLabel = CCLabelBMFont::create("100", bigFontName);
        m_mainLayer->addChild(firstPracticeCheckpointsLabel, 2);
        firstPracticeCheckpointsLabel->setScale(0.3f);
        firstPracticeCheckpointsLabel->setAnchorPoint(ccp(0, 0.5f));
        firstPracticeCheckpointsLabel->setPosition(ccp(checkPointSprite2->getPositionX() + 4, checkPointSprite2->getPositionY()));

        CCSprite *lastPlayedSprite = CCSprite::createWithSpriteFrameName(checkPointSpriteName);
        m_mainLayer->addChild(lastPlayedSprite, 2);
        lastPlayedSprite->setScale(0.3f);
        lastPlayedSprite->setPosition(ccp(90, 100));

        CCLabelBMFont *lastPlayedTimeLabel = CCLabelBMFont::create("Last Played: 23/06/2025 12:00", bigFontName);
        m_mainLayer->addChild(lastPlayedTimeLabel, 2);
        lastPlayedTimeLabel->setScale(0.3f);
        lastPlayedTimeLabel->setAnchorPoint(ccp(0, 0.5f));
        lastPlayedTimeLabel->setPosition(ccp(lastPlayedSprite->getPositionX() + lastPlayedSprite->getScaledContentWidth() + 5, lastPlayedSprite->getPositionY()));

        CCMenu *menu = CCMenu::create();
        menu->setLayout(RowLayout::create());

        CCSprite *infoIcon = CCSprite::createWithSpriteFrameName(infoIconName);
        auto infoBtn = CCMenuItemSpriteExtra::create(
            infoIcon,
            this, menu_selector(MyPopup::onInfoBtn));
        infoBtn->setPosition(ccp(220, 180));
        menu->addChild(infoBtn);

        m_mainLayer->addChildAtPosition(menu, Anchor::BottomRight);

        return true;
    }

    void onInfoBtn(CCObject *node)
    {
        FLAlertLayer::create("Title", "callback", "OK")->show();
    }

    void onAccuracyBtn(CCObject *node)
    {
        FLAlertLayer::create("Accuracy", "callback", "OK")->show();
    }

public:
    static MyPopup *create(std::string const &title, LevelStats const &data)
    {
        auto ret = new MyPopup();
        if (ret->initAnchored(440.f, 260.f, title, data))
        {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }
};
