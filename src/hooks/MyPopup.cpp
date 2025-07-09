#include <Geode/Geode.hpp>
using namespace geode::prelude;

class MyPopup : public geode::Popup<std::string const &, std::string const &>
{
protected:
    bool setup(std::string const &title, std::string const &value)
    {
        // @geode-ignore(unknown-resource)
        CCSprite *cornerSprite = CCSprite::createWithSpriteFrameName("rewardCorner_001.png");
        cornerSprite->setScale(1.0f);
        cornerSprite->setPosition(ccp(25, 25));
        m_mainLayer->addChild(cornerSprite);

        // @geode-ignore(unknown-resource)
        CCSprite *cornerSprite2 = CCSprite::createWithSpriteFrameName("rewardCorner_001.png");
        cornerSprite2->setScale(1.0f);
        cornerSprite2->setPosition(ccp(25, 235));
        cornerSprite2->setRotation(90.f);
        m_mainLayer->addChild(cornerSprite2);

        // @geode-ignore(unknown-resource)
        CCSprite *cornerSprite3 = CCSprite::createWithSpriteFrameName("rewardCorner_001.png");
        cornerSprite3->setScale(1.0f);
        cornerSprite3->setPosition(ccp(415, 25));
        cornerSprite3->setRotation(270.f);
        m_mainLayer->addChild(cornerSprite3);

        // @geode-ignore(unknown-resource)
        CCSprite *cornerSprite4 = CCSprite::createWithSpriteFrameName("rewardCorner_001.png");
        cornerSprite4->setScale(1.0f);
        cornerSprite4->setPosition(ccp(415, 235));
        cornerSprite4->setRotation(180.f);
        m_mainLayer->addChild(cornerSprite4);

        // @geode-ignore(unknown-resource)
        CCLabelBMFont *titleLabel = CCLabelBMFont::create(title.c_str(), "goldFont.fnt");
        titleLabel->setScale(0.7f);
        titleLabel->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(titleLabel, Anchor::Top, ccp(-150.0f, -25.5f));

        // @geode-ignore(unknown-resource)
        CCSprite *ratingSprite = CCSprite::createWithSpriteFrameName("GJ_featuredCoin_001.png");
        ratingSprite->setScale(0.9f);
        m_mainLayer->addChildAtPosition(ratingSprite, Anchor::Top, ccp(-175.0f, -40.0f));

        // @geode-ignore(unknown-resource)
        CCSprite *difficultySprite = CCSprite::createWithSpriteFrameName("difficulty_06_btn_001.png");
        difficultySprite->setScale(0.9f);
        m_mainLayer->addChildAtPosition(difficultySprite, Anchor::Top, ccp(-175.0f, -40.0f));

        // @geode-ignore(unknown-resource)
        CCSprite *playIcon = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");
        playIcon->setScale(0.18f);
        playIcon->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(playIcon, Anchor::Top, ccp(-192, -80));

        // @geode-ignore(unknown-resource)
        CCLabelBMFont *statsSubtitle = CCLabelBMFont::create("Stats", "goldFont.fnt");
        statsSubtitle->setScale(0.6f);
        statsSubtitle->setAnchorPoint(ccp(0, 0.5f));
        statsSubtitle->setPosition(ccp(playIcon->getPositionX() + 5, playIcon->getPositionY()));
        m_mainLayer->addChild(statsSubtitle);

        // @geode-ignore(unknown-resource)
        CCLabelBMFont *attemptsLabel = CCLabelBMFont::create("Total Attempts: 100", "bigFont.fnt");
        attemptsLabel->setScale(0.4f);
        attemptsLabel->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(attemptsLabel, Anchor::Center, ccp(-192, 35));

        // @geode-ignore(unknown-resource)
        CCLabelBMFont *normalLabel = CCLabelBMFont::create("Normal Attempts: 100", "bigFont.fnt");
        normalLabel->setScale(0.4f);
        normalLabel->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(normalLabel, Anchor::Center, ccp(-192, 20));

        // @geode-ignore(unknown-resource)
        CCLabelBMFont *practiceLabel = CCLabelBMFont::create("Practice Attempts: 100", "bigFont.fnt");
        practiceLabel->setScale(0.4f);
        practiceLabel->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(practiceLabel, Anchor::Center, ccp(-192, 5));

        // @geode-ignore(unknown-resource)
        CCLabelBMFont *jumpsLabel = CCLabelBMFont::create("Jumps: 100", "bigFont.fnt");
        jumpsLabel->setScale(0.4f);
        jumpsLabel->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(jumpsLabel, Anchor::Center, ccp(-192, -10));

        // @geode-ignore(unknown-resource)
        CCSprite *practiceIcon = CCSprite::createWithSpriteFrameName("GJ_practiceBtn_001.png");
        practiceIcon->setScale(0.22f);
        practiceIcon->setAnchorPoint(ccp(0, 0.5f));
        m_mainLayer->addChildAtPosition(practiceIcon, Anchor::Top, ccp(-192, -160));

        // @geode-ignore(unknown-resource)
        CCLabelBMFont *practiceSubtitle = CCLabelBMFont::create("Practice Runs", "goldFont.fnt");
        practiceSubtitle->setScale(0.6f);
        practiceSubtitle->setAnchorPoint(ccp(0, 0.5f));
        practiceSubtitle->setPosition(ccp(practiceIcon->getPositionX() + 5, practiceIcon->getPositionY()));
        m_mainLayer->addChild(practiceSubtitle);

        // @geode-ignore(unknown-resource)
        CCSprite *timeSprite = CCSprite::createWithSpriteFrameName("GJ_timeIcon_001.png");
        timeSprite->setScale(0.4f);
        timeSprite->setPosition(ccp(titleLabel->getPositionX() + 5, titleLabel->getPositionY() - 15));
        m_mainLayer->addChild(timeSprite);

        // @geode-ignore(unknown-resource)
        CCLabelBMFont *timeLabel = CCLabelBMFont::create("Time played: 1h 20m", "bigFont.fnt");
        timeLabel->setScale(0.4f);
        timeLabel->setAnchorPoint(ccp(0, 0.5f));
        timeLabel->setPosition(ccp(timeSprite->getPositionX() + 5, timeSprite->getPositionY() + 1));
        m_mainLayer->addChild(timeLabel);

        CCMenu *menu = CCMenu::create();
        menu->setLayout(RowLayout::create());

        // @geode-ignore(unknown-resource)
        CCSprite *infoIcon = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
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

public:
    static MyPopup *create(std::string const &title, std::string const &data)
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
