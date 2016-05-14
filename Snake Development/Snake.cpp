#include "Snake.h"


Snake::Snake():m_eDirection(Snake::UP),
               m_fTimer(0.0),
               m_fTimerLimit(0.0),
               m_fSAMinTimerLimit(0.0),
               m_fFreezeSnakeTimer(0.0),
               m_fFreezeSnakeTimerLimit(0.5),
               m_fRATTimeTimer(0.0),
               m_fRATFreezeTimeTimer(0.0),
               m_fImmuneTimer(0.0),
               m_fImmuneTimerLimit(1.5),
               m_fFinalScoreDelay(0.0),
               m_fButtonDelay(0.0),
               m_fBonusAppleEffectTimer(0.0),
               m_fDisplayNotifTimer(0.0),
               m_bGameStart(false),
               m_bGrowBody(false),
               m_bShrinkBody(false),
               m_bGameOver(false),
               m_bDisplayNotif(false),
               m_bSASpeedUp(false),
               m_bTeleport(false),
               m_bRATFreezeTime(false),
               m_bVisible(true),
               m_bFreezeSnake(false),
               m_bReverseControls(false),
               m_bUpdateWalls(false),
               m_bWallsMade(false),
               m_bImmune(false),
               m_bUpdateBonusApple(false),
               m_nBodyGrowth(0),
               m_nBodyReduction(0),
               m_nAppleCount(0),
               m_nSATimerDivisor(1),
               m_nTeleLevelCount(0),
               m_nRATMaxTime(0),
               m_nBonusAppleCounter(0),
               m_nCountToBonusApple(10),
               m_nBodySquareSpin(1),
               CONST_BODY_SQUARE_LENGTH(11),
               CONST_COLOR_SQUARE_LENGTH(7),
               CONST_GAP_BETWEEN_SQUARES(1),
               CONST_SA_APPLES_PER_LEVEL(5),
               CONST_TELE_START_BODY_LENGTH(15),
               CONST_TELE_APPLES_PER_LEVEL(5),
               CONST_RAT_TIME_INCREASE(4),
               CONST_RAT_MAX_TIME_EASY(30),
               CONST_RAT_MAX_TIME_NORMAL(25),
               CONST_RAT_MAX_TIME_HARD(20),
               CONST_FIELD_SQUARE_LENGTH(12.0),
               CONST_TIMER_EASY(0.2),
               CONST_TIMER_NORMAL(0.15),
               CONST_TIMER_HARD(0.1),
               CONST_TIMER_SA_START(0.2),
               CONST_SA_TIMER_DECREASE(0.01),
               CONST_SA_MAX_TIMER_DECREASE(0.15),
               CONST_SA_SPEED_UP_TIMER_LIMIT(3.0),
               CONST_SA_TIMER_DIVISOR(2),
               CONST_TIMER_TELE_START(0.16),
               CONST_TELEPORTATION_TIME_DECREASE(0.08),
               CONST_MIN_TELEPORTATION_TIME(0.02),
               CONST_TELE_TIMER_DECREASE(0.01),
               CONST_TELE_MIN_TIMER_LIMIT(0.1),
               CONST_RAT_TIMER_LIMIT_DIVISOR(2.0),
               CONST_RAT_SECOND(1.0),
               CONST_RAT_FREEZE_TIME_TIMER_LIMIT(5.0),
               CONST_TIMER_MIR_EASY(0.22),
               CONST_TIMER_MIR_NORMAL(0.17),
               CONST_TIMER_MIR_HARD(0.12),
               CONST_MIR_IMMUNE_TIMER_LIMIT(15.0),
               CONST_DISPLAY_NOTIF_TIMER_LIMIT(1.0),
               CONST_FINAL_DISPLAY_DELAY_LIMIT(0.7)
{
    //load the font for the Font object (this is for the Game Over text)
    assert(m_font.loadFromFile("GILSANUB.TTF"));

    //make the first rectangle for the snake head
    sf::RectangleShape headSquare(sf::Vector2f(CONST_BODY_SQUARE_LENGTH, CONST_BODY_SQUARE_LENGTH));
    headSquare.setFillColor(sf::Color::Black);
    //origin is set at top left corner of the square
    headSquare.setOrigin(headSquare.getLocalBounds().left - CONST_GAP_BETWEEN_SQUARES, headSquare.getLocalBounds().top - CONST_GAP_BETWEEN_SQUARES);
    const int CONST_POSITION_EXTENSION = 24;//see Game CONST_TOP_BAR_L variable
    headSquare.setPosition(CONST_FIELD_SQUARE_LENGTH * 20.0, CONST_FIELD_SQUARE_LENGTH * 17.0 + CONST_POSITION_EXTENSION);


    //add the snake head, the neck and a body sqaure for the first 3 squares
    GetSnakeBody().push_back(headSquare);
    AddNeck();
    AddBodySquare();



    SetColBox();
}

Snake::~Snake(){}

