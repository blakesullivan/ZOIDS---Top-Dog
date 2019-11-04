//Blake Sullivan - Splash.cpp
#include "Host.h"

Host::Host()
{
	m_iMapID = -1;
	Init();
}

Host::Host(MyText* mt, NetworkClient* nc)
{
	m_pNC = nc;
	m_pMT = mt;
	Init();
}

void Host::Init()
{
	//m_Background = NULL;
	//m_Background = SDL_LoadBMP("Roses.bmp");

	m_iIsRunning = sceneRunning;
	m_pBM = new ButtonManager(m_pMT);

	m_Background = NULL;
	m_Background = SDL_LoadBMP("Menu.bmp");

	m_Map = NULL;
	m_Map = SDL_LoadBMP("DM.bmp");

	AddMenuButtons();
	AddOptions();
}

void Host::Update(SDL_Surface* screen, float fDeltaTime)
{
	//if (m_bKeysHeld[SDLK_BACKSPACE])
		//{m_iIsRunning = sceneMenu;}

	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	m_pBM->UpdateButton(mouseX, mouseY);
	if (m_bButtonHeld[SDL_BUTTON_LEFT] == true)
	{
		m_pBM->ButtonPressed(mouseX, mouseY);
		if (m_pBM->FindButton(buttonName)->GetPressed() == true)
		{
			if (m_pBM->FindButton(buttonName)->GetText() == "Player")
			{
				m_pBM->FindButton(buttonName)->SetText("");
				//m_pNetworkClient->SetName("");
			}
		}
	}
	ManageButtonPress();
	//if (m_pNetworkClient->Receive())
	//{
	//	m_pBM->ButtonUnPressed(buttonHost);
	//	m_pBM->ButtonUnPressed(buttonJoin);
	//}
}

void Host::Draw(SDL_Surface* screen, float fDeltaTime)
{
	SDL_Rect sclip, dclip;
	//SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 200, 0, 0) ); 
	SDL_BlitSurface(m_Background, NULL, screen, NULL);

	//Map Image
	int x1 = 256, x2 = x1 + 512, y1 = 275, y2 = y1 + 384;
	boxRGBA(screen, x1, y1, x2, y2, 255, 255, 255, 150);

	if (m_iMapID >= 0)
	{
		//cout << "In Draw: MapID: " << m_iMapID << endl;
		sclip.x = 0; sclip.y = 0; sclip.w = 512; sclip.h = 384;
		dclip.x = x1; dclip.y = y1;	dclip.w = 512; dclip.h = 384;
		SDL_BlitSurface(m_Map, &sclip, screen, &dclip);
	}
	rectangleRGBA(screen, x1, y1, x2, y2, 0, 0, 0, 255);

	//Name
	m_pMT->Print(screen, 190, 675, "Player Name:", 255, 255, 255);

	m_pBM->DrawButton(screen);
	DrawText(screen);
}

//int Host::Status()
//{
//	return m_iIsRunning;
//}

void Host::Dispose()
{
	SDL_FreeSurface(m_Map);
	SDL_FreeSurface(m_Background);
	delete m_pBM;
}

void Host::MouseUpEvent(SDL_Event* event)
{
	Scene::MouseUpEvent(event);
}
void Host::MouseDownEvent (SDL_Event* event)
{
	Scene::MouseDownEvent(event);
}
void Host::KeyUpEvent(SDL_Event* event)
{
	Scene::KeyUpEvent(event);
}
void Host::KeyDownEvent(SDL_Event* event)
{
	Scene::KeyDownEvent(event);
}

