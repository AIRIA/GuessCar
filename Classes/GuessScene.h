//
//  GuessScene.h
//  GuessCar
//
//  Created by AIRIA on 14-9-24.
//
//

#ifndef __GuessCar__GuessScene__
#define __GuessCar__GuessScene__

#include "BaseScene.h"
#include "BlankFont.h"

class GuessScene:public BaseScene,public ScrollViewDelegate
{
public:
    void showCarInfo();
    virtual bool init();
    CREATE_FUNC(GuessScene);
    
    std::string answer;
    Vector<BlankFont*> targetFontVec;
    Vector<BlankFont*> fontVec;
    
    void scrollViewDidScroll(ScrollView *view);
    void scrollViewDidZoom(ScrollView *view);
    
protected:
    void showErrorTip();
    void hideErrorTip();
    Sprite *tip;
};

#endif /* defined(__GuessCar__GuessScene__) */
