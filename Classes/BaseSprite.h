//
//  BaseSprite.h
//  PopBird
//
//  Created by AIRIA on 14-9-5.
//
//

#ifndef __PopBird__BaseSprite__
#define __PopBird__BaseSprite__

#include "Headers.h"

class BaseSprite:public Sprite
{
public:
    static BaseSprite *create(std::string fileName);
    void setTouchEndedHandler(std::function<void(BaseSprite*)> handler);
    void setTouchMovedHandler(std::function<void(BaseSprite*)> handler);
    void setTouchBeganHandler(std::function<void(BaseSprite*)> handler);
    virtual void onEnter();
    virtual void onExit();
    CC_SYNTHESIZE(bool, m_bTouchEnabled, TouchEnabled);
protected:
    std::function<void(BaseSprite*)> touchEndedHandler;
    std::function<void(BaseSprite*)> touchMovedHandler;
    std::function<void(BaseSprite*)> touchBeganHandler;

    void __initEventListener();
    bool isContainPoint(Touch* touch,Event* event);
    
};

#endif /* defined(__PopBird__BaseSprite__) */
