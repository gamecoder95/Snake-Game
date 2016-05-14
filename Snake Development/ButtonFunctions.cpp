#include "MainMenu.h"
#include "Game.h"
#include "FadingObject.h"

void BackButton()
{
    if(MainMenu::GetMenuStateAsString() == "Choose Difficulty"
       || MainMenu::GetMenuStateAsString() == "Choose Mode 2")
    {
        MainMenu::SetMenuState("Choose Mode");
    }
    else if(MainMenu::GetMenuStateAsString() == "Choose Mode"
            || MainMenu::GetMenuStateAsString() == "Options")
    {
        MainMenu::SetMenuState("Begin");
    }
    else if(MainMenu::GetMenuStateAsString() == "Tutorial")
    {
        if(MainMenu::GetTutorialPage() == 1)
        {
            MainMenu::SetMenuState("Begin");
        }
        else
        {
           MainMenu::BackTutorialPage();
        }
    }

}

void NextButton()
{
    if(MainMenu::GetMenuStateAsString() == "Choose Mode")
    {
        MainMenu::SetMenuState("Choose Mode 2");
    }
    else if(MainMenu::GetMenuStateAsString() == "Tutorial")
    {
        if(MainMenu::GetTutorialPage() == 6)
        {
            MainMenu::SetMenuState("Begin");
        }
        else
        {
           MainMenu::ForwardTutorialPage();
        }
    }
}

void PlayButton()
{
    MainMenu::SetMenuState("Choose Mode");
}

void TutorialButton()
{
    MainMenu::SetTutorialPage(1);
    MainMenu::SetMenuState("Tutorial");
}

void OptionsButton()
{
    MainMenu::SetMenuState("Options");
}

void ArrowKeysButton()
{
    if(Game::GetControlSet() != "Arrow Keys")
    {
        Game::SetControlSet("Arrow Keys");
    }
}

void WASDButton()
{
    if(Game::GetControlSet() != "WASD")
    {
        Game::SetControlSet("WASD");
    }
}

void SoundOnButton()
{
    Game::SetSoundOn(true);
}

void SoundOffButton()
{
    Game::SetSoundOn(false);
}

void ClassicModeButton()
{
    Game::SetGameMode("CLASSIC");
    MainMenu::SetMenuState("Choose Difficulty");
}

void SpeedAddictModeButton()
{
    Game::SetGameMode("SPEED ADDICT");
    SetPlaying("No Difficulty");
}

void TeleporterModeButton()
{
    Game::SetGameMode("TELEPORTER");
    SetPlaying("No Difficulty");
}

void RaceAgainstTimeModeButton()
{
    Game::SetGameMode("RACE AGAINST TIME");
    MainMenu::SetMenuState("Choose Difficulty");
}

void MirrorModeButton()
{
    Game::SetGameMode("MIRROR MODE");
    MainMenu::SetMenuState("Choose Difficulty");
}

void LabyrinthModeButton()
{
    Game::SetGameMode("LABYRINTH MODE");
    SetPlaying("No Difficulty");
}

void EasyButton()
{
    SetPlaying("EASY");
}

void NormalButton()
{
    SetPlaying("NORMAL");
}

void HardButton()
{
    SetPlaying("HARD");
}

void RetryGame()
{
    Game::SetRetry(true);
}

void RestartGame()
{
    Game::SetGameState("Uninitialized");
}

void SetPlaying(std::string strDifficulty)
{
    Game::SetGameDifficulty(strDifficulty);
    Game::SetGameState("Playing");
    Game::ChangeWindow();
}

//look in the FadingObject.h to find these
void FadeObject(FadingObject* pcFadingObj, bool bFade)
{
    pcFadingObj->SetFaded(bFade);
}

FadingObject* GetFadingObject(std::string strID)
{
    int nTotalOptionsObj = Game::GetOptionsGOM().GetObjectCount();
    //FadingObject* pcArrowKeys = NULL;
    for(int i = 0; i < nTotalOptionsObj; ++i)
    {
        if(Game::GetOptionsGOM().GetObject(i).GetID() == strID)
        {
            VisibleGameObject* pcVGO = &Game::GetOptionsGOM().GetObject(i);
            return dynamic_cast<FadingObject*>(pcVGO);
        }
    }
}