void Snake::Update(float fElapsedTime)
{
    static Border cBorder;//declaration of border object
    cBorder.Update(fElapsedTime);//updating border

    if(m_bUpdateWalls && Game::GetGameModeAsString() == "TELEPORTER" && m_bGameStart && !m_bGameOver)
    {
        if(!m_bWallsMade)
        {
            WallMaker::MakeWallSetUp_1();
            m_bWallsMade = true;
        }

        WallMaker::UpdateWalls(fElapsedTime);
    }

    static Apple cRedApple(sf::Color::Red);//declaration of the red apple object
    static Apple cBonusApple(sf::Color::Green);//declaration of the green apple object
    if(!m_bGameOver && m_bGameStart)
    {
        cRedApple.Update(fElapsedTime);//updating red apple

        if(m_bUpdateBonusApple)//updating bonus apple
        {
            if(Game::GetGameModeAsString() == "SPEED ADDICT")
            {
                cBonusApple.SetColor(sf::Color::Green);
            }
            else if(Game::GetGameModeAsString() == "RACE AGAINST TIME")
            {
                cBonusApple.SetColor(sf::Color::Yellow);
            }
            else if(Game::GetGameModeAsString() == "MIRROR MODE")
            {
                cBonusApple.SetColor(sf::Color(56, 6, 155));//purple-ish color
            }
            cBonusApple.Update(fElapsedTime);
        }
    }

    static Score cScore;//declaration of the score
    cScore.Update(fElapsedTime);//updating the score

    static BonusAppleTimeDisplay cBATD;
    if(!m_bGameOver)
        cBATD.Update(fElapsedTime);

    //setting the game speed (only once) depending on the game mode and difficulty
    if(m_fTimerLimit == 0.0)
    {
        //CLASSIC MODE ONLY: set the speed of the game according to the difficulty
        if(   Game::GetGameModeAsString() == "CLASSIC"
           || Game::GetGameModeAsString() == "RACE AGAINST TIME")
        {
            if(Game::GetGameDifficultyAsString() == "EASY")
                m_fTimerLimit = CONST_TIMER_EASY;
            else if(Game::GetGameDifficultyAsString() == "NORMAL")
                m_fTimerLimit = CONST_TIMER_NORMAL;
            else if(Game::GetGameDifficultyAsString() == "HARD")
                m_fTimerLimit = CONST_TIMER_HARD;

            if(Game::GetGameModeAsString() == "RACE AGAINST TIME")
            {
                cScore.ResetTime();
                m_fTimerLimit /= CONST_RAT_TIMER_LIMIT_DIVISOR;

                if(Game::GetGameDifficultyAsString() == "EASY")
                    m_nRATMaxTime = CONST_RAT_MAX_TIME_EASY;
                else if(Game::GetGameDifficultyAsString() == "NORMAL")
                    m_nRATMaxTime = CONST_RAT_MAX_TIME_NORMAL;
                else if(Game::GetGameDifficultyAsString() == "HARD")
                    m_nRATMaxTime = CONST_RAT_MAX_TIME_HARD;
            }

        }
        else if(Game::GetGameModeAsString() == "SPEED ADDICT")
        {
            m_fTimerLimit = CONST_TIMER_SA_START;
            m_fSAMinTimerLimit = m_fTimerLimit - CONST_SA_MAX_TIMER_DECREASE;
        }
        else if(Game::GetGameModeAsString() == "TELEPORTER")
        {
            m_fTimerLimit = CONST_TIMER_TELE_START;
            while(GetSnakeBody().size() < CONST_TELE_START_BODY_LENGTH)
                AddBodySquare();
        }
        else if(Game::GetGameModeAsString() == "MIRROR MODE")
        {
            if(Game::GetGameDifficultyAsString() == "EASY")
                m_fTimerLimit = CONST_TIMER_MIR_EASY;
            else if(Game::GetGameDifficultyAsString() == "NORMAL")
                m_fTimerLimit = CONST_TIMER_MIR_NORMAL;
            else if(Game::GetGameDifficultyAsString() == "HARD")
                m_fTimerLimit = CONST_TIMER_MIR_HARD;

            m_bReverseControls = true;
        }

        cRedApple.AppleTeleport();//re-locate the apple when starting a new game
        cBonusApple.AppleTeleport();//randomize location of green apple
        cScore.ClearScore();//clear the score to start over
    }

    //so the apples don't end up overlaying
    while(   cRedApple.GetApple().getPosition().x == cBonusApple.GetApple().getPosition().x
          && cRedApple.GetApple().getPosition().y == cBonusApple.GetApple().getPosition().y)
    {
        cBonusApple.AppleTeleport();
    }

    //set the collision box for every frame
    SetColBox();

    //user must press the up arrow key to start the game
    if(!m_bGameStart)
    {
        if(Game::GetGameModeAsString() == "MIRROR MODE")
        {
            if(Game::GetControlSet() == "Arrow Keys")
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    m_bGameStart = true;
            }
            else if(Game::GetControlSet() == "WASD")
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    m_bGameStart = true;
            }
        }
        else
        {
            if(Game::GetControlSet() == "Arrow Keys")
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    m_bGameStart = true;
            }
            else if(Game::GetControlSet() == "WASD")
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    m_bGameStart = true;
            }
        }
    }

    //collision with self or the border (death)
    if(IsDeathCollision(cBorder.GetBorder()) || (IsDeathCollision(GetSnakeBody()) && !m_bImmune) )
        m_bGameOver = true;

    //collision with wall(s)
    if(m_bUpdateWalls && WallMaker::GetWallCount() > 0)
    {
        for(int i = 0; i < WallMaker::GetWallCount(); i++)
        {
            if(IsDeathCollision(WallMaker::GetWallObj(i).GetWall()))
                m_bGameOver = true;
        }
    }

    //if the apple has collided with the snake head, displace it
    if(IsCollision(cRedApple.GetColBox(), GetColBox()))
    {
        if(Game::IsSoundOn())
        {
            SoundEffect::playCrunchSound();
        }

        cRedApple.AppleTeleport();
        cScore.AddScore();

        if(Game::GetGameModeAsString() != "TELEPORTER")
            m_bGrowBody = true;

        if(   Game::GetGameModeAsString() == "SPEED ADDICT"
            || Game::GetGameModeAsString() == "RACE AGAINST TIME"
            || Game::GetGameModeAsString() == "MIRROR MODE")
        {
            if(m_nBonusAppleCounter >= m_nCountToBonusApple && !m_bUpdateBonusApple)
                m_bUpdateBonusApple = true;
            else if(m_nBonusAppleCounter < m_nCountToBonusApple)
                m_nBonusAppleCounter++;
        }

        if(Game::GetGameModeAsString() == "SPEED ADDICT")
        {
            m_nAppleCount++;

            if(m_nAppleCount >= CONST_SA_APPLES_PER_LEVEL)
            {
                m_nAppleCount = 0;
                m_bDisplayNotif = true;

                if(m_fTimerLimit > m_fSAMinTimerLimit)
                    m_fTimerLimit -= CONST_SA_TIMER_DECREASE;

            }
        }
        else if(Game::GetGameModeAsString() == "TELEPORTER")
        {
            m_nAppleCount++;
            if(!m_bTeleport)
            {
                m_bTeleport = true;

                if(m_nAppleCount >= CONST_TELE_APPLES_PER_LEVEL)
                {
                    cScore.IncrementLevel();
                    m_bDisplayNotif = true;
                    m_fFreezeSnakeTimerLimit -= CONST_TELEPORTATION_TIME_DECREASE;
                    if(m_fFreezeSnakeTimerLimit <= CONST_MIN_TELEPORTATION_TIME)
                    {
                        m_fFreezeSnakeTimerLimit = CONST_MIN_TELEPORTATION_TIME;

                        if(m_fTimerLimit > CONST_TELE_MIN_TIMER_LIMIT)
                            m_fTimerLimit -= CONST_TELE_TIMER_DECREASE;
                        else if(m_fTimerLimit <= CONST_TELE_MIN_TIMER_LIMIT)
                            m_fTimerLimit = CONST_TELE_MIN_TIMER_LIMIT;
                    }

                    m_nAppleCount = 0;
                }
            }


        }
        else if(Game::GetGameModeAsString() == "RACE AGAINST TIME")
        {
            if(cScore.GetTime() < m_nRATMaxTime)
            {
                cScore.AddTime(CONST_RAT_TIME_INCREASE);
                m_fRATTimeTimer = 0.0;

                if(cScore.GetTime() >= m_nRATMaxTime)
                    cScore.SetTime(m_nRATMaxTime);
            }
        }


    }


    //collision with bonus apple
    if(IsCollision(cBonusApple.GetColBox(), GetColBox()) && m_bUpdateBonusApple)
    {
        if(Game::IsSoundOn())
        {
            SoundEffect::playCrunchSound();
        }

        if(Game::GetGameModeAsString() == "SPEED ADDICT")
        {
            m_bShrinkBody = true;
            m_bSASpeedUp = true;
            cBATD.SetTimerLimit(CONST_SA_SPEED_UP_TIMER_LIMIT);
        }
        else if(Game::GetGameModeAsString() == "RACE AGAINST TIME")
        {
            if(!m_bRATFreezeTime)
                m_bRATFreezeTime = true;

            m_fRATFreezeTimeTimer = 0.0;
            cBATD.SetTimerLimit(CONST_RAT_FREEZE_TIME_TIMER_LIMIT);
        }
        else if(Game::GetGameModeAsString() == "MIRROR MODE")
        {
            m_fImmuneTimerLimit = CONST_MIR_IMMUNE_TIMER_LIMIT;
            m_bImmune = true;
            m_bDisplayNotif = true;
            cBATD.SetTimerLimit(m_fImmuneTimerLimit);
        }

        cBATD.SetColor(cBonusApple.GetColor());
        m_bUpdateBonusApple  = false;
        m_nBonusAppleCounter = 0;
        m_nCountToBonusApple = (std::rand() % 15) + 1;
    }

    if(m_bTeleport && Game::GetGameModeAsString() == "TELEPORTER")
    {
        const int CONST_FIELD_SQUARE_LENGTH = CONST_BODY_SQUARE_LENGTH + CONST_GAP_BETWEEN_SQUARES,//12
                  CONST_MIN_MULTIPLE        = 7,
                  CONST_MAX_MULTIPLE_X      = Game::GetFieldWidth()/CONST_FIELD_SQUARE_LENGTH - 2 * CONST_MIN_MULTIPLE,
                  CONST_MAX_MULTIPLE_Y      = Game::GetGameWindow().getSize().y/CONST_FIELD_SQUARE_LENGTH
                                              - 2 * CONST_MIN_MULTIPLE,
                  CONST_VERTICAL            = 1,
                  CONST_HORIZONTAL          = 2;
/*
        const float CONST_TOP          = Game::GetGameWindow().getSize().y - Game::GetFieldWidth() + CONST_FIELD_SQUARE_LENGTH,
                    CONST_BOTTOM       = Game::GetGameWindow().getSize().y,
                    CONST_FIELD_WIDTH  = Game::GetFieldWidth();
*/

        int nOrientationNumber     = std::rand()%2 + 1;
        std::string strOrientation = "";

        switch(nOrientationNumber)
        {
        case CONST_VERTICAL:
            strOrientation = "Vertical";
            break;

        case CONST_HORIZONTAL:
            strOrientation = "Horizontal";
            break;

        default:
            strOrientation = "Horizontal";
            break;
        }

        int nMultiple_X = std::rand()%CONST_MAX_MULTIPLE_X + CONST_MIN_MULTIPLE,
            nMultiple_Y = std::rand()%CONST_MAX_MULTIPLE_Y + CONST_MIN_MULTIPLE;

        float fX = nMultiple_X * CONST_FIELD_SQUARE_LENGTH,
              fY = nMultiple_Y * CONST_FIELD_SQUARE_LENGTH;

        RelocateSnake(strOrientation, fX, fY);

        m_bFreezeSnake = true;
        m_bTeleport = false;
    }



    //effects for collision with green apple
    if(m_bSASpeedUp && Game::GetGameModeAsString() == "SPEED ADDICT" && !m_bGameOver)
    {
        if(m_fBonusAppleEffectTimer < CONST_SA_SPEED_UP_TIMER_LIMIT)
        {
            m_nSATimerDivisor = CONST_SA_TIMER_DIVISOR;
            m_fBonusAppleEffectTimer += fElapsedTime;
        }
        else
        {
            m_nSATimerDivisor = 1;//(x/1 = x)
            m_fBonusAppleEffectTimer  = 0.0;
            m_bSASpeedUp = false;
        }
    }


    //this is so the apple(s) doesn't end up under the snake body after the initial displacement
    for(int i = 1; i < GetSnakeBody().size(); i++)
    {
        sf::Rect<float> rectColBox;
        rectColBox.left   = m_vectSnakeBody[i].getPosition().x;
        rectColBox.width  =  m_vectSnakeBody[i].getPosition().x + m_vectSnakeBody[i].getLocalBounds().width;
        rectColBox.top    = m_vectSnakeBody[i].getPosition().y;
        rectColBox.height =  m_vectSnakeBody[i].getPosition().y + m_vectSnakeBody[i].getLocalBounds().height;
        while(IsCollision(cRedApple.GetColBox(), rectColBox))
        {
            cRedApple.AppleTeleport();
            break;
        }
        while(IsCollision(cBonusApple.GetColBox(), rectColBox))
        {
            cBonusApple.AppleTeleport();
            break;
        }
    }

    //this is so the apple(s) doesn't end on the border after the initial displacement
    for(int i = 1; i < cBorder.GetBorder().size(); i++)
    {
        sf::Rect<float> rectColBox;
        rectColBox.left   = cBorder.GetBorder()[i].getPosition().x;
        rectColBox.width  = cBorder.GetBorder()[i].getPosition().x + cBorder.GetBorder()[i].getLocalBounds().width;
        rectColBox.top    = cBorder.GetBorder()[i].getPosition().y;
        rectColBox.height = cBorder.GetBorder()[i].getPosition().y + cBorder.GetBorder()[i].getLocalBounds().height;
        while(IsCollision(cRedApple.GetColBox(), rectColBox))
        {
            cRedApple.AppleTeleport();
            break;
        }
        while(IsCollision(cBonusApple.GetColBox(), rectColBox))
        {
            cBonusApple.AppleTeleport();
            break;
        }
    }

    //this is so the apple(s) doesn't end on a wall after the initial displacement
    if(m_bUpdateWalls)
    {
        for(int j = 0; j < WallMaker::GetWallCount(); j++)
        {
            for(int i = 1; i < WallMaker::GetWallObj(j).GetWall().size(); i++)
            {
                sf::Rect<float> rectColBox;
                rectColBox.left   = cBorder.GetBorder()[i].getPosition().x;
                rectColBox.width  = cBorder.GetBorder()[i].getPosition().x + cBorder.GetBorder()[i].getLocalBounds().width;
                rectColBox.top    = cBorder.GetBorder()[i].getPosition().y;
                rectColBox.height = cBorder.GetBorder()[i].getPosition().y + cBorder.GetBorder()[i].getLocalBounds().height;
                while(IsCollision(cRedApple.GetColBox(), rectColBox))
                {
                    cRedApple.AppleTeleport();
                    break;
                }
                while(IsCollision(cBonusApple.GetColBox(), rectColBox))
                {
                    cBonusApple.AppleTeleport();
                    break;
                }
            }
        }
    }


    if(Game::GetGameModeAsString() == "RACE AGAINST TIME" && !m_bGameOver && m_bGameStart)
    {
        if(m_bRATFreezeTime)
        {
            if(m_fRATFreezeTimeTimer >= CONST_RAT_FREEZE_TIME_TIMER_LIMIT)
            {
                m_bRATFreezeTime = false;
                m_fRATFreezeTimeTimer = 0.0;
            }
            else
                m_fRATFreezeTimeTimer += fElapsedTime;
        }
        else
        {
            if(cScore.GetTime() > 0)
            {
                if(m_fRATTimeTimer >= CONST_RAT_SECOND)
                {
                    cScore.DecrementTime();
                    m_fRATTimeTimer = 0.0;
                }
                else
                    m_fRATTimeTimer += fElapsedTime;
            }
            else
                m_bGameOver = true;
        }
    }

    if(m_bFreezeSnake)
    {
        if(m_fFreezeSnakeTimer < m_fFreezeSnakeTimerLimit)
            m_fFreezeSnakeTimer += fElapsedTime;
        else
        {
            m_bFreezeSnake = false;
            m_fFreezeSnakeTimer = 0.0;
        }
    }

    if(m_bImmune)
    {
        if(m_fImmuneTimer < m_fImmuneTimerLimit)
            m_fImmuneTimer += fElapsedTime;
        else
        {
            m_bImmune = false;
            m_fImmuneTimer = 0.0;
        }
    }

    //changing direction
    if(m_bGameStart && !m_bFreezeSnake)
    {
        if(Game::GetControlSet() == "Arrow Keys")
        {
            if(!m_bReverseControls)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                    && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && GetDirection() != Snake::DOWN)
                         {
                             if(GetSnakeHead().getPosition().x - GetBodySquare(1).getPosition().x != 0)
                             {
                                 SetDirection(Snake::UP);
                             }
                         }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                         && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && GetDirection() != Snake::UP)
                         {
                             if(GetSnakeHead().getPosition().x - GetBodySquare(1).getPosition().x != 0)
                             {
                                 SetDirection(Snake::DOWN);
                             }
                         }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
                         && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && GetDirection() != Snake::LEFT)
                         {
                             if(GetSnakeHead().getPosition().y - GetBodySquare(1).getPosition().y  != 0)
                             {
                                 SetDirection(Snake::RIGHT);
                             }
                         }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
                         && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && GetDirection() != Snake::RIGHT)
                         {
                             if(GetSnakeHead().getPosition().y - GetBodySquare(1).getPosition().y  != 0)
                             {
                                 SetDirection(Snake::LEFT);
                             }
                         }
            }
            else
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                    && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && GetDirection() != Snake::UP)
                         {
                             if(GetSnakeHead().getPosition().x - GetBodySquare(1).getPosition().x != 0)
                             {
                                 SetDirection(Snake::DOWN);
                             }
                         }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
                         && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && GetDirection() != Snake::DOWN)
                         {
                             if(GetSnakeHead().getPosition().x - GetBodySquare(1).getPosition().x != 0)
                             {
                                 SetDirection(Snake::UP);
                             }
                         }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
                         && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && GetDirection() != Snake::RIGHT)
                         {
                             if(GetSnakeHead().getPosition().y - GetBodySquare(1).getPosition().y  != 0)
                             {
                                 SetDirection(Snake::LEFT);
                             }
                         }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
                         && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && GetDirection() != Snake::LEFT)
                         {
                             if(GetSnakeHead().getPosition().y - GetBodySquare(1).getPosition().y  != 0)
                             {
                                 SetDirection(Snake::RIGHT);
                             }
                         }
            }
        }
        else if(Game::GetControlSet() == "WASD")
        {
            if(!m_bReverseControls)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
                    && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && GetDirection() != Snake::DOWN)
                         {
                             if(GetSnakeHead().getPosition().x - GetBodySquare(1).getPosition().x != 0)
                             {
                                 SetDirection(Snake::UP);
                             }
                         }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
                         && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && GetDirection() != Snake::UP)
                         {
                             if(GetSnakeHead().getPosition().x - GetBodySquare(1).getPosition().x != 0)
                             {
                                 SetDirection(Snake::DOWN);
                             }
                         }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W)
                         && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && GetDirection() != Snake::LEFT)
                         {
                             if(GetSnakeHead().getPosition().y - GetBodySquare(1).getPosition().y  != 0)
                             {
                                 SetDirection(Snake::RIGHT);
                             }
                         }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W)
                         && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && GetDirection() != Snake::RIGHT)
                         {
                             if(GetSnakeHead().getPosition().y - GetBodySquare(1).getPosition().y  != 0)
                             {
                                 SetDirection(Snake::LEFT);
                             }
                         }
            }
            else
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
                    && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && GetDirection() != Snake::UP)
                         {
                             if(GetSnakeHead().getPosition().x - GetBodySquare(1).getPosition().x != 0)
                             {
                                 SetDirection(Snake::DOWN);
                             }
                         }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
                         && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && GetDirection() != Snake::DOWN)
                         {
                             if(GetSnakeHead().getPosition().x - GetBodySquare(1).getPosition().x != 0)
                             {
                                 SetDirection(Snake::UP);
                             }
                         }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W)
                         && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && GetDirection() != Snake::RIGHT)
                         {
                             if(GetSnakeHead().getPosition().y - GetBodySquare(1).getPosition().y  != 0)
                             {
                                 SetDirection(Snake::LEFT);
                             }
                         }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W)
                         && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && GetDirection() != Snake::LEFT)
                         {
                             if(GetSnakeHead().getPosition().y - GetBodySquare(1).getPosition().y  != 0)
                             {
                                 SetDirection(Snake::RIGHT);
                             }
                         }
            }
        }
    }



    //moving body after every time interval (when game is active)
    if(m_fTimer >= (m_fTimerLimit/m_nSATimerDivisor)
       && !m_bGameOver && m_bGameStart && !m_bFreezeSnake)
    {
        MoveBody();
        m_fTimer = 0.0;
        //grow the body
        GrowBody();
        //shrink the body (if necessary)
        ShrinkBody();
    }


    //display the snake body
    if(m_bGameStart && m_bVisible)
    {
        DrawSnakeBody(Game::GetGameWindow());
    }


    //declaration of MAIN MENU button
    static Button cRetryButton(sf::Vector2f(130, 313), sf::Color::Red, "RETRY", 35, RetryGame);
    static Button cGameOverButton(sf::Vector2f(74, 372), sf::Color::Red, "MAIN MENU", 35, RestartGame);

    //end the game and do the necessary things when the player dies
    if(m_bGameOver)
    {
        DeathAnimation();
        cBATD.SetTimerLimit(0.0);

        if(m_fFinalScoreDelay > CONST_FINAL_DISPLAY_DELAY_LIMIT)
            GameOver();

        if(m_fFinalScoreDelay < (2 * CONST_FINAL_DISPLAY_DELAY_LIMIT))
            m_fFinalScoreDelay += fElapsedTime;
        else
        {
            if(   Game::GetGameModeAsString() == "CLASSIC"
               || Game::GetGameModeAsString() == "RACE AGAINST TIME"
               || Game::GetGameModeAsString() == "MIRROR MODE")
                DrawFinalScore(cScore.GetApplesAte());
            else if(   Game::GetGameModeAsString() == "SPEED ADDICT"
                    || Game::GetGameModeAsString() == "TELEPORTER")
                 DrawFinalScore(cScore.GetApplesAte(), cScore.GetLevel(), "LEVEL: ");
        }

        if(m_fButtonDelay < (3 * CONST_FINAL_DISPLAY_DELAY_LIMIT))
            m_fButtonDelay += fElapsedTime;
        else
        {
            cRetryButton.Update(fElapsedTime);
            cGameOverButton.Update(fElapsedTime);
        }


    }

    if(m_bDisplayNotif && !m_bGameOver)
    {
        if(m_fDisplayNotifTimer < CONST_DISPLAY_NOTIF_TIMER_LIMIT)
        {
            if(Game::GetGameModeAsString() == "SPEED ADDICT")
                SALevelUpNotif(Game::GetGameWindow(), cScore.GetLevel());
            else if(Game::GetGameModeAsString() == "TELEPORTER")
                LevelUpNotif(Game::GetGameWindow(), cScore.GetLevel());
            else if(Game::GetGameModeAsString() == "MIRROR MODE")
                Notif(Game::GetGameWindow(), "IMMUNITY!");

            m_fDisplayNotifTimer += fElapsedTime;
        }
        else
            m_bDisplayNotif = false;

    }
    else
    {
        m_fDisplayNotifTimer = 0.0;
    }

    //draw the beginning instructions
    if(!m_bGameStart)
        GameStart(Game::GetGameWindow());

    //increase the time interval by the elapsed time
    if(m_bGameStart)
        m_fTimer += fElapsedTime;

}//end of update function


