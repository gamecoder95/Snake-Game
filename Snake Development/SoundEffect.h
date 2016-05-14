#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include "ImportantHeaders.h"

class SoundEffect
{
    private:
        static sf::SoundBuffer buffer;
        static sf::Sound sound;
        static std::string m_strFileName;
        static void playSound(const std::string& strFileName);

    public:

        static void playCrunchSound();
};

#endif // SOUNDEFFECT_H
