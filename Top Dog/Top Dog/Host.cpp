//Blake Sullivan - Splash.cpp
#include "Host.h"

Host::Host()
{
	Init();
}

Host::Host(MyText* mt)//NetworkClient* nc, MyText* mt)
{
	//m_pNetworkClient = nc;
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

	AddMenuButtons();
	AddOptions();
}

void Host::Update(SDL_Surface* screen, float fDeltaTime)
{
	if (m_bKeysHeld[SDLK_BACKSPACE])
		{m_iIsRunning = sceneMenu;}

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
	//SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 200, 0, 0) ); 
	SDL_BlitSurface(m_Background, NULL, screen, NULL);

	m_pBM->DrawButton(screen);
	DrawText(screen);
}

//int Host::Status()
//{
//	return m_iIsRunning;
//}

void Host::Dispose()
{
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
		{m_iIsRunning = sceneJoin;}

	if (m_iIsRunning != sceneRunning)
		{m_pBM->ButtonUnPressed(iButtonPressed);}

	if (iButtonPressed == buttonName)
	{
		AddLetterToName();
		//m_pBM->FindButton(buttonName)->SetText(m_pNetworkClient->GetName());
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
}

void Host::AddMenuButtons()
{
	Colours cN, cH, cD;
	//cN.iRed = 255; cN.iGreen = 255; cN.iBlue = 255; cN.iAlpha = 255;
	cN.iRed = 150; cN.iGreen = 050; cN.iBlue = 150; cN.iAlpha = 255;
	cH.iRed = 150; cH.iGreen = 150; cH.iBlue = 0; cH.iAlpha = 255;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;
	m_pBM->AddButton(300, 450, "To Join", 100, 30, true, true, cN, cH, cD, false, sceneJoin);
	m_pBM->AddButton(300, 500, "To Menu", 100, 30, true, true, cN, cH, cD, false, sceneMenu);
}

void Host::AddOptions()
{
	Colours cN, cH, cD, cWhite, cGrey;
	cWhite.iRed = 255; cWhite.iGreen = 255; cWhite.iBlue = 255; cWhite.iAlpha = 255;
	cGrey.iRed = 150; cGrey.iGreen = 150; cGrey.iBlue = 150; cGrey.iAlpha = 255;
	cN.iRed = 150; cN.iGreen = 050; cN.iBlue = 150; cN.iAlpha = 255;
	cH.iRed = 150; cH.iGreen = 150; cH.iBlue = 0; cH.iAlpha = 255;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;
	//if (m_pNetworkClient->GetName().length() == 0) 
	//	{m_pNetworkClient->SetName("Player");}

	//m_pBM->AddButton(200, 200, m_pNetworkClient->GetName(), 400, 30, true, true, cWhite, cGrey, cWhite, true, buttonName);
	bool bClick = true;
	//if (m_pNetworkClient->GetJoined() == true) {bClick = false;} else {bClick = true;}
	m_pBM->AddButton(300, 250, "Host", 50, 30, bClick, true, cN, cH, cD, false, buttonHost);
	m_pBM->AddButton(375, 250, "Join", 50, 30, bClick, true, cN, cH, cD, false, buttonJoin);
}
void Host::DrawText(SDL_Surface* screen)
{
	std::string sTemp = "";
	
	m_pMT->Print(screen, 145, 210, "Name:");
	sTemp = "Network Status: " ;
	//if (m_pNetworkClient->GetJoined()) 
	//	{sTemp += "Joined";} 
	//else 
		{sTemp += "Not Connected";}
	m_pMT->Print(screen, 250, 290, sTemp);
}

void Host::AddLetterToName()
{
	for(int i = SDLK_a; i <= SDLK_z; i++)
	{
		if(m_bKeysHeld[i])
		{
			//if(!m_bShiftMod)
				//{m_pNetworkClient->AddToName((char)(i));}
			//else
				//{m_pNetworkClient->AddToName((char)(i - 32));}
			m_bKeysHeld[i] = false;
		}
	}

	if (m_bKeysHeld[SDLK_1] || m_bKeysHeld[SDLK_KP1])
	{
		//m_pNetworkClient->AddToName("1");
		m_bKeysHeld[SDLK_1] = false;
		m_bKeysHeld[SDLK_KP1] = false;
	}
	else if (m_bKeysHeld[SDLK_2] || m_bKeysHeld[SDLK_KP2])
	{
		//m_pNetworkClient->AddToName("2");
		m_bKeysHeld[SDLK_2] = false;
		m_bKeysHeld[SDLK_KP2] = false;
	}
	else if (m_bKeysHeld[SDLK_3] || m_bKeysHeld[SDLK_KP3])
	{
		//m_pNetworkClient->AddToName("3");
		m_bKeysHeld[SDLK_3] = false;
		m_bKeysHeld[SDLK_KP3] = false;
	}
	else if (m_bKeysHeld[SDLK_4] || m_bKeysHeld[SDLK_KP4])
	{
		//m_pNetworkClient->AddToName("4");
		m_bKeysHeld[SDLK_4] = false;
		m_bKeysHeld[SDLK_KP4] = false;
	}
	else if (m_bKeysHeld[SDLK_5] || m_bKeysHeld[SDLK_KP5])
	{
		//m_pNetworkClient->AddToName("5");
		m_bKeysHeld[SDLK_5] = false;
		m_bKeysHeld[SDLK_KP5] = false;
	}
	else if (m_bKeysHeld[SDLK_6] || m_bKeysHeld[SDLK_KP6])
	{
		//m_pNetworkClient->AddToName("6");
		m_bKeysHeld[SDLK_6] = false;
		m_bKeysHeld[SDLK_KP6] = false;
	}
	else if (m_bKeysHeld[SDLK_7] || m_bKeysHeld[SDLK_KP7])
	{
		//m_pNetworkClient->AddToName("7");
		m_bKeysHeld[SDLK_7] = false;
		m_bKeysHeld[SDLK_KP7] = false;
	}
	else if (m_bKeysHeld[SDLK_8] || m_bKeysHeld[SDLK_KP8])
	{
		//m_pNetworkClient->AddToName("8");
		m_bKeysHeld[SDLK_8] = false;
		m_bKeysHeld[SDLK_KP8] = false;
	}
	else if (m_bKeysHeld[SDLK_9] || m_bKeysHeld[SDLK_KP9])
	{
		//m_pNetworkClient->AddToName("9");
		m_bKeysHeld[SDLK_9] = false;
		m_bKeysHeld[SDLK_KP9] = false;
	}
	else if (m_bKeysHeld[SDLK_0] || m_bKeysHeld[SDLK_KP0])
	{
		//m_pNetworkClient->AddToName("0");
		m_bKeysHeld[SDLK_0] = false;
		m_bKeysHeld[SDLK_KP0] = false;
	}
	else if (m_bKeysHeld[SDLK_BACKSPACE])
	{
		//m_pNetworkClient->SetName(m_pNetworkClient->GetName().substr(0, m_pNetworkClient->GetName().length() - 1));
		m_bKeysHeld[SDLK_BACKSPACE] = false;
	}
	else if (m_bKeysHeld[SDLK_DELETE])
	{
		//m_pNetworkClient->SetName("");
	}
	else if (m_bKeysHeld[SDLK_SPACE])
	{
		//m_pNetworkClient->AddToName(" ");
		m_bKeysHeld[SDLK_SPACE] = false;
	}
}