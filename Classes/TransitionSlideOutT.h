//
//  TransitionSlideOutT.h
//  GuessCar
//
//  Created by AIRIA on 14-9-25.
//
//

#ifndef __GuessCar__TransitionSlideOutT__
#define __GuessCar__TransitionSlideOutT__

#include "Headers.h"

class TransitionSlideOutT: public TransitionScene, public TransitionEaseScene
{

public:
    static TransitionSlideOutT* create(float t, Scene* scene);
    virtual ActionInterval* easeActionWithAction(ActionInterval * action);
    virtual ActionInterval* action(void);
    virtual void onEnter() override;
    
CC_CONSTRUCTOR_ACCESS:
    TransitionSlideOutT(){};
    virtual ~TransitionSlideOutT(){};
    
protected:
    /** initializes the scenes */
    virtual void initScenes(void);
    virtual void sceneOrder() override;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(TransitionSlideOutT);
};

#endif /* defined(__GuessCar__TransitionSlideOutT__) */
