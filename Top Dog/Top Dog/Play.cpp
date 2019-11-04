//Blake Sullivan - Play.cpp
#include "Play.h"

Play::Play()
{
	Init();
}

Play::Play(MyText* mt)
{
	m_pMT = mt;
	Init();
}

void Play::Init()
{
	m_iIsRunning = sceneRunning;

	m_pBM = new ButtonManager(m_pMT);
	AddAndSetButtons();
}

void Play::Update(SDL_Surface* screen, float fDeltaTime)
{
	if (m_bKeysHeld[SDLK_BACKSPACE])
		{m_iIsRunning = sceneMenu;}
	ManageButtons();
}

void Play::Draw(SDL_Surface* screen, float fDeltaTime)
{
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 200, 200, 0) ); 
	//stringRGBA(screen, 300, 290, "Play!", 0, 0, 0, 255);
	//stringRGBA(screen, 250, 310, "Press backspace to go back to Menu", 0, 0, 0, 255);
	m_pBM->DrawButton(screen);
}

//int Play::Status()
//{
//	return m_iIsRunning;
//}

void Play::Dispose()
{
	delete m_pBM;
}

void Play::MouseUpEvent(SDL_Event* event)
{
	Scene::MouseUpEvent(event);
}
void Play::MouseDownEvent (SDL_Event* event)
{
	Scene::MouseDownEvent(event);
}
void Play::KeyUpEvent(SDL_Event* event)
{
	Scene::KeyUpEvent(event);
}
void Play::KeyDownEvent(SDL_Event* event)
{
	Scene::KeyDownEvent(event);
}

void Play::AddAndSetButtons()
{
	Colours colD, colH, colP;
	colD.iRed = 128; colD.iGreen = 128; colD.iBlue = 128; colD.iAlpha = 255;
	colH.iRed = 255; colH.iGreen = 255; colH.iBlue = 130; colH.iAlpha = 100;
	colP.iRed = 255; colP.iGreen = 0; colP.iBlue = 0; colP.iAlpha = 255;

	m_pBM->AddButton(300, 500, "Result", 90, 30, true, true, colD, colH, colP, true, sceneResult);
}

void Play::UpdateButtons()
{
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	m_pBM->UpdateButton(mouseX, mouseY);
	if (m_bButtonHeld[SDL_BUTTON_LEFT] == true)
		{m_pBM->ButtonPressed(mouseX, mouseY);}
}

void Play::ManageButtons()
{
	UpdateButtons();

	int iButtonPressed = m_pBM->CheckButtonPressed();

	if (m_bKeysHeld[SDLK_ESCAPE] || iButtonPressed == buttonExit)
		{m_iIsRunning = sceneQuit;}
	else if (iButtonPressed == sceneResult)
		{m_iIsRunning = sceneResult;}

	if (m_iIsRunning != sceneRunning)
		{m_pBM->ButtonUnPressed(iButtonPressed);}
}