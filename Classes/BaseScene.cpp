//
//  BaseScene.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-2.
//
//

#include "BaseScene.h"
#include "TransitionSlideOutT.h"

void BaseScene::run()
{
    auto scene = Scene::create();
    scene->addChild(this);
    auto runningScene = Director::getInstance()->getRunningScene();
    if(runningScene==nullptr)
    {
        Director::getInstance()->runWithScene(scene);
    }
    else
    {
        Director::getInstance()->replaceScene(TransitionSlideOutT::create(0.5f, scene));
    }
}

bool BaseScene::init()
{
    if(!BaseLayer::init())
    {
        return false;
    }
    
    auto scaleX = m_winSize.width/DESIGN_WIDTH;
    auto scaleY = m_winSize.height/DESIGN_HEIGHT;
    m_fScaleFactor = scaleX<scaleY?scaleX:scaleY;
    m_fScaleFactorBig = scaleX>scaleY?scaleX:scaleY;
    auto initLayer = [&](Point anchor,Point pos)->Layer*{
        auto layer = Layer::create();
        layer->ignoreAnchorPointForPosition(false);
        layer->setContentSize(Size(DESIGN_WIDTH,DESIGN_HEIGHT));
        layer->setScale(m_fScaleFactor);
        layer->setAnchorPoint(anchor);
        layer->setPosition(pos);
        this->addChild(layer);
        return layer;
    };
    
    /* 中间的在最下层 */
    m_pMid = initLayer(Point::ANCHOR_MIDDLE,VisibleRect::center());
    m_pBtm = initLayer(Point::ANCHOR_MIDDLE_BOTTOM,VisibleRect::bottom());
    m_pTop = initLayer(Point::ANCHOR_MIDDLE_TOP,VisibleRect::top());
    
    return true;
}