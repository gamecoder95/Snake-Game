#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "ImportantHeaders.h"
#include "GameObjectManager.h"
#include "Snake.h"
#include "Apple.h"
#include "Border.h"
#include "Score.h"
#include "MainMenu.h"
#include "Button.h"
#include "BonusAppleTimeDisplay.h"
#include "SoundEffect.h"
#include "FadingObject.h"


class Game
{

private:

    static sf::RenderWindow rwMainWindow;
    static sf::RenderWindow rwGameWindow;
    static const int CONST_TOP_BAR_L = 24;//L stands for length
    static bool bRetry;
    static bool bSoundOn;

    static bool IsExiting();
    static void GameLoop();

    static GameObjectManager cMainGOM;
    static GameObjectManager cButtonsPersistentGOM;
    static GameObjectManager cButtonsPersistent_2GOM;
    static GameObjectManager cButtonsBeginGOM;
    static GameObjectManager cButtonsModeGOM;
    static GameObjectManager cButtonsMode_2GOM;
    static GameObjectManager cButtonsDifficultyGOM;
    static GameObjectManager cOptionsGOM;
    static MainMenu cMainMenu;
    static int nFieldWidth, nFieldHeight;
    static std::vector<sf::RectangleShape> m_vectGrid;
    static void DrawGrid(sf::RenderWindow& rwMainWindow);
    static std::vector<sf::RectangleShape>& GetGrid();
    static std::string strControlSet;


    enum Gamestate
    {
        UNINITIALIZED,
        MAIN_MENU,
        PLAYING,
        EXITING
    };

    enum GameMode
    {
        CLASSIC,
        SPEED_ADDICT,
        TELEPORTER,
        RACE_AGAINST_TIME,
        MIRROR_MODE,
        LABYRINTH,
    };

    enum GameDifficulty
    {
        NOTHING,
        EASY,
        NORMAL,
        HARD
    };

    static Gamestate eGameState;
    static GameMode eGameMode;
    static GameDifficulty eGameDifficulty;

    static GameObjectManager& GetMainGOM();
    static GameObjectManager& GetButtonsPersistentGOM();
    static GameObjectManager& GetButtonsPersistent_2GOM();
    static GameObjectManager& GetButtonsBeginGOM();
    static GameObjectManager& GetButtonsModeGOM();
    static GameObjectManager& GetButtonsMode_2GOM();
    static GameObjectManager& GetButtonsDifficultyGOM();


public:

    static GameObjectManager& GetOptionsGOM();
    static std::string& GetControlSet();
    static void SetControlSet(std::string strCS);

    static void Start();
    static sf::RenderWindow&  GetMainWindow();
    static sf::RenderWindow&  GetGameWindow();
    static void ChangeWindow();

    static int GetFieldWidth();
    static void SetRetry(bool retry);
    static void SetSoundOn(bool soundOn);
    static bool IsSoundOn();

    static void SetGameState(std::string strGameState);
    static void SetGameMode(std::string strGameMode);
    static void SetGameDifficulty(std::string strGameDifficulty);

    static std::string GetGameStateAsString();
    static std::string GetGameModeAsString();
    static std::string GetGameDifficultyAsString();

};


#endif // GAME_H_INCLUDED