void Snake::GameStart(sf::RenderWindow& rw)
{
    std::vector<sf::Text> vectText;

    if(Game::GetGameModeAsString() == "MIRROR MODE")
    {
        vectText.push_back(sf::Text("PRESS THE", m_font, 34));
        if(Game::GetControlSet() == "Arrow Keys")
        {
            vectText.push_back(sf::Text("DOWN ARROW KEY", m_font, 34));
        }
        else if(Game::GetControlSet() == "WASD")
        {
            vectText.push_back(sf::Text("S KEY", m_font, 34));
        }
        vectText.push_back(sf::Text("TO START", m_font, 34));
    }
    else
    {
        vectText.push_back(sf::Text("PRESS THE", m_font, 40));
        if(Game::GetControlSet() == "Arrow Keys")
        {
            vectText.push_back(sf::Text("UP ARROW KEY", m_font, 34));
        }
        else if(Game::GetControlSet() == "WASD")
        {
            vectText.push_back(sf::Text("W KEY", m_font, 34));
        }
        vectText.push_back(sf::Text("TO START", m_font, 40));
    }

    for(int i = 0; i < vectText.size(); i++)
    {
        vectText[i].setColor(sf::Color(0, 153, 0));//dark green
        vectText[i].setOrigin(vectText[i].getLocalBounds().width/2, vectText[i].getLocalBounds().height/2);
    }

    vectText[0].setPosition(Game::GetFieldWidth()/2, Game::GetFieldWidth()/2 - vectText[0].getLocalBounds().height - 15);
    vectText[1].setPosition(Game::GetFieldWidth()/2, Game::GetFieldWidth()/2);
    vectText[2].setPosition(Game::GetFieldWidth()/2, Game::GetFieldWidth()/2 + vectText[2].getLocalBounds().height + 15);

    for(int i = 0; i < vectText.size(); i++)
    {
        rw.draw(vectText[i]);
    }
}

