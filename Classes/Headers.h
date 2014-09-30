//
//  Headers.h
//  PopBird
//
//  Created by AIRIA on 14-9-2.
//
//

#ifndef                          PopBird_Headers_h
#define                          PopBird_Headers_h

#include                         "cocos2d.h"
#include                         "VisibleRect.h"
#include                         "SimpleAudioEngine.h"
#include                         "external/tinyxml2/tinyxml2.h"
#include                         "extensions/cocos-ext.h"


using namespace                  cocos2d;
using namespace                  CocosDenshion;
using namespace                  tinyxml2;
using namespace                  cocos2d::extension;

#define DESIGN_WIDTH             640
#define DESIGN_HEIGHT            960

#define SharePreference          UserDefault::getInstance()
#define SPRITE(url)              Sprite::createWithSpriteFrameName(url)

#define KEY_CURRENT_LEVEL        "current_level"
#define KEY_CURRENT_PLAYER_LEVEL "player_level"

#define EVENT_BASESPRITE_DISABLE "basesprite_disable"
#define EVENT_BASESPRITE_ENABLE  "basesprite_enable"

#endif
