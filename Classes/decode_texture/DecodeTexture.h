//
//  DecodeTexture.h
//  GuessCar
//
//  Created by AIRIA on 14-9-23.
//
//

#ifndef __GuessCar__DecodeTexture__
#define __GuessCar__DecodeTexture__

#include "BaseScene.h"

class DecodeTexture:public BaseScene
{
public:
    virtual bool init();
    CREATE_FUNC(DecodeTexture);
    std::string plistPath;
    virtual void onEnter();
};

#endif /* defined(__GuessCar__DecodeTexture__) */
