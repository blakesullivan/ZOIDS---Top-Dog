//Blake Sullivan - Host.cpp
#include "Options.h"

Options::Options()
{
	Init();
}
Options::Options(MyText* mt)
{
	m_pMT = mt;
	Init();
}

void Options::Init()
{
	m_iIsRunning = sceneRunning;
	m_pBM = new ButtonManager(m_pMT);

	m_Background = NULL;
	m_Background = SDL_LoadBMP("Menu.bmp");

	m_Instructions = NULL;
	m_Instructions = SDL_LoadBMP("I.bmp");
	SDL_SetColorKey(m_Instructions, SDL_SRCCOLORKEY, SDL_MapRGB(m_Instructions->format, 255, 0, 255));

	AddButtons();
}
void Options::Update(SDL_Surface* screen, float fDeltaTime)
{
	UpdateButtons();
	ManageButtonPress();
}
void Options::Draw(SDL_Surface* screen, float fDeltaTime)
{
	//SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 200) );
	SDL_BlitSurface(m_Background, NULL, screen, NULL);

	boxRGBA(screen, 62, 150, 962, 725, 255, 255, 255, 150);
	SDL_Rect dclip;
	dclip.x = 62; dclip.y = 150;
	dclip.w = 900; dclip.h = 575;
	SDL_BlitSurface(m_Instructions, NULL, screen, &dclip);

	rectangleRGBA(screen, 62, 150, 962, 725, 0, 0, 0, 255);

	m_pBM->DrawButton(screen);
}
//int Options::Status()
//{
//	return m_iIsRunning;
//}
void Options::Dispose()
{
	SDL_FreeSurface(m_Background);
	SDL_FreeSurface(m_Instructions);
	delete m_pBM;
}

void Options::MouseUpEvent(SDL_Event* event)
{
	Scene::MouseUpEvent(event);
}
void Options::MouseDownEvent (SDL_Event* event)
{
	Scene::MouseDownEvent(event);
}
void Options::KeyUpEvent(SDL_Event* event)
{
	Scene::KeyUpEvent(event);
}
void Options::KeyDownEvent(SDL_Event* event)
{
	Scene::KeyDownEvent(event);
}

void Options::AddButtons()
{
	Colours cN, cH, cD;

	cN.iRed = 0; cN.iGreen = 148; cN.iBlue = 255; cN.iAlpha = 50;
	cH.iRed = 0; cH.iGreen = 0; cH.iBlue = 0; cH.iAlpha = 150;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;

	m_pBM->AddButton(462, 730, "Back", 100, 30, true, true, cN, cH, cD, false, sceneMenu);
}
void Options::UpdateButtons()
{
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	m_pBM->UpdateButton(mouseX, mouseY);
	if (m_bButtonHeld[SDL_BUTTON_LEFT] == true)
		{m_pBM->ButtonPressed(mouseX, mouseY);}
}

void Options::ManageButtonPress()
{
	int iButtonPressed = m_pBM->CheckButtonPressed();

	if (m_bKeysHeld[SDLK_ESCAPE] == true || m_bKeysHeld[SDLK_BACKSPACE] == true)
		{m_iIsRunning = sceneMenu;}
	if (iButtonPressed == sceneMenu)
		{m_iIsRunning = sceneMenu;}

	if (m_iIsRunning != sceneRunning)
		{m_pBM->ButtonUnPressed(iButtonPressed);}
}