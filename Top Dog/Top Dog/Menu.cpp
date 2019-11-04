//Blake Sullivan - Splash.cpp
#include "Menu.h"

Menu::Menu()
{
	//Init();
}
Menu::Menu(MyText* mt)
{
	m_pBM = new ButtonManager(mt);
	Init();
}

void Menu::Init()
{
	m_iIsRunning = sceneRunning;

	m_Background = NULL;
	m_Background = SDL_LoadBMP("Menu.bmp");

	Colours cN, cH, cD;
	cN.iRed = 0; cN.iGreen = 148; cN.iBlue = 255; cN.iAlpha = 50;
	cH.iRed = 150; cH.iGreen = 150; cH.iBlue = 0; cH.iAlpha = 255;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;
	int iStartPos = 200, iButtSpace = 60;
	m_pBM->AddButton(400, iStartPos+(iButtSpace*0), "Join", 200, 50, true, true, cN, cH, cD, false, sceneJoin);
	m_pBM->AddButton(400, iStartPos+(iButtSpace*1), "Host", 200, 50, true, true, cN, cH, cD, false, sceneHost);
	m_pBM->AddButton(400, iStartPos+(iButtSpace*2), "Options", 200, 50, true, true, cN, cH, cD, false, sceneOptions);
	m_pBM->AddButton(400, iStartPos+(iButtSpace*3), "Exit", 200, 50, true, true, cN, cH, cD, false, buttonExit);
}

void Menu::Update(SDL_Surface* screen, float fDeltaTime)
{
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	m_pBM->UpdateButton(mouseX, mouseY);
	if (m_bButtonHeld[SDL_BUTTON_LEFT] == true)
		{m_pBM->ButtonPressed(mouseX, mouseY);}
	ManageMenu();
}

void Menu::Draw(SDL_Surface* screen, float fDeltaTime)
{
	//SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 200, 0) ); 
	SDL_BlitSurface(m_Background, NULL, screen, NULL);
	m_pBM->DrawButton(screen);
}

//int Menu::Status()
//{
//	return m_iIsRunning;
//}

void Menu::Dispose()
{
	SDL_FreeSurface(m_Background);
	delete m_pBM;
}

void Menu::MouseUpEvent(SDL_Event* event)
{
	Scene::MouseUpEvent(event);
}
void Menu::MouseDownEvent (SDL_Event* event)
{
	Scene::MouseDownEvent(event);
}
void Menu::KeyUpEvent(SDL_Event* event)
{
	Scene::KeyUpEvent(event);
}
void Menu::KeyDownEvent(SDL_Event* event)
{
	Scene::KeyDownEvent(event);
}

void Menu::ManageMenu()
{
	int iButtonPressed = m_pBM->CheckButtonPressed();

	if (m_bKeysHeld[SDLK_ESCAPE]  || iButtonPressed == buttonExit)
		{m_iIsRunning = sceneQuit;}
	else if (m_bKeysHeld[SDLK_0] || m_bKeysHeld[SDLK_KP0] || iButtonPressed == sceneSplash)
		{m_iIsRunning = sceneSplash;}
	else if (m_bKeysHeld[SDLK_1] || m_bKeysHeld[SDLK_KP1] || iButtonPressed == sceneMenu)
		{m_iIsRunning = sceneMenu;}
	else if (m_bKeysHeld[SDLK_2] || m_bKeysHeld[SDLK_KP2] || iButtonPressed == sceneOptions)
		{m_iIsRunning = sceneOptions;}
	else if (m_bKeysHeld[SDLK_3] || m_bKeysHeld[SDLK_KP3] || iButtonPressed == scenePlay)
		{m_iIsRunning = scenePlay;}
	else if (m_bKeysHeld[SDLK_4] || m_bKeysHeld[SDLK_KP4] || iButtonPressed == sceneHost)
		{m_iIsRunning = sceneHost;}
	else if (m_bKeysHeld[SDLK_5] || m_bKeysHeld[SDLK_KP5] || iButtonPressed == sceneJoin)
		{m_iIsRunning = sceneJoin;}
	else if (m_bKeysHeld[SDLK_6] || m_bKeysHeld[SDLK_KP6] || iButtonPressed == sceneCharacter)
		{m_iIsRunning = sceneCharacter;}
	else if (m_bKeysHeld[SDLK_7] || m_bKeysHeld[SDLK_KP7] || iButtonPressed == sceneResult)
		{m_iIsRunning = sceneResult;}

	if (m_iIsRunning != sceneRunning)
		{m_pBM->ButtonUnPressed(iButtonPressed);}
}