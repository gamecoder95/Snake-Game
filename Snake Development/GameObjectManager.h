#ifndef GAMEOBJECTMANAGER_H_INCLUDED
#define GAMEOBJECTMANAGER_H_INCLUDED

#include "ImportantHeaders.h"
#include "VisibleGameObject.h"

class GameObjectManager
{
private:
    std::vector<VisibleGameObject*> vectGameObjList;
    sf::Clock clock;

public:
    GameObjectManager();
    ~GameObjectManager();

    void AddObject(VisibleGameObject* pcObj);
    void RemoveObject(int nObjIndex);


    VisibleGameObject& GetObject(int nObjIndex);
    int GetObjectCount() const;
    int GetObjectIndex(VisibleGameObject* pcObj) const;

    void UpdateAll();
    void DrawAll(sf::RenderWindow& rwMainWindow);
    void RemoveAll();

};

#endif // GAMEOBJECTMANAGER_H_INCLUDED
