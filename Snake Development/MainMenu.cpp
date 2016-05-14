#include "MainMenu.h"

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu(){}

void MainMenu::DrawMain(sf::RenderWindow& rwMainWindow)
{
   Draw("images/SnakeGameTitle.png", rwMainWindow);
}

void MainMenu::DrawOptions(sf::RenderWindow& rwMainWindow)
{
   Draw("images/Options.png", rwMainWindow);
}

void MainMenu::DrawTut(int nTutorialPageNumber, sf::RenderWindow& rwMainWindow)
{
    switch(nTutorialPage)
    {
    case MIN_TUT_PAGE:
        Draw("images/sgt_01_Controls.png", rwMainWindow);
        break;

    case 2:
        Draw("images/sgt_02_MainObj.png", rwMainWindow);
        break;

    case 3:
        Draw("images/sgt_03_SpecObj_01.png", rwMainWindow);
        break;

    case 4:
        Draw("images/sgt_04_SpecObj_02.png", rwMainWindow);
        break;

    case 5:
        Draw("images/sgt_05_SpecObj_03.png", rwMainWindow);
        break;

    case MAX_TUT_PAGE:
        Draw("images/sgt_06_Other.png", rwMainWindow);
        break;

    default:
        break;
    }
}

void MainMenu::Draw(std::string strFileName, sf::RenderWindow& rwMainWindow)
{
    sf::Texture txtrMenuImg;
    assert(txtrMenuImg.loadFromFile(strFileName));

    sf::Sprite sprMenuImg;
    sprMenuImg.setTexture(txtrMenuImg);
    sprMenuImg.setOrigin(0, 0);
    sprMenuImg.setPosition(0, 0);

    rwMainWindow.draw(sprMenuImg);

}
void MainMenu::SetMenuState(std::string strMenuState)
{
    if(strMenuState == "Begin")
        eMenuState = BEGIN;
    else if(strMenuState == "Tutorial")
        eMenuState = TUTORIAL;
    else if(strMenuState == "Options")
        eMenuState = OPTIONS;
    else if(strMenuState == "Choose Mode")
        eMenuState = CHOOSE_MODE;
    else if(strMenuState == "Choose Mode 2")
        eMenuState = CHOOSE_MODE_2;
    else if(strMenuState == "Choose Difficulty")
        eMenuState = CHOOSE_DIFFICULTY;
}

std::string MainMenu::GetMenuStateAsString()
{
    switch(eMenuState)
    {

    case BEGIN:
        return "Begin";

    case TUTORIAL:
        return "Tutorial";

    case OPTIONS:
        return "Options";

    case CHOOSE_MODE:
        return "Choose Mode";

    case CHOOSE_MODE_2:
        return "Choose Mode 2";

    case CHOOSE_DIFFICULTY:
        return "Choose Difficulty";

    default:
        return "Null";

    }
}

int MainMenu::GetTutorialPage()
{
    return nTutorialPage;
}

void MainMenu::SetTutorialPage(int nTutPage)
{
    nTutorialPage = nTutPage;
}

void MainMenu::BackTutorialPage()
{
    if(nTutorialPage > MIN_TUT_PAGE)
    {
        --nTutorialPage;
    }
}

void MainMenu::ForwardTutorialPage()
{
    if(nTutorialPage < MAX_TUT_PAGE)
    {
        ++nTutorialPage;
    }
}

MainMenu::MenuState MainMenu::eMenuState  = MainMenu::BEGIN;
int MainMenu::nTutorialPage = 0;
