//Blake Sullivan - HUD.cpp
#include "HUD.h"

HUD::HUD()
{
	m_Avatar = NULL;
}

void HUD::Init(Character* c, MyText* mt)
{
	m_Char = c;

	string sTempName = m_Char->GetSurfaceName();
	m_Avatar = NULL;
	sTempName.replace(sTempName.find("."), 1, "P.");
	m_Avatar = IMG_Load(sTempName.c_str());

	m_pMT = mt;

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

	DrawFrameRate(screen);

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

void HUD::DrawTimer(SDL_Surface* screen, float Time)
{
	string sTempLine = "";
	char buffer[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	int timeBuff = 5;

	if (Time * 100 < 100) {timeBuff = 2;}
	else if (Time * 100 < 1000) {timeBuff = 3;}
	else if (Time * 100 < 10000) {timeBuff = 4;}
	
	//Timer
	boxRGBA(screen, (screen->clip_rect.w / 2) - 50, 0, (screen->clip_rect.w / 2) + 50, 30, 0, 0, 0, 150);
	rectangleRGBA(screen, (screen->clip_rect.w / 2) - 50, 0, (screen->clip_rect.w / 2) + 50, 30, 0, 0, 0, 255);
	
	sTempLine = gcvt(Time * 100, timeBuff, buffer);
	m_pMT->Print(screen, (screen->clip_rect.w / 2) - 25, 5, sTempLine, 255, 255, 255);
	//stringRGBA(screen, (screen->clip_rect.w / 2) - 49, 10, sTempLine.c_str(), 255, 255, 255, 255);
}

void HUD::DrawFrameRate(SDL_Surface* screen)
{
	static int siFrameRate = 0, siLastTick = 0, siLastFrameRate = 0;
	string sTemp = "FPS: "; char buffer[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	if (SDL_GetTicks() - siLastTick >= 1000)
	{
		siLastFrameRate = siFrameRate;
		siFrameRate = 0;
		siLastTick = SDL_GetTicks();
	}
	boxRGBA(screen, screen->clip_rect.w - 100, screen->clip_rect.h - 20, screen->clip_rect.w, screen->clip_rect.h, 0, 0, 0, 150);
	rectangleRGBA(screen, screen->clip_rect.w - 100, screen->clip_rect.h - 20, screen->clip_rect.w, screen->clip_rect.h, 0, 0, 0, 255);

	sTemp += itoa(siLastFrameRate, buffer, 10);
	m_pMT->Print(screen, screen->clip_rect.w - 100, screen->clip_rect.h - 20, sTemp, 255, 255, 255);
	siFrameRate++;
}