//
//  BlankFont.cpp
//  GuessCar
//
//  Created by AIRIA on 14-9-24.
//
//

#include "BlankFont.h"

BlankFont *BlankFont::create(int colorIdx, std::string text)
{
    auto bf = new BlankFont();
    if(bf&&bf->initWithSpriteFrameName(__String::createWithFormat("C%03d.png",colorIdx)->getCString()));
    {
        bf->autorelease();
        bf->m_pLabel = Label::createWithSystemFont(text, "黑体", 65);
        auto size = bf->getContentSize();
        bf->m_pLabel->setPosition(Point(size.width/2,size.height/2+10));
        bf->setText(text);
        bf->setTouchEnabled(true);
        bf->addChild(bf->m_pLabel);
        return bf;
    }
    CC_SAFE_DELETE(bf);
    return nullptr;
}

void BlankFont::updateText()
{
    m_pLabel->setString(getText());
}