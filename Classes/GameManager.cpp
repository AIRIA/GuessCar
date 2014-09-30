//
//  GameManager.cpp
//  GuessCar
//
//  Created by AIRIA on 14-9-24.
//
//

#include "GameManager.h"

GameManager *GameManager::getInstance()
{
    static GameManager *_instance = nullptr;
    if (_instance==nullptr) {
        _instance = new GameManager();
        _instance->setPage(1);
    }
    
    auto isExist = UserDefault::getInstance()->isXMLFileExist();
    if (!isExist)
    {

    }
    
    return _instance;
}

void GameManager::loadQA()
{
    XMLDocument doc;
    Data data = FileUtils::getInstance()->getDataFromFile("data/strings.xml");
    doc.Parse((const char*)data.getBytes(),data.getSize());
    auto root = doc.RootElement();
    auto node = root->FirstChildElement();
    
    while (node!=nullptr)
    {
        std::string key = node->GetText();
        std::string value = node->NextSiblingElement()->GetText();
        node = node->NextSiblingElement()->NextSiblingElement();
        dataMap.insert(std::pair<std::string, std::string>(key,value));
    }
    
}