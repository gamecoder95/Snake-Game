#include "Button.h"

Button::Button(sf::Vector2f v2fPosition,
               sf::Color faceColor,
               std::string strFaceText,
               int nTextSize,
               void (*pFunction)()) : m_eButtonState(Button::DESELECTED),
                                      m_bCanBeClicked(true)
{
    //load the font
    assert(m_Font.loadFromFile("GILSANUB.TTF"));

    //assign the color to the color member variable, making sure that it's not white (default color is grey)
    if(faceColor == sf::Color::White)
        faceColor = sf::Color(51, 51, 51);//grey

    m_faceColor = faceColor;

    //assigin the funciton to the function pointer
    m_pFunction = pFunction;

    //assign the string parameter to the text string
    m_strFaceText = strFaceText;

    //assign the integer parameter to the text size, making sure it's at least CONST_MIN_TEXT_SIZE(20)
    //and at most CONST_MAX_TEXT_SIZE(50)
    m_nTextSize = nTextSize;

    if(m_nTextSize < CONST_MIN_TEXT_SIZE)
        m_nTextSize = CONST_MIN_TEXT_SIZE;

    if(m_nTextSize > CONST_MAX_TEXT_SIZE)
        m_nTextSize = CONST_MAX_TEXT_SIZE;

    //insert an endline character after every 15th character in the text string
    int nTextLines = m_strFaceText.length()/15;

    if(nTextLines > 1)
    {
        for(int i = 0; i < nTextLines; i++)
            m_strFaceText.insert(i * 15, "\n");
    }

    //declare a text object only to determine the size of the button
    sf::Text txtSample(m_strFaceText, m_Font, m_nTextSize);
    sf::Vector2f v2fFaceSize;
    sf::Vector2f v2fBackSize;

    v2fFaceSize.x = txtSample.getLocalBounds().width  + CONST_BORDER_L;
    v2fFaceSize.y = txtSample.getLocalBounds().height + CONST_BORDER_L;

    v2fBackSize.x = txtSample.getLocalBounds().width  + (2 * CONST_BORDER_L);
    v2fBackSize.y = txtSample.getLocalBounds().height + (2 * CONST_BORDER_L);

    //this is the border rectangle set-up
    sf::RectangleShape rsBack(v2fBackSize);
    rsBack.setOrigin(rsBack.getLocalBounds().left,
                     rsBack.getLocalBounds().top);//set origin as top left corner
    rsBack.setPosition(v2fPosition);
    rsBack.setFillColor(sf::Color::Black);
    m_vectButtonImage.push_back(rsBack);

    //this is the face rectangle set-up
    sf::RectangleShape rsFace(v2fFaceSize);
    rsFace.setOrigin(rsFace.getLocalBounds().left,
                     rsFace.getLocalBounds().top);//set origin as top left corner
    rsFace.setPosition(rsBack.getPosition().x + CONST_BORDER_L/2,
                       rsBack.getPosition().y + CONST_BORDER_L/2);
    rsFace.setFillColor(m_faceColor);
    m_vectButtonImage.push_back(rsFace);

}

Button::~Button(){}

void Button::Update(float fElapsedTime)
{
    if(IsSelected())
    {

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(m_bCanBeClicked)
                {
                    m_bCanBeClicked = false;
                }
            }
            else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_bCanBeClicked)
            {
                m_pFunction();
                m_bCanBeClicked = true;
            }

    }
    else
        m_bCanBeClicked = true;

    sf::RenderWindow* pcWindow = (Game::GetGameStateAsString() == "Playing")?
                                  pcWindow = &Game::GetGameWindow() : pcWindow = &Game::GetMainWindow();


    DrawButton(*(pcWindow));
}


bool Button::IsMouseWithinButton()
{
    sf::RenderWindow* pcWindow;

    if(Game::GetGameStateAsString() == "Playing")
        pcWindow = &Game::GetGameWindow();
    else
        pcWindow = &Game::GetMainWindow();

    if(sf::Mouse::getPosition(*(pcWindow)).x < (m_vectButtonImage[CONST_BUTTON_BORDER].getPosition().x
                                    + m_vectButtonImage[CONST_BUTTON_BORDER].getLocalBounds().width)
       && sf::Mouse::getPosition(*(pcWindow)).x > m_vectButtonImage[CONST_BUTTON_BORDER].getPosition().x
       && sf::Mouse::getPosition(*(pcWindow)).y < (m_vectButtonImage[CONST_BUTTON_BORDER].getPosition().y
                                       + m_vectButtonImage[CONST_BUTTON_BORDER].getLocalBounds().height)
       && sf::Mouse::getPosition(*(pcWindow)).y > m_vectButtonImage[CONST_BUTTON_BORDER].getPosition().y)
    {
        return true;
    }

    return false;
}

bool Button::IsSelected()
{
    if(IsMouseWithinButton())
    {
        m_eButtonState = SELECTED;
        m_vectButtonImage[CONST_BUTTON_FACE].setFillColor(sf::Color::White);
    }
    else
    {
        m_eButtonState = DESELECTED;
        m_vectButtonImage[CONST_BUTTON_FACE].setFillColor(m_faceColor);
    }

    return m_eButtonState == SELECTED;
}

void Button::DrawButton(sf::RenderWindow& rwMainWindow)
{
    //declare the text object that will be displayed on the button
    sf::Text txtFaceText(m_strFaceText, m_Font, m_nTextSize);
    txtFaceText.setOrigin(txtFaceText.getLocalBounds().left,
                          txtFaceText.getLocalBounds().top);//set origin as top left corner
    txtFaceText.setPosition(m_vectButtonImage[CONST_BUTTON_FACE].getPosition().x + CONST_BORDER_L/2,
                            m_vectButtonImage[CONST_BUTTON_FACE].getPosition().y + CONST_BORDER_L/2);//set position within the button face

    //setting the text color depending on the face color (default text color is white for this game)
    sf::Color textColor = (IsSelected())? sf::Color::Black  :  sf::Color::White;
    txtFaceText.setColor(textColor);

    //draw the button rectangle shapes
    for(int i = 0; i < m_vectButtonImage.size(); i++)
        rwMainWindow.draw(m_vectButtonImage[i]);

    //then draw the text
    rwMainWindow.draw(txtFaceText);
}


