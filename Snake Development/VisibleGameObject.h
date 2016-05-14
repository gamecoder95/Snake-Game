#ifndef VISIBLEGAMEOBJECT_H_INCLUDED
#define VISIBLEGAMEOBJECT_H_INCLUDED

#include "ImportantHeaders.h"

class VisibleGameObject
{
public:
    VisibleGameObject();
    VisibleGameObject(std::string strID);
    virtual ~VisibleGameObject();

    /*enum ColBoxVertex
    {
        LEFT,
        WIDTH,
        TOP,
        HEIGHT
    };*/

    virtual void Load(std::string strFilename);
    virtual bool IsLoaded() const;
    virtual void Draw(sf::RenderWindow& rw);
    virtual void Update(float fElapsedTime);

    virtual void SetOrigin(float x, float y);

    virtual void SetPosition(float x, float y);
    virtual void SetPosition(sf::Vector2f v2fPosition);
    virtual sf::Vector2f GetPosition() const;

    virtual void SetScale(float x, float y);
    virtual sf::Vector2f GetScale() const;

    virtual float GetWidth() const;
    virtual float GetHeight() const;
    virtual sf::Rect<float> GetBoundingRect() const;
    virtual std::string& GetID();


protected:

    sf::Sprite& GetSprite();
    void SetID(std::string strID);

private:
    sf::Texture m_txtr;
    sf::Sprite m_spr;
    std::string m_strFilename;
    bool m_bIsLoaded;
    std::string m_strID;
};

#endif // VISIBLEGAMEOBJECT_H_INCLUDED
