//
//  BlankFont.h
//  GuessCar
//
//  Created by AIRIA on 14-9-24.
//
//

#ifndef __GuessCar__BlankFont__
#define __GuessCar__BlankFont__

#include "BaseSprite.h"

class BlankFont:public BaseSprite
{
public:
    static BlankFont *create(int colorIdx,std::string text);
    void updateText();
    CC_SYNTHESIZE(std::string, m_sText, Text);
    CC_SYNTHESIZE(int ,m_iId,Id);
    Label *m_pLabel;
};

#endif /* defined(__GuessCar__BlankFont__) */
