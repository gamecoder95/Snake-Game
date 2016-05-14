#include "SoundEffect.h"

void SoundEffect::playSound(const std::string& strFileName)
{
    if(m_strFileName != strFileName)
    {
        m_strFileName = strFileName;
        buffer.loadFromFile(strFileName);
        sound.setBuffer(buffer);
    }
    sound.play();
}

void SoundEffect::playCrunchSound()
{
    playSound("appleCrunchOne.wav");
}

sf::SoundBuffer SoundEffect::buffer;
sf::Sound SoundEffect::sound;
std::string SoundEffect::m_strFileName = "";
