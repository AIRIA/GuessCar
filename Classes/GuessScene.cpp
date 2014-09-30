//
//  GuessScene.cpp
//  GuessCar
//
//  Created by AIRIA on 14-9-24.
//
//

#include "GuessScene.h"
#include "GameManager.h"
#include "BlankFont.h"
#include "SelectLevelScene.h"
#include "Util.h"

bool GuessScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }
    
    auto bg = Sprite::create("images/background.png");
    bg->setPosition(VisibleRect::center());
    bg->setScale(m_fScaleFactorBig);
    addChild(bg,-1);
    
    auto header = SPRITE("share_top_bar.png");
    header->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    header->setPosition(Point(DESIGN_WIDTH/2,DESIGN_HEIGHT));
    m_pTop->addChild(header);
    
    auto back = BaseSprite::create("images/back.png");
    back->setTouchEnabled(true);
    back->setTouchEndedHandler([](BaseSprite* bs)->void{
        SelectLevelScene::create()->run();
    });
    back->setPosition(Point(50,44));
    header->addChild(back);
    
    
    auto border = SPRITE("username_board.png");
    border->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    border->setPosition(Point(DESIGN_WIDTH/2,DESIGN_HEIGHT-150));
    m_pTop->addChild(border);
    
    auto borderSize = border->getContentSize();
    char iconName[50];
    sprintf(iconName, "images/data/%d.png",GameManager::getInstance()->getSelectLevel());
    auto icon = Sprite::create(iconName);
    icon->setPosition(Point(borderSize.width/2,borderSize.height/2));
    icon->setScale(1.0f/0.7f);
    border->addChild(icon);
    border->setScale(0.7f);
    char lengthKey[20];
    sprintf(lengthKey,"l1%04d",GameManager::getInstance()->getSelectLevel());
    /* 获取有几个字 */
    std::map<std::string,std::string>::iterator it = GameManager::getInstance()->dataMap.find(lengthKey);
    auto length = atoi(it->second.c_str());
    auto offset = (DESIGN_WIDTH-(80*(length-1)))/2;
    it = GameManager::getInstance()->dataMap.find(__String::createWithFormat("k1%04d",GameManager::getInstance()->getSelectLevel())->getCString());
    answer = it->second;
    
    for (auto i=0; i<length; i++)
    {
        auto blankfont = BlankFont::create(9,""/*name.substr(i*3,3)*/);
        blankfont->setPosition(Point(offset+i%7*80,DESIGN_HEIGHT-500));
        blankfont->setTouchEndedHandler([&](BaseSprite *bs)->void{
            auto bf = static_cast<BlankFont*>(bs);
            bf->setText("");
            bf->updateText();
            auto idx = bf->getId();
            fontVec.at(idx)->setVisible(true);
            fontVec.at(idx)->setTouchEnabled(true);
            this->hideErrorTip();
        });
        blankfont->setScale(0.7f);
        m_pTop->addChild(blankfont);
        targetFontVec.pushBack(blankfont);
    }
    
    auto sep = Sprite::create("images/activity_board02.png");
    sep->setPosition(Point(DESIGN_WIDTH/2,DESIGN_HEIGHT-570));
    m_pTop->addChild(sep);
    
    std::vector<int> idxVec;
    std::string nameStr = answer;
    int selectTxtLen = length;
    
    /* 设置候选的文字 随机获取几个车标的名字凑齐21个字*/
    offset = (DESIGN_WIDTH-(80*6))/2;
    idxVec.push_back(GameManager::getInstance()->getSelectLevel());
    while (selectTxtLen<=21) {
        auto randomIdx = rand()%141;
        if(std::find(idxVec.begin(), idxVec.end(), randomIdx) == idxVec.end())
        {
            idxVec.push_back(randomIdx);
            char key[20];
            sprintf(key, "k1%04d",randomIdx);
            it = GameManager::getInstance()->dataMap.find(key);
            auto name = it->second;
            sprintf(key, "l1%04d",randomIdx);
            it = GameManager::getInstance()->dataMap.find(key);
            auto length = atoi(it->second.c_str());
            selectTxtLen += length;
            if(selectTxtLen>21)
            {
                auto len = selectTxtLen-21;
                name = name.substr(0,(length-len)*3);
            }
            nameStr += name;
        }
    }
    idxVec.clear();
    log("%s",nameStr.c_str());
    for(auto i=0;i<21;i++)
    {
        auto randomIdx = rand()%21;
        while (true)
        {
            if (std::find(idxVec.begin(), idxVec.end(), randomIdx)==idxVec.end())
            {
                idxVec.push_back(randomIdx);
                break;
            }
            randomIdx = rand()%21;
        }
        
        auto blankfont = BlankFont::create(9,nameStr.substr(randomIdx*3,3));
        blankfont->setId(i);
        blankfont->setPosition(Point(offset+i%7*80,DESIGN_HEIGHT-630-i/7*80));
        blankfont->setTouchEndedHandler([&](BaseSprite *bs)->void{
            auto bf = static_cast<BlankFont*>(bs);
            
            for (auto i=0;i<targetFontVec.size(); i++)
            {
                auto targetBF = targetFontVec.at(i);
                if(targetBF->getText()=="")
                {
                    targetBF->setId(bf->getId());
                    targetBF->setText(bf->getText());
                    targetBF->updateText();
                    bf->setVisible(false);
                    bf->setTouchEnabled(false);
                    break;
                }
            }
            
            /* 选择以后判断结果是否正确 */
            std::string currentStr = "";
            for(auto i=0;i<targetFontVec.size();i++)
            {
                currentStr += targetFontVec.at(i)->getText();
            }
            if(currentStr==answer)
            {
                this->showCarInfo();
                return;
            }

            auto fontNum = 0;
            for (auto i=0; i<targetFontVec.size(); i++) {
                if (targetFontVec.at(i)->getText()!="") {
                    fontNum++;
                }
            }
            
            if (fontNum==targetFontVec.size()) {
                this->showErrorTip();
            }
            

            
        });
        blankfont->setScale(0.7f);
        m_pTop->addChild(blankfont);
        fontVec.pushBack(blankfont);
    }

    
    return true;
}


