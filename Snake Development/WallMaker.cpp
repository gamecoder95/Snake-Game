#include "WallMaker.h"
#include "Game.h"

Wall* WallMaker::MakeWall(float fPosition_X, float fPosition_Y, int nNumSquares, char chOrientation)
{
    Wall* pcWall = new Wall(fPosition_X, fPosition_Y, nNumSquares, chOrientation);
    return pcWall;
}

void WallMaker::AddWall(Wall* pcWall)
{
    vectWallList.push_back(pcWall);
}

void WallMaker::MakeWallSetUp_1()
{
    if(GetWallCount() > 0)
        ClearWallList();

    const float CONST_FIELD_WIDTH  = Game::GetFieldWidth(),
                CONST_TOP          = (Game::GetGameWindow().getSize().y - Game::GetFieldWidth()),
                CONST_BOTTOM       = Game::GetGameWindow().getSize().y;

    AddWall(MakeWall(CONST_FIELD_SQUARE_LENGTH,
                     CONST_BOTTOM - CONST_FIELD_SQUARE_LENGTH * 6, 2, 'h'));

    AddWall(MakeWall(CONST_FIELD_SQUARE_LENGTH * 6,
                     CONST_TOP + CONST_FIELD_SQUARE_LENGTH, 2, 'v'));

    AddWall(MakeWall(CONST_FIELD_SQUARE_LENGTH * 6,
                     CONST_BOTTOM - CONST_FIELD_SQUARE_LENGTH * 14, 3, 'h'));

    AddWall(MakeWall(CONST_FIELD_SQUARE_LENGTH * 11,
                     CONST_TOP + CONST_FIELD_SQUARE_LENGTH * 14, 4, 'v'));

    AddWall(MakeWall(CONST_FIELD_SQUARE_LENGTH * 12,
                     CONST_TOP + CONST_FIELD_SQUARE_LENGTH * 17, 3, 'h'));

    AddWall(MakeWall(CONST_FIELD_SQUARE_LENGTH * 14,
                     CONST_TOP + CONST_FIELD_SQUARE_LENGTH * 6, 4, 'h'));

    AddWall(MakeWall(CONST_FIELD_SQUARE_LENGTH * 16,
                     CONST_BOTTOM - CONST_FIELD_SQUARE_LENGTH * 9, 4, 'h'));

    AddWall(MakeWall(CONST_FIELD_SQUARE_LENGTH * 17,
                     CONST_BOTTOM - CONST_FIELD_SQUARE_LENGTH * 2, 2, 'v'));

    AddWall(MakeWall(CONST_FIELD_SQUARE_LENGTH * 24,
                     CONST_TOP + CONST_FIELD_SQUARE_LENGTH * 11, 3, 'v'));

    AddWall(MakeWall(CONST_FIELD_SQUARE_LENGTH * 25,
                     CONST_TOP + CONST_FIELD_SQUARE_LENGTH * 20, 3, 'h'));

    AddWall(MakeWall(CONST_FIELD_SQUARE_LENGTH * 25,
                     CONST_TOP + CONST_FIELD_SQUARE_LENGTH * 22, 2, 'v'));

    AddWall(MakeWall(CONST_FIELD_SQUARE_LENGTH * 26,
                     CONST_TOP + CONST_FIELD_SQUARE_LENGTH * 23, 3, 'h'));

    AddWall(MakeWall(CONST_FIELD_WIDTH - CONST_FIELD_SQUARE_LENGTH * 7,
                     CONST_TOP + CONST_FIELD_SQUARE_LENGTH * 5, 4, 'h'));

    AddWall(MakeWall(CONST_FIELD_WIDTH - CONST_FIELD_SQUARE_LENGTH * 2,
                     CONST_BOTTOM - CONST_FIELD_SQUARE_LENGTH * 7, 3, 'h'));

}

void WallMaker::ClearWallList()
{
    std::vector<Wall*>::iterator it = vectWallList.begin();

    while(it != vectWallList.end())
    {
        delete *it;
        *it = 0;
        vectWallList.erase(it);
    }
}

void WallMaker::UpdateWalls(float fElapsedTime)
{
    for(int i = 0; i < vectWallList.size(); i++)
        vectWallList[i]->Update(fElapsedTime);
}

Wall& WallMaker::GetWallObj(int nIndex)
{
    return *(vectWallList[nIndex]);
}

int WallMaker::GetWallCount()
{
    return vectWallList.size();
}

std::vector<Wall*> WallMaker::vectWallList;
