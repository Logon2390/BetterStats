#include "../managers/StatsManager.hpp"

using namespace geode::prelude;

class DeathsDistributionAlert : public FLAlertLayer {
protected:
    bool init() {
        if (!FLAlertLayer::init(
            nullptr,
            "Deaths Distribution",
            "\n\n\n\n\n\n\n\n\n\n",
            "OK",
            nullptr,
            400.f,
            true,
            0,
            1
        )) {
            return false;
        }
        const auto& arr = StatsManager::getLevelData().deathsPerPercent;

        CCLabelBMFont* bestPracticeSubtitle = CCLabelBMFont::create(("Most Deadly Percent: " + std::to_string(StatsManager::getMostDeadlyPercent())).c_str(), "chatFont.fnt");
        CCNode* mainMenu = CCNode::create();
        mainMenu->setContentSize({ 360.f, 220.f });
		mainMenu->setAnchorPoint({ 0.5f, 0.5f });
        mainMenu->setZOrder(2);
        mainMenu->setPosition({
            m_mainLayer->getContentSize().width / 2,
           m_mainLayer->getContentSize().height / 2
            });

        mainMenu->setLayout(RowLayout::create()
            ->setGap(35.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setCrossAxisLineAlignment(AxisAlignment::Center)
        );

        const int columns = 5;
        const int total = 100;
        const int perColumn = total / columns;

        for (int col = 0; col < columns; col++) {

            CCNode* columnMenu = CCNode::create();
			columnMenu->setAnchorPoint({ 0.5f, 0.5f });
			columnMenu->setContentSize({ 60.f, 300.f });
            columnMenu->setLayout(ColumnLayout::create()
                ->setGap(4.f)
                ->setAxisAlignment(AxisAlignment::Start)
                ->setCrossAxisLineAlignment(AxisAlignment::Start)
                ->setAxisReverse(true)
            );

            int start = col * perColumn;
            int end = start + perColumn;

            for (int i = start; i < end; i++) {

                int deaths = arr[i];

                std::string text =
                    std::to_string(i) + "%: " +
                    std::to_string(deaths);

                auto label = CCLabelBMFont::create(text.c_str(), "ChatFont.fnt");
                label->setScale(0.35f);
                label->setAnchorPoint({ 0.f, 0.5f });

                columnMenu->addChild(label);
            }
            columnMenu->updateLayout();
            mainMenu->addChild(columnMenu);
        }
        mainMenu->updateLayout();

        auto layer = m_mainLayer->getChildByID("scroll-layer");
        auto textArea = layer->getChildByIDRecursive("content-text-area");
        textArea->setPositionY(140.f);
        textArea->addChildAtPosition(bestPracticeSubtitle, Anchor::Top, ccp(0, 85));
        textArea->addChildAtPosition(mainMenu, Anchor::Center, ccp(0, 0));

        return true;
    }

public:
    static DeathsDistributionAlert* create() {
        auto alert = new DeathsDistributionAlert();
        if (alert && alert->init()) {
            alert->autorelease();
            return alert;
        }

        delete alert;
        return nullptr;
    }
};