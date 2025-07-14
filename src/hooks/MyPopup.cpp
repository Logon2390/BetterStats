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
        const char *goldFontName = "goldFont.fnt";                      // @geode-ignore(unknown-resource)
        const char *bigFontName = "bigFont.fnt";                        // @geode-ignore(unknown-resource)

        CCSprite *cornerSprite = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        cornerSprite->setScale(1.0f);
        cornerSprite->setPosition(ccp(25, 25));
        m_mainLayer->addChild(cornerSprite);

        CCSprite *cornerSprite2 = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        cornerSprite2->setScale(1.0f);
        cornerSprite2->setPosition(ccp(25, 235));
        cornerSprite2->setRotation(90.f);
        m_mainLayer->addChild(cornerSprite2);

        CCSprite *cornerSprite3 = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        cornerSprite3->setScale(1.0f);
        cornerSprite3->setPosition(ccp(415, 25));
        cornerSprite3->setRotation(270.f);
        m_mainLayer->addChild(cornerSprite3);

        CCSprite *cornerSprite4 = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        cornerSprite4->setScale(1.0f);
        cornerSprite4->setPosition(ccp(415, 235));
        cornerSprite4->setRotation(180.f);
        m_mainLayer->addChild(cornerSprite4);

        CCMenu *titleMenu = CCMenu::create();
        titleMenu->setLayout(RowLayout::create());
        titleMenu->setPosition(ccp(350.0f, 393.0f));
        m_mainLayer->addChild(titleMenu);

        CCLabelBMFont *titleLabel = CCLabelBMFont::create(title.c_str(), goldFontName);
        titleLabel->setScale(0.7f);
        titleLabel->setAnchorPoint(ccp(0, 0.5f));
        titleMenu->addChild(titleLabel);

        CCSprite *accuracySprite = CCSprite::createWithSpriteFrameName(accuracySpriteName);
        accuracySprite->setScale(0.5f);

        CCSprite *accuracySpriteSelected = CCSprite::createWithSpriteFrameName(accuracySpriteName);
        accuracySpriteSelected->setScale(0.5f);

        CCMenuItemSpriteExtra *accuracyBtn = CCMenuItemSpriteExtra::create(
            accuracySprite,
            accuracySpriteSelected,
            this, menu_selector(MyPopup::onAccuracyBtn));

        accuracyBtn->setPosition(ccp(titleLabel->getPositionX() + titleLabel->getScaledContentWidth() + 15, titleLabel->getPositionY()));
        titleMenu->addChild(accuracyBtn);

        CCLabelBMFont *accuracyLabel = CCLabelBMFont::create("69", bigFontName);
        accuracyLabel->setScale(0.3f);
        accuracyLabel->setPosition(ccp(accuracyBtn->getPositionX(), accuracyBtn->getPositionY()));
        titleMenu->addChild(accuracyLabel);

        CCSprite *ratingSprite = CCSprite::createWithSpriteFrameName(ratingSpriteName);
        ratingSprite->setScale(0.9f);
        m_mainLayer->addChildAtPosition(ratingSprite, Anchor::Top, ccp(-175.0f, -40.0f));

        CCSprite *difficultySprite = CCSprite::createWithSpriteFrameName(difficultySpriteName);
        difficultySprite->setScale(0.9f);
        m_mainLayer->addChildAtPosition(difficultySprite, Anchor::Top, ccp(-175.0f, -40.0f));

        CCSprite *timeSprite = CCSprite::createWithSpriteFrameName(timeSpriteName);
        timeSprite->setScale(0.4f);
        timeSprite->setPosition(ccp(73, 217));
        m_mainLayer->addChild(timeSprite);

        CCLabelBMFont *timeLabel = CCLabelBMFont::create(("Time Played: " + std::to_string(data.time_played)).c_str(), bigFontName);
        timeLabel->setScale(0.3f);
        timeLabel->setAnchorPoint(ccp(0, 0.5f));
        timeLabel->setPosition(ccp(timeSprite->getPositionX() + 5, timeSprite->getPositionY() + 1));
        m_mainLayer->addChild(timeLabel);

        CCSprite *playIcon = CCSprite::createWithSpriteFrameName(playIconName);
        playIcon->setScale(0.18f);
        playIcon->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(playIcon, Anchor::Top, ccp(-192, -80));

        CCLabelBMFont *statsSubtitle = CCLabelBMFont::create("Stats", goldFontName);
        statsSubtitle->setScale(0.6f);
        statsSubtitle->setAnchorPoint(ccp(0, 0.5f));
        statsSubtitle->setPosition(ccp(playIcon->getPositionX() + 17, playIcon->getPositionY()));
        m_mainLayer->addChild(statsSubtitle);

        CCLabelBMFont *attemptsLabel = CCLabelBMFont::create(("Total Attempts: " + std::to_string(data.attempts)).c_str(), bigFontName);
        attemptsLabel->setScale(0.4f);
        attemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(attemptsLabel, Anchor::Center, ccp(-192, 35));

        CCLabelBMFont *normalLabel = CCLabelBMFont::create(("Normal Attempts: " + std::to_string(data.practice_stats.attempts)).c_str(), bigFontName);
        normalLabel->setScale(0.4f);
        normalLabel->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(normalLabel, Anchor::Center, ccp(-192, 20));

        CCLabelBMFont *practiceLabel = CCLabelBMFont::create(("Practice Attempts: " + std::to_string(data.practice_stats.attempts)).c_str(), bigFontName);
        practiceLabel->setScale(0.4f);
        practiceLabel->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(practiceLabel, Anchor::Center, ccp(-192, 5));

        CCLabelBMFont *jumpsLabel = CCLabelBMFont::create("Jumps: 100", bigFontName);
        jumpsLabel->setScale(0.4f);
        jumpsLabel->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(jumpsLabel, Anchor::Center, ccp(-192, -10));

        CCLabelBMFont *bestPracticeSubtitle = CCLabelBMFont::create("Best Practice Run", goldFontName);
        bestPracticeSubtitle->setScale(0.6f);
        bestPracticeSubtitle->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(bestPracticeSubtitle, Anchor::Center, ccp(-192, -30));

        CCLabelBMFont *bestPracticeAttemptsLabel = CCLabelBMFont::create("Attempts: 100", bigFontName);
        bestPracticeAttemptsLabel->setScale(0.3f);
        bestPracticeAttemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        bestPracticeAttemptsLabel->setPosition(ccp(bestPracticeSubtitle->getPositionX(), bestPracticeSubtitle->getPositionY() - 12));
        m_mainLayer->addChild(bestPracticeAttemptsLabel);

        CCSprite *timeSprite2 = CCSprite::createWithSpriteFrameName(timeSpriteName);
        timeSprite2->setScale(0.3f);
        timeSprite2->setPosition(ccp(bestPracticeAttemptsLabel->getPositionX() + bestPracticeAttemptsLabel->getScaledContentWidth() + 5, bestPracticeAttemptsLabel->getPositionY() - 1));
        m_mainLayer->addChild(timeSprite2);

        CCLabelBMFont *bestPracticeTimeLabel = CCLabelBMFont::create("1h 40m", bigFontName);
        bestPracticeTimeLabel->setScale(0.3f);
        bestPracticeTimeLabel->setAnchorPoint(ccp(0, 0.5f));
        bestPracticeTimeLabel->setPosition(ccp(timeSprite2->getPositionX() + 4, timeSprite2->getPositionY()));
        m_mainLayer->addChild(bestPracticeTimeLabel);

        CCSprite *checkPointSprite = CCSprite::createWithSpriteFrameName(checkPointSpriteName);
        checkPointSprite->setScale(0.3f);
        checkPointSprite->setPosition(ccp(bestPracticeTimeLabel->getPositionX() + bestPracticeTimeLabel->getScaledContentWidth() + 5, bestPracticeTimeLabel->getPositionY()));
        m_mainLayer->addChild(checkPointSprite);

        CCLabelBMFont *bestPracticeCheckpointsLabel = CCLabelBMFont::create("100", bigFontName);
        bestPracticeCheckpointsLabel->setScale(0.3f);
        bestPracticeCheckpointsLabel->setAnchorPoint(ccp(0, 0.5f));
        bestPracticeCheckpointsLabel->setPosition(ccp(checkPointSprite->getPositionX() + 4, checkPointSprite->getPositionY()));
        m_mainLayer->addChild(bestPracticeCheckpointsLabel);

        CCLabelBMFont *firstPracticeSubtitle = CCLabelBMFont::create("First Practice Run", goldFontName);
        firstPracticeSubtitle->setScale(0.6f);
        firstPracticeSubtitle->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(firstPracticeSubtitle, Anchor::Center, ccp(-192, -57));

        CCLabelBMFont *firstPracticeAttemptsLabel = CCLabelBMFont::create("Attempts: 100", bigFontName);
        firstPracticeAttemptsLabel->setScale(0.3f);
        firstPracticeAttemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        firstPracticeAttemptsLabel->setPosition(ccp(firstPracticeSubtitle->getPositionX(), firstPracticeSubtitle->getPositionY() - 12));
        m_mainLayer->addChild(firstPracticeAttemptsLabel);

        CCSprite *timeSprite3 = CCSprite::createWithSpriteFrameName(timeSpriteName);
        timeSprite3->setScale(0.3f);
        timeSprite3->setPosition(ccp(firstPracticeAttemptsLabel->getPositionX() + firstPracticeAttemptsLabel->getScaledContentWidth() + 5, firstPracticeAttemptsLabel->getPositionY() - 1));
        m_mainLayer->addChild(timeSprite3);

        CCLabelBMFont *firstPracticeTimeLabel = CCLabelBMFont::create("1h 20m", bigFontName);
        firstPracticeTimeLabel->setScale(0.3f);
        firstPracticeTimeLabel->setAnchorPoint(ccp(0, 0.5f));
        firstPracticeTimeLabel->setPosition(ccp(timeSprite3->getPositionX() + 4, timeSprite3->getPositionY()));
        m_mainLayer->addChild(firstPracticeTimeLabel);

        CCSprite *checkPointSprite2 = CCSprite::createWithSpriteFrameName(checkPointSpriteName);
        checkPointSprite2->setScale(0.3f);
        checkPointSprite2->setPosition(ccp(firstPracticeTimeLabel->getPositionX() + firstPracticeTimeLabel->getScaledContentWidth() + 5, firstPracticeTimeLabel->getPositionY()));
        m_mainLayer->addChild(checkPointSprite2);

        CCLabelBMFont *firstPracticeCheckpointsLabel = CCLabelBMFont::create("100", bigFontName);
        firstPracticeCheckpointsLabel->setScale(0.3f);
        firstPracticeCheckpointsLabel->setAnchorPoint(ccp(0, 0.5f));
        firstPracticeCheckpointsLabel->setPosition(ccp(checkPointSprite2->getPositionX() + 4, checkPointSprite2->getPositionY()));
        m_mainLayer->addChild(firstPracticeCheckpointsLabel);

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
