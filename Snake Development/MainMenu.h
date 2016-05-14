#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include "ImportantHeaders.h"

class MainMenu
{
private:
    enum MenuState
    {
        BEGIN,
        TUTORIAL,
        OPTIONS,
        CHOOSE_MODE,
        CHOOSE_MODE_2,
        CHOOSE_DIFFICULTY
    };

    static MenuState eMenuState;
    static int nTutorialPage;
    static const int MIN_TUT_PAGE = 1, MAX_TUT_PAGE = 6;

public:

    MainMenu();
    ~MainMenu();

    void DrawMain(sf::RenderWindow& rwMainWindow);
    void DrawOptions(sf::RenderWindow& rwMainWindow);
    void DrawTut(int nTutorialPageNumber, sf::RenderWindow& rwMainWindow);
    void Draw(std::string strFileName, sf::RenderWindow& rwMainWindow);

    static void SetMenuState(std::string strMenuState);
    static std::string GetMenuStateAsString();
    static int GetTutorialPage();
    static void SetTutorialPage(int nTutPage);
    static void BackTutorialPage();
    static void ForwardTutorialPage();

};

//these are the button functions
void BackButton();
void NextButton();

void PlayButton();
void TutorialButton();
void OptionsButton();

void ArrowKeysButton();
void WASDButton();
void SoundOnButton();
void SoundOffButton();

void ClassicModeButton();
void SpeedAddictModeButton();
void TeleporterModeButton();
void RaceAgainstTimeModeButton();
void MirrorModeButton();
void LabyrinthModeButton();

void EasyButton();
void NormalButton();
void HardButton();

void RetryGame();
void RestartGame();

void SetPlaying(std::string strDifficulty);

#endif // MAINMENU_H_INCLUDED
