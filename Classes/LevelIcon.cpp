//
//  LevelIcon.cpp
//  GuessCar
//
//  Created by AIRIA on 14-9-24.
//
//

#include "LevelIcon.h"
#include "GameManager.h"
#include "BaseSprite.h"
#include "GuessScene.h"
#include "TransitionSlideOutT.h"

LevelIcon *LevelIcon::create(int level)
{
    auto levelIcon = new LevelIcon();
    if(levelIcon)
    {
        levelIcon->setLevel(level);
        if(levelIcon->init())
        {
            levelIcon->autorelease();
            return levelIcon;
        }
    }

    return nullptr;
}

bool LevelIcon::init()
{
    if(!Node::init())
    {
        return false;
    }
    auto currentLevel = UserDefault::getInstance()->getIntegerForKey(KEY_CURRENT_LEVEL,1);
    BaseSprite *icon;
    if (m_iLevel<(currentLevel-1))//已经通过了
    {
        char iconName[50];
        sprintf(iconName,"images/data/%d.png",m_iLevel);
        auto iconWidth = 100;
        icon = BaseSprite::create(iconName);
        auto iconSize = icon->getContentSize();
        auto scale = iconWidth/iconSize.width;
        icon->setScale(scale);
        icon->setPositionY(10);
        
        char key[50];
        sprintf(key, "k1%04d",m_iLevel);
        std::map<std::string,std::string>::iterator it = GameManager::getInstance()->dataMap.find(key);
        auto carname = it->second;

        auto label = Label::createWithSystemFont(carname,"Arial",24);
        label->setPosition(0,-55);
        addChild(label);
        icon->setTouchEnabled(true);
    }
    else if(m_iLevel==currentLevel-1) //当前正在过的
    {
        icon = BaseSprite::create("images/unlock.png");
        icon->setTouchEnabled(true);
    }
    else //为通关的
    {
        icon = BaseSprite::create("images/locked.png");
        icon->setTouchEnabled(false);
    }
    
    icon->setTouchEndedHandler([&](BaseSprite *sprite)->void{
        GameManager::getInstance()->setSelectLevel(m_iLevel);
        GuessScene::create()->run();
    });
    addChild(icon);

    return true;
}