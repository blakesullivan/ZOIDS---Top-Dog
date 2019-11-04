//Blake Sullivan - HUD.cpp
#include "HUD.h"

HUD::HUD()
{
	m_Avatar = NULL;
}

void HUD::Init(Character* c)
{
	m_Char = c;

	string sTempName = m_Char->GetSurfaceName();
	m_Avatar = NULL;
	sTempName.replace(sTempName.find("."), 1, "P.");
	m_Avatar = SDL_LoadBMP(sTempName.c_str());

}
void HUD::Dispose()
{
	SDL_FreeSurface(m_Avatar);
}

void HUD::Draw(SDL_Surface* screen)
{
	int iTopPos = screen->clip_rect.h - 100;
	string sTempLine = "";
	char buffer[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

	//Background
	boxRGBA(screen, 0, iTopPos, 300, iTopPos + 100, 255, 255, 255, 150);
	//Avatar
	SDL_Rect dclip;
	dclip.x = 0; dclip.y = iTopPos;
	dclip.w = 100; dclip.h = 100;
	SDL_BlitSurface(m_Avatar, NULL, screen, &dclip);

	//Text
	// - Name
	sTempLine = "Pilot: ";
	sTempLine += m_Char->GetName();
	stringRGBA(screen, 100, iTopPos + 10, sTempLine.c_str(), 0, 0, 0, 255);
	// - Score
	sTempLine = "Score: ";
	sTempLine += "0"; //itoa(m_Char->GetScore(), buffer, 10);
	stringRGBA(screen, 100, iTopPos + 30, sTempLine.c_str(), 0, 0, 0, 255);
	// - Health
	sTempLine = "Health: ";
	sTempLine += itoa(m_Char->GetStats()->GetHealth(), buffer, 10);
	sTempLine += " / ";
	sTempLine += itoa(m_Char->GetStats()->GetMaxHealth(), buffer, 10);
	stringRGBA(screen, 100, iTopPos + 50, sTempLine.c_str(), 0, 0, 0, 255);
	// - Ammo
	sTempLine = "Ammo: ";
	sTempLine += itoa(m_Char->GetStats()->GetBulletsLeft(), buffer, 10);
	stringRGBA(screen, 100, iTopPos + 70, sTempLine.c_str(), 0, 0, 0, 255);
	// - Energy
	if (m_Char->GetCharID() > cidPteras)
		{sTempLine = "Energy: ";}
	else
		{sTempLine = "Missiles: ";}
	sTempLine += itoa(m_Char->GetStats()->GetEnergy(), buffer, 10);
	stringRGBA(screen, 190, iTopPos + 70, sTempLine.c_str(), 0, 0, 0, 255);
}