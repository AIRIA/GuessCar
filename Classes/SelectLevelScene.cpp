//
//  SelectLevelScene.cpp
//  GuessCar
//
//  Created by AIRIA on 14-9-26.
//
//

#include "SelectLevelScene.h"
#include "LevelIcon.h"
#include "GameManager.h"
#include "Util.h"
#include "BaseSprite.h"

bool SelectLevelScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }

    auto bg = Sprite::create("images/background.png");
    bg->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    bg->setPosition(VisibleRect::top());
    bg->setScale(m_fScaleFactorBig);
    addChild(bg,-1);
    iconNode = Node::create();
    auto wrapper = Node::create();
    auto header = SPRITE("share_top_bar.png");
    header->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    header->setPosition(Point(DESIGN_WIDTH/2,DESIGN_HEIGHT));
    wrapper->addChild(header);
    auto leftNav = BaseSprite::create("images/left.png");
    leftNav->setPosition(Point(50,44));
    header->addChild(leftNav);
    
    leftNav->setTouchEndedHandler([&](BaseSprite *bs)->void{
        auto page = GameManager::getInstance()->getPage();
        if(page==1)
        {
            return;
        }
        page--;
        GameManager::getInstance()->setPage(page);
        scrollFunc();
        log("page=%d",page);
    });
    
    auto rightNav = BaseSprite::create("images/right.png");
    rightNav->setPosition(Point(DESIGN_WIDTH-50,44));
    rightNav->setTouchEndedHandler([&](BaseSprite*)->void{
        auto page = GameManager::getInstance()->getPage();
        if (page==7) {
            return;
        }
        page++;
        GameManager::getInstance()->setPage(page);
        scrollFunc();
         log("page=%d",page);
    });
    header->addChild(rightNav);

    m_pTop->addChild(wrapper);
    
    auto title = Sprite::create("images/select_level.png");
    header->addChild(title);
    auto headerSize = header->getContentSize();
    title->setPosition(Point(headerSize.width/2,headerSize.height/2));
    
    createNewLevelIcon();
    wrapper->addChild(iconNode);
    auto page = GameManager::getInstance()->getPage();
    auto offsetX = (1-page)*DESIGN_WIDTH;
    iconNode->setPositionX(offsetX);
    
    
    /*show ads*/
    Util::invokeNativeMethod(kMethodShowBannerAd);
    
    return true;
}

void SelectLevelScene::scrollFunc()
{
    iconNode->stopAllActions();
    auto page = GameManager::getInstance()->getPage();
    auto targetPos = DESIGN_WIDTH*(page-1);
    iconNode->runAction(MoveTo::create(0.5f, Point(-targetPos,0)));
}

void SelectLevelScene::createNewLevelIcon()
{
    for (auto page=1; page<=7; page++) {
        for(auto i=0;i<20;i++)
        {
            auto icon = LevelIcon::create(i+(page-1)*20);
            auto x = i%4*150+95+(page-1)*DESIGN_WIDTH;
            auto y = (960-200)-i/4*140;
            icon->setPosition(Point(x,y));
            iconNode->addChild(icon);
        }
    }
}