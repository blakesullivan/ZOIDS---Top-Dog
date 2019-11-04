//Blake Sullivan - Join.cpp
#include "Join.h"

Join::Join()
{
	Init();
}
Join::Join(MyText* mt, NetworkClient* nc)
{
	m_pMT = mt;
	m_pNC = nc;
	Init();
}

void Join::Init()
{
	m_iIsRunning = sceneRunning;
	m_pBM = new ButtonManager(m_pMT);

	m_Background = NULL;
	m_Background = SDL_LoadBMP("Menu.bmp");

	m_bIsRefreshing = false;
	m_pNC->SetServerAddress(m_pNC->GetNetworkManager()->ResolveHost("255.255.255.255", 2000));

	m_iNumServers = 0;
	m_bIsRefreshing = false;

	for (int i = 0; i < 20; i++)
	{
		m_asMessages[i] = "";
	}

	AddButtons();
	RefreshServerList();
	if (m_pNC->GetIsHost() == true)
	{
		//SDL_Delay(5000);
		ConnectToServer(70);
	}
}
void Join::Update(SDL_Surface* screen, float fDeltaTime)
{
	UpdateButtons();
	ManageButtonPress();
	if (m_pNC->Receive() == true)
	{
		ResponseToReceive();
	}
}
void Join::Draw(SDL_Surface* screen, float fDeltaTime)
{
	string sTemp = "";
	char buffer[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	//SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 20, 150, 20) );
	SDL_BlitSurface(m_Background, NULL, screen, NULL);

	//Name
	m_pMT->Print(screen, 350, 175, "Name:", 255, 255, 255, 0, 0);

	//Server Box
	m_pMT->Print(screen, 125, 150, "Server List", 255, 255, 255, 0, 0);
	boxRGBA(screen, 50, 170, 300, 500, 255, 255, 255, 150);
	rectangleRGBA(screen, 50, 170, 300, 500, 0, 0, 0, 255);

	//Chat Box
	m_pMT->Print(screen, 600, 220, "Chat", 255, 255, 255, 0, 0);
	boxRGBA(screen, 350, 240, screen->clip_rect.w - 50, 720, 255, 255, 255, 150);
	rectangleRGBA(screen, 350, 240, screen->clip_rect.w - 50, 720, 0, 0, 0, 255);
	for (int j = 0; j < 20; j++)
	{
		m_pMT->Print(screen, 355, (690 - 20) - (j * 20), m_asMessages[j], 0, 0, 0, 0, 0);
	}

	//Game Details
	m_pMT->Print(screen, 100, 580, "Server Settings", 255, 255, 255, 0, 0);
	boxRGBA(screen, 50, 600, 300, 720, 255, 255, 255, 150);
	rectangleRGBA(screen, 50, 600, 300, 720, 0, 0, 0, 255);
	if (m_pNC->GetMapID() >= 0 && m_pNC->GetServerID() >= 0)
	{
		m_pMT->Print(screen, 55, 605, "Connected to Server: ", 0, 0, 0, 0, 0);
		m_pMT->Print(screen, 55, 630, m_pNC->GetServerName(), 0, 0, 0, 0, 0);
		sTemp = "Map ID: ";
		sTemp += itoa(m_pNC->GetMapID() + 1, buffer, 10);
		m_pMT->Print(screen, 55, 655, sTemp, 0, 0, 0, 0, 0);
		sTemp = "Player ID: ";
		sTemp += itoa(m_pNC->GetServerID() + 1, buffer, 10);
		m_pMT->Print(screen, 55, 680, sTemp, 0, 0, 0, 0, 0);
	}

	m_pBM->DrawButton(screen);
}
//int Join::Status()
//{
//	return m_iIsRunning;
//}
void Join::Dispose()
{
	SDL_FreeSurface(m_Background);
	delete m_pBM;
}

void Join::MouseUpEvent(SDL_Event* event)
{
	Scene::MouseUpEvent(event);
	m_bIsRefreshing = false;
}
void Join::MouseDownEvent (SDL_Event* event)
{
	Scene::MouseDownEvent(event);
}
void Join::KeyUpEvent(SDL_Event* event)
{
	Scene::KeyUpEvent(event);
}
void Join::KeyDownEvent(SDL_Event* event)
{
	Scene::KeyDownEvent(event);
}

void Join::AddButtons()
{
	Colours cN, cH, cD, cWhite, cGrey;
	cWhite.iRed = 255; cWhite.iGreen = 255; cWhite.iBlue = 255; cWhite.iAlpha = 255;
	cGrey.iRed = 150; cGrey.iGreen = 150; cGrey.iBlue = 150; cGrey.iAlpha = 255;
	cN.iRed = 0; cN.iGreen = 148; cN.iBlue = 255; cN.iAlpha = 50;
	cH.iRed = 0; cH.iGreen = 0; cH.iBlue = 0; cH.iAlpha = 150;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;

	//Menu buttons
	m_pBM->AddButton(410, 730, "Back", 100, 30, true, true, cN, cH, cD, false, sceneMenu);
	m_pBM->AddButton(514, 730, "Join", 100, 30, false, true, cN, cH, cD, false, sceneCharacter);

	//Setting Buttons
	m_pBM->AddButton(50, 510, "Refresh", 250, 50, true, true, cN, cH, cD, false, buttonRefresh);
	m_pBM->AddButton(410, 170, m_pNC->GetName(), 564, 30, true, true, cWhite, cGrey, cGrey, true, buttonName);

	//Chat buttons
	m_pBM->AddButton(350, 690, "Enter Chat Message Here", 549, 30, true, true, cWhite, cGrey, cGrey, true, buttonChat);
	m_pBM->AddButton(899, 690, "Send", 75, 30, true, true, cN, cH, cD, false, buttonSendChat);

	//Server List Buttons
	int butY = 170, butSize = 30, butID = 70;
	for (int i = 0; i < MCS_IMAXSERVERS; i++)
	{
		m_pBM->AddButton(50, butY, "", 250, 30, false, false, cN, cH, cD, false, butID);
		butY += butSize; butID++;
	}
}
void Join::UpdateButtons()
{
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	m_pBM->UpdateButton(mouseX, mouseY);
	if (m_bButtonHeld[SDL_BUTTON_LEFT] == true)
		{m_pBM->ButtonPressed(mouseX, mouseY);}
}

void Join::ManageButtonPress()
{
	int iButtonPressed = m_pBM->CheckButtonPressed();

	if (m_bKeysHeld[SDLK_ESCAPE] == true)// || m_bKeysHeld[SDLK_BACKSPACE] == true)
		{m_iIsRunning = sceneMenu;}
	if (iButtonPressed == sceneMenu)
		{m_iIsRunning = sceneMenu;}
	if (iButtonPressed == sceneCharacter)
		{m_iIsRunning = sceneCharacter;}

	if (m_pBM->FindButton(buttonSendChat)->GetPressed())
	{
		if (m_pBM->FindButton(buttonChat)->GetText() != "")
		{
			SendChatMessage(m_pBM->FindButton(buttonChat)->GetText());
			m_pBM->FindButton(buttonChat)->SetText("");
			SetChatMessage("");
		}
		m_pBM->ButtonUnPressed(buttonSendChat);
	}

	if (m_pBM->FindButton(buttonRefresh)->GetPressed() == true)
	{
		if (m_bIsRefreshing == false)
		{
			m_bIsRefreshing = true;
			RefreshServerList();
		}
		m_pBM->ButtonUnPressed(buttonRefresh);
	}
	for (int i = 0; i < MCS_IMAXSERVERS; i++)
	{
		if (m_pBM->FindButton(m_aSvrButtons[i].buttID)->GetPressed() == true &&  m_aSvrButtons[i].buttID >= 0)
		{
			if (m_bIsRefreshing == false)
			{
				m_bIsRefreshing = true;
				ConnectToServer(i);
			}
		}
		m_pBM->ButtonUnPressed(m_aSvrButtons[i].buttID);
	}

	if (m_pBM->FindButton(buttonChat)->GetPressed())
	{
		m_pBM->ButtonUnPressed(buttonName);
		AddLetterToName(buttonChat);
		m_pBM->FindButton(buttonChat)->SetText(GetChatMessage());
	}
	if (m_pBM->FindButton(buttonName)->GetPressed())
	{
		m_pBM->ButtonUnPressed(buttonChat);
		AddLetterToName(buttonName);
		m_pBM->FindButton(buttonName)->SetText(m_pNC->GetName());
	}

	if (m_iIsRunning != sceneRunning)
		{m_pBM->ButtonUnPressed(iButtonPressed);}
}

void Join::RefreshServerList()
{
	m_iNumServers = 0;
	for (int i = 0; i < MCS_IMAXSERVERS; i++)
	{
		m_aSvrButtons[i].buttID = -1;
		m_aSvrButtons[i].srvAdd = m_pNC->GetNetworkManager()->ResolveHost("127.0.0.1", 2000);
	}

	basePacket* pData = new basePacket();

	pData->id = CLIENT_BROADCAST;
	m_pNC->GetNetworkManager()->SendStruct(pData, m_pNC->GetServerAddress(), sizeof(*pData));

	delete[] pData;
}

void Join::ResponseToReceive()
{
	cout << "Packet ID: " << m_pNC->GetPacketReceived()->id << endl;
	if (m_pNC->GetPacketReceived()->id == SERVER_RESPONSE)
	{
		SetupServerButtons();
	}
	else if (m_pNC->GetPacketReceived()->id == SERVER_NEW_USER)
	{
		SetupConnectedUser();
	}
	else if (m_pNC->GetPacketReceived()->id == SERVER_MESSAGE)
	{
		AddToChatWindow();
	}
}

void Join::SetupServerButtons()
{
	serverResponsePacket* srData = (serverResponsePacket*)m_pNC->GetNetworkManager()->GetPacket()->data;
	for (int i = 0; i < MCS_IMAXSERVERS; i++)
	{
		if (m_aSvrButtons[i].buttID == -1)
		{
			m_aSvrButtons[i].buttID = 70 + i;
			m_aSvrButtons[i].srvAdd = m_pNC->GetNetworkManager()->GetPacket()->address;
			m_pBM->FindButton(m_aSvrButtons[i].buttID)->SetText(srData->serverName);
			m_pBM->FindButton(m_aSvrButtons[i].buttID)->SetClickable(true);
			m_pBM->FindButton(m_aSvrButtons[i].buttID)->SetOutlined(true);
			break;
		}
	}
}

void Join::ConnectToServer(int iSvrNum)
{
	if (m_pBM->FindButton(buttonName)->GetText() == "" || m_pBM->FindButton(buttonName)->GetText() == "Enter a Name before connecting.")
	{
		m_pBM->FindButton(buttonName)->SetText("Enter a Name before connecting.");
	}
	else
	{
		cout << "In Connect To Server." << endl;
		m_pNC->SetServerAddress(m_pNC->GetIPFromServerAdd(m_aSvrButtons[iSvrNum].srvAdd));
		m_pNC->SetServerName(m_pBM->FindButton(m_aSvrButtons[iSvrNum].buttID)->GetText());

		connectPacket* cData = new connectPacket();

		cData->id = CLIENT_NEW_USER;
		sprintf(cData->userName, m_pBM->FindButton(buttonName)->GetText().c_str());

		m_pNC->Send((basePacket*)cData, sizeof(*cData));

		delete[] cData;
	}
}

void Join::SetupConnectedUser()
{
	mapPacket* mData = (mapPacket*)m_pNC->GetPacketReceived();

	m_pNC->SetIsJoined(true);
	m_pNC->SetMapID(mData->mapID);
	m_pNC->SetServerID(mData->numConnected);
	m_pBM->FindButton(sceneCharacter)->SetClickable(true);
}

void Join::SendChatMessage(string msg)
{
	messagePacket* mData = new messagePacket();

	mData->id = CLIENT_MESSAGE;
	sprintf(mData->message, msg.c_str());
	mData->userID = m_pNC->GetServerID();

	m_pNC->Send((basePacket*)mData, sizeof(*mData));

	delete[] mData;
}
void Join::AddToChatWindow()
{
	messagePacket* smData = (messagePacket*)m_pNC->GetNetworkManager()->GetPacket()->data;

	for (int mNum = 19; mNum > 0; mNum--)
	{
		m_asMessages[mNum] = m_asMessages[mNum-1];
	}
	m_asMessages[0] = "";
	for (int i = 0; i < 255; i++)
	{
		//cout << "Chat message: " << smData->message[i] << endl;
		if (smData->message[i] == '#') {break;}
		m_asMessages[0] += smData->message[i];
	}
	//cout << "Chat message after: " << m_asMessages[0] << endl;
}


void Join::AddLetterToName(int addToButton)
{
	for(int i = SDLK_a; i <= SDLK_z; i++)
	{
		if(m_bKeysHeld[i])
		{
			if(!m_bShiftMod)
			{
				if (addToButton == buttonChat) {AddToChatMessage((char)(i));}
				if (addToButton == buttonName) {m_pNC->AddToName((char)(i));}
			}
			else
			{
				if (addToButton == buttonChat) {AddToChatMessage((char)(i - 32));}
				if (addToButton == buttonName) {m_pNC->AddToName((char)(i - 32));}
			}
			m_bKeysHeld[i] = false;
		}
	}

	if (m_bKeysHeld[SDLK_1] || m_bKeysHeld[SDLK_KP1])
	{
		if (addToButton == buttonChat) {AddToChatMessage("1");}
		if (addToButton == buttonName) {m_pNC->AddToName("1");}
		m_bKeysHeld[SDLK_1] = false;
		m_bKeysHeld[SDLK_KP1] = false;
	}
	else if (m_bKeysHeld[SDLK_2] || m_bKeysHeld[SDLK_KP2])
	{
		if (addToButton == buttonChat) {AddToChatMessage("2");}
		if (addToButton == buttonName) {m_pNC->AddToName("2");}
		m_bKeysHeld[SDLK_2] = false;
		m_bKeysHeld[SDLK_KP2] = false;
	}
	else if (m_bKeysHeld[SDLK_3] || m_bKeysHeld[SDLK_KP3])
	{
		if (addToButton == buttonChat) {AddToChatMessage("3");}
		if (addToButton == buttonName) {m_pNC->AddToName("3");}
		m_bKeysHeld[SDLK_3] = false;
		m_bKeysHeld[SDLK_KP3] = false;
	}
	else if (m_bKeysHeld[SDLK_4] || m_bKeysHeld[SDLK_KP4])
	{
		if (addToButton == buttonChat) {AddToChatMessage("4");}
		if (addToButton == buttonName) {m_pNC->AddToName("4");}
		m_bKeysHeld[SDLK_4] = false;
		m_bKeysHeld[SDLK_KP4] = false;
	}
	else if (m_bKeysHeld[SDLK_5] || m_bKeysHeld[SDLK_KP5])
	{
		if (addToButton == buttonChat) {AddToChatMessage("5");}
		if (addToButton == buttonName) {m_pNC->AddToName("5");}
		m_bKeysHeld[SDLK_5] = false;
		m_bKeysHeld[SDLK_KP5] = false;
	}
	else if (m_bKeysHeld[SDLK_6] || m_bKeysHeld[SDLK_KP6])
	{
		if (addToButton == buttonChat) {AddToChatMessage("6");}
		if (addToButton == buttonName) {m_pNC->AddToName("6");}
		m_bKeysHeld[SDLK_6] = false;
		m_bKeysHeld[SDLK_KP6] = false;
	}
	else if (m_bKeysHeld[SDLK_7] || m_bKeysHeld[SDLK_KP7])
	{
		if (addToButton == buttonChat) {AddToChatMessage("7");}
		if (addToButton == buttonName) {m_pNC->AddToName("7");}
		m_bKeysHeld[SDLK_7] = false;
		m_bKeysHeld[SDLK_KP7] = false;
	}
	else if (m_bKeysHeld[SDLK_8] || m_bKeysHeld[SDLK_KP8])
	{
		if (addToButton == buttonChat) {AddToChatMessage("8");}
		if (addToButton == buttonName) {m_pNC->AddToName("8");}
		m_bKeysHeld[SDLK_8] = false;
		m_bKeysHeld[SDLK_KP8] = false;
	}
	else if (m_bKeysHeld[SDLK_9] || m_bKeysHeld[SDLK_KP9])
	{
		if (addToButton == buttonChat) {AddToChatMessage("9");}
		if (addToButton == buttonName) {m_pNC->AddToName("9");}
		m_bKeysHeld[SDLK_9] = false;
		m_bKeysHeld[SDLK_KP9] = false;
	}
	else if (m_bKeysHeld[SDLK_0] || m_bKeysHeld[SDLK_KP0])
	{
		if (addToButton == buttonChat) {AddToChatMessage("0");}
		if (addToButton == buttonName) {m_pNC->AddToName("0");}
		m_bKeysHeld[SDLK_0] = false;
		m_bKeysHeld[SDLK_KP0] = false;
	}
	else if (m_bKeysHeld[SDLK_BACKSPACE])
	{
		if (addToButton == buttonChat) {SetChatMessage(GetChatMessage().substr(0, GetChatMessage().length() - 1));}
		if (addToButton == buttonName) {m_pNC->SetName(m_pNC->GetName().substr(0, m_pNC->GetName().length() - 1));}
		m_bKeysHeld[SDLK_BACKSPACE] = false;
	}
	else if (m_bKeysHeld[SDLK_DELETE])
	{
		if (addToButton == buttonChat) {SetChatMessage("");}
		if (addToButton == buttonName) {m_pNC->SetName("");}
	}
	else if (m_bKeysHeld[SDLK_SPACE])
	{
		if (addToButton == buttonChat) {AddToChatMessage(" ");}
		if (addToButton == buttonName) {m_pNC->AddToName(" ");}
		m_bKeysHeld[SDLK_SPACE] = false;
	}
	else if (m_bKeysHeld[SDLK_RETURN])
	{
		m_pBM->ButtonUnPressed(addToButton);
	}
}

void Join::SetChatMessage(string cm)
{
	m_sChatMessage = cm;
}
void Join::AddToChatMessage(string atcm)
{
	m_sChatMessage += atcm;
}
void Join::AddToChatMessage(char c)
{
	m_sChatMessage = m_sChatMessage + c;
}
string Join::GetChatMessage()
{
	return m_sChatMessage;
}