//
//  HomeScene.h
//  GuessCar
//
//  Created by AIRIA on 14-9-23.
//
//

#ifndef __GuessCar__HomeScene__
#define __GuessCar__HomeScene__

#include "BaseScene.h"

class HomeScene:public BaseScene
{
public:
    virtual bool init();
    CREATE_FUNC(HomeScene);
    
protected:
    void selectLevel();
    
private:
    int m_iLevel = 5;
    
};

#endif /* defined(__GuessCar__HomeScene__) */
