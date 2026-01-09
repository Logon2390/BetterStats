#include <Geode/Geode.hpp>
#include "../shared/LevelData.hpp"
#include <Geode/binding/GJDifficultySprite.hpp>

using namespace geode::prelude;

class MyPopup : public geode::Popup<GJGameLevel* const &, GJDifficultySprite* , LevelStats const &>
{
protected:
    bool setup(GJGameLevel* const &level, GJDifficultySprite* difficultySprite, LevelStats const &data)
    {
        const char *cornerSpriteName = "rewardCorner_001.png";
        const char *accuracySpriteName = "pathIcon_09_001.png";
        const char* infoIconName = "GJ_infoIcon_001.png";
        const char *backgroundName = "square02b_001.png";
        const char* bigFontName = "bigFont.fnt";
		const char* goldFontName = "goldFont.fnt";

        CCSprite *BottomLeftSprite = CCSprite::createWithSpriteFrameName(cornerSpriteName);
		m_mainLayer->addChildAtPosition(BottomLeftSprite, Anchor::BottomLeft, ccp(25, 25));

        CCSprite *cornerSprite2 = CCSprite::createWithSpriteFrameName(cornerSpriteName);
		m_mainLayer->addChildAtPosition(cornerSprite2, Anchor::TopLeft, ccp(25, -25));
        cornerSprite2->setRotation(90.f);

        CCSprite *cornerSprite3 = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChildAtPosition(cornerSprite3, Anchor::BottomRight, ccp(-25, 25));
        cornerSprite3->setRotation(270.f);

        CCSprite *cornerSprite4 = CCSprite::createWithSpriteFrameName(cornerSpriteName);
		m_mainLayer->addChildAtPosition(cornerSprite4, Anchor::TopRight, ccp(-25, -25));
        cornerSprite4->setRotation(180.f);

        CCScale9Sprite *practiceRunsBG = cocos2d::extension::CCScale9Sprite::create(backgroundName, {0.0f, 0.0f, 80.0f, 80.0f});
		m_mainLayer->addChildAtPosition(practiceRunsBG, Anchor::Center, ccp(0, -70));
        practiceRunsBG->setContentSize({200, 75});
        practiceRunsBG->setColor({130, 64, 33});
        practiceRunsBG->setZOrder(1);
        practiceRunsBG->setID("practiceRunsBG"_spr);

        CCScale9Sprite *completionBG = cocos2d::extension::CCScale9Sprite::create(backgroundName, {0.0f, 0.0f, 80.0f, 80.0f});
        m_mainLayer->addChildAtPosition(completionBG, Anchor::Center, ccp(0, 15));
        completionBG->setContentSize({200, 75});
        completionBG->setColor({130, 64, 33});
		completionBG->setZOrder(1);
        completionBG->setID("completionBG"_spr);

        CCMenu *titleMenu = CCMenu::create();
        m_mainLayer->addChild(titleMenu);
        titleMenu->setLayout(RowLayout::create());
        titleMenu->setPosition(ccp(350.0f, 393.0f));

        CCLabelBMFont *titleLabel = CCLabelBMFont::create(std::string(level->m_levelName).c_str(), goldFontName);
        titleMenu->addChild(titleLabel);
        titleLabel->setScale((level->m_levelName.size() > 11) ? 0.4f : 0.7);
        
        titleLabel->setAnchorPoint(ccp(0, 0.5f));

        CCSprite *accuracySprite = CCSprite::createWithSpriteFrameName(accuracySpriteName);
        accuracySprite->setScale(0.5f);

        CCSprite *accuracySpriteSelected = CCSprite::createWithSpriteFrameName(accuracySpriteName);
        accuracySpriteSelected->setScale(0.5f);

        CCMenuItemSpriteExtra *accuracyBtn = CCMenuItemSpriteExtra::create(
            accuracySprite,
            accuracySpriteSelected,
            this, menu_selector(MyPopup::onPracticeInfo));

        titleMenu->addChild(accuracyBtn);
        accuracyBtn->setPosition(ccp(titleLabel->getPositionX() + titleLabel->getScaledContentWidth() + 15, titleLabel->getPositionY()));

        CCLabelBMFont *accuracyLabel = CCLabelBMFont::create("69", bigFontName);
        titleMenu->addChild(accuracyLabel);
        accuracyLabel->setScale(0.25f);
        accuracyLabel->setPosition(ccp(accuracyBtn->getPositionX(), accuracyBtn->getPositionY()));

       
        GJDifficultySprite* difficulty = new GJDifficultySprite(*difficultySprite);
        m_mainLayer->addChildAtPosition(difficulty, Anchor::TopRight, ccp(-200.0f, -40.0f));
        difficulty->setScale(0.9f);

        CCLabelBMFont *timeLabel = CCLabelBMFont::create(("Time Played: " + std::to_string(data.time_played)).c_str(), bigFontName);
        m_mainLayer->addChild(timeLabel);
        timeLabel->setScale(0.3f);
        timeLabel->setAnchorPoint(ccp(0, 0.5f));
        timeLabel->setPosition(ccp(67, 217));

        CCLabelBMFont* lastPlayedTimeLabel = CCLabelBMFont::create("Last Played: 23/06/2025", bigFontName);
        m_mainLayer->addChild(lastPlayedTimeLabel);
        lastPlayedTimeLabel->setScale(0.3f);
        lastPlayedTimeLabel->setAnchorPoint(ccp(0, 0.5f));
        lastPlayedTimeLabel->setPosition(ccp(67, 207));

        CCLabelBMFont* completedLabel = CCLabelBMFont::create("Complete date: 23/06/2025", bigFontName);
        m_mainLayer->addChild(completedLabel);
        completedLabel->setScale(0.3f);
        completedLabel->setAnchorPoint(ccp(0, 0.5f));
        completedLabel->setPosition(ccp(67, 197));

        CCMenu* statsMenu = CCMenu::create();
        CCMenu* practiceMenu = CCMenu::create();

		ColumnLayout* statsMenuLayout = ColumnLayout::create();
		statsMenuLayout->setCrossAxisLineAlignment(AxisAlignment::Start);
		statsMenuLayout->setAxisAlignment(AxisAlignment::End);
		statsMenuLayout->setAxisReverse(true);
		statsMenuLayout->setGap(10.f);

        RowLayout* practiceMenuLayout = RowLayout::create();
        statsMenuLayout->setCrossAxisLineAlignment(AxisAlignment::Start);
        statsMenuLayout->setAxisAlignment(AxisAlignment::End);
        statsMenuLayout->setAxisReverse(true);
        statsMenuLayout->setGap(5.f);


        ColumnLayout* practiceStatsLayout = ColumnLayout::create();
        practiceStatsLayout->setCrossAxisLineAlignment(AxisAlignment::Start);
        practiceStatsLayout->setAxisAlignment(AxisAlignment::Even);
        practiceStatsLayout->setAxisReverse(true);
        practiceStatsLayout->setGap(5.f);

		m_mainLayer->addChildAtPosition(statsMenu, Anchor::Center, ccp(-20, 10));
        m_mainLayer->addChildAtPosition(practiceMenu, Anchor::Center, ccp(-35, -70));
		
		statsMenu->setZOrder(2);
        statsMenu->setScale(0.35f);
        statsMenu->setContentSize(ccp(400, 220));
        statsMenu->setLayout(statsMenuLayout);

        practiceMenu->setZOrder(2);
        practiceMenu->setScale(0.35f);
        practiceMenu->setContentSize(ccp(550, 200));
        practiceMenu->setLayout(practiceStatsLayout);
		

        CCLabelBMFont *attemptsLabel = CCLabelBMFont::create(("Total Attempts: " + std::to_string(data.attempts)).c_str(), bigFontName);
		statsMenu->addChild(attemptsLabel);
        attemptsLabel->setAnchorPoint(ccp(0, 0.5f));

        const int normalAttempts = data.attempts - data.practice_stats.attempts;
        CCLabelBMFont *normalLabel = CCLabelBMFont::create(("Normal Attempts: " + std::to_string(normalAttempts)).c_str(), bigFontName);
		statsMenu->addChild(normalLabel);
        normalLabel->setAnchorPoint(ccp(0, 0.5f));

        CCLabelBMFont *practiceLabel = CCLabelBMFont::create(("Practice Attempts: " + std::to_string(data.practice_stats.attempts)).c_str(), bigFontName);
		statsMenu->addChild(practiceLabel);
        practiceLabel->setAnchorPoint(ccp(0, 0.5f));

        CCLabelBMFont* practiceRunsLabel = CCLabelBMFont::create(("Practice Runs: " + std::to_string(data.practice_stats.practice_count)).c_str(), bigFontName);
		practiceLabel->setAnchorPoint(ccp(0, 0.5f));
        statsMenu->addChild(practiceRunsLabel);

        CCLabelBMFont *jumpsLabel = CCLabelBMFont::create("Jumps: 100", bigFontName);
		statsMenu->addChild(jumpsLabel);
        jumpsLabel->setAnchorPoint(ccp(0, 0.5f));

        CCLabelBMFont* practiceTitle= CCLabelBMFont::create("Practice Runs", goldFontName);
		m_mainLayer->addChildAtPosition(practiceTitle, Anchor::Center, ccp(0, -30));
        practiceTitle->setScale(0.4f);
		practiceTitle->setZOrder(2);

        CCLabelBMFont *bestPracticeSubtitle = CCLabelBMFont::create("Best", goldFontName);
		practiceMenu->addChild(bestPracticeSubtitle);

        CCLabelBMFont *bestPracticeAttemptsLabel = CCLabelBMFont::create("1100 / 1h 23m / 23", bigFontName);
        bestPracticeAttemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        bestPracticeAttemptsLabel->setPosition(ccp(bestPracticeSubtitle->getPositionX(), bestPracticeSubtitle->getPositionY() - 12));
        practiceMenu->addChild(bestPracticeAttemptsLabel);

        CCLabelBMFont *firstPracticeSubtitle = CCLabelBMFont::create("First", goldFontName);
		practiceMenu->addChild(firstPracticeSubtitle);

        CCLabelBMFont *firstPracticeAttemptsLabel = CCLabelBMFont::create("1100 / 1h 23m / 23", bigFontName);
        firstPracticeAttemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        firstPracticeAttemptsLabel->setPosition(ccp(firstPracticeSubtitle->getPositionX(), firstPracticeSubtitle->getPositionY() - 12));
        practiceMenu->addChild(firstPracticeAttemptsLabel);

        CCLabelBMFont* lastPracticeSubtitle = CCLabelBMFont::create("Last", goldFontName);
        practiceMenu->addChild(lastPracticeSubtitle);


        CCLabelBMFont* lastPracticeAttemptsLabel = CCLabelBMFont::create("1100 / 1h 23m / 23", bigFontName);
        firstPracticeAttemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        firstPracticeAttemptsLabel->setPosition(ccp(lastPracticeSubtitle->getPositionX(), lastPracticeSubtitle->getPositionY() - 12));
        practiceMenu->addChild(lastPracticeAttemptsLabel);


        statsMenu->updateLayout();
        practiceMenu->updateLayout();

        CCMenu* optsMenu = CCMenu::create();
		optsMenu->setLayout(RowLayout::create());
		optsMenu->setZOrder(2);

        CCSprite *infoIcon = CCSprite::createWithSpriteFrameName(infoIconName);
        infoIcon->setScale(0.5f);

        CCMenuItemSpriteExtra *infoBtn = CCMenuItemSpriteExtra::create(
            infoIcon, 
            this, 
            menu_selector(MyPopup::onPracticeInfo));
		optsMenu->addChild(infoBtn);
        m_mainLayer->addChildAtPosition(optsMenu, Anchor::TopRight, ccp(255, -10));
        return true;
    }

    void onAccuracyInfo(CCObject *node)
    {
        FLAlertLayer::create("Accuracy", "text", "OK")->show();
    }

    void onPracticeInfo(CCObject* node)
    {
        FLAlertLayer::create("Accuracy", "text", "OK")->show();
    }

public:
    static MyPopup *create(GJGameLevel* const &level, GJDifficultySprite* difficultySprite, LevelStats const &data)
    {
        auto ret = new MyPopup();
        if (ret->initAnchored(240.f, 260.f, level, difficultySprite, data))
        {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }
};
