#include "Game.h"

void Game::Start()
{
    if(eGameState != UNINITIALIZED)
        return;

    const int CONST_WIDTH_EXTENSION = 60;

    rwGameWindow.create(sf::VideoMode(nFieldWidth , nFieldHeight + CONST_TOP_BAR_L, 32),
                        "Snake Game", sf::Style::Titlebar | sf::Style::Close);

    rwGameWindow.setVisible(false);
    rwGameWindow.setActive(false);

    rwMainWindow.create(sf::VideoMode(nFieldWidth + CONST_WIDTH_EXTENSION, nFieldHeight , 32),
                        "Snake Game", sf::Style::Titlebar | sf::Style::Close);


    //adding the snake object (essentially the entire game)
    Snake* pcSnake = new Snake;
    GetMainGOM().AddObject(pcSnake);

    //adding the button objects

    GetButtonsPersistentGOM().AddObject(new Button(sf::Vector2f(0, nFieldHeight - 41), sf::Color(33, 31, 31), "BACK", 25, BackButton));

    GetButtonsPersistent_2GOM().AddObject(new Button(sf::Vector2f(nFieldWidth - 40, nFieldHeight - 41), sf::Color(33, 31, 31), "NEXT", 25, NextButton));

    GetButtonsBeginGOM().AddObject(new Button(sf::Vector2f(167, 225), sf::Color(33, 31, 31), "PLAY", 35, PlayButton));

    GetButtonsBeginGOM().AddObject(new Button(sf::Vector2f(118, 280), sf::Color(33, 31, 31), "TUTORIAL", 35, TutorialButton));

    GetButtonsBeginGOM().AddObject(new Button(sf::Vector2f(133, 335), sf::Color(33, 31, 31), "OPTIONS", 35, OptionsButton));

    GetButtonsModeGOM().AddObject(new Button(sf::Vector2f(120, 215), sf::Color(33, 31, 31), "CLASSIC MODE", 25, ClassicModeButton));

    GetButtonsModeGOM().AddObject(new Button(sf::Vector2f(73, 270), sf::Color(33, 31, 31), "SPEED ADDICT MODE", 25, SpeedAddictModeButton));

    GetButtonsModeGOM().AddObject(new Button(sf::Vector2f(95, 325), sf::Color(33, 31, 31), "TELEPORTER MODE", 25, TeleporterModeButton));

    GetButtonsMode_2GOM().AddObject(new Button(sf::Vector2f(30, /*215*/240), sf::Color(33, 31, 31), "RACE AGAINST TIME MODE", 25, RaceAgainstTimeModeButton));

    GetButtonsMode_2GOM().AddObject(new Button(sf::Vector2f(115, /*270*/295), sf::Color(33, 31, 31), "MIRROR MODE", 25, MirrorModeButton));

    GetButtonsDifficultyGOM().AddObject(new Button(sf::Vector2f(167, 215), sf::Color(33, 31, 31), "EASY", 35, EasyButton));

    GetButtonsDifficultyGOM().AddObject(new Button(sf::Vector2f(135, 285), sf::Color(33, 31, 31), "NORMAL", 35, NormalButton));

    GetButtonsDifficultyGOM().AddObject(new Button(sf::Vector2f(162, 355), sf::Color(33, 31, 31), "HARD", 35, HardButton));

    GetOptionsGOM().AddObject(new FadingObject("Arrow Keys", "images/ArrowKeys.png", 0.5, 310, 140));

    GetOptionsGOM().AddObject(new FadingObject("WASD", "images/WASD.png", 0.5, 20, 140, true));

    GetOptionsGOM().AddObject(new FadingObject("NO", "images/NO.png", 0.0, 190, 287, true));

    GetOptionsGOM().AddObject(new Button(sf::Vector2f(144, 139), sf::Color(33, 31, 31), "ARROW KEYS", 20, ArrowKeysButton));

    GetOptionsGOM().AddObject(new Button(sf::Vector2f(189, 189), sf::Color(33, 31, 31), "WASD", 20, WASDButton));

    GetOptionsGOM().AddObject(new Button(sf::Vector2f(25, 315), sf::Color(33, 31, 31), "SOUND: ON", 20, SoundOnButton));

    GetOptionsGOM().AddObject(new Button(sf::Vector2f(303, 315), sf::Color(33, 31, 31), "SOUND: OFF", 20, SoundOffButton));

    //setting up the grid
    int nLines = nFieldWidth/12;

    //veritcal lines
    for(int i = 0; i < nLines; i++)
    {
        sf::RectangleShape rs(sf::Vector2f(1, nFieldHeight));
        rs.setFillColor(sf::Color(192, 192, 192));
        rs.setOrigin(0.0, 0.0);
        rs.setPosition(sf::Vector2f(i* 12.0, CONST_TOP_BAR_L));
        GetGrid().push_back(rs);
    }

    //horizontal lines
    for(int j = 0; j < nLines; j++)
    {
        sf::RectangleShape rs(sf::Vector2f(nFieldWidth, 1));
        rs.setFillColor(sf::Color(192, 192, 192));
        rs.setOrigin(0.0, 0.0);
        rs.setPosition(sf::Vector2f(0.0, j* 12.0 + CONST_TOP_BAR_L));
        GetGrid().push_back(rs);
    }


    eGameState = MAIN_MENU;//PLAYING;//PLAYING is for testing only//after all initial setup is done

    while(!IsExiting())
        GameLoop();

    rwGameWindow.close();
    rwMainWindow.close();
}