void Host::ManageButtonPress()
{
	int iButtonPressed = m_pBM->CheckButtonPressed();

	if (m_bKeysHeld[SDLK_ESCAPE])
		{m_iIsRunning = sceneQuit;}
	/*else if (m_bKeysHeld[SDLK_0] || m_bKeysHeld[SDLK_KP0] || iButtonPressed == buttonSplash)
		{m_iIsRunning = sceneSplash;}
	else if (m_bKeysHeld[SDLK_2] || m_bKeysHeld[SDLK_KP2] || iButtonPressed == buttonHost)
		{m_iIsRunning = sceneHost;}*/
	if (iButtonPressed == sceneMenu)
		{m_iIsRunning = sceneMenu;}

	if (iButtonPressed == sceneJoin)
	{
		m_iIsRunning = sceneJoin;
		SetupHostWithServer();
		//m_pBM->ButtonUnPressed(iButtonPressed);
	}
	if (m_iIsRunning != sceneRunning)
		{m_pBM->ButtonUnPressed(iButtonPressed);}

	if (m_pBM->FindButton(buttonChat)->GetPressed())
	{
		m_pBM->ButtonUnPressed(buttonName);
		AddLetterToName(buttonChat);
		m_pBM->FindButton(buttonChat)->SetText(m_pNC->GetName());
	}

	if (m_pBM->FindButton(buttonName)->GetPressed())
	{
		m_pBM->ButtonUnPressed(buttonChat);
		AddLetterToName(buttonName);
		m_pBM->FindButton(buttonName)->SetText(GetServerName());
	}

	if (m_pBM->FindButton(buttonHost)->GetPressed() == true)
	{
		m_pBM->ButtonUnPressed(buttonHost);
		m_pBM->FindButton(buttonHost)->SetClickable(false);
		m_pBM->FindButton(buttonJoin)->SetClickable(false);
		//m_pNetworkClient->Send('h', m_pNetworkClient->GetName());
	}
	else if (m_pBM->FindButton(buttonJoin)->GetPressed() == true)
	{
		m_pBM->ButtonUnPressed(buttonJoin);
		m_pBM->FindButton(buttonHost)->SetClickable(false);
		m_pBM->FindButton(buttonJoin)->SetClickable(false);
		//m_pNetworkClient->Send('j', m_pNetworkClient->GetName());
	}

	if (m_pBM->FindButton(buttonDesert)->GetPressed() == true)
	{
		m_iMapID = buttonDesert - 10;
		//cout << "MapID: " << m_iMapID << endl;
		m_Map = NULL;
		m_Map = SDL_LoadBMP("DM.bmp");
		m_pBM->ButtonUnPressed(buttonDesert);
	}
	else if (m_pBM->FindButton(buttonForest)->GetPressed() == true)
	{
		m_iMapID = buttonForest - 10;
		//cout << "MapID: " << m_iMapID << endl;
		m_Map = NULL;
		m_Map = SDL_LoadBMP("FM.bmp");
		m_pBM->ButtonUnPressed(buttonForest);
	}
	else if (m_pBM->FindButton(buttonCity)->GetPressed() == true)
	{
		m_iMapID = buttonCity - 10;
		//cout << "MapID: " << m_iMapID << endl;
		m_Map = NULL;
		m_Map = SDL_LoadBMP("CM.bmp");
		m_pBM->ButtonUnPressed(buttonCity);
	}
	else if (m_pBM->FindButton(buttonLake)->GetPressed() == true)
	{
		m_iMapID = buttonLake - 10;
		//cout << "MapID: " << m_iMapID << endl;
		m_Map = NULL;
		m_Map = SDL_LoadBMP("LM.bmp");
		m_pBM->ButtonUnPressed(buttonLake);
	}
	
}

void Host::AddMenuButtons()
{
	Colours cN, cH, cD;
	//cN.iRed = 255; cN.iGreen = 255; cN.iBlue = 255; cN.iAlpha = 255;
	cN.iRed = 0; cN.iGreen = 148; cN.iBlue = 255; cN.iAlpha = 50;
	cH.iRed = 0; cH.iGreen = 0; cH.iBlue = 0; cH.iAlpha = 150;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;
	m_pBM->AddButton(410, 730, "Back", 100, 30, true, true, cN, cH, cD, false, sceneMenu);
	m_pBM->AddButton(514, 730, "Create", 100, 30, true, true, cN, cH, cD, false, sceneJoin);	
}

