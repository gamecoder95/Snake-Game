#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "ImportantHeaders.h"
#include "VisibleGameObject.h"
#include "Game.h"
#include "WallMaker.h"




class Snake: public VisibleGameObject
{
private:
    std::vector<sf::RectangleShape> m_vectSnakeBody, m_vectColorBody;
    const float CONST_FIELD_SQUARE_LENGTH, CONST_TIMER_EASY, CONST_TIMER_NORMAL, CONST_TIMER_HARD,
                CONST_TIMER_SA_START, CONST_SA_TIMER_DECREASE, CONST_SA_MAX_TIMER_DECREASE,
                CONST_SA_SPEED_UP_TIMER_LIMIT, CONST_SA_TIMER_DIVISOR, CONST_TIMER_TELE_START,
                CONST_TELEPORTATION_TIME_DECREASE, CONST_MIN_TELEPORTATION_TIME,
                CONST_TELE_TIMER_DECREASE, CONST_TELE_MIN_TIMER_LIMIT, CONST_RAT_TIMER_LIMIT_DIVISOR, CONST_RAT_SECOND,
                CONST_RAT_FREEZE_TIME_TIMER_LIMIT, CONST_TIMER_MIR_EASY, CONST_TIMER_MIR_NORMAL,
                CONST_TIMER_MIR_HARD, CONST_MIR_IMMUNE_TIMER_LIMIT, CONST_DISPLAY_NOTIF_TIMER_LIMIT,
                CONST_FINAL_DISPLAY_DELAY_LIMIT;

    const int   CONST_BODY_SQUARE_LENGTH, CONST_GAP_BETWEEN_SQUARES, CONST_COLOR_SQUARE_LENGTH, CONST_SA_APPLES_PER_LEVEL,
                CONST_TELE_START_BODY_LENGTH, CONST_TELE_APPLES_PER_LEVEL, CONST_RAT_TIME_INCREASE, CONST_RAT_MAX_TIME_EASY,
                CONST_RAT_MAX_TIME_NORMAL, CONST_RAT_MAX_TIME_HARD;

    float m_fTimer, m_fTimerLimit, m_fSAMinTimerLimit, m_fFreezeSnakeTimer, m_fFreezeSnakeTimerLimit,
          m_fRATTimeTimer, m_fRATFreezeTimeTimer, m_fImmuneTimer, m_fImmuneTimerLimit, m_fFinalScoreDelay, m_fButtonDelay,
          m_fBonusAppleEffectTimer, m_fDisplayNotifTimer;

    bool  m_bGameStart, m_bGrowBody, m_bShrinkBody, m_bGameOver, m_bDisplayNotif, m_bSASpeedUp, m_bTeleport,
          m_bRATFreezeTime, m_bVisible, m_bFreezeSnake, m_bReverseControls,
          m_bUpdateWalls, m_bWallsMade, m_bImmune, m_bUpdateBonusApple;

    int   m_nBodyGrowth, m_nBodyReduction, m_nAppleCount, m_nSATimerDivisor, m_nTeleLevelCount, m_nRATMaxTime,
          m_nBonusAppleCounter, m_nCountToBonusApple, m_nBodySquareSpin;

    enum Direction
    {
        UP,
        DOWN,
        RIGHT,
        LEFT
    };

    Direction m_eDirection;

    sf::Rect<float> m_rectColBox;
    sf::Font m_font;

    void GameStart(sf::RenderWindow& rw);
    void GameOver();
    void DrawFinalScore(int nApplesAte);
    void DrawFinalScore(int nApplesAte, int nOtherStat, std::string strOtherStat);
    void SquareRelocate(sf::RectangleShape& bodySquare);//for death animation
    void SquareSpin(sf::RectangleShape& bodySquare);//for death animation
    void SquareShrink(sf::RectangleShape& bodySquare);//for death animation
    void DeathAnimation();
    void MoveBody();
    void AddNeck();
    void AddBodySquare();
    void GrowBody();
    void ShrinkBody();
    void RemoveTail();


    void SALevelUpNotif(sf::RenderWindow& rw, int nLevel);
    void LevelUpNotif(sf::RenderWindow& rw, int nLevel);
    void Notif(sf::RenderWindow& rw, const std::string& str);


    void TeleportSnake();
    void ReverseTeleportSnake();
    void RelocateSnake(const std::string& strOrientation, float x, float y);

    void SetColBox();
    bool IsCollision(sf::Rect<float> rectApple, sf::Rect<float> rectSnakeHead);
    bool IsDeathCollision(std::vector<sf::RectangleShape>& vectRS);


    void DrawSnakeBody(sf::RenderWindow& rwMainWindow);

    std::vector<sf::RectangleShape>& GetSnakeBody();
    std::vector<sf::RectangleShape>& GetColorBody();
    sf::RectangleShape& GetSnakeHead();
    sf::RectangleShape& GetBodySquare(int nIndex);
    Direction GetDirection();
    sf::Rect<float>& GetColBox();

public:

    Snake();
    ~Snake();

    void SetDirection(Direction eDirection);
    void Update(float fElapsedTime);
};



#endif // SNAKE_H_INCLUDED
