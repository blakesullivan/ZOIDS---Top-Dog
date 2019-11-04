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

	m_iMyID = cidPteras;
	m_pLevel = new Level();
	m_pLevel->Init(m_iMyID);
	m_fWindowX = 0; m_fWindowY = 0;
}

void Play::Update(SDL_Surface* screen, float fDeltaTime)
{
	if (m_bKeysHeld[SDLK_BACKSPACE])
		{m_iIsRunning = sceneMenu;}
	ManageButtons();

	m_pLevel->Update(fDeltaTime);
	//do something
	if (m_bKeysHeld[SDLK_UP] == true || m_bKeysHeld[SDLK_w] == true)
		{m_pLevel->GetCharacter(m_iMyID)->MoveCharacter('u', fDeltaTime);}

	if (m_bKeysHeld[SDLK_DOWN] == true || m_bKeysHeld[SDLK_s] == true)
		{m_pLevel->GetCharacter(m_iMyID)->MoveCharacter('d', fDeltaTime);}

	if (m_bKeysHeld[SDLK_LEFT] == true || m_bKeysHeld[SDLK_a] == true)
		{m_pLevel->GetCharacter(m_iMyID)->MoveCharacter('l', fDeltaTime);}

	if (m_bKeysHeld[SDLK_RIGHT] == true || m_bKeysHeld[SDLK_d] == true)
		{m_pLevel->GetCharacter(m_iMyID)->MoveCharacter('r', fDeltaTime);}

	if (m_bKeysHeld[SDLK_q] == true)
		{m_pLevel->GetCharacter(m_iMyID)->MoveCharacter('q', fDeltaTime);}

	if (m_bKeysHeld[SDLK_e] == true)
		{m_pLevel->GetCharacter(m_iMyID)->MoveCharacter('e', fDeltaTime);}

	m_fWindowX = m_pLevel->GetCharacter(m_iMyID)->GetX() - (screen->clip_rect.w/2);
	m_fWindowY = m_pLevel->GetCharacter(m_iMyID)->GetY() - (screen->clip_rect.h/2);
	m_pLevel->UpdateWindowPos(m_fWindowX, m_fWindowY);

	if (m_bKeysHeld[SDLK_c] == true)
	{
		m_bKeysHeld[SDLK_c] = false;
		if (m_iMyID < cidZabat)
			{m_iMyID++;}
		else
			{m_iMyID = cidBuster;}
	}

	if (m_bButtonHeld[SDL_BUTTON_LEFT] == true)
	{
		m_pLevel->AddBullet(m_iMyID);
		m_bButtonHeld[SDL_BUTTON_LEFT] = false;
	}

	if (m_bButtonHeld[SDL_BUTTON_RIGHT] == true)
	{
		if (m_iMyID <= cidPteras)
		{m_bButtonHeld[SDL_BUTTON_RIGHT] = false;}
		m_pLevel->StartEnergy(m_iMyID);
	}
	if (m_bButtonHeld[SDL_BUTTON_RIGHT] == false)
	{
		m_pLevel->StopEnergy(m_iMyID);
	}

}

void Play::Draw(SDL_Surface* screen, float fDeltaTime)
{
	//SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 200, 200, 0) ); 
	//stringRGBA(screen, 300, 290, "Play!", 0, 0, 0, 255);
	//stringRGBA(screen, 250, 310, "Press backspace to go back to Menu", 0, 0, 0, 255);
	m_pLevel->Draw(screen, fDeltaTime);
	m_pBM->DrawButton(screen);
}

//int Play::Status()
//{
//	return m_iIsRunning;
//}

void Play::Dispose()
{
	delete m_pLevel;
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
	Colours cN, cH, cD;
	cN.iRed = 0; cN.iGreen = 148; cN.iBlue = 255; cN.iAlpha = 50;
	cH.iRed = 150; cH.iGreen = 150; cH.iBlue = 0; cH.iAlpha = 255;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;

	m_pBM->AddButton(300, 500, "Result", 90, 30, true, true, cN, cH, cD, true, sceneResult);
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