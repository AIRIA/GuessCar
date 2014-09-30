//
//  TransitionSlideOutT.cpp
//  GuessCar
//
//  Created by AIRIA on 14-9-25.
//
//

#include "TransitionSlideOutT.h"

#define ADJUST_FACTOR 0.5f
TransitionSlideOutT *TransitionSlideOutT::create(float duration,Scene *scene)
{
    TransitionSlideOutT* newScene = new TransitionSlideOutT();
    if(newScene && newScene->initWithDuration(duration, scene))
    {
        newScene->autorelease();
        return newScene;
    }
    CC_SAFE_DELETE(newScene);
    return nullptr;
}

void TransitionSlideOutT::initScenes()
{
    _inScene->setPosition(Point::ZERO);
}

void TransitionSlideOutT::onEnter()
{
    TransitionScene::onEnter();
    this->initScenes();
    auto *a = this->action();
    
    _outScene->runAction
    (
     Sequence::create
     (
      this->easeActionWithAction(a),
      CallFunc::create(CC_CALLBACK_0(TransitionScene::finish, this)),
      nullptr
      )
     );
}

ActionInterval *TransitionSlideOutT::easeActionWithAction(cocos2d::ActionInterval *action)
{
    return EaseOut::create(action, 2.0f);
}

void TransitionSlideOutT::sceneOrder()
{
    _isInSceneOnTop = false;
}


ActionInterval* TransitionSlideOutT::action()
{
    auto s = Director::getInstance()->getWinSize();
    return MoveTo::create(_duration, Point(0,-s.height));
}
