//Blake Sullivan - HUD.h
#ifndef HUD_H
#define HUD_H

#include "SDL_gfxPrimitives.h"
#include "Character.h"

class HUD
{
private:
	SDL_Surface* m_Avatar;
	Character* m_Char;

public:
	HUD();

	void Init(Character* c);
	void Dispose();

	void Draw(SDL_Surface* screen);

};
#endif