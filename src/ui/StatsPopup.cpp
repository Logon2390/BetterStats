#include <Geode/Geode.hpp>
#include <Geode/binding/GJDifficultySprite.hpp>
#include "../managers/StatsManager.hpp"
#include "../utils/Formatters.hpp"
#include <string>
#include "DeathsDistributionChart.cpp"
#include "../utils/LevelUtils.hpp"

using namespace geode::prelude;

class StatsPopup : public geode::Popup
{
protected:
    bool init(GJGameLevel* const& level, int difficulty)
    {
        if (!level) return false;

		bool isPlatformer = level->isPlatformer();
		float xOffset = isPlatformer ? 0.f : -95.f;
		float titleScale = (isPlatformer && std::string(level->m_levelName).length() > 12) ? 0.5f : 0.7f;
		float width = isPlatformer ? 240.f : 440.f;
		float height = 260.f;

        if (!Popup::init(width, height)) return false;

        const char* cornerSpriteName = "rewardCorner_001.png";
        const char* accuracySpriteName = "pathIcon_09_001.png";
        const char* infoIconName = "GJ_infoIcon_001.png";
        const char* backgroundName = "square02b_001.png";
        const char* bigFontName = "bigFont.fnt";
        const char* goldFontName = "goldFont.fnt";

        CCSprite* bottomLeftSprite = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChildAtPosition(bottomLeftSprite, Anchor::BottomLeft);
        bottomLeftSprite->setAnchorPoint(ccp(0.f, 0.f));

        CCSprite* topLeftSprite = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChildAtPosition(topLeftSprite, Anchor::TopLeft);
		topLeftSprite->setAnchorPoint(ccp(0.f, 1.f));
		topLeftSprite->setFlipY(true);

        CCSprite* bottomRightSprite = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChildAtPosition(bottomRightSprite, Anchor::BottomRight);
		bottomRightSprite->setFlipX(true);
		bottomRightSprite->setAnchorPoint(ccp(1.f, 0.f));

        CCSprite* topRightSprite = CCSprite::createWithSpriteFrameName(cornerSpriteName);
        m_mainLayer->addChildAtPosition(topRightSprite, Anchor::TopRight);
		topRightSprite->setAnchorPoint(ccp(1.f, 1.f));
		topRightSprite->setFlipX(true);
		topRightSprite->setFlipY(true);

        CCScale9Sprite* practiceRunsBG = cocos2d::extension::CCScale9Sprite::create(backgroundName, { 0.0f, 0.0f, 80.0f, 80.0f });
        m_mainLayer->addChildAtPosition(practiceRunsBG, Anchor::Center, ccp(xOffset, -70.f));
        practiceRunsBG->setContentSize({ 200.f, 75.f });
        practiceRunsBG->setColor({ 130, 64, 33 });
        practiceRunsBG->setZOrder(1);
        practiceRunsBG->setID("practiceRunsBG"_spr);

        CCScale9Sprite* completionBG = cocos2d::extension::CCScale9Sprite::create(backgroundName, { 0.0f, 0.0f, 80.0f, 80.0f });
        m_mainLayer->addChildAtPosition(completionBG, Anchor::Center, ccp(xOffset, 15.f));
        completionBG->setContentSize({ 200.f, 75.f });
        completionBG->setColor({ 130, 64, 33 });
        completionBG->setZOrder(1);
        completionBG->setID("completionBG"_spr);

        if (!isPlatformer) {
            CCScale9Sprite* chart = DeathsDistributionChart::create();
            m_mainLayer->addChildAtPosition(chart, Anchor::Center, ccp(105.0f, -27.5f));
        }

        CCLabelBMFont* titleLabel = CCLabelBMFont::create(std::string(level->m_levelName).c_str(), goldFontName);
		m_mainLayer->addChild(titleLabel);
        titleLabel->setPosition(ccp(67.0f, 233.0f));
		titleLabel->setScale(titleScale);
        titleLabel->setAnchorPoint(ccp(0.f, 0.5f));

		auto difficultSprite = GJDifficultySprite::create(difficulty, GJDifficultyName::Short);
        difficultSprite->updateFeatureStateFromLevel(level);
        m_mainLayer->addChildAtPosition(difficultSprite, Anchor::TopLeft, ccp(40.0f, -45.0f));
        difficultSprite->setScale(0.9f);

        CCLabelBMFont* timeLabel = CCLabelBMFont::create(("Time Played: " + StatsManager::getTimePlayed()).c_str(), bigFontName);
        m_mainLayer->addChild(timeLabel);
        timeLabel->setScale(0.3f);
        timeLabel->setAnchorPoint(ccp(0.f, 0.5f));
        timeLabel->setPosition(ccp(67.f, 217.f));

        CCLabelBMFont* practiceTimeLabel = CCLabelBMFont::create((" • "  + StatsManager::getPracticeTimePlayed()).c_str(), bigFontName);
        m_mainLayer->addChild(practiceTimeLabel);
        practiceTimeLabel->setScale(0.3f);
        practiceTimeLabel->setAnchorPoint(ccp(0.f, 0.5f));
        practiceTimeLabel->setColor({ 124, 255, 255 });
        practiceTimeLabel->setPosition(ccp((timeLabel->getPositionX() + timeLabel->getScaledContentWidth()), 217));

        CCLabelBMFont* lastPlayedTimeLabel = CCLabelBMFont::create(("Last Played: " + 
            StatsManager::getLastPlayed(isLevelComplete(level))).c_str(), bigFontName);

        m_mainLayer->addChild(lastPlayedTimeLabel);
        lastPlayedTimeLabel->setScale(0.3f);
        lastPlayedTimeLabel->setAnchorPoint(ccp(0.f, 0.5f));
        lastPlayedTimeLabel->setPosition(ccp(67.f, 207.f));

        CCLabelBMFont* completedLabel = CCLabelBMFont::create(("Complete date: " + 
            StatsManager::getCompleteDate(isLevelComplete(level))).c_str(), bigFontName);
        m_mainLayer->addChild(completedLabel);
        completedLabel->setScale(0.3f);
        completedLabel->setAnchorPoint(ccp(0.f, 0.5f));
        completedLabel->setPosition(ccp(67.f, 197.f));

        CCNode* statsMenu = CCNode::create();
        CCNode* practiceMenu = CCNode::create();

        completionBG->addChildAtPosition(statsMenu, Anchor::Left, ccp(10.f, 0.f));
        practiceRunsBG->addChildAtPosition(practiceMenu, Anchor::Left, ccp(10.f, 0.f));

        statsMenu->setZOrder(2);
        statsMenu->setScale(0.35f);
        statsMenu->setContentSize(ccp(400.f, 220.f));
        statsMenu->setAnchorPoint(ccp(0.f, 0.5f));
        statsMenu->setLayout(ColumnLayout::create()
            ->setCrossAxisLineAlignment(AxisAlignment::Start)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAxisReverse(true)
            ->setGap(5.f));

        practiceMenu->setZOrder(2);
        practiceMenu->setScale(0.35f);
        practiceMenu->setContentSize(ccp(550.f, 200.f));
		practiceMenu->setAnchorPoint(ccp(0.f, 0.5f));
        practiceMenu->setLayout(ColumnLayout::create()
            ->setCrossAxisLineAlignment(AxisAlignment::Start)
            ->setAxisAlignment(AxisAlignment::End)
            ->setAxisReverse(true)
            ->setGap(5.f));


        CCLabelBMFont* attemptsLabel = CCLabelBMFont::create(("Total Attempts: " + 
            std::to_string(level->m_attempts.value())).c_str(), bigFontName);

        statsMenu->addChild(attemptsLabel);
        attemptsLabel->setAnchorPoint(ccp(0.f, 0.5f));

        CCLabelBMFont* normalLabel = CCLabelBMFont::create(("Normal Attempts: " + 
            std::to_string(StatsManager::getNormalAttempts(level->m_attempts))).c_str(), bigFontName);

        statsMenu->addChild(normalLabel);
        normalLabel->setAnchorPoint(ccp(0.f, 0.5f));

        CCLabelBMFont* practiceLabel = CCLabelBMFont::create(("Practice Attempts: " +
            std::to_string(StatsManager::getPracticeAttempts())).c_str(), bigFontName);

        statsMenu->addChild(practiceLabel);
        practiceLabel->setAnchorPoint(ccp(0.f, 0.5f));

        CCLabelBMFont* practiceRunsLabel = CCLabelBMFont::create(("Practice Runs: " + 
            std::to_string(StatsManager::getPracticeRunsCount())).c_str(), bigFontName);

        practiceLabel->setAnchorPoint(ccp(0.f, 0.5f));
        statsMenu->addChild(practiceRunsLabel);

        CCLabelBMFont* jumpsLabel = CCLabelBMFont::create(("Jumps: " + 
            std::to_string(level->m_jumps.value())).c_str(), bigFontName);

        statsMenu->addChild(jumpsLabel);
        jumpsLabel->setAnchorPoint(ccp(0.f, 0.5f));

        CCLabelBMFont* practiceTitle = CCLabelBMFont::create("Practice Runs", goldFontName);
        m_mainLayer->addChildAtPosition(practiceTitle, Anchor::Center, ccp(-100.f, -30.f));
        practiceTitle->setScale(0.4f);
        practiceTitle->setZOrder(2);

        CCLabelBMFont* bestPracticeSubtitle = CCLabelBMFont::create("Best", goldFontName);  
        bestPracticeSubtitle->setAnchorPoint(ccp(0.f, 0.5f));
        practiceMenu->addChild(bestPracticeSubtitle);

		PracticeRunStats bestPracticeRun = StatsManager::getBestPractice();
        CCLabelBMFont* bestPracticeAttemptsLabel = CCLabelBMFont::create((
            std::to_string(bestPracticeRun.attempts) + " / " +
            formatDuration(bestPracticeRun.time_played) + " / " +
            std::to_string(bestPracticeRun.checkpoints)).c_str(), bigFontName);

        bestPracticeAttemptsLabel->setAnchorPoint(ccp(0.f, 0.5f));
        bestPracticeAttemptsLabel->setPosition(ccp(bestPracticeSubtitle->getPositionX(), bestPracticeSubtitle->getPositionY() - 12));
        practiceMenu->addChild(bestPracticeAttemptsLabel);

        CCLabelBMFont* firstPracticeSubtitle = CCLabelBMFont::create("First", goldFontName);
		firstPracticeSubtitle->setAnchorPoint(ccp(0.f, 0.5f));
        practiceMenu->addChild(firstPracticeSubtitle);

		PracticeRunStats firstPracticeRun = StatsManager::getFirstPractice();
        CCLabelBMFont* firstPracticeAttemptsLabel = CCLabelBMFont::create((
            std::to_string(firstPracticeRun.attempts) + " / " +
            formatDuration(firstPracticeRun.time_played) + " / " +
            std::to_string(firstPracticeRun.checkpoints)).c_str(), bigFontName);

        firstPracticeAttemptsLabel->setAnchorPoint(ccp(0.f, 0.5f));
        firstPracticeAttemptsLabel->setPosition(ccp(firstPracticeSubtitle->getPositionX(), firstPracticeSubtitle->getPositionY() - 12));
        practiceMenu->addChild(firstPracticeAttemptsLabel);

        CCLabelBMFont* lastPracticeSubtitle = CCLabelBMFont::create("Last", goldFontName);
		lastPracticeSubtitle->setAnchorPoint(ccp(0.f, 0.5f));
        practiceMenu->addChild(lastPracticeSubtitle);

        PracticeRunStats lastPracticeRun = StatsManager::getLastPractice();
        CCLabelBMFont* lastPracticeAttemptsLabel = CCLabelBMFont::create((
            std::to_string(lastPracticeRun.attempts) + " / " +
            formatDuration(lastPracticeRun.time_played) + " / " +
            std::to_string(lastPracticeRun.checkpoints)).c_str(), bigFontName);

        lastPracticeAttemptsLabel->setAnchorPoint(ccp(0.f, 0.5f));
        lastPracticeAttemptsLabel->setPosition(ccp(lastPracticeSubtitle->getPositionX(), lastPracticeSubtitle->getPositionY() - 12));
        practiceMenu->addChild(lastPracticeAttemptsLabel);

        statsMenu->updateLayout();
        practiceMenu->updateLayout();

        CCMenu* optsMenu = CCMenu::create();
        optsMenu->setLayout(RowLayout::create());
        optsMenu->setZOrder(2);
		optsMenu->setAnchorPoint(ccp(0.f, 0.f));

        CCSprite* infoIcon = CCSprite::createWithSpriteFrameName(infoIconName);
        infoIcon->setScale(0.5f);

        CCMenuItemSpriteExtra* infoBtn = CCMenuItemSpriteExtra::create(
            infoIcon,
            this,
            menu_selector(StatsPopup::onPracticeInfo));
        optsMenu->addChild(infoBtn);
        practiceRunsBG->addChildAtPosition(optsMenu, Anchor::TopRight, ccp(-10.f, -10.f));
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
    static StatsPopup* create(GJGameLevel* const& level, int difficulty)
    {
        auto popup = new StatsPopup();
        if (popup->init(level, difficulty))
        {
            popup->autorelease();
            return popup;
        }

        delete popup;
        return nullptr;
    }
};
