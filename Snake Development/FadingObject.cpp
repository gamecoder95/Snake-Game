#include "FadingObject.h"


FadingObject::FadingObject(std::string strID, std::string strSprFileName)
              :FadingObject(strID, strSprFileName, 0.5, 0, 0, false)
{
}

FadingObject::FadingObject(std::string strID, std::string strSprFileName, float fFadeOpacity, float fXPos, float fYPos)
             :FadingObject(strID, strSprFileName, fFadeOpacity, fXPos, fYPos, false)
{
}

FadingObject::FadingObject(std::string strID, std::string strSprFileName, float fFadeOpacity, float fXPos, float fYPos, bool bFaded)
             :VisibleGameObject(strID),
              m_bFaded(bFaded),
              m_fFadeOpacity(fFadeOpacity),
              MAX_ALPHA(256)
{
    Load(strSprFileName);
    assert(IsLoaded());
    SetOrigin(0,0);
    SetPosition(fXPos, fYPos);
}

FadingObject::~FadingObject()
{
}

void FadingObject::Fade()
{
    int r = GetSprite().getColor().r,
        g = GetSprite().getColor().g,
        b = GetSprite().getColor().b;

    if(m_bFaded)
    {
        GetSprite().setColor(sf::Color(r,g,b,MAX_ALPHA*m_fFadeOpacity));
    }
    else if(!m_bFaded)
    {
        GetSprite().setColor(sf::Color(r,g,b));
    }
}

void FadingObject::Update(float fElapsedTime)
{
    Fade();
    sf::RenderWindow* pcWindow = (Game::GetGameStateAsString() == "Playing")?
                                  pcWindow = &Game::GetGameWindow() : pcWindow = &Game::GetMainWindow();

    Draw(*(pcWindow));
}

bool FadingObject::IsFaded() { return m_bFaded; }
void FadingObject::SetFaded(bool bFaded) { m_bFaded = bFaded; }
bool FadingObject::GetFadeOpacity() { return m_fFadeOpacity; }
void FadingObject::SetFadeOpacity(bool fFadeOpacity) { m_fFadeOpacity = fFadeOpacity; }

