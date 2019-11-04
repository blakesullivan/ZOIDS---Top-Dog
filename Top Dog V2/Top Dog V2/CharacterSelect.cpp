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

	m_Characters = NULL;
	m_Characters = SDL_LoadBMP("C.bmp");
	SDL_SetColorKey(m_Characters, SDL_SRCCOLORKEY, SDL_MapRGB(m_Characters->format, 0, 64, 64));

	m_Avatars = NULL;
	m_Avatars = SDL_LoadBMP("A.bmp");

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
	DrawCharacters(screen);
	m_pBM->DrawButton(screen);
}
//int CharacterSelect::Status()
//{
//	return m_iIsRunning;
//}
void CharacterSelect::Dispose()
{
	SDL_FreeSurface(m_Avatars);
	SDL_FreeSurface(m_Characters);
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

	cN.iRed = 0; cN.iGreen = 148; cN.iBlue = 255; cN.iAlpha = 50;
	cH.iRed = 150; cH.iGreen = 150; cH.iBlue = 0; cH.iAlpha = 255;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;

	m_pBM->AddButton(410, 700, "BACK", 100, 30, true, true, cN, cH, cD, false, sceneJoin);
	m_pBM->AddButton(514, 700, "PLAY", 100, 30, true, true, cN, cH, cD, false, scenePlay);

	m_pBM->AddButton(390, 200, "SELECT", 100, 30, true, true, cN, cH, cD, false, 10);
	m_pBM->AddButton(390, 400, "SELECT", 100, 30, true, true, cN, cH, cD, false, 11);
	m_pBM->AddButton(390, 600, "SELECT", 100, 30, true, true, cN, cH, cD, false, 12);

	m_pBM->AddButton(534, 200, "SELECT", 100, 30, true, true, cN, cH, cD, false, 13);
	m_pBM->AddButton(534, 400, "SELECT", 100, 30, true, true, cN, cH, cD, false, 14);
	m_pBM->AddButton(534, 600, "SELECT", 100, 30, true, true, cN, cH, cD, false, 15);


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

void CharacterSelect::DrawCharacters(SDL_Surface* screen)
{
	SDL_Rect sclip, dclip;
	int iPosX[6] = {0,0,0,0,0,0};
	int iPosY[6] = {0,0,0,0,0,0};

	int iAvPosX[6] = {0,0,0,0,0,0};
	int iAvPosY[6] = {0,0,0,0,0,0};

	iPosX[0] = 0; iPosY[0] = 140;
	iPosX[1] = -35; iPosY[1] = 350;
	iPosX[2] = -30; iPosY[2] = 560;
	iPosX[3] = 855; iPosY[3] = 140;
	iPosX[4] = 835; iPosY[4] = 350;
	iPosX[5] = 845; iPosY[5] = 560;

	iAvPosX[0] = 1; iAvPosY[0] = 240;
	iAvPosX[1] = 1; iAvPosY[1] = 450;
	iAvPosX[2] = 1; iAvPosY[2] = 660;
	iAvPosX[3] = 937; iAvPosY[3] = 240;
	iAvPosX[4] = 928; iAvPosY[4] = 450;
	iAvPosX[5] = 940; iAvPosY[5] = 660;

	//Background
	for (int i = 0; i < 3; i++)
	{
		boxRGBA(screen, 0, iPosY[i], 375, iPosY[i] + 200, 232, 242, 213, 255);
		boxRGBA(screen, 1024-375, iPosY[i], 1023, iPosY[i] + 200, 232, 242, 213, 255);
	}

	//Pictures
	for (int i = 0; i < 6; i++)
	{
		sclip.x = i * 96; sclip.y = 0; sclip.w = 96; sclip.h = 100;
		dclip.x = iAvPosX[i]; dclip.y = iAvPosY[i]; dclip.w = sclip.w; dclip.h = sclip.h;
		SDL_BlitSurface(m_Avatars, &sclip, screen, &dclip);

		sclip.x = i * 215; sclip.y = 0; sclip.w = 215; sclip.h = 100;
		dclip.x = iPosX[i]; dclip.y = iPosY[i]; dclip.w = sclip.w; dclip.h = sclip.h;
		SDL_BlitSurface(m_Characters, &sclip, screen, &dclip);
	}

	//Borders
	for (int i = 0; i < 3; i++)
	{
		rectangleRGBA(screen, 0, iPosY[i], 375, iPosY[i] + 200, 0, 0, 0, 255);
		rectangleRGBA(screen, 1024-375, iPosY[i], 1023, iPosY[i] + 200, 0, 0, 0, 255);
	}
}