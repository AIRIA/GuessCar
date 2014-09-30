//
//  HomeScene.cpp
//  GuessCar
//
//  Created by AIRIA on 14-9-23.
//
//

#include "HomeScene.h"
#include "GameManager.h"
#include "LevelIcon.h"
#include "TransitionSlideOutT.h"
#include "SelectLevelScene.h"

bool HomeScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/color.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/main.plist");
    
    auto background = Sprite::create("images/home_bg.jpg");
    background->setPosition(VisibleRect::center());
    background->setScale(m_fScaleFactorBig);
    addChild(background,-1);
    
    auto title = Sprite::create("images/title.png");
    title->setPosition(Point(DESIGN_WIDTH/2,DESIGN_HEIGHT-100));
    m_pTop->addChild(title);

    auto startItem = MenuItemSprite::create(SPRITE("button_activity01.png"), SPRITE("button_activity02.png"));
    auto menu = Menu::create(startItem,nullptr);
    menu->setPosition(Point::ZERO);
    startItem->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    startItem->setPosition(Point(DESIGN_WIDTH/2,0));
    startItem->setCallback([&](Ref *pSender)->void{
        auto scene = Scene::create();
        scene->addChild(SelectLevelScene::create());
        Director::getInstance()->replaceScene(TransitionSlideOutT::create(0.5f, scene));
//        this->selectLevel();
    });
    m_pBtm->addChild(menu);
    GameManager::getInstance()->loadQA();
    return true;
}

void HomeScene::selectLevel()
{
    auto bg = Sprite::create("images/background.png");
    bg->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    bg->setPosition(Point(DESIGN_WIDTH/2,DESIGN_HEIGHT));
    bg->setScale(1/m_fScaleFactor*m_fScaleFactorBig);
    auto wrapper = Node::create();
    wrapper->addChild(bg);

    auto header = SPRITE("share_top_bar.png");
    header->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    header->setPosition(Point(DESIGN_WIDTH/2,DESIGN_HEIGHT));
    wrapper->addChild(header);
    m_pTop->addChild(wrapper);
    
    auto title = Sprite::create("images/select_level.png");
    header->addChild(title);
    auto headerSize = header->getContentSize();
    title->setPosition(Point(headerSize.width/2,headerSize.height/2));
   
    for(auto i=0;i<20;i++)
    {
        auto icon = LevelIcon::create(i);
        auto x = i%4*150+95;
        auto y = (960-200)-i/4*140;
        icon->setPosition(Point(x,y));
        wrapper->addChild(icon);
    }
    
    wrapper->setPosition(Point(0,-m_winSize.height));
    wrapper->runAction(MoveTo::create(0.3f, Point::ZERO));
}