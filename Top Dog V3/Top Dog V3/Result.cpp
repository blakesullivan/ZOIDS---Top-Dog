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
	m_Background = IMG_Load("Images/Menu.png");

	m_Avatars = NULL;
	m_Avatars = IMG_Load("Images/Avatars.png");

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

	//Background
	boxRGBA(screen, 150, 200, 874, 510, 232, 242, 213, 255);

	//Avatars
	DrawAvatars(screen);

	//Border
	rectangleRGBA(screen, 150, 200, 874, 510, 0, 0, 0, 255);

	m_pBM->DrawButton(screen);
}

void Result::DrawAvatars(SDL_Surface* screen)
{
	int iAvX[6], iAvY[6];
	SDL_Rect sclip, dclip;

	iAvX[0] = 150; iAvY[0] = 200;
	iAvX[1] = 150; iAvY[1] = 305;
	iAvX[2] = 150; iAvY[2] = 410;

	iAvX[3] = 778; iAvY[3] = 200;
	iAvX[4] = 778; iAvY[4] = 305;
	iAvX[5] = 778; iAvY[5] = 410;

	for (int i = 0; i < 6; i++)
	{
		sclip.x = i * 96; sclip.y = 0; sclip.w = 96; sclip.h = 100;
		dclip.x = iAvX[i]; dclip.y = iAvY[i]; dclip.w = 96; dclip.h = 100;
		SDL_BlitSurface(m_Avatars, &sclip, screen, &dclip);

	}
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

	cN.iRed = 0; cN.iGreen = 148; cN.iBlue = 255; cN.iAlpha = 50;
	cH.iRed = 0; cH.iGreen = 0; cH.iBlue = 0; cH.iAlpha = 150;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;

	m_pBM->AddButton(357, 730, "To Menu", 100, 30, true, true, cN, cH, cD, false, sceneMenu);
	m_pBM->AddButton(462, 730, "To Join", 100, 30, true, true, cN, cH, cD, false, sceneJoin);
	m_pBM->AddButton(567, 730, "To Host", 100, 30, true, true, cN, cH, cD, false, sceneHost);
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