void Host::AddOptions()
{
	Colours cN, cH, cD, cWhite, cGrey;
	cWhite.iRed = 255; cWhite.iGreen = 255; cWhite.iBlue = 255; cWhite.iAlpha = 255;
	cGrey.iRed = 150; cGrey.iGreen = 150; cGrey.iBlue = 150; cGrey.iAlpha = 255;
	cN.iRed = 0; cN.iGreen = 148; cN.iBlue = 255; cN.iAlpha = 50;
	cH.iRed = 0; cH.iGreen = 0; cH.iBlue = 0; cH.iAlpha = 150;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;
	//if (m_pNetworkClient->GetName().length() == 0) 
	//	{m_pNetworkClient->SetName("Player");}

	m_pBM->AddButton(300, 150, "", 400, 30, true, true, cWhite, cGrey, cGrey, true, buttonName);
	bool bClick = true;
	//if (m_pNetworkClient->GetJoined() == true) {bClick = false;} else {bClick = true;}
	m_pBM->AddButton(300, 225, "Desert", 75, 30, bClick, true, cN, cH, cD, false, buttonDesert);
	m_pBM->AddButton(400, 225, "Forest", 75, 30, bClick, true, cN, cH, cD, false, buttonForest);
	m_pBM->AddButton(500, 225, "City", 75, 30, bClick, true, cN, cH, cD, false, buttonCity);
	m_pBM->AddButton(600, 225, "Lake", 75, 30, bClick, true, cN, cH, cD, false, buttonLake);

	m_pBM->AddButton(300, 670, "", 400, 30, true, true, cWhite, cGrey, cGrey, true, buttonChat);
}
void Host::DrawText(SDL_Surface* screen)
{
	std::string sTemp = "";
	
	m_pMT->Print(screen, 175, 155, "Server Name:");
	m_pMT->Print(screen, 425, 200, "Choose Map");
	//sTemp = "Network Status: " ;
	//if (m_pNetworkClient->GetJoined()) 
	//	{sTemp += "Joined";} 
	//else 
		//{sTemp += "Not Connected";}
	//m_pMT->Print(screen, 250, 290, sTemp);
}