void Game::GameLoop()
{
    sf::Event event;

    switch(eGameState)
    {
    case MAIN_MENU:

        while(rwMainWindow.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                eGameState = EXITING;
                break;

           default://for event.type
               break;
            }
        }//for pollEvent switch statement

        rwMainWindow.clear(sf::Color(57, 52, 52));//kinda dark gray (check the photoshop file)

        if(MainMenu::GetMenuStateAsString() == "Tutorial")
        {
            cMainMenu.DrawTut(MainMenu::GetTutorialPage(), rwMainWindow);
        }
        else if(MainMenu::GetMenuStateAsString() == "Options")
        {
           cMainMenu.DrawOptions(rwMainWindow);
        }
        else
        {
            cMainMenu.DrawMain(rwMainWindow);
        }

        if(MainMenu::GetMenuStateAsString() != "Begin")
            GetButtonsPersistentGOM().UpdateAll();

        if(MainMenu::GetMenuStateAsString() == "Choose Mode"
           || MainMenu::GetMenuStateAsString() == "Tutorial")
            GetButtonsPersistent_2GOM().UpdateAll();

        if(MainMenu::GetMenuStateAsString() == "Begin")
            GetButtonsBeginGOM().UpdateAll();
        else if(MainMenu::GetMenuStateAsString() == "Choose Mode")
            GetButtonsModeGOM().UpdateAll();
        else if(MainMenu::GetMenuStateAsString() == "Choose Mode 2")
            GetButtonsMode_2GOM().UpdateAll();
        else if(MainMenu::GetMenuStateAsString() == "Choose Difficulty")
            GetButtonsDifficultyGOM().UpdateAll();
        else if(MainMenu::GetMenuStateAsString() == "Options")
        {
            if(GetControlSet() == "Arrow Keys")
            {
                FadeObject(GetFadingObject("Arrow Keys"), false);
                FadeObject(GetFadingObject("WASD"), true);
            }
            else if(GetControlSet() == "WASD")
            {
                FadeObject(GetFadingObject("Arrow Keys"), true);
                FadeObject(GetFadingObject("WASD"), false);
            }

            if(IsSoundOn())
            {
                FadeObject(GetFadingObject("NO"), true);
            }
            else
            {
                FadeObject(GetFadingObject("NO"), false);
            }
            GetOptionsGOM().UpdateAll();
        }

        rwMainWindow.display();
        break;//for case MAIN_MENU

    case PLAYING:

            while(rwGameWindow.pollEvent(event))
            {
                switch(event.type)
                {
                case sf::Event::Closed:
                    WallMaker::ClearWallList();
                    eGameState = EXITING;
                    break;

                    //add rest here

                default://for event.type
                    break;
                }
            }//for pollEvent switch statement

            if(bRetry)
            {
                Snake* pcSnake = new Snake;
                GetMainGOM().AddObject(pcSnake);
                GetMainGOM().RemoveObject(0);
                WallMaker::ClearWallList();
                bRetry = false;
            }

            rwGameWindow.clear(sf::Color(255,255,255));//white
            DrawGrid(rwGameWindow); //make option in the game to set grid on/off
            GetMainGOM().UpdateAll();
            GetMainGOM().DrawAll(rwGameWindow);
            rwGameWindow.display();

    break;//case PLAYING:

    case UNINITIALIZED:
        GetMainGOM().RemoveAll();
        GetButtonsBeginGOM().RemoveAll();
        GetButtonsModeGOM().RemoveAll();
        GetButtonsMode_2GOM().RemoveAll();
        GetButtonsDifficultyGOM().RemoveAll();
        GetButtonsPersistentGOM().RemoveAll();
        GetButtonsPersistent_2GOM().RemoveAll();
        GetOptionsGOM().RemoveAll();
        WallMaker::ClearWallList();
        cMainMenu.SetMenuState("Begin");
        ChangeWindow();
        Start();
        break;

    default: //for eGameState
        break;

    }//end of eGameState switch




}//end of GameLoop function

