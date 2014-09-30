//
//  SelectLevelScene.h
//  GuessCar
//
//  Created by AIRIA on 14-9-26.
//
//

#ifndef __GuessCar__SelectLevelScene__
#define __GuessCar__SelectLevelScene__

#include "BaseScene.h"

class SelectLevelScene:public BaseScene
{
public:
    virtual bool init();
    CREATE_FUNC(SelectLevelScene);
    
protected:
    void createNewLevelIcon();
    void scrollFunc();
private:
    Point beganPoint;
    Point currentPoint;
    bool flag = false;
    Node* iconNode;
    
};

#endif /* defined(__GuessCar__SelectLevelScene__) */