void Host::AddLetterToName(int addToButton)
{
	for(int i = SDLK_a; i <= SDLK_z; i++)
	{
		if(m_bKeysHeld[i])
		{
			if(!m_bShiftMod)
			{
				if (addToButton == buttonName) {AddToServerName((char)(i));}
				if (addToButton == buttonChat) {m_pNC->AddToName((char)(i));}
			}
			else
			{
				if (addToButton == buttonName) {AddToServerName((char)(i - 32));}
				if (addToButton == buttonChat) {m_pNC->AddToName((char)(i - 32));}
			}
			m_bKeysHeld[i] = false;
		}
	}

	if (m_bKeysHeld[SDLK_1] || m_bKeysHeld[SDLK_KP1])
	{
		if (addToButton == buttonName) {AddToServerName("1");}
		if (addToButton == buttonChat) {m_pNC->AddToName("1");}
		m_bKeysHeld[SDLK_1] = false;
		m_bKeysHeld[SDLK_KP1] = false;
	}
	else if (m_bKeysHeld[SDLK_2] || m_bKeysHeld[SDLK_KP2])
	{
		if (addToButton == buttonName) {AddToServerName("2");}
		if (addToButton == buttonChat) {m_pNC->AddToName("2");}
		m_bKeysHeld[SDLK_2] = false;
		m_bKeysHeld[SDLK_KP2] = false;
	}
	else if (m_bKeysHeld[SDLK_3] || m_bKeysHeld[SDLK_KP3])
	{
		if (addToButton == buttonName) {AddToServerName("3");}
		if (addToButton == buttonChat) {m_pNC->AddToName("3");}
		m_bKeysHeld[SDLK_3] = false;
		m_bKeysHeld[SDLK_KP3] = false;
	}
	else if (m_bKeysHeld[SDLK_4] || m_bKeysHeld[SDLK_KP4])
	{
		if (addToButton == buttonName) {AddToServerName("4");}
		if (addToButton == buttonChat) {m_pNC->AddToName("4");}
		m_bKeysHeld[SDLK_4] = false;
		m_bKeysHeld[SDLK_KP4] = false;
	}
	else if (m_bKeysHeld[SDLK_5] || m_bKeysHeld[SDLK_KP5])
	{
		if (addToButton == buttonName) {AddToServerName("5");}
		if (addToButton == buttonChat) {m_pNC->AddToName("5");}
		m_bKeysHeld[SDLK_5] = false;
		m_bKeysHeld[SDLK_KP5] = false;
	}
	else if (m_bKeysHeld[SDLK_6] || m_bKeysHeld[SDLK_KP6])
	{
		if (addToButton == buttonName) {AddToServerName("6");}
		if (addToButton == buttonChat) {m_pNC->AddToName("6");}
		m_bKeysHeld[SDLK_6] = false;
		m_bKeysHeld[SDLK_KP6] = false;
	}
	else if (m_bKeysHeld[SDLK_7] || m_bKeysHeld[SDLK_KP7])
	{
		if (addToButton == buttonName) {AddToServerName("7");}
		if (addToButton == buttonChat) {m_pNC->AddToName("7");}
		m_bKeysHeld[SDLK_7] = false;
		m_bKeysHeld[SDLK_KP7] = false;
	}
	else if (m_bKeysHeld[SDLK_8] || m_bKeysHeld[SDLK_KP8])
	{
		if (addToButton == buttonName) {AddToServerName("8");}
		if (addToButton == buttonChat) {m_pNC->AddToName("8");}
		m_bKeysHeld[SDLK_8] = false;
		m_bKeysHeld[SDLK_KP8] = false;
	}
	else if (m_bKeysHeld[SDLK_9] || m_bKeysHeld[SDLK_KP9])
	{
		if (addToButton == buttonName) {AddToServerName("9");}
		if (addToButton == buttonChat) {m_pNC->AddToName("9");}
		m_bKeysHeld[SDLK_9] = false;
		m_bKeysHeld[SDLK_KP9] = false;
	}
	else if (m_bKeysHeld[SDLK_0] || m_bKeysHeld[SDLK_KP0])
	{
		if (addToButton == buttonName) {AddToServerName("0");}
		if (addToButton == buttonChat) {m_pNC->AddToName("0");}
		m_bKeysHeld[SDLK_0] = false;
		m_bKeysHeld[SDLK_KP0] = false;
	}
	else if (m_bKeysHeld[SDLK_BACKSPACE])
	{
		if (addToButton == buttonName) {SetServerName(GetServerName().substr(0, GetServerName().length() - 1));}
		if (addToButton == buttonChat) {m_pNC->SetName(m_pNC->GetName().substr(0, m_pNC->GetName().length() - 1));}
		m_bKeysHeld[SDLK_BACKSPACE] = false;
	}
	else if (m_bKeysHeld[SDLK_DELETE])
	{
		if (addToButton == buttonName) {SetServerName("");}
		if (addToButton == buttonChat) {m_pNC->SetName("");}
	}
	else if (m_bKeysHeld[SDLK_SPACE])
	{
		if (addToButton == buttonName) {AddToServerName(" ");}
		if (addToButton == buttonChat) {m_pNC->AddToName(" ");}
		m_bKeysHeld[SDLK_SPACE] = false;
	}
	else if (m_bKeysHeld[SDLK_RETURN])
	{
		m_pBM->ButtonUnPressed(addToButton);
	}
}

void Host::SetupHostWithServer()
{
	setupPacket* spData = new setupPacket();
	
	spData->id = CLIENT_SETUP;
	spData->mapID = m_iMapID;
	sprintf(spData->serverName, m_pBM->FindButton(buttonName)->GetText().c_str());

	m_pNC->Send((basePacket*)spData, sizeof(*spData));

	delete[] spData;

	m_pNC->SetIsHost(true);
}

void Host::SetServerName(string sn)
{
	m_sServerName = sn;
}
void Host::AddToServerName(string atsn)
{
	m_sServerName += atsn;
}
void Host::AddToServerName(char c)
{
	m_sServerName = m_sServerName + c;
}
string Host::GetServerName()
{
	return m_sServerName;
}