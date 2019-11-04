//Blake Sullivan - CharacterSelect.cpp
#include "CharacterSelect.h"

CharacterSelect::CharacterSelect()
{
	Init();
}
CharacterSelect::CharacterSelect(MyText* mt, NetworkClient* nc)
{
	m_pMT = mt;
	m_pNC = nc;
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

	m_bIsRefreshing = false;

	AddButtons();
}
void CharacterSelect::Update(SDL_Surface* screen, float fDeltaTime)
{
	UpdateButtons();
	ManageButtonPress();
	if (m_pNC->Receive() == true)
	{
		cout << "Got Packet." << endl;
		CharacterSelected();
	}
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
	m_bIsRefreshing = false;
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
	cH.iRed = 0; cH.iGreen = 0; cH.iBlue = 0; cH.iAlpha = 150;
	cD.iRed = 255; cD.iGreen = 0; cD.iBlue = 0; cD.iAlpha = 255;

	m_pBM->AddButton(410, 730, "BACK", 100, 30, true, true, cN, cH, cD, false, sceneJoin);
	m_pBM->AddButton(514, 730, "PLAY", 100, 30, false, true, cN, cH, cD, false, scenePlay);

	m_pBM->AddButton(390, 200, "SELECT", 100, 30, true, true, cN, cH, cD, false, buttonCharBE);
	m_pBM->AddButton(390, 400, "SELECT", 100, 30, true, true, cN, cH, cD, false, buttonCharPT);
	m_pBM->AddButton(390, 600, "SELECT", 100, 30, true, true, cN, cH, cD, false, buttonCharRN);
	m_pBM->AddButton(534, 200, "SELECT", 100, 30, true, true, cN, cH, cD, false, buttonCharRD);
	m_pBM->AddButton(534, 400, "SELECT", 100, 30, true, true, cN, cH, cD, false, buttonCharSS);
	m_pBM->AddButton(534, 600, "SELECT", 100, 30, true, true, cN, cH, cD, false, buttonCharZB);


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

	if (m_bIsRefreshing == false)
	{
		m_bIsRefreshing = true;
		if (iButtonPressed == buttonCharBE) {ConnectCharacter(buttonCharBE);}
		if (iButtonPressed == buttonCharPT) {ConnectCharacter(buttonCharPT);}
		if (iButtonPressed == buttonCharRN) {ConnectCharacter(buttonCharRN);}
		if (iButtonPressed == buttonCharRD) {ConnectCharacter(buttonCharRD);}
		if (iButtonPressed == buttonCharSS) {ConnectCharacter(buttonCharSS);}
		if (iButtonPressed == buttonCharZB) {ConnectCharacter(buttonCharZB);}
	}

	if (m_iIsRunning != sceneRunning)
		{m_pBM->ButtonUnPressed(iButtonPressed);}
}

void CharacterSelect::ConnectCharacter(int connectChar)
{
	characterPacket* cData = new characterPacket();

	cData->id = CLIENT_CHARACTER;
	cData->userID = m_pNC->GetServerID();
	cData->charID = connectChar - 20;

	m_pNC->Send((basePacket*)cData, sizeof(*cData));

	delete[] cData;

	m_pBM->ButtonUnPressed(connectChar);
}
void CharacterSelect::CharacterSelected()
{
	characterConnectedPacket* cData = (characterConnectedPacket*)m_pNC->GetNetworkManager()->GetPacket()->data;

	m_pNC->SetCharacter(cData->userID, cData->charID, cData->userName);

	for (int i = 0; i < 6; i++)
	{
		if (cData->charID == i)
			{m_pBM->FindButton(cData->charID + 20)->SetClickable(false);}
		if (cData->userID == m_pNC->GetServerID())
		{
			m_pNC->SetCharSelected(cData->charID);
			m_pBM->FindButton(scenePlay)->SetClickable(true);
		}
	}
}

