//
//  GameManager.h
//  GuessCar
//
//  Created by AIRIA on 14-9-24.
//
//

#ifndef __GuessCar__GameManager__
#define __GuessCar__GameManager__

#include "Headers.h"

class GameManager
{
public:
    static GameManager *getInstance();
    void loadQA();
    CC_SYNTHESIZE(int, m_iLevel, Level); //当前的级别
    CC_SYNTHESIZE(int, m_iPlayerLevel, PlayerLevel); //玩家的级别
    std::map<std::string, std::string> dataMap;
    CC_SYNTHESIZE(int,m_iSelectLevel,SelectLevel);
    CC_SYNTHESIZE(int,m_iPage,Page);
    CC_SYNTHESIZE(bool,m_bIsScroll,IsScroll);
private:
};

#endif /* defined(__GuessCar__GameManager__) */
