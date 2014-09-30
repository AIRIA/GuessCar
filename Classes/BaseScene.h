//
//  BaseScene.h
//  PopBird
//
//  Created by AIRIA on 14-9-2.
//
//

#ifndef __PopBird__BaseScene__
#define __PopBird__BaseScene__

#include "BaseLayer.h"
#include "Util.h"

class BaseScene:public BaseLayer
{
public:
    virtual void run();
    virtual bool init();
protected:
    Layer *m_pTop;
    Layer *m_pMid;
    Layer *m_pBtm;
    
    float m_fScaleFactor;
    float m_fScaleFactorBig;
    
};

#endif /* defined(__PopBird__BaseScene__) */
