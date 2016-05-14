#ifndef FADINGOBJECT_H
#define FADINGOBJECT_H

#include "VisibleGameObject.h"
#include "ImportantHeaders.h"
#include "Game.h"

class FadingObject : public VisibleGameObject
{
    private:
        bool m_bFaded;
        float m_fFadeOpacity;
        const int MAX_ALPHA;

        bool GetFadeOpacity();
        void SetFadeOpacity(bool fFadeOpacity);

    public:
        FadingObject(std::string strID, std::string strSprFileName);
        FadingObject(std::string strID, std::string strSprFileName, float fFadeOpacity, float fXPos, float fYPos);
        FadingObject(std::string strID, std::string strSprFileName, float fFadeOpacity, float fXPos, float fYPos, bool bFaded);
        virtual ~FadingObject();
        bool IsFaded();
        void SetFaded(bool bFaded);
        void Fade();
        void Update(float fElapsedTime);

};

//this is for the button
void FadeObject(FadingObject* pcFadingObj, bool bFade);
FadingObject* GetFadingObject(std::string strID);

#endif // FADINGOBJECT_H
