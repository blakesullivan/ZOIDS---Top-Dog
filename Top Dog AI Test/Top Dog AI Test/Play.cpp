//Blake Sullivan - Play.cpp
#include "Play.h"

Play::Play()
{
	Init();
}

Play::Play(MyText* mt, NetworkClient* nc, SoundManager* sm)
{
	m_pMT = mt;
	m_pNC = nc;
	m_pSM = sm;
	Init();
}

void Play::Init()
{
	m_iIsRunning = sceneRunning;

	m_pBM = new ButtonManager(m_pMT);
	AddAndSetButtons();

	m_fTimer = 300;
	SetupLevel();
	m_fWindowX = 0; m_fWindowY = 0;
}

void Play::Update(SDL_Surface* screen, float fDeltaTime)
{
	static bool bEnergyStarted = false;
	if (m_bKeysHeld[SDLK_BACKSPACE])
		{m_iIsRunning = sceneMenu;}

	m_fTimer -= fDeltaTime;
	if (m_fTimer <= 0) {m_iIsRunning = sceneResult;}

	if (m_pNC->Receive())
	{
		ResponseToReceive();
	}

	ManageButtons();

	m_pLevel->Update(fDeltaTime);
	//do something
	if (m_pLevel->GetCharacter(m_iMyID)->GetState() == stateAlive)
	{
		bool bMoved = false;
		if (m_bKeysHeld[SDLK_UP] == true || m_bKeysHeld[SDLK_w] == true)
			{m_pLevel->GetCharacter(m_iMyID)->MoveCharacter('u', fDeltaTime); bMoved = true;}

		if (m_bKeysHeld[SDLK_DOWN] == true || m_bKeysHeld[SDLK_s] == true)
			{m_pLevel->GetCharacter(m_iMyID)->MoveCharacter('d', fDeltaTime); bMoved = true;}

		if (m_bKeysHeld[SDLK_LEFT] == true || m_bKeysHeld[SDLK_a] == true)
			{m_pLevel->GetCharacter(m_iMyID)->MoveCharacter('q', fDeltaTime); bMoved = true;}

		if (m_bKeysHeld[SDLK_RIGHT] == true || m_bKeysHeld[SDLK_d] == true)
			{m_pLevel->GetCharacter(m_iMyID)->MoveCharacter('e', fDeltaTime); bMoved = true;}

		if (m_bKeysHeld[SDLK_q] == true)
			{m_pLevel->GetCharacter(m_iMyID)->MoveCharacter('l', fDeltaTime); bMoved = true;}

		if (m_bKeysHeld[SDLK_e] == true)
			{m_pLevel->GetCharacter(m_iMyID)->MoveCharacter('r', fDeltaTime); bMoved = true;}

		if (bMoved == true)
		{
			//SendCharacterPos();
		}

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
			m_HUD.Init(m_pLevel->GetCharacter(m_iMyID), m_pMT);
		}

		if (m_bButtonHeld[SDL_BUTTON_LEFT] == true)
		{
			m_pLevel->AddBullet(m_iMyID);
			//SendBullet();
			m_bButtonHeld[SDL_BUTTON_LEFT] = false;
		}

		if (m_bButtonHeld[SDL_BUTTON_RIGHT] == true)
		{
			if (m_iMyID <= cidPteras)
			{m_bButtonHeld[SDL_BUTTON_RIGHT] = false;}
			if (bEnergyStarted == false)
			{
				m_pLevel->StartEnergy(m_iMyID);
				bEnergyStarted = true;
			}
		}
		if (m_bButtonHeld[SDL_BUTTON_RIGHT] == false)
		{
			m_pLevel->StopEnergy(m_iMyID);
			bEnergyStarted = false;
		}
	}

}

void Play::Draw(SDL_Surface* screen, float fDeltaTime)
{
	//SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 200, 200, 0) ); 
	//stringRGBA(screen, 300, 290, "Play!", 0, 0, 0, 255);
	//stringRGBA(screen, 250, 310, "Press backspace to go back to Menu", 0, 0, 0, 255);
	m_pLevel->Draw(screen, fDeltaTime);
	m_HUD.Draw(screen);
	m_HUD.DrawTimer(screen, m_fTimer);
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
	cH.iRed = 0; cH.iGreen = 0; cH.iBlue = 0; cH.iAlpha = 150;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;

	m_pBM->AddButton(500, 730, "Result", 90, 30, true, true, cN, cH, cD, true, sceneResult);
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

void Play::SetupLevel()
{
	m_iMyID = m_pNC->GetCharSelected();
	m_pLevel = new Level(m_pSM);
	m_pLevel->Init(m_iMyID, m_pNC->GetIsHost());
	m_pLevel->SetupMap(m_pNC->GetMapID(), 1024*2, 768*2);
	SetupCharacters();
	m_pLevel->SetupPickups();
	m_HUD.Init(m_pLevel->GetCharacter(m_iMyID), m_pMT);
	m_pSM->PlayMusic(m_pNC->GetMapID(), 30);
}

void Play::SetupCharacters()
{
	char buffer[10] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	bool bCharUsed[6] = {false, false, false, false, false, false};
	for (int i = 0; i < 6; i++)
	{
		if (m_pNC->GetCharacter(i).charID >= 0)
		{
			bCharUsed[m_pNC->GetCharacter(i).charID] = true;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (bCharUsed[i] == true)
		{
			for (int j = 0; j < 6; j++)
			{
				if (m_pNC->GetCharacter(j).charID == i)
				{
					m_pLevel->AddCharacter(m_pNC->GetCharacter(j).charID, m_pNC->GetCharacter(j).playerName, false);
				}
			}
		}
		else
		{
			string tempName = "Bot#";
			tempName.replace(tempName.find("#"), 1, itoa(i+1, buffer, 10));
			m_pLevel->AddCharacter(i, tempName, true);
		}
	}
}

void Play::ResponseToReceive()
{
	//cout << "Packet ID: " << m_pNC->GetPacketReceived()->id << endl;
	if (m_pNC->GetPacketReceived()->id == PLAYER_UPDATE)
	{
		movePacket* mData = (movePacket*)m_pNC->GetNetworkManager()->GetPacket()->data;
		m_pLevel->UpdateCharacterPos(m_pNC->GetCharacter(mData->userID).charID, mData->x, mData->y, mData->dir);
	}
	else if (m_pNC->GetPacketReceived()->id == PLAYER_SHOOT)
	{
		bulletPacket* bData = (bulletPacket*)m_pNC->GetNetworkManager()->GetPacket()->data;
		m_pLevel->AddBullet(m_pNC->GetCharacter(bData->userID).charID);
	}
}

void Play::SendCharacterPos()
{
	movePacket* mData = new movePacket();

	mData->id = PLAYER_UPDATE;
	mData->userID = m_pNC->GetServerID();
	mData->x = m_pLevel->GetCharacter(m_iMyID)->GetX();
	mData->y = m_pLevel->GetCharacter(m_iMyID)->GetY();
	mData->dir = m_pLevel->GetCharacter(m_iMyID)->GetStats()->GetDirection();

	m_pNC->Send((basePacket*)mData, sizeof(*mData));

	delete[] mData;
}

void Play::SendBullet()
{
	bulletPacket* bData = new bulletPacket();

	bData->id = PLAYER_SHOOT;
	bData->userID = m_pNC->GetServerID();

	m_pNC->Send((basePacket*)bData, sizeof(*bData));
	delete[] bData;
}