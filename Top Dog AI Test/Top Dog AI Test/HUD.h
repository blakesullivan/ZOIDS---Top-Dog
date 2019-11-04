//Blake Sullivan - HUD.h
#ifndef HUD_H
#define HUD_H

#include "SDL_gfxPrimitives.h"
#include "Character.h"
#include "MyText.h"

class HUD
{
private:
	SDL_Surface* m_Avatar;
	Character* m_Char;
	MyText* m_pMT;

public:
	HUD();

	void Init(Character* c, MyText* mt);
	void Dispose();

	void Draw(SDL_Surface* screen);
	void DrawTimer(SDL_Surface* screen, float Time);
	void DrawFrameRate(SDL_Surface* screen);
};
#endif