bool Game::IsExiting()
{
    return (eGameState == EXITING) ? true : false;
}

sf::RenderWindow& Game::GetMainWindow()
{
    return rwMainWindow;
}

sf::RenderWindow& Game::GetGameWindow()
{
    return rwGameWindow;
}

void Game::ChangeWindow()
{
    if(GetGameStateAsString() != "Playing")
    {
        GetGameWindow().setActive(false);
        GetMainWindow().setActive(true);
        GetGameWindow().setVisible(false);
        GetMainWindow().setVisible(true);
    }
    else
    {
        GetGameWindow().setActive(true);
        GetMainWindow().setActive(false);
        GetGameWindow().setVisible(true);
        GetMainWindow().setVisible(false);
    }
}

GameObjectManager& Game::GetMainGOM()
{
    return cMainGOM;
}

GameObjectManager& Game::GetButtonsPersistentGOM()
{
    return cButtonsPersistentGOM;
}

GameObjectManager& Game::GetButtonsPersistent_2GOM()
{
    return cButtonsPersistent_2GOM;
}

GameObjectManager& Game::GetButtonsBeginGOM()
{
    return cButtonsBeginGOM;
}

GameObjectManager& Game::GetButtonsModeGOM()
{
    return cButtonsModeGOM;
}

GameObjectManager& Game::GetButtonsMode_2GOM()
{
    return cButtonsMode_2GOM;
}

GameObjectManager& Game::GetButtonsDifficultyGOM()
{
    return cButtonsDifficultyGOM;
}

GameObjectManager& Game::GetOptionsGOM()
{
    return cOptionsGOM;
}

std::string& Game::GetControlSet()
{
    return strControlSet;
}

void Game::SetControlSet(std::string strCS)
{
    strControlSet = strCS;
}

void Game::DrawGrid(sf::RenderWindow& rwMainWindow)
{
    for(int i = 0; i < GetGrid().size(); i++)
        rwMainWindow.draw(m_vectGrid[i]);
}

std::vector<sf::RectangleShape>& Game::GetGrid()
{
    return m_vectGrid;
}



int Game::GetFieldWidth()
{
    return nFieldWidth;
}

