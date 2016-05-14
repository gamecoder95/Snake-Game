#include "Score.h"

Score::Score()
        :m_nApplesAte(0),
         m_nLevel(1),
         m_nTime(10),
         CONST_APPLES_PER_LEVEL(5),
         CONST_TEXT_SIZE(11),
         CONST_TIME_START_VALUE(8)
{
   assert(m_Font.loadFromFile("GILSANUB.TTF"));
}

Score::~Score(){}

void Score::Update(float fElapsedTime)
{
    DrawTopPanel(Game::GetGameWindow());
}

void Score::AddScore()
{
    m_nApplesAte++;

    if(Game::GetGameModeAsString() == "SPEED ADDICT")
    {
        if(m_nApplesAte%CONST_APPLES_PER_LEVEL == 0)
            m_nLevel = m_nApplesAte/CONST_APPLES_PER_LEVEL + 1;
    }
}

void Score::ClearScore()
{
    m_nApplesAte = 0;
    m_nLevel = 1;
}

void Score::DrawTopPanel(sf::RenderWindow& rw)
{
    const float CONST_TOP_PANEL_HEIGHT = Game::GetGameWindow().getSize().y - Game::GetFieldWidth();

    //create the text objects
    sf::Text gameModeText,
             gameDifficultyText,
             applesAteText,
             levelText,
             timeText;

    std::string strLevel = "";
    if(   Game::GetGameModeAsString() == "CLASSIC"
       || Game::GetGameModeAsString() == "RACE AGAINST TIME"
       || Game::GetGameModeAsString() == "MIRROR MODE")
        strLevel = ConcatenateString(m_strLevel, "-----");
    else
        strLevel = ConcatenateString(m_strLevel, m_nLevel);


    //setting up the text objects
    SetUpText(gameModeText, Game::GetGameModeAsString(), LEFT);
    SetUpText(gameDifficultyText, ConcatenateString(m_strDifficulty, Game::GetGameDifficultyAsString()), RIGHT);
    SetUpText(applesAteText, ConcatenateString(m_strApplesAte, m_nApplesAte), LEFT);
    SetUpText(levelText, strLevel, LEFT);//level text is still being displayed on the right though
    SetUpText(timeText, ConcatenateString("Time: ", m_nTime), CENTER);

    //set their positions based on the game mode
    gameModeText.setPosition(0, -1);
    gameDifficultyText.setPosition(Game::GetFieldWidth(), -1);
    applesAteText.setPosition(0, applesAteText.getLocalBounds().height + 1);
    levelText.setPosition(Game::GetFieldWidth() - gameDifficultyText.getLocalBounds().width,//to be inline with
                          levelText.getLocalBounds().height + 1);                           //the word "difficulty"
    timeText.setPosition(Game::GetFieldWidth()/2, CONST_TOP_PANEL_HEIGHT/2 - timeText.getLocalBounds().height /2);

    //draw the text
    rw.draw(gameModeText);
    rw.draw(gameDifficultyText);
    rw.draw(applesAteText);
    rw.draw(levelText);

    if(Game::GetGameModeAsString() == "RACE AGAINST TIME")
        rw.draw(timeText);
}

void Score::SetUpText(sf::Text& text, std::string str, Side eSide)
{

    text.setString(str);
    text.setFont(m_Font);
    int nCharacterSize = (str == ConcatenateString("Time: ", m_nTime))? CONST_TEXT_SIZE + 3 : CONST_TEXT_SIZE;
    text.setCharacterSize(nCharacterSize);
    text.setColor(sf::Color::Black);

    switch(eSide)
    {
    case RIGHT:
        text.setOrigin(text.getLocalBounds().width, 0);
        break;

    case CENTER:
        text.setOrigin(text.getLocalBounds().width/2, 0);
        break;

    case LEFT:
        text.setOrigin(0, 0);
        break;

    default:
        break;
    }

}

int Score::GetApplesAte()
{
    return m_nApplesAte;
}

void Score::IncrementLevel()
{
    m_nLevel++;
}

int Score::GetLevel()
{
    return m_nLevel;
}


void Score::DecrementTime()
{
    m_nTime--;
}

void Score::AddTime(int nTime)
{
    m_nTime += nTime;
}

void Score::SubtractTime(int nTime)
{
    m_nTime -= nTime;
}

void Score::ResetTime()
{
    m_nTime = CONST_TIME_START_VALUE;
}

void Score::SetTime(int nTime)
{
    m_nTime = nTime;
}

int Score::GetTime()
{
    return m_nTime;
}

std::string ConcatenateString(const std::string& str, int n)
{
    std::string strInitial = str, strFinal;
    std::stringstream sstm;
    sstm<<strInitial<<n;

    strFinal = sstm.str();

    return strFinal;
}

std::string ConcatenateString(const std::string& str_1, const std::string& str_2)
{
    std::string strFinal;
    std::stringstream sstm;
    sstm<<str_1<<str_2;

    strFinal = sstm.str();

    return strFinal;
}