void CharacterSelect::DrawCharacters(SDL_Surface* screen)
{
	SDL_Rect sclip, dclip;
	int iPosX[6] = {0,0,0,0,0,0};
	int iPosY[6] = {0,0,0,0,0,0};

	int iAvPosX[6] = {0,0,0,0,0,0};
	int iAvPosY[6] = {0,0,0,0,0,0};

	int iTextPosX[6][6];
	int iTextPosY[6][6];
	string sText[6][6];

	iPosX[0] = -50; iPosY[0] = 140;
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

	//Raven - Buster Eagle
	iTextPosX[0][0] = 160; iTextPosY[0][0] = 150; sText[0][0] = "ZOID: Buster Eagle";
	iTextPosX[0][1] = 160; iTextPosY[0][1] = 180; sText[0][1] = "Health: 100";
	iTextPosX[0][2] = 160; iTextPosY[0][2] = 210; sText[0][2] = "Speed: 2";
	iTextPosX[0][3] = 100; iTextPosY[0][3] = 240; sText[0][3] = "Weapon: Buster Cannon";
	iTextPosX[0][4] = 100; iTextPosY[0][4] = 270; sText[0][4] = "Special: Torpedo";
	iTextPosX[0][5] = 100; iTextPosY[0][5] = 300; sText[0][5] = "Pilot: Raven Vega";

	//Brad - Pteras
	iTextPosX[1][0] = 130; iTextPosY[1][0] = 360; sText[1][0] = "ZOID: Pteras";
	iTextPosX[1][1] = 130; iTextPosY[1][1] = 390; sText[1][1] = "Health: 100";
	iTextPosX[1][2] = 130; iTextPosY[1][2] = 420; sText[1][2] = "Speed: 3";
	iTextPosX[1][3] = 100; iTextPosY[1][3] = 450; sText[1][3] = "Weapon: Machine Gun";
	iTextPosX[1][4] = 100; iTextPosY[1][4] = 480; sText[1][4] = "Special: Heat Seeking Missile";
	iTextPosX[1][5] = 100; iTextPosY[1][5] = 510; sText[1][5] = "Pilot: Brad Hunter";

	//Bit - Raynos
	iTextPosX[2][0] = 140; iTextPosY[2][0] = 570; sText[2][0] = "ZOID: Raynos";
	iTextPosX[2][1] = 140; iTextPosY[2][1] = 600; sText[2][1] = "Health: 100";
	iTextPosX[2][2] = 140; iTextPosY[2][2] = 630; sText[2][2] = "Speed: 4";
	iTextPosX[2][3] = 100; iTextPosY[2][3] = 660; sText[2][3] = "Weapon: Laser Gun";
	iTextPosX[2][4] = 100; iTextPosY[2][4] = 690; sText[2][4] = "Special: Super Speed";
	iTextPosX[2][5] = 100; iTextPosY[2][5] = 720; sText[2][5] = "Pilot: Bit Cloud";

	//Leena - Redler
	iTextPosX[3][0] = 660; iTextPosY[3][0] = 150; sText[3][0] = "ZOID: Redler";
	iTextPosX[3][1] = 660; iTextPosY[3][1] = 180; sText[3][1] = "Health: 100";
	iTextPosX[3][2] = 660; iTextPosY[3][2] = 210; sText[3][2] = "Speed: 3";
	iTextPosX[3][3] = 660; iTextPosY[3][3] = 240; sText[3][3] = "Weapon: Machine Gun";
	iTextPosX[3][4] = 660; iTextPosY[3][4] = 270; sText[3][4] = "Special: Cloaking Stealth Unit";
	iTextPosX[3][5] = 660; iTextPosY[3][5] = 300; sText[3][5] = "Pilot: Leena Tauros";

	//Van - Storm Sworder
	iTextPosX[4][0] = 660; iTextPosY[4][0] = 360; sText[4][0] = "ZOID: Storm Sworder";
	iTextPosX[4][1] = 660; iTextPosY[4][1] = 390; sText[4][1] = "Health: 100";
	iTextPosX[4][2] = 660; iTextPosY[4][2] = 420; sText[4][2] = "Speed: 5";
	iTextPosX[4][3] = 660; iTextPosY[4][3] = 450; sText[4][3] = "Weapon: Machine Gun";
	iTextPosX[4][4] = 660; iTextPosY[4][4] = 480; sText[4][4] = "Special: Charging Wing Attack";
	iTextPosX[4][5] = 660; iTextPosY[4][5] = 510; sText[4][5] = "Pilot: Van Flyheight";

	//Irvine - Zabat
	iTextPosX[5][0] = 660; iTextPosY[5][0] = 570; sText[5][0] = "ZOID: Zabat";
	iTextPosX[5][1] = 660; iTextPosY[5][1] = 600; sText[5][1] = "Health: 100";
	iTextPosX[5][2] = 660; iTextPosY[5][2] = 630; sText[5][2] = "Speed: 2";
	iTextPosX[5][3] = 660; iTextPosY[5][3] = 660; sText[5][3] = "Weapon: Laser Gun";
	iTextPosX[5][4] = 660; iTextPosY[5][4] = 690; sText[5][4] = "Special: Sonar Enemy Detection";
	iTextPosX[5][5] = 660; iTextPosY[5][5] = 720; sText[5][5] = "Pilot: Irvine Kinneas";

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

	//Text
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			m_pMT->Print(screen, iTextPosX[i][j], iTextPosY[i][j], sText[i][j], 0, 0, 0);
		}
	}

	int x1 = 0, x2 = 0;
	for (int i = 0; i < 6; i++)
	{
		if (i < 3) {x1 = 0; x2 = 375;} else {x1 = 1024-375; x2 = 1023;}
		if (m_pBM->FindButton(i + 20)->GetClickable() == false)
		{
			if (m_pNC->GetCharSelected() == i)
				{boxRGBA(screen, x1, iPosY[i], x2, iPosY[i] + 200, 0, 255, 0, 150);}
			else
				{boxRGBA(screen, x1, iPosY[i], x2, iPosY[i] + 200, 255, 0, 0, 150);}
		}
	}
}