void GuessScene::showCarInfo()
{
    /* 七分之一的概率显示广告插屏广告 */
    if(rand()%7==0)
    {
        Util::invokeNativeMethod(kMethodShowSpotAd);
    }
    
    /* 回答正确后调用此方法 同时要保存当前关卡  */
    auto currentLevel = UserDefault::getInstance()->getIntegerForKey(KEY_CURRENT_LEVEL);
    auto selectLevel = GameManager::getInstance()->getSelectLevel();
    if ((selectLevel+2)>=currentLevel)
    {
        UserDefault::getInstance()->setIntegerForKey(KEY_CURRENT_LEVEL, GameManager::getInstance()->getSelectLevel()+2);
        UserDefault::getInstance()->flush();
    }
    
    
    auto colorBg = LayerColor::create(Color4B(0, 0, 0, 128), m_winSize.width, m_winSize.height);
    auto event = EventListenerTouchOneByOne::create();
    event->setSwallowTouches(true);
    event->onTouchBegan = [](Touch *touch,Event *event)->bool
    {
        return true;
    };
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, colorBg);
    addChild(colorBg);
    char key[20];
    sprintf(key, "e1%04d",GameManager::getInstance()->getSelectLevel());
    std::map<std::string,std::string>::iterator it = GameManager::getInstance()->dataMap.find(key);
    
    
    auto border = SPRITE("username_board.png");
    border->setPosition(VisibleRect::center());
    border->setScale(m_fScaleFactor);
    
    auto carInfo = Label::createWithSystemFont(it->second, "黑体", 34,Size(530,0));
    carInfo->setAnchorPoint(Point(0,0));
    auto scrollView = ScrollView::create(Size(530,300),carInfo);
    scrollView->setContentOffset(Point(0,300-carInfo->getContentSize().height));
    scrollView->setTouchEnabled(true);
    scrollView->setDelegate(this);
    scrollView->setDirection(ScrollView::Direction::VERTICAL);
    scrollView->setBounceable(true);
    scrollView->setContentSize(Size(530, carInfo->getContentSize().height));
    
    scrollView->ignoreAnchorPointForPosition(false);
    scrollView->setAnchorPoint(Point(0.5,0.5));
    scrollView->setScale(m_fScaleFactor);
    scrollView->setPosition(VisibleRect::center());

    auto next = MenuItemSprite::create(SPRITE("Button_next_quize.png"),SPRITE("Button_next_quize01.png"));
    next->setCallback([](Ref *pSender)->void{
        GameManager::getInstance()->setSelectLevel(GameManager::getInstance()->getSelectLevel()+1);
        GuessScene::create()->run();
    });
    auto menu = Menu::create(next,nullptr);
    next->setPosition(VisibleRect::center()-Point(0,280*m_fScaleFactor));
    next->setScale(m_fScaleFactor);
    menu->setPosition(Point::ZERO);
    
    auto wrapperNode = Node::create();
    wrapperNode->addChild(border);
    wrapperNode->addChild(scrollView);
    wrapperNode->addChild(menu);
    
    wrapperNode->setPosition(Point(0,DESIGN_HEIGHT));
    addChild(wrapperNode);
    wrapperNode->runAction(EaseBackOut::create(MoveTo::create(0.5f, Point::ZERO))); 
    
}

void GuessScene::showErrorTip()
{
    if(tip)
    {
        return;
    }
    tip = SPRITE("tip_board02.png");
    auto tipMsg = Label::createWithSystemFont("输入的不对哦~", "黑体", 35);
    auto tipSize = tip->getContentSize();
    tip->addChild(tipMsg);
    tipMsg->setPosition(Point(tipSize.width/2,tipSize.height/2+10));
    tip->setPosition(Point(DESIGN_WIDTH/2+100,DESIGN_HEIGHT-400));
    m_pTop->addChild(tip);

    auto moveBy = MoveBy::create(0.1f, Point(20,0));
    tip->runAction(Sequence::create(moveBy,moveBy->reverse(),moveBy,moveBy->reverse(), nullptr));
}

void GuessScene::hideErrorTip()
{
    if (tip) {
        tip->removeFromParent();
        tip = nullptr;
    }
}

void GuessScene::scrollViewDidScroll(cocos2d::extension::ScrollView *view)
{
    
}

void GuessScene::scrollViewDidZoom(cocos2d::extension::ScrollView *view)
{
    
}