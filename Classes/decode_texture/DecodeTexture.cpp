//
//  DecodeTexture.cpp
//  GuessCar
//
//  Created by AIRIA on 14-9-23.
//
//

#include "DecodeTexture.h"

bool DecodeTexture::init()
{
    if(!BaseScene::init())
    {
        return false;
    }
    plistPath = "ui/ui_main.plist";
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath);
   

    return true;
}

void DecodeTexture::onEnter()
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plistPath);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
    ValueMap& framesDict = dict["frames"].asValueMap();
    for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter)
    {
        std::string spriteFrameName = iter->first;
        auto sprite = Sprite::createWithSpriteFrameName(spriteFrameName);
        sprite->setAnchorPoint(Point::ZERO);
        auto ss = sprite->getContentSize();
        RenderTexture *render = RenderTexture::create(ss.width, ss.height);
        render->beginWithClear(1,1,1,0);
        sprite->visit();
        render->end();
        auto savePath = FileUtils::getInstance()->getWritablePath()+spriteFrameName;
        log("%s",savePath.c_str());
        render->saveToFile(spriteFrameName, Image::Format::PNG);
    }
}