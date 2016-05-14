#ifndef WALLMAKER_H_INCLUDED
#define WALLMAKER_H_INCLUDED

#include "ImportantHeaders.h"
#include "Wall.h"

class WallMaker
{
private:

    static std::vector<Wall*> vectWallList;
    static const float CONST_FIELD_SQUARE_LENGTH = 12.0;
    static Wall* MakeWall(float fPosition_X = 0.0, float fPosition_Y = 0.0, int nNumSquares = 2, char chOrientation = 'h');
    static void AddWall(Wall* pcWall);

public:

    static void MakeWallSetUp_1();
    static void ClearWallList();
    static void UpdateWalls(float fElapsedTime);
    static Wall& GetWallObj(int nIndex);
    static int GetWallCount();

};

#endif // WALLMAKER_H_INCLUDED
