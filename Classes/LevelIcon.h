//
//  LevelIcon.h
//  GuessCar
//
//  Created by AIRIA on 14-9-24.
//
//

#ifndef __GuessCar__LevelIcon__
#define __GuessCar__LevelIcon__

#include "Headers.h"

class LevelIcon:public Node
{
public:
    virtual bool init();
    static LevelIcon *create(int level);
    
    CC_SYNTHESIZE(int, m_iLevel, Level);

};

#endif /* defined(__GuessCar__LevelIcon__) */
