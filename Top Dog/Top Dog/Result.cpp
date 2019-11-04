//Blake Sullivan - Result.cpp
#include "Result.h"

Result::Result()
{
	Init();
}
Result::Result(MyText* mt)
{
	m_pMT = mt;
	Init();
}

void Result::Init()
{
	m_iIsRunning = sceneRunning;
	m_pBM = new ButtonManager(m_pMT);

	m_Background = NULL;
	m_Background = SDL_LoadBMP("Menu.bmp");

	AddButtons();
}
void Result::Update(SDL_Surface* screen, float fDeltaTime)
{
	UpdateButtons();
	ManageButtonPress();
}
void Result::Draw(SDL_Surface* screen, float fDeltaTime)
{
	//SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 150, 200) );
	SDL_BlitSurface(m_Background, NULL, screen, NULL);
	m_pBM->DrawButton(screen);
}
//int Result::Status()
//{
//	return m_iIsRunning;
//}
void Result::Dispose()
{
	SDL_FreeSurface(m_Background);
	delete m_pBM;
}

void Result::MouseUpEvent(SDL_Event* event)
{
	Scene::MouseUpEvent(event);
}
void Result::MouseDownEvent (SDL_Event* event)
{
	Scene::MouseDownEvent(event);
}
void Result::KeyUpEvent(SDL_Event* event)
{
	Scene::KeyUpEvent(event);
}
void Result::KeyDownEvent(SDL_Event* event)
{
	Scene::KeyDownEvent(event);
}

void Result::AddButtons()
{
	Colours cN, cH, cD;

	cN.iRed = 150; cN.iGreen = 050; cN.iBlue = 150; cN.iAlpha = 255;
	cH.iRed = 150; cH.iGreen = 150; cH.iBlue = 0; cH.iAlpha = 255;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;

	m_pBM->AddButton(300, 450, "To Menu", 100, 30, true, true, cN, cH, cD, false, sceneMenu);
	m_pBM->AddButton(300, 490, "To Join", 100, 30, true, true, cN, cH, cD, false, sceneJoin);
	m_pBM->AddButton(300, 530, "To Host", 100, 30, true, true, cN, cH, cD, false, sceneHost);
}
void Result::UpdateButtons()
{
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	m_pBM->UpdateButton(mouseX, mouseY);
	if (m_bButtonHeld[SDL_BUTTON_LEFT] == true)
		{m_pBM->ButtonPressed(mouseX, mouseY);}
}

void Result::ManageButtonPress()
{
	int iButtonPressed = m_pBM->CheckButtonPressed();

	if (m_bKeysHeld[SDLK_ESCAPE] == true || m_bKeysHeld[SDLK_BACKSPACE] == true)
		{m_iIsRunning = sceneMenu;}
	if (iButtonPressed == sceneMenu)
		{m_iIsRunning = sceneMenu;}
	if (iButtonPressed == sceneJoin)
		{m_iIsRunning = sceneJoin;}
	if (iButtonPressed == sceneHost)
		{m_iIsRunning = sceneHost;}

	if (m_iIsRunning != sceneRunning)
		{m_pBM->ButtonUnPressed(iButtonPressed);}
}