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
        CCMenu* mainMenu = CCMenu::create();
        mainMenu->setContentSize({ 360.f, 220.f });
        mainMenu->setZOrder(2);
        mainMenu->setPosition({
            m_mainLayer->getContentSize().width / 2,
           m_mainLayer->getContentSize().height / 2
            });

        RowLayout* rowLayout = RowLayout::create();
        rowLayout->setGap(35.f);
        rowLayout->setAxisAlignment(AxisAlignment::Center);
        rowLayout->setCrossAxisLineAlignment(AxisAlignment::Center);

        mainMenu->setLayout(rowLayout);

        const int columns = 5;
        const int total = 100;
        const int perColumn = total / columns;

        for (int col = 0; col < columns; col++) {

            CCMenu* columnMenu = CCMenu::create();
            ColumnLayout* columnLayout = ColumnLayout::create();
            columnLayout->setGap(4.f);
            columnLayout->setAxisAlignment(AxisAlignment::Start);
            columnLayout->setCrossAxisLineAlignment(AxisAlignment::Start);
            columnLayout->setAxisReverse(true);

            columnMenu->setLayout(columnLayout);

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