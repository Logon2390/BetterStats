#include <Geode/Geode.hpp>
#include <Geode/binding/GJDifficultySprite.hpp>
#include "../managers/StatsManager.hpp"
#include "../utils/Formatters.hpp"

using namespace geode::prelude;

class StatsPopup : public geode::Popup
{
protected:
    bool init(GJGameLevel* const& level, GJDifficultySprite* difficultySprite, LevelStats const& data)
    {
        if (!Popup::init(440.f, 260.f)) return false;

        const char* cornerSpriteName = "rewardCorner_001.png";
        const char* accuracySpriteName = "pathIcon_09_001.png";
        const char* infoIconName = "GJ_infoIcon_001.png";
        const char* backgroundName = "square02b_001.png";
        const char* bigFontName = "bigFont.fnt";
        const char* goldFontName = "goldFont.fnt";

        CCSprite* BottomLeftSprite = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChildAtPosition(BottomLeftSprite, Anchor::BottomLeft, ccp(25, 25));

        CCSprite* cornerSprite2 = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChildAtPosition(cornerSprite2, Anchor::TopLeft, ccp(25, -25));
        cornerSprite2->setRotation(90.f);

        CCSprite* cornerSprite3 = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChildAtPosition(cornerSprite3, Anchor::BottomRight, ccp(-25, 25));
        cornerSprite3->setRotation(270.f);

        CCSprite* cornerSprite4 = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChildAtPosition(cornerSprite4, Anchor::TopRight, ccp(-25, -25));
        cornerSprite4->setRotation(180.f);

        CCScale9Sprite* practiceRunsBG = cocos2d::extension::CCScale9Sprite::create(backgroundName, { 0.0f, 0.0f, 80.0f, 80.0f });
        m_mainLayer->addChildAtPosition(practiceRunsBG, Anchor::Center, ccp(-95, -70));
        practiceRunsBG->setContentSize({ 200, 75 });
        practiceRunsBG->setColor({ 130, 64, 33 });
        practiceRunsBG->setZOrder(1);
        practiceRunsBG->setID("practiceRunsBG"_spr);

        CCScale9Sprite* completionBG = cocos2d::extension::CCScale9Sprite::create(backgroundName, { 0.0f, 0.0f, 80.0f, 80.0f });
        m_mainLayer->addChildAtPosition(completionBG, Anchor::Center, ccp(-95, 15));
        completionBG->setContentSize({ 200, 75 });
        completionBG->setColor({ 130, 64, 33 });
        completionBG->setZOrder(1);
        completionBG->setID("completionBG"_spr);

        CCMenu* titleMenu = CCMenu::create();
        m_mainLayer->addChild(titleMenu);
        titleMenu->setLayout(RowLayout::create());
        titleMenu->setPosition(ccp(350.0f, 393.0f));

        CCLabelBMFont* titleLabel = CCLabelBMFont::create(std::string(level->m_levelName).c_str(), goldFontName);
        titleMenu->addChild(titleLabel);
        titleLabel->setScale(0.7);

        titleLabel->setAnchorPoint(ccp(0, 0.5f));

        GJDifficultySprite* difficulty = new GJDifficultySprite(*difficultySprite);
        m_mainLayer->addChildAtPosition(difficulty, Anchor::TopLeft, ccp(40.0f, -45.0f));
        difficulty->setScale(0.9f);

        CCLabelBMFont* timeLabel = CCLabelBMFont::create(("Time Played: " + StatsManager::getTimePlayed(data)).c_str(), bigFontName);
        m_mainLayer->addChild(timeLabel);
        timeLabel->setScale(0.3f);
        timeLabel->setAnchorPoint(ccp(0, 0.5f));
        timeLabel->setPosition(ccp(67, 217));

        CCLabelBMFont* practiceTimeLabel = CCLabelBMFont::create((" • "  + StatsManager::getPracticeTimePlayed(data)).c_str(), bigFontName);
        m_mainLayer->addChild(practiceTimeLabel);
        practiceTimeLabel->setScale(0.3f);
        practiceTimeLabel->setAnchorPoint(ccp(0, 0.5f));
        practiceTimeLabel->setColor({ 124, 255, 255 });
        practiceTimeLabel->setPosition(ccp((timeLabel->getPositionX() + timeLabel->getScaledContentWidth()), 217));

        CCLabelBMFont* lastPlayedTimeLabel = CCLabelBMFont::create(("Last Played: " + StatsManager::getLastPlayed(data)).c_str(), bigFontName);

        m_mainLayer->addChild(lastPlayedTimeLabel);
        lastPlayedTimeLabel->setScale(0.3f);
        lastPlayedTimeLabel->setAnchorPoint(ccp(0, 0.5f));
        lastPlayedTimeLabel->setPosition(ccp(67, 207));

        CCLabelBMFont* completedLabel = CCLabelBMFont::create(("Complete date: " + StatsManager::getCompleteDate(data)).c_str(), bigFontName);
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

        m_mainLayer->addChildAtPosition(statsMenu, Anchor::Center, ccp(-190, 10));
        m_mainLayer->addChildAtPosition(practiceMenu, Anchor::Center, ccp(-190, -70));

        statsMenu->setZOrder(2);
        statsMenu->setScale(0.35f);
        statsMenu->setContentSize(ccp(400, 220));
        statsMenu->setAnchorPoint(ccp(0, 0.5f));
        statsMenu->setLayout(statsMenuLayout);

        practiceMenu->setZOrder(2);
        practiceMenu->setScale(0.35f);
        practiceMenu->setContentSize(ccp(550, 200));
		practiceMenu->setAnchorPoint(ccp(0, 0.5f));
        practiceMenu->setLayout(practiceStatsLayout);


        CCLabelBMFont* attemptsLabel = CCLabelBMFont::create(("Total Attempts: " + std::to_string(level->m_attempts.value())).c_str(), bigFontName);
        statsMenu->addChild(attemptsLabel);
        attemptsLabel->setAnchorPoint(ccp(0, 0.5f));

        CCLabelBMFont* normalLabel = CCLabelBMFont::create(("Normal Attempts: " + std::to_string(StatsManager::getNormalAttempts(level, data))).c_str(), bigFontName);
        statsMenu->addChild(normalLabel);
        normalLabel->setAnchorPoint(ccp(0, 0.5f));

        CCLabelBMFont* practiceLabel = CCLabelBMFont::create(("Practice Attempts: " + std::to_string(StatsManager::getPracticeAttempts(data))).c_str(), bigFontName);
        statsMenu->addChild(practiceLabel);
        practiceLabel->setAnchorPoint(ccp(0, 0.5f));

        CCLabelBMFont* practiceRunsLabel = CCLabelBMFont::create(("Practice Runs: " + std::to_string(StatsManager::getPracticeRunsCount(data))).c_str(), bigFontName);
        practiceLabel->setAnchorPoint(ccp(0, 0.5f));
        statsMenu->addChild(practiceRunsLabel);

        CCLabelBMFont* jumpsLabel = CCLabelBMFont::create(("Jumps: " + std::to_string(level->m_jumps.value())).c_str(), bigFontName);
        statsMenu->addChild(jumpsLabel);
        jumpsLabel->setAnchorPoint(ccp(0, 0.5f));

        CCLabelBMFont* practiceTitle = CCLabelBMFont::create("Practice Runs", goldFontName);
        m_mainLayer->addChildAtPosition(practiceTitle, Anchor::Center, ccp(-100, -30));
        practiceTitle->setScale(0.4f);
        practiceTitle->setZOrder(2);

        CCLabelBMFont* bestPracticeSubtitle = CCLabelBMFont::create("Best", goldFontName);  
        bestPracticeSubtitle->setAnchorPoint(ccp(0, 0.5f));
        practiceMenu->addChild(bestPracticeSubtitle);

		PracticeRunStats bestPracticeRun = StatsManager::getBestPractice(data);
        CCLabelBMFont* bestPracticeAttemptsLabel = CCLabelBMFont::create((
            std::to_string(bestPracticeRun.attempts) + " / " +
            formatDuration(bestPracticeRun.time_played) + " / " +
            std::to_string(bestPracticeRun.checkpoints)).c_str(), bigFontName);

        bestPracticeAttemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        bestPracticeAttemptsLabel->setPosition(ccp(bestPracticeSubtitle->getPositionX(), bestPracticeSubtitle->getPositionY() - 12));
        practiceMenu->addChild(bestPracticeAttemptsLabel);

        CCLabelBMFont* firstPracticeSubtitle = CCLabelBMFont::create("First", goldFontName);
		firstPracticeSubtitle->setAnchorPoint(ccp(0, 0.5f));
        practiceMenu->addChild(firstPracticeSubtitle);

		PracticeRunStats firstPracticeRun = StatsManager::getFirstPractice(data);
        CCLabelBMFont* firstPracticeAttemptsLabel = CCLabelBMFont::create((
            std::to_string(firstPracticeRun.attempts) + " / " +
            formatDuration(firstPracticeRun.time_played) + " / " +
            std::to_string(firstPracticeRun.checkpoints)).c_str(), bigFontName);

        firstPracticeAttemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        firstPracticeAttemptsLabel->setPosition(ccp(firstPracticeSubtitle->getPositionX(), firstPracticeSubtitle->getPositionY() - 12));
        practiceMenu->addChild(firstPracticeAttemptsLabel);

        CCLabelBMFont* lastPracticeSubtitle = CCLabelBMFont::create("Last", goldFontName);
		lastPracticeSubtitle->setAnchorPoint(ccp(0, 0.5f));
        practiceMenu->addChild(lastPracticeSubtitle);

        PracticeRunStats lastPracticeRun = StatsManager::getLastPractice(data);
        CCLabelBMFont* lastPracticeAttemptsLabel = CCLabelBMFont::create((
            std::to_string(lastPracticeRun.attempts) + " / " +
            formatDuration(lastPracticeRun.time_played) + " / " +
            std::to_string(lastPracticeRun.checkpoints)).c_str(), bigFontName);

        lastPracticeAttemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        lastPracticeAttemptsLabel->setPosition(ccp(lastPracticeSubtitle->getPositionX(), lastPracticeSubtitle->getPositionY() - 12));
        practiceMenu->addChild(lastPracticeAttemptsLabel);

        statsMenu->updateLayout();
        practiceMenu->updateLayout();

        CCMenu* optsMenu = CCMenu::create();
        optsMenu->setLayout(RowLayout::create());
        optsMenu->setZOrder(2);

        CCSprite* infoIcon = CCSprite::createWithSpriteFrameName(infoIconName);
        infoIcon->setScale(0.5f);

        CCMenuItemSpriteExtra* infoBtn = CCMenuItemSpriteExtra::create(
            infoIcon,
            this,
            menu_selector(StatsPopup::onPracticeInfo));
        optsMenu->addChild(infoBtn);
        m_mainLayer->addChildAtPosition(optsMenu, Anchor::TopRight, ccp(60, -10));
        return true;
    }

    void onPracticeInfo(CCObject* node)
    {
        std::string message =
            "The practice run information is shown in the following format:\n"
            "<cy>Attempts</c> / <cb>Time</c> / <cj>Checkpoints</c>";

        FLAlertLayer::create("Info", message, "OK")->show();
    }

public:
    static StatsPopup* create(GJGameLevel* const& level, GJDifficultySprite* difficultySprite, LevelStats const& data)
    {
        auto popup = new StatsPopup();
        if (popup->init(level, difficultySprite, data))
        {
            popup->autorelease();
            return popup;
        }

        delete popup;
        return nullptr;
    }
};