void Game::SetRetry(bool retry)
{
    bRetry = retry;
}

void Game::SetSoundOn(bool soundOn)
{
    bSoundOn = soundOn;
}

bool Game::IsSoundOn()
{
    return bSoundOn;
}

void Game::SetGameState(std::string strGameState)
{
    if(strGameState == "Uninitialized")
        eGameState = UNINITIALIZED;
    else if(strGameState == "Main Menu")
        eGameState = MAIN_MENU;
    else if(strGameState == "Playing")
        eGameState = PLAYING;
    else if(strGameState == "Exiting")
        eGameState = EXITING;
}

void Game::SetGameMode(std::string strGameMode)
{
    if(strGameMode == "CLASSIC")
        eGameMode = CLASSIC;
    else if(strGameMode == "SPEED ADDICT")
        eGameMode = SPEED_ADDICT;
    else if(strGameMode == "TELEPORTER")
        eGameMode = TELEPORTER;
    else if(strGameMode == "RACE AGAINST TIME")
        eGameMode = RACE_AGAINST_TIME;
    else if(strGameMode == "MIRROR MODE")
        eGameMode = MIRROR_MODE;
    else if(strGameMode == "LABYRINTH")
        eGameMode = LABYRINTH;
}

void Game::SetGameDifficulty(std::string strGameDifficulty)
{
    if(strGameDifficulty == "EASY")
        eGameDifficulty = EASY;
    else if(strGameDifficulty == "NORMAL")
        eGameDifficulty = NORMAL;
    else if(strGameDifficulty == "HARD")
        eGameDifficulty = HARD;
    else
        eGameDifficulty = NOTHING;
}

std::string Game::GetGameStateAsString()
{
    switch(eGameState)
    {
    case UNINITIALIZED:
        return "Uninitialized";

    case MAIN_MENU:
        return "Main Menu";

    case PLAYING:
        return "Playing";

    case EXITING:
        return "Exiting";

    default:
        return "Null";
    }
}

std::string Game::GetGameModeAsString()
{
    switch(eGameMode)
    {
    case CLASSIC:
        return "CLASSIC";

    case SPEED_ADDICT:
        return "SPEED ADDICT";

    case TELEPORTER:
        return "TELEPORTER";

    case RACE_AGAINST_TIME:
        return "RACE AGAINST TIME";

    case MIRROR_MODE:
        return "MIRROR MODE";

    case LABYRINTH:
        return "LABYRINTH";
        //add rest here

    default:
        return "CLASSIC";
    }
}

std::string Game::GetGameDifficultyAsString()
{
    switch(eGameDifficulty)
    {
    case EASY:
        return "EASY";

    case NORMAL:
        return "NORMAL";

    case HARD:
        return "HARD";

    default:
        return "-----";
    }
}


Game::Gamestate Game::eGameState = Game::UNINITIALIZED;
Game::GameMode Game::eGameMode = Game::CLASSIC;
Game::GameDifficulty Game::eGameDifficulty = Game::EASY;

sf::RenderWindow Game::rwMainWindow;
sf::RenderWindow Game::rwGameWindow;
int Game::nFieldWidth = 420, Game::nFieldHeight = 420;
bool Game::bRetry = false;
bool Game::bSoundOn = true;
GameObjectManager Game::cMainGOM;
GameObjectManager Game::cButtonsPersistentGOM;
GameObjectManager Game::cButtonsPersistent_2GOM;
GameObjectManager Game::cButtonsBeginGOM;
GameObjectManager Game::cButtonsModeGOM;
GameObjectManager Game::cButtonsMode_2GOM;
GameObjectManager Game::cButtonsDifficultyGOM;
GameObjectManager Game::cOptionsGOM;
MainMenu Game::cMainMenu;
std::vector<sf::RectangleShape> Game::m_vectGrid;
std::string Game::strControlSet = "Arrow Keys";