void Snake::GameOver()
{
    sf::Text text("GAME OVER", m_font, 52);
    text.setOrigin(0, 0);
    text.setPosition(23, 30);
    text.setColor(sf::Color::Black);

    Game::GetGameWindow().draw(text);
}

void Snake::DrawFinalScore(int nApplesAte)
{
    std::string strApplesAte = "APPLES: ";

    sf::Text applesText(ConcatenateString(strApplesAte, nApplesAte), m_font, 30);
    applesText.setOrigin(0, 0);
    applesText.setPosition(90, 200);
    applesText.setColor(sf::Color::Black);

    Game::GetGameWindow().draw(applesText);
}

void Snake::DrawFinalScore(int nApplesAte, int nOtherStat, std::string strOtherStat)
{
    std::string strApplesAte = "APPLES: ";

    //for the number of apples eaten
    sf::Text applesText(ConcatenateString(strApplesAte, nApplesAte), m_font, 30);
    applesText.setOrigin(0, 0);
    applesText.setPosition(90, 170);
    applesText.setColor(sf::Color::Black);

    //for the other stat
    sf::Text otherStatText(ConcatenateString(strOtherStat, nOtherStat), m_font, 30);
    otherStatText.setOrigin(0, 0);
    otherStatText.setPosition(90, 230);
    otherStatText.setColor(sf::Color::Black);

    Game::GetGameWindow().draw(applesText);
    Game::GetGameWindow().draw(otherStatText);
}

