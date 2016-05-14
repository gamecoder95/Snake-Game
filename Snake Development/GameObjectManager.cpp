#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(){}

GameObjectManager::~GameObjectManager()
{
    RemoveAll();
}

void GameObjectManager::AddObject(VisibleGameObject* pcObj)
{
    vectGameObjList.push_back(pcObj);
}

void GameObjectManager::RemoveObject(int nObjIndex)
{
    std::vector<VisibleGameObject*>::iterator it = vectGameObjList.begin()+ nObjIndex;
    if(it >= vectGameObjList.end())
        return;

    delete *it;
    *it = 0;
    vectGameObjList.erase(it);

}




VisibleGameObject& GameObjectManager::GetObject(int nObjIndex)
{
    return *(vectGameObjList[nObjIndex]);
}


int GameObjectManager::GetObjectCount() const
{
    return vectGameObjList.size();
}


int GameObjectManager::GetObjectIndex(VisibleGameObject* pcObj) const
{
    std::vector<VisibleGameObject*>::const_iterator it = vectGameObjList.begin();
    while(it != vectGameObjList.end())
    {
        int nObjIndex = std::distance(vectGameObjList.begin(),it);
        if(vectGameObjList[nObjIndex] == pcObj)
            return nObjIndex;

        it++;
    }

    return 0;//if not found
}




void GameObjectManager::UpdateAll()
{
    std::vector<VisibleGameObject*>::iterator it = vectGameObjList.begin();
    float fTimeDelta = clock.restart().asSeconds();
    while(it != vectGameObjList.end())
    {
        vectGameObjList[std::distance(vectGameObjList.begin(), it)]->Update(fTimeDelta);
        it++;
    }
}

void GameObjectManager::DrawAll(sf::RenderWindow& rwMainWindow)
{
    std::vector<VisibleGameObject*>::iterator it;

    for(it = vectGameObjList.begin(); it != vectGameObjList.end();it++)
    {
        vectGameObjList[std::distance(vectGameObjList.begin(), it)]->Draw(rwMainWindow);
    }
}

void GameObjectManager::RemoveAll()
{
    std::vector<VisibleGameObject*>::iterator it = vectGameObjList.begin();
    while(it != vectGameObjList.end())
    {
        delete *it;
        *it = 0;
        vectGameObjList.erase(it);
    }

}
