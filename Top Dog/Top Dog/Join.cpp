//Blake Sullivan - Join.cpp
#include "Join.h"

Join::Join()
{
	Init();
}
Join::Join(MyText* mt)
{
	m_pMT = mt;
	Init();
}

void Join::Init()
{
	m_iIsRunning = sceneRunning;
	m_pBM = new ButtonManager(m_pMT);

	m_Background = NULL;
	m_Background = SDL_LoadBMP("Menu.bmp");

	AddButtons();
}
void Join::Update(SDL_Surface* screen, float fDeltaTime)
{
	UpdateButtons();
	ManageButtonPress();
}
void Join::Draw(SDL_Surface* screen, float fDeltaTime)
{
	//SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 20, 150, 20) );
	SDL_BlitSurface(m_Background, NULL, screen, NULL);
	m_pBM->DrawButton(screen);
}
//int Join::Status()
//{
//	return m_iIsRunning;
//}
void Join::Dispose()
{
	SDL_FreeSurface(m_Background);
	delete m_pBM;
}

void Join::MouseUpEvent(SDL_Event* event)
{
	Scene::MouseUpEvent(event);
}
void Join::MouseDownEvent (SDL_Event* event)
{
	Scene::MouseDownEvent(event);
}
void Join::KeyUpEvent(SDL_Event* event)
{
	Scene::KeyUpEvent(event);
}
void Join::KeyDownEvent(SDL_Event* event)
{
	Scene::KeyDownEvent(event);
}

void Join::AddButtons()
{
	Colours cN, cH, cD;

	cN.iRed = 150; cN.iGreen = 050; cN.iBlue = 150; cN.iAlpha = 255;
	cH.iRed = 150; cH.iGreen = 150; cH.iBlue = 0; cH.iAlpha = 255;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;

	m_pBM->AddButton(300, 450, "Menu", 100, 30, true, true, cN, cH, cD, false, sceneMenu);
	m_pBM->AddButton(300, 490, "Character", 100, 30, true, true, cN, cH, cD, false, sceneCharacter);
}
void Join::UpdateButtons()
{
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	m_pBM->UpdateButton(mouseX, mouseY);
	if (m_bButtonHeld[SDL_BUTTON_LEFT] == true)
		{m_pBM->ButtonPressed(mouseX, mouseY);}
}

void Join::ManageButtonPress()
{
	int iButtonPressed = m_pBM->CheckButtonPressed();

	if (m_bKeysHeld[SDLK_ESCAPE] == true || m_bKeysHeld[SDLK_BACKSPACE] == true)
		{m_iIsRunning = sceneMenu;}
	if (iButtonPressed == sceneMenu)
		{m_iIsRunning = sceneMenu;}
	if (iButtonPressed == sceneCharacter)
		{m_iIsRunning = sceneCharacter;}

	if (m_iIsRunning != sceneRunning)
		{m_pBM->ButtonUnPressed(iButtonPressed);}
}