void Snake::SquareRelocate(sf::RectangleShape& bodySquare)
{
    bodySquare.setOrigin(bodySquare.getLocalBounds().width/2, bodySquare.getLocalBounds().height/2);
    bodySquare.setPosition(bodySquare.getPosition().x + bodySquare.getLocalBounds().width/2,
                           bodySquare.getPosition().y + bodySquare.getLocalBounds().height/2);
}



void Snake::SquareSpin(sf::RectangleShape& bodySquare)
{
    float fNextAngle = bodySquare.getRotation() + 2.5;
    bodySquare.setRotation(fNextAngle);
}

void Snake::SquareShrink(sf::RectangleShape& bodySquare)
{
    float fNextScale = bodySquare.getScale().x - 0.0025;
    if(fNextScale <= 0.0)
        fNextScale = 0.0;
    bodySquare.setScale(fNextScale, fNextScale);
}

void Snake::DeathAnimation()
{
    //set the origins of each square to their center so they rotate around their centers
    //and reloacte them to their original spots so they don't shit awkwardly
    if(m_nBodySquareSpin == 1)
    {
        for(int i = 0; i < GetSnakeBody().size(); i++)
            SquareRelocate(GetBodySquare(i));
    }

    //rotate them and shrink each square
    for(int i = 0; i < m_nBodySquareSpin; i++)
    {
        SquareSpin(GetBodySquare(i));
        SquareShrink(GetBodySquare(i));
    }

    //increment this value (see above block)
    if(m_nBodySquareSpin <= GetSnakeBody().size())
        m_nBodySquareSpin++;

}

