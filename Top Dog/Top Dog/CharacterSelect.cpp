//Blake Sullivan - CharacterSelect.cpp
#include "CharacterSelect.h"

CharacterSelect::CharacterSelect()
{
	Init();
}
CharacterSelect::CharacterSelect(MyText* mt)
{
	m_pMT = mt;
	Init();
}

void CharacterSelect::Init()
{
	m_iIsRunning = sceneRunning;
	m_pBM = new ButtonManager(m_pMT);

	m_Background = NULL;
	m_Background = SDL_LoadBMP("Menu.bmp");

	AddButtons();
}
void CharacterSelect::Update(SDL_Surface* screen, float fDeltaTime)
{
	UpdateButtons();
	ManageButtonPress();
}
void CharacterSelect::Draw(SDL_Surface* screen, float fDeltaTime)
{
	//SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 50, 200, 200));
	SDL_BlitSurface(m_Background, NULL, screen, NULL);
	m_pBM->DrawButton(screen);
}
//int CharacterSelect::Status()
//{
//	return m_iIsRunning;
//}
void CharacterSelect::Dispose()
{
	SDL_FreeSurface(m_Background);
	delete m_pBM;
}

void CharacterSelect::MouseUpEvent(SDL_Event* event)
{
	Scene::MouseUpEvent(event);
}
void CharacterSelect::MouseDownEvent (SDL_Event* event)
{
	Scene::MouseDownEvent(event);
}
void CharacterSelect::KeyUpEvent(SDL_Event* event)
{
	Scene::KeyUpEvent(event);
}
void CharacterSelect::KeyDownEvent(SDL_Event* event)
{
	Scene::KeyDownEvent(event);
}

void CharacterSelect::AddButtons()
{
	Colours cN, cH, cD;

	cN.iRed = 150; cN.iGreen = 050; cN.iBlue = 150; cN.iAlpha = 255;
	cH.iRed = 150; cH.iGreen = 150; cH.iBlue = 0; cH.iAlpha = 255;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;

	m_pBM->AddButton(300, 450, "To Join", 100, 30, true, true, cN, cH, cD, false, sceneJoin);
	m_pBM->AddButton(300, 490, "To Play", 100, 30, true, true, cN, cH, cD, false, scenePlay);
}
void CharacterSelect::UpdateButtons()
{
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	m_pBM->UpdateButton(mouseX, mouseY);
	if (m_bButtonHeld[SDL_BUTTON_LEFT] == true)
		{m_pBM->ButtonPressed(mouseX, mouseY);}
}
void CharacterSelect::ManageButtonPress()
{
	int iButtonPressed = m_pBM->CheckButtonPressed();

	if (m_bKeysHeld[SDLK_ESCAPE] == true || m_bKeysHeld[SDLK_BACKSPACE] == true)
		{m_iIsRunning = sceneMenu;}
	if (iButtonPressed == sceneJoin)
		{m_iIsRunning = sceneJoin;}
	if (iButtonPressed == scenePlay)
		{m_iIsRunning = scenePlay;}

	if (m_iIsRunning != sceneRunning)
		{m_pBM->ButtonUnPressed(iButtonPressed);}
}