#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "ImportantHeaders.h"
#include "Game.h"
#include "VisibleGameObject.h"

class Button: public VisibleGameObject
{
private:
    std::vector<sf::RectangleShape> m_vectButtonImage;
    sf::Color m_faceColor;
    static const int CONST_BUTTON_BORDER = 0,//this is the index of the border
                     CONST_BUTTON_FACE = 1,//this is the index of the face
                     CONST_MIN_TEXT_SIZE = 20,//this is the size of the text on the button
                     CONST_MAX_TEXT_SIZE = 50,
                     CONST_BORDER_L = 10;//L stands for length
    int m_nTextSize;
    std::string m_strFaceText;
    void (*m_pFunction)();
    sf::Font m_Font;
    bool m_bCanBeClicked;

    enum ButtonState
    {
        SELECTED,
        DESELECTED
    };

    ButtonState m_eButtonState;

public:

    Button(sf::Vector2f v2fPosition,
           sf::Color faceColor,
           std::string strFaceText,
           int nTextize,
           void (*pFunction)());

    ~Button();

    void Update(float fElapsedTime);
    bool IsMouseWithinButton();
    bool IsSelected();
    void DrawButton(sf::RenderWindow& rwMainWindow);



};

#endif // BUTTON_H_INCLUDED