void Snake::MoveBody()
{
    switch(GetDirection())
    {
    case Snake::UP:
        GetSnakeHead().setPosition(GetSnakeHead().getPosition().x,
                                    GetSnakeHead().getPosition().y - GetSnakeHead().getLocalBounds().height - 1);
        break;
    case Snake::DOWN:
        GetSnakeHead().setPosition(GetSnakeHead().getPosition().x,
                                    GetSnakeHead().getPosition().y + GetSnakeHead().getLocalBounds().height + 1);
        break;
    case Snake::RIGHT:
        GetSnakeHead().setPosition(GetSnakeHead().getPosition().x + GetSnakeHead().getLocalBounds().width + 1,
                                    GetSnakeHead().getPosition().y);
        break;
    case Snake::LEFT:
        GetSnakeHead().setPosition(GetSnakeHead().getPosition().x - GetSnakeHead().getLocalBounds().width - 1,
                                    GetSnakeHead().getPosition().y);
        break;
    default:
        break;
    }

    RemoveTail();
    AddNeck();

}


void Snake::AddNeck()
{
    sf::RectangleShape neckSquare(sf::Vector2f(CONST_BODY_SQUARE_LENGTH, CONST_BODY_SQUARE_LENGTH));
    neckSquare.setFillColor(sf::Color::Black);
    //origin is set at top left corner of the square
    neckSquare.setOrigin(neckSquare.getLocalBounds().left - CONST_GAP_BETWEEN_SQUARES, neckSquare.getLocalBounds().top - CONST_GAP_BETWEEN_SQUARES);

    //set the position of this new one directly behind the head depending on the direction
    switch(GetDirection())
    {
    case Snake::UP:
        neckSquare.setPosition(GetSnakeHead().getPosition().x,
                                GetSnakeHead().getPosition().y + neckSquare.getLocalBounds().height + CONST_GAP_BETWEEN_SQUARES);
        break;

    case Snake::DOWN:
        neckSquare.setPosition(GetSnakeHead().getPosition().x,
                                GetSnakeHead().getPosition().y - neckSquare.getLocalBounds().height - CONST_GAP_BETWEEN_SQUARES);
        break;

    case Snake::RIGHT:
        neckSquare.setPosition(GetSnakeHead().getPosition().x - neckSquare.getLocalBounds().width - CONST_GAP_BETWEEN_SQUARES,
                                GetSnakeHead().getPosition().y);
        break;

    case Snake::LEFT:
        neckSquare.setPosition(GetSnakeHead().getPosition().x + neckSquare.getLocalBounds().width + CONST_GAP_BETWEEN_SQUARES,
                                GetSnakeHead().getPosition().y);
        break;

    default:
        break;
    }

    GetSnakeBody().insert(GetSnakeBody().begin() + 1, neckSquare);
}


