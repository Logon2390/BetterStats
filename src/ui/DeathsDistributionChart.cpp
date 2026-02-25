#include "../managers/StatsManager.hpp"
#include "DeathsDistributionAlert.cpp"

using namespace geode::prelude;

class DeathsDistributionChart : public CCScale9Sprite {
protected:

    bool init() override {
        if (!this->initWithFile("square02b_001.png", { 0.f, 0.f, 80.f, 80.f })) {
            return false;
        }

        this->setAnchorPoint({ 0.5f, 0.5f });
        this->setContentSize({ 180.f, 160.f });
        this->setColor({ 130, 64, 33 });
        this->setZOrder(1);
        this->setID("DeathsChartsBG"_spr);

        auto distribution = StatsManager::getDeathsDistributionByRange();
        auto normalizedDistribution = StatsManager::getNormalizedDeathsDistribution();

        CCSprite* infoIcon = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        infoIcon->setScale(0.5f);

        CCSprite* separator = CCSprite::createWithSpriteFrameName("floorLine_001.png");
        separator->setScaleX(0.4f);

        CCLabelBMFont* title = CCLabelBMFont::create("Deaths Distribution", "goldFont.fnt");
		title->setScale(0.35f);
		title->setAnchorPoint({ 0.f, 0.5f });

        CCMenu* menu = CCMenu::create();
        menu->setLayout(RowLayout::create()
            ->setAxisAlignment(AxisAlignment::Between));
        menu->setContentWidth(170.f);
        menu->setZOrder(2);

        menu->addChild(
            CCMenuItemSpriteExtra::create(title, this,
            menu_selector(DeathsDistributionChart::onChartInfo)));

        menu->addChild(
            CCMenuItemSpriteExtra::create(infoIcon, this,
                menu_selector(DeathsDistributionChart::onDeathsPerPercent)));


        CCNode* mainContainer = CCNode::create();
        mainContainer->setLayout(
            RowLayout::create()
            ->setGap(0.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setCrossAxisLineAlignment(AxisAlignment::Center)
            ->setCrossAxisOverflow(false)
            ->setAutoScale(false)
        );

        mainContainer->setContentSize({ 180.f, 160.f });
        mainContainer->setAnchorPoint({ 0.5f, 0.5f });
        mainContainer->updateLayout();
		menu->updateLayout();

        this->addChildAtPosition(mainContainer, Anchor::Center);
		this->addChildAtPosition(separator, Anchor::Bottom, ccp(0.f, 17.f));
		this->addChildAtPosition(menu, Anchor::Top, ccp(0.f, -10.f));

		int rangeStart = 0;
		float DeathLabelY = 0.f;

        for (int i = 0; i < 10; i++) {
            rangeStart = i * 10;
            DeathLabelY = 25.f;

            CCNode* bottomContainer = CCNode::create();
            bottomContainer->setContentSize({ (180/10), 160.f });
            bottomContainer->setAnchorPoint({ 0.5f, 0.5f });
			bottomContainer->setScale(1.f);
            mainContainer->addChildAtPosition(bottomContainer, Anchor::Center);

            bottomContainer->updateLayout();

            CCLabelBMFont* rangeLabel = CCLabelBMFont::create((
                std::to_string(rangeStart)).c_str(),
                "bigFont.fnt"
            );

            rangeLabel->setScale(0.3f);
            rangeLabel->setPosition(10.f, 10.f);
    
            CCScale9Sprite* bar = CCScale9Sprite::create("square.png");

            if (normalizedDistribution[i] != 0.f) {
                bar->setContentSize({ 30.f, 100.f });
                bar->setColor({ 0, 255, 0 });
                bar->setScaleX(0.3f);
                bar->setScaleY(normalizedDistribution[i]);
                bar->setAnchorPoint({ 0.5f, 0.f });
                bar->setPosition(10.f, 20.f);

				DeathLabelY = bar->getPositionY() + bar->getScaledContentHeight() + 5.f;
			}

            CCLabelBMFont* deathsLabel = CCLabelBMFont::create((
                std::to_string(distribution[i])).c_str(),
                "bigFont.fnt"
            );
            deathsLabel->setScale(0.25f);
			deathsLabel->setPosition(10.f, DeathLabelY);

            bottomContainer->addChild(rangeLabel);
            if (normalizedDistribution[i] != 0.f) {
                bottomContainer->addChild(bar);
            }
			bottomContainer->addChild(deathsLabel);
            bottomContainer->updateLayout();
        }

        mainContainer->updateLayout();
        return true;
    }

    void onChartInfo(CCObject* node)
    {
        std::string message =
            "The chart displays the <cy>distribution of deaths</c> by percentage ranges.\n\n"
            "Each <cb>bar</c> represents a <cj>10% range</c>.\n"
            "The number <cy>below</c> the bar indicates the <cb>start of the range</c> "
            "(0, 10, 20, etc.).\n"
            "The number <cy>above</c> the bar shows the <cj>total deaths</c> within that range.";

        FLAlertLayer::create("Chart Info", message, "OK")->show();
    }

    void onDeathsPerPercent(CCObject* node) {
        DeathsDistributionAlert::create()->show();
    }

public:

    static DeathsDistributionChart* create() {
        auto chart = new DeathsDistributionChart();
        if (chart && chart->init()) {
            chart->autorelease();
            return chart;
        }

        delete chart;
        return nullptr;
    }
};