#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject():m_bIsLoaded(false)
{
    m_strID = "";
}

VisibleGameObject::VisibleGameObject(std::string strID)
                  :VisibleGameObject()
{
    m_strID = strID;
}


VisibleGameObject::~VisibleGameObject(){}



void VisibleGameObject::Load(std::string strFilename)
{
    if(!m_txtr.loadFromFile(strFilename))
    {
        m_strFilename = "";
        m_bIsLoaded = false;
    }
    else
    {
        strFilename = m_strFilename;
        m_spr.setTexture(m_txtr);
        m_bIsLoaded = true;
    }
}

bool VisibleGameObject::IsLoaded() const
{
    return m_bIsLoaded;
}

void VisibleGameObject::Draw(sf::RenderWindow& rw)
{
    if(m_bIsLoaded)
        rw.draw(m_spr);
}

void VisibleGameObject::Update(float fElapsedTime){}//this will be redefined by all derived classes



void VisibleGameObject::SetOrigin(float x, float y)
{
    m_spr.setOrigin(x,y);
}




void VisibleGameObject::SetPosition(float x, float y)
{
    if(m_bIsLoaded)
        m_spr.setPosition(x,y);
}

void VisibleGameObject::SetPosition(sf::Vector2f v2fPosition)
{
    if(m_bIsLoaded)
        m_spr.setPosition(v2fPosition);
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
    if(m_bIsLoaded)
        return m_spr.getPosition();

    return sf::Vector2f(0.0, 0.0);
}



void VisibleGameObject::SetScale(float x, float y)
{
    m_spr.setScale(x, y);
}

sf::Vector2f VisibleGameObject::GetScale() const
{
    return m_spr.getScale();
}



float VisibleGameObject::GetWidth()const
{
    return m_spr.getLocalBounds().width;
}

float VisibleGameObject::GetHeight()const
{
    return m_spr.getLocalBounds().height;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
    return m_spr.getGlobalBounds();
}

std::string& VisibleGameObject::GetID()
{
    return m_strID;
}



sf::Sprite& VisibleGameObject::GetSprite()
{
    return m_spr;
}

void VisibleGameObject::SetID(std::string strID)
{
    m_strID = strID;
}