void Snake::AddBodySquare()
{
    sf::RectangleShape bodySquare(sf::Vector2f(CONST_BODY_SQUARE_LENGTH, CONST_BODY_SQUARE_LENGTH));
    bodySquare.setFillColor(sf::Color::Black);
    //origin is set at top left corner of the square
    bodySquare.setOrigin(bodySquare.getLocalBounds().left - CONST_GAP_BETWEEN_SQUARES, bodySquare.getLocalBounds().top - CONST_GAP_BETWEEN_SQUARES);

    //the two last squares
    std::vector<sf::RectangleShape>::const_iterator itTail = GetSnakeBody().end() - 1;
    std::vector<sf::RectangleShape>::const_iterator itSquareBeforeTail = GetSnakeBody().end() - 2;

    //if tail is on the right of the square before the tail, put the next square on the right of the tail
    if(itTail->getPosition().x > itSquareBeforeTail->getPosition().x)
        bodySquare.setPosition(itTail->getPosition().x + bodySquare.getLocalBounds().width + 1, itTail->getPosition().y);

    //if tail is on the left of the square before the tail, put the next square on the left of the tail
    else if(itTail->getPosition().x < itSquareBeforeTail->getPosition().x)
        bodySquare.setPosition(itTail->getPosition().x - bodySquare.getLocalBounds().width - 1, itTail->getPosition().y);

    //if tail is under of the square before the tail, put the next square under the tail
    else if(itTail->getPosition().y > itSquareBeforeTail->getPosition().y)
        bodySquare.setPosition(itTail->getPosition().x, itTail->getPosition().y + bodySquare.getLocalBounds().height + 1);

    //if tail is on top of the square before the tail, put the next square on top of the tail
    else if(itTail->getPosition().y < itSquareBeforeTail->getPosition().y)
        bodySquare.setPosition(itTail->getPosition().x, itTail->getPosition().y - bodySquare.getLocalBounds().height - 1);


    GetSnakeBody().push_back(bodySquare);

}

void Snake::GrowBody()
{
    if(m_bGrowBody)
    {
        if(m_nBodyGrowth < 3)
        {
            AddBodySquare();
            m_nBodyGrowth++;
        }
        else
        {
            m_bGrowBody = false;
            m_nBodyGrowth = 0;
        }


    }

}

void Snake::ShrinkBody()
{
    int nBodyReductionLimit = 0;

    if(Game::GetGameModeAsString() == "SPEED ADDICT")
        nBodyReductionLimit = GetSnakeBody().size()/4;

    if(m_bShrinkBody && GetSnakeBody().size() > 3)
    {

        if(m_nBodyReduction < nBodyReductionLimit)
        {
            RemoveTail();
            m_nBodyReduction++;
        }
        else
        {
            m_bShrinkBody = false;
            m_nBodyReduction = 0;
        }
    }
    else
        m_bShrinkBody = false;

}

void Snake::RemoveTail()
{
    if(GetSnakeBody().size() > 0)
    {
        std::vector<sf::RectangleShape>::iterator it = GetSnakeBody().end();
        GetSnakeBody().erase(it);
    }

}

void Snake::RelocateSnake(const std::string& strOrientation, float x, float y)
{
    GetSnakeHead().setPosition(x, y);

    float fDistanceToRight  = Game::GetFieldWidth() - GetSnakeHead().getPosition().x,
          fDistanceToLeft   = GetSnakeHead().getPosition().x,
          fDistanceToTop    = GetSnakeHead().getPosition().y - (Game::GetGameWindow().getSize().y - Game::GetFieldWidth()),
          fDistanceToBottom = Game::GetFieldWidth() - GetSnakeHead().getPosition().y,
          fSizeOfBodySquare = GetSnakeHead().getLocalBounds().width;


    if(strOrientation == "Horizontal" || strOrientation == "horizontal")
    {
        if(fDistanceToRight < fDistanceToLeft)
        {
            for(int i = 1; i < GetSnakeBody().size(); i++)
            {
                sf::Vector2f v2fPosition_2;
                v2fPosition_2.x = GetSnakeHead().getPosition().x - (i * fSizeOfBodySquare) - i;
                v2fPosition_2.y = GetSnakeHead().getPosition().y;
                m_vectSnakeBody[i].setPosition(v2fPosition_2);
            }

            SetDirection(Snake::RIGHT);
        }
        else
        {
            for(int i = 1; i < GetSnakeBody().size(); i++)
            {
                sf::Vector2f v2fPosition_2;
                v2fPosition_2.x = GetSnakeHead().getPosition().x + (i * fSizeOfBodySquare) + i;
                v2fPosition_2.y = GetSnakeHead().getPosition().y;
                m_vectSnakeBody[i].setPosition(v2fPosition_2);
            }

            SetDirection(Snake::LEFT);
        }
    }
    else if(strOrientation == "Vertical" || strOrientation == "vertical")
    {
        if(fDistanceToBottom < fDistanceToTop)
        {
            for(int i = 1; i < GetSnakeBody().size(); i++)
            {
                sf::Vector2f v2fPosition_2;
                v2fPosition_2.x = GetSnakeHead().getPosition().x;
                v2fPosition_2.y = GetSnakeHead().getPosition().y - (i * fSizeOfBodySquare) - i;
                m_vectSnakeBody[i].setPosition(v2fPosition_2);
            }

            SetDirection(DOWN);
        }
        else
        {
            for(int i = 1; i < GetSnakeBody().size(); i++)
            {
                sf::Vector2f v2fPosition_2;
                v2fPosition_2.x = GetSnakeHead().getPosition().x;
                v2fPosition_2.y = GetSnakeHead().getPosition().y + (i * fSizeOfBodySquare) + i;
                m_vectSnakeBody[i].setPosition(v2fPosition_2);
            }

            SetDirection(UP);
        }
    }


}

void Snake::SALevelUpNotif(sf::RenderWindow& rw, int nLevel)
{
    if(m_nAppleCount%CONST_SA_APPLES_PER_LEVEL != 0)
        return;

    if(Game::GetGameModeAsString() != "SPEED ADDICT")
        return;

    const int CONST_MAX_SPEED_LEVEL = 1 + CONST_SA_MAX_TIMER_DECREASE/CONST_SA_TIMER_DECREASE;

    std::string strLevelUpText  = "LEVEL UP!",
                strMaxSpeedText = "MAX SPEED ACHIEVED!";

    sf::Text levelUpText(strLevelUpText, m_font, 25);
    levelUpText.setOrigin(levelUpText.getLocalBounds().width/2, levelUpText.getLocalBounds().height/2);

    float fLevelUpTextYPosition = (nLevel == CONST_MAX_SPEED_LEVEL)? Game::GetFieldWidth()/2
                                                                     + (Game::GetGameWindow().getSize().y - Game::GetFieldWidth())
                                                                     - levelUpText.getLocalBounds().height/2
                                                                   : Game::GetFieldWidth()/2
                                                                     + (Game::GetGameWindow().getSize().y - Game::GetFieldWidth());

    levelUpText.setPosition(Game::GetFieldWidth()/2, fLevelUpTextYPosition);
    levelUpText.setColor(sf::Color::Blue);

    sf::Text maxSpeedText(strMaxSpeedText, m_font, 25);
    maxSpeedText.setOrigin(maxSpeedText.getLocalBounds().width/2, maxSpeedText.getLocalBounds().height/2);
    maxSpeedText.setPosition(Game::GetFieldWidth()/2, Game::GetFieldWidth()/2
                                                      + (Game::GetGameWindow().getSize().y - Game::GetFieldWidth())
                                                      + maxSpeedText.getLocalBounds().height/2);
    maxSpeedText.setColor(sf::Color::Blue);


    rw.draw(levelUpText);
    if(nLevel == CONST_MAX_SPEED_LEVEL)
        rw.draw(maxSpeedText);
}

void Snake::LevelUpNotif(sf::RenderWindow& rw, int nLevel)
{
    if(m_nAppleCount%CONST_TELE_APPLES_PER_LEVEL != 0)
        return;

    sf::Text levelUpText("LEVEL UP!", m_font, 25);
    levelUpText.setOrigin(levelUpText.getLocalBounds().width/2, levelUpText.getLocalBounds().height/2);
    levelUpText.setPosition(Game::GetFieldWidth()/2, Game::GetFieldWidth()/2);
    levelUpText.setColor(sf::Color::Blue);

    rw.draw(levelUpText);
}

void Snake::Notif(sf::RenderWindow& rw, const std::string& str)
{
    sf::Text text(str, m_font, 25);
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(Game::GetFieldWidth()/2, Game::GetFieldWidth()/2);
    text.setColor(sf::Color::Blue);

    rw.draw(text);
}

void Snake::SetColBox()
{
    GetColBox().left   = GetSnakeHead().getPosition().x;
    GetColBox().width  = GetSnakeHead().getPosition().x + GetSnakeHead().getLocalBounds().width;
    GetColBox().top    = GetSnakeHead().getPosition().y;
    GetColBox().height = GetSnakeHead().getPosition().y + GetSnakeHead().getLocalBounds().height;
}

bool Snake::IsCollision(sf::Rect<float> rectApple, sf::Rect<float> rectSnakeHead)
{
    if(rectApple.height < rectSnakeHead.top || rectApple.top > rectSnakeHead.height
       || rectApple.left > rectSnakeHead.width || rectApple.width < rectSnakeHead.left)
            return false;

    return true;
}

bool Snake::IsDeathCollision(std::vector<sf::RectangleShape>& vectRS)
{
    if(vectRS[1].getPosition().x == m_vectSnakeBody[1].getPosition().x)
    {
        for(int i = 1; i < vectRS.size(); i++)
        {
            sf::Rect<float> rectColBox;
            rectColBox.left   =  vectRS[i].getPosition().x;
            rectColBox.width  =  vectRS[i].getPosition().x + vectRS[i].getLocalBounds().width;
            rectColBox.top    =  vectRS[i].getPosition().y;
            rectColBox.height =  vectRS[i].getPosition().y + vectRS[i].getLocalBounds().height;

            if(IsCollision(rectColBox, GetColBox()))
            {
                return true;
            }
        }
    }
    else
    {
        for(int i = 0; i < vectRS.size(); i++)
        {
            sf::Rect<float> rectColBox;
            rectColBox.left   =  vectRS[i].getPosition().x;
            rectColBox.width  =  vectRS[i].getPosition().x + vectRS[i].getLocalBounds().width;
            rectColBox.top    =  vectRS[i].getPosition().y;
            rectColBox.height =  vectRS[i].getPosition().y + vectRS[i].getLocalBounds().height;

            if(IsCollision(rectColBox, GetColBox()))
            {
                return true;
                break;
            }
        }
    }

    return false;
}

void Snake::SetDirection(Direction eDirection)
{
    m_eDirection = eDirection;
}

void Snake::DrawSnakeBody(sf::RenderWindow& rwMainWindow)
{
    for(int i = 0; i < GetSnakeBody().size(); i++)
        rwMainWindow.draw(GetBodySquare(i));
}

std::vector<sf::RectangleShape>& Snake::GetSnakeBody()
{
    return m_vectSnakeBody;
}

std::vector<sf::RectangleShape>& Snake::GetColorBody()
{
    return m_vectColorBody;
}

sf::RectangleShape& Snake::GetSnakeHead()
{
    return m_vectSnakeBody[0];
}

sf::RectangleShape& Snake::GetBodySquare(int nIndex)
{
    if(nIndex < 0)
        nIndex = 0;

    if(nIndex >= GetSnakeBody().size())
        nIndex = GetSnakeBody().size() - 1;

    return m_vectSnakeBody[nIndex];
}

Snake::Direction Snake::GetDirection()
{
    return m_eDirection;
}

sf::Rect<float>& Snake::GetColBox()
{
    return m_rectColBox;
}
