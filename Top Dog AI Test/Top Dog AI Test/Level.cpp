//Blake Sullivan - Level.cpp
#include "Level.h"

Level::Level(SoundManager* sm)
{
	m_pSM = sm;
	m_Arrow = NULL;
	m_pMap = new Map();
	m_pPF = new PathFinder();
	//Init();
}
Level::~Level()
{
	delete m_pMap;
	delete m_pPF;
	SDL_FreeSurface(m_Arrow);
}

void Level::Init(int myID, bool isHost)
{
	/*AddCharacter(cidBuster, 2*32, 3*32, "Raven Vega", stateAlive, false);
	AddCharacter(cidPteras, 31*32, 3*32, "Brad Hunter", stateAlive, true);
	AddCharacter(cidRaynos, 61*32, 3*32, "Bit Cloud", stateAlive, true);
	AddCharacter(cidRedler, 12*32, 44*32, "Leena Tauros", stateAlive, true);
	AddCharacter(cidStorm, 31*32, 44*32, "Van Flyheight", stateAlive, true);	
	AddCharacter(cidZabat, 61*32, 44*32, "Irvine Kinneas", stateAlive, true);*/
	m_iMyID = myID;
	m_bIsHost = isHost;
	m_Arrow = IMG_Load("Images/Arrow.png");
}

void Level::Draw(SDL_Surface* screen, float fDT)
{
	//static int siFPS = 0;

	//if (siFPS == 0) 
	{m_pMap->DrawMap(screen, m_fWinPosX, m_fWinPosY);}

	for (int i = m_vpObj.size() - 1; i >= 0; i--)
	{
		if (m_vpObj[i]->GetState() == stateAlive && m_vpObj[i]->GetType() != typeTile)
		{
			m_vpObj[i]->Draw(screen, fDT, m_fWinPosX, m_fWinPosY);
			if (m_vpObj[i]->GetType() == typeCharacter)
			{
				if (dynamic_cast<Character*>(m_vpObj[i])->GetIsBot() == true)
				{
					//m_aFSM[dynamic_cast<Character*>(m_vpObj[i])->GetCharID()]->GetWS()->DrawWaypoints(screen, 32, m_fWinPosX, m_fWinPosY);
				}
				if (dynamic_cast<Character*>(m_vpObj[i])->GetCharID() == cidZabat)
				{
					DrawZabatRadar(screen);
				}
			}
		}
	}
	//if (siFPS >= 1) {siFPS = 0;}
	//siFPS++;
}

void Level::Update(float fDeltaTime)
{
	CheckForCollisions();
	for (int i = m_vpObj.size() - 1; i >= 0; i--)
	{
		//if (m_vpObj[i]->GetState() == stateAlive)
		if (m_vpObj[i]->GetState() == stateDead && m_vpObj[i]->GetType() == typeCharacter)
		{
			AddExplosion(m_vpObj[i]);
			Tile* temp = NULL;
			while (temp == NULL)
			{temp = m_pMap->FindEmptyPickupPoint(ttSpawnPoint);}
			m_vpObj[i]->SetX(temp->GetX() + 16);
			m_vpObj[i]->SetY(temp->GetY() + 16);
			temp->SetHasPickup(true);
		}
		
		if (m_vpObj[i]->GetType() == typeCharacter)
		{
			if (dynamic_cast<Character*>(m_vpObj[i])->GetIsBot() == true)
			{
				m_aFSM[dynamic_cast<Character*>(m_vpObj[i])->GetCharID()]->process(fDeltaTime);
			}
		}
		
		m_vpObj[i]->Update(fDeltaTime);
		
		if (m_vpObj[i]->GetState() == stateDead)
		{
			if (m_vpObj[i]->GetType() == typeBullet)
			{
				KillBullet(m_vpObj[i], i);
			}
			else if (m_vpObj[i]->GetType() == typeExplosion)
			{
				m_vpObj[i]->Dispose();
				m_vpObj.erase(m_vpObj.begin() + i);
			}
		}
	}
}

Character* Level::GetCharacter(int id)
{
	for (m_vpObjIT = m_vpObj.begin(); m_vpObjIT != m_vpObj.end(); m_vpObjIT++)
	{
		if ((*m_vpObjIT)->GetType() == typeCharacter)
		{
			Character* c1 = dynamic_cast<Character*>((*m_vpObjIT));
			if (c1->GetCharID() == id)
			{
				return c1;
			}
		}
	}
	return dynamic_cast<Character*>(*m_vpObj.begin());
}
Object* Level::GetObject(int id)
{
	for (m_vpObjIT = m_vpObj.begin(); m_vpObjIT != m_vpObj.end(); m_vpObjIT++)
	{
		if ((*m_vpObjIT)->GetID() == id)
		{
			return (*m_vpObjIT);
		}
	}
	return *m_vpObj.begin();
}

void Level::AddCharacter(int cID, float x, float y, string name, int state, bool bot)
{
	Character *temp;
	temp = new Character();
	temp->Init(cID, x, y, name, bot);
	temp->SetState(state);
	temp->SetType(typeCharacter);
	m_vpObj.push_back(temp);
}

void Level::AddCharacter(int cID, string name, bool bot)
{
	int x = 0, y = 0;
	Character *temp;
	temp = new Character();
	Tile* tileTemp = m_pMap->FindEmptyPickupPoint(ttSpawnPoint);
	if (tileTemp != NULL)
	{
		x = tileTemp->GetX() + 16; y = tileTemp->GetY() + 16;
		temp->Init(cID, x, y, name, bot);
		temp->SetState(stateAlive);
		temp->SetType(typeCharacter);
		tileTemp->SetHasPickup(true);
		m_vpObj.push_back(temp);
	}
	//if (bot == true)
	//{
		m_aFSM[cID] = new FSM(temp, this, m_pPF);
	//}
}

void Level::AddBullet(int cID, bool bUseAlt)
{
	Character* c = GetCharacter(cID);
	if ((bUseAlt == false && c->GetStats()->GetBulletsLeft() > 0) || (bUseAlt == true && c->GetStats()->GetEnergy() > 0))
	{
		Bullet* temp;
		temp = new Bullet();
		int tempBT = c->GetStats()->GetBulletType();
		if (bUseAlt == true) {tempBT = btMissile;}
		temp->Init(cID, tempBT, c->GetX(), c->GetY(), c->GetStats()->GetDirection());
		temp->SetState(stateAlive);
		temp->SetType(typeBullet);
		m_vpObj.push_back(temp);
		if (bUseAlt == true) 
		{
			c->GetStats()->SetEnergy(c->GetStats()->GetEnergy() - 1);
			m_pSM->PlaySoundEffect(soundMissile, soundMissile);
		}
		else 
		{
			c->GetStats()->SetBulletsLeft(c->GetStats()->GetBulletsLeft() - 1);
			if (temp->GetBullType() == btBullet)
			{m_pSM->PlaySoundEffect(soundBullet, soundBullet);}
			else
			{m_pSM->PlaySoundEffect(soundLaser, soundLaser);}
		}
	}
}

void Level::AddExplosion(Object* obj)
{
	cout << "Adding Explosion!" << endl;
	Explosions* temp;
	temp = new Explosions;
	if (obj->GetType() == typeBullet)
	{
		Bullet* b = dynamic_cast<Bullet*>(obj);
		temp->Init(b->GetType(), b->GetID(), b->GetOwner(), b->GetX(), b->GetY(), 10);
		m_pSM->PlaySoundEffect(soundExplosion, soundExplosion);
	}
	else if (obj->GetType() == typeCharacter)
	{
		Character* c = dynamic_cast<Character*>(obj);
		temp->Init(c->GetType(), c->GetID(), c->GetCharID(), c->GetX(), c->GetY(), 12);
		m_pSM->PlaySoundEffect(soundDead, soundDead);
	}

	m_vpObj.push_back(temp);
}

void Level::KillBullet(Object* obj, int pos)
{
	bool bAddExplosion = false;
	Bullet *temp = new Bullet;
	if (dynamic_cast<Bullet*>(obj)->GetBullType() == btMissile)
	{
		temp->SetType(typeBullet);
		temp->SetID(obj->GetID());
		temp->SetX(obj->GetX());
		temp->SetY(obj->GetY());
		temp->SetOwner(dynamic_cast<Bullet*>(obj)->GetOwner());
		temp->SetBullType(dynamic_cast<Bullet*>(obj)->GetBullType());
		bAddExplosion = true;
	}
	obj->Dispose();
	m_vpObj.erase(m_vpObj.begin() + pos);
	if (bAddExplosion == true) {AddExplosion(temp);}
	delete temp;
	//cout << "Object Erased: " << i << endl;
}

void Level::AddPickup(int pt, float x, float y)
{
	//static int iCurrPickup = 0;
	Pickup* temp;
	temp = new Pickup();
	temp->Init(pt, x, y);
	temp->SetState(stateAlive);
	temp->SetType(typePickup);
	m_vpObj.push_back(temp);
	//iCurrPickup++;
	//if (iCurrPickup > 2)
	//{iCurrPickup = 0;}
}

void Level::AddPickup(int pt)
{
	Pickup* temp;
	temp = new Pickup();
	Tile* tileTemp = m_pMap->FindEmptyPickupPoint(pt+20);
	if (tileTemp != NULL)
	{
		//cout << "Pickup Location: R: " << tileTemp->GetRow() << " Col: " << tileTemp->GetCol() << endl;
		//cout << "Pickup Location: X: " << tileTemp->GetX() << " Y: " << tileTemp->GetY() << endl;
		temp->Init(pt, tileTemp->GetX() + 16, tileTemp->GetY() + 16);
		temp->SetState(stateAlive);
		temp->SetType(typePickup);
		tileTemp->SetHasPickup(true);
		m_vpObj.push_back(temp);
	}
	else
	{cout << "No Pickup Location Found." << endl;}
}

Object* Level::FindNearestObject(int myX, int myY, int myID, int searchType, float searchRadius)
{
	Object* temp = NULL;
	float fDistance = 0, fCurrShortest = 0;
	int pickupSearchType = -1; bool bSearchFound = false;

	if (searchType > 9)
	{
		pickupSearchType = searchType - 10;
		searchType = 1;
	}

	for (m_vpObjIT = m_vpObj.begin(); m_vpObjIT != m_vpObj.end(); m_vpObjIT++)
	{
		bSearchFound = false;
		if ((*m_vpObjIT)->GetID() != myID && (*m_vpObjIT)->GetState() == stateAlive)
		{
			if ((*m_vpObjIT)->GetType() == searchType || searchType == -1)
			{
				if (pickupSearchType > -1)
				{
					if (dynamic_cast<Pickup*>((*m_vpObjIT))->GetPickupType() == pickupSearchType)
						{bSearchFound = true;}
				}
				else
					{bSearchFound = true;}

				if (bSearchFound == true)
				{
					fDistance = pow(((*m_vpObjIT)->GetX() - myX), 2)+ pow(((*m_vpObjIT)->GetY() - myY), 2);
					if (searchRadius > -1) {searchRadius = pow(searchRadius, 2);}
					if ((fDistance < fCurrShortest || fCurrShortest == 0) && (searchRadius == -1 || fDistance <= searchRadius))
					{
						temp = (*m_vpObjIT);
						fCurrShortest = fDistance;
						//cout << "Found Nearest Object!" << endl;
					}
				}
			}
		}
	}
	//cout << "Exiting FindNearestObject." << endl;
	return temp;
}

Object* Level::FindFurthestObject(int myX, int myY,int myID, int searchType)
{
	Object* temp = NULL;
	float fDistance = 0, fCurrLongest = 0;
	int pickupSearchType = -1; bool bSearchFound = false;

	if (searchType >= 10)
	{
		pickupSearchType = searchType - 10;
		searchType = 1;
	}

	for (m_vpObjIT = m_vpObj.begin(); m_vpObjIT != m_vpObj.end(); m_vpObjIT++)
	{
		bSearchFound = false;
		if ((*m_vpObjIT)->GetID() != myID)
		{
			if ((*m_vpObjIT)->GetType() == searchType || searchType == -1)
			{
				if (pickupSearchType >= 0)
				{
					if (dynamic_cast<Pickup*>((*m_vpObjIT))->GetPickupType() == pickupSearchType)
						{bSearchFound = true;}
				}
				else
					{bSearchFound = true;}

				if (bSearchFound == true)
				{
					fDistance = pow(((*m_vpObjIT)->GetX() - myX), 2)+ pow(((*m_vpObjIT)->GetY() - myY), 2);
					if (fDistance > fCurrLongest || fCurrLongest == 0)
					{
						temp = (*m_vpObjIT);
						fCurrLongest = fDistance;
					}
				}
			}
		}
	}
	return temp;
}

void Level::CheckForCollisions()
{
	if (m_bIsHost == true)
	{
		for (int i = m_vpObj.size() - 1; i > 0; i--)
		{
			if (m_vpObj[i]->GetState() == stateAlive)
			{
				for (int j = i-1; j >= 0; j--)
				{
					if (m_vpObj[j]->GetState() == stateAlive)
					{
						if (CheckCollision(m_vpObj[i], m_vpObj[j]) == true)
						{
							/*if (m_vpObj[j]->GetType() == typeCharacter || m_vpObj[i]->GetType() == typeCharacter)
							{
								cout << "Objects: t: " << m_vpObj[i]->GetType() << " i:" << m_vpObj[i]->GetID() << " x: " <<  m_vpObj[i]->GetX() << " y: " <<  m_vpObj[i]->GetY();
								cout << " t: " << m_vpObj[j]->GetType() << " j: " << m_vpObj[j]->GetID() << " x: " <<  m_vpObj[j]->GetX() << " y: " <<  m_vpObj[j]->GetY() << endl;
							}*/
							m_vpObj[j]->Collide(m_vpObj[i]);
							m_vpObj[i]->Collide(m_vpObj[j]);
						}
					}
				}
			}
		}
	}
	else
	{
		for (m_vpObjIT = m_vpObj.begin(); m_vpObjIT != m_vpObj.end(); m_vpObjIT++)
		{
			if ((*m_vpObjIT)->GetType() == typeCharacter)
			{
				if (reinterpret_cast<Character*>((*m_vpObjIT))->GetCharID() == m_iMyID)
				{
					if ((*m_vpObjIT)->GetState() == stateAlive)
					{
						CheckCollisionAgainst((*m_vpObjIT));
						break;
					}
				}
			}
		}
	}
}

void Level::CheckCollisionAgainst(Object* testObj)
{
	for (int j = m_vpObj.size() - 1; j > 0; j--)
	{
		if (m_vpObj[j]->GetState() == stateAlive && m_vpObj[j] != (*m_vpObjIT))
		{
			if (CheckCollision((*m_vpObjIT), m_vpObj[j]) == true)
			{
				/*if (m_vpObj[j]->GetType() == typeCharacter || m_vpObj[i]->GetType() == typeCharacter)
				{
					cout << "Objects: t: " << m_vpObj[i]->GetType() << " i:" << m_vpObj[i]->GetID() << " x: " <<  m_vpObj[i]->GetX() << " y: " <<  m_vpObj[i]->GetY();
					cout << " t: " << m_vpObj[j]->GetType() << " j: " << m_vpObj[j]->GetID() << " x: " <<  m_vpObj[j]->GetX() << " y: " <<  m_vpObj[j]->GetY() << endl;
				}*/
				m_vpObj[j]->Collide((*m_vpObjIT));
				(*m_vpObjIT)->Collide(m_vpObj[j]);
			}
		}
	}
}

bool Level::CheckCollision(Object *Obj1, Object *Obj2)
{
	bool bResult = false;

	float i1X = Obj1->GetX(), i1Y = Obj1->GetY();
	float i2X = Obj2->GetX(), i2Y = Obj2->GetY();
	float i1S = Obj1->GetSize(), i2S = Obj2->GetSize();

	/*if (Obj1->GetType() == typeCharacter || Obj2->GetType() == typeCharacter)
	{
		cout << "bResult = true.";
		cout << " i1X: " << i1X << " i1Y: " << i1Y << " i1S: " << i1S;
		cout << " i2X: " << i2X << " i2Y: " << i2Y << " i2S: " << i2S;
		cout << endl;
	}*/

	if (Obj1->GetType() == typeCharacter)
	{
		i1X -= 16;//= (i1X - (Obj1->GetSize() / 2)) + (Obj1->GetSize() / 3); 
		i1Y -= 16;//= (i1Y - (Obj1->GetSize() / 2)) + (Obj1->GetSize() / 3);
		i1S = 32; ///= 3;
	}
	else if (Obj1->GetType() == typeTile)
	{//do nothing
	}
	else
		{i1X -= Obj1->GetSize() / 2; i1Y -= Obj1->GetSize() / 2;}

	if (Obj2->GetType() == typeCharacter)
	{
		i2X -= 16; //= (i2X - (Obj1->GetSize() / 2)) + (Obj2->GetSize() / 3); 
		i2Y -= 16; //= (i2Y - (Obj1->GetSize() / 2)) + (Obj2->GetSize() / 3);
		i2S = 32; // /= 3;
	}
	else if (Obj2->GetType() == typeTile)
	{//do nothing
	}
	else
		{i2X -= Obj2->GetSize() / 2; i2Y -= Obj2->GetSize() / 2;}

	if (i1X > (i2X + i2S))
		{bResult = false;}
	else if ((i1X + i1S) < i2X)
		{bResult = false;}
	else if (i1Y > (i2Y + i2S))
		{bResult = false;}
	else if ((i1Y + i1S) < i2Y)
		{bResult = false;}
	else
	{
		/*if (Obj1->GetType() == typeCharacter || Obj2->GetType() == typeCharacter)
		{
			cout << "bResult: ";
			cout << " T: " << Obj1->GetType() << " i1X: " << i1X << " i1Y: " << i1Y << " i1S: " << i1S;
			cout << " T: " << Obj2->GetType() << " i2X: " << i2X << " i2Y: " << i2Y << " i2S: " << i2S;
			cout << endl;
		}*/
		bResult = true;
	}

	return bResult;
}

bool Level::CheckCollision(float p1X, float p1Y, float p1S, float p2X, float p2Y, float p2S)
{
	bool bResult = false;

	if (p1X > (p2X + p2S))
		{bResult = false;}
	else if ((p1X + p1S) < p2X)
		{bResult = false;}
	else if (p1Y > (p2Y + p2S))
		{bResult = false;}
	else if ((p1Y + p1S) < p2Y)
		{bResult = false;}
	else
		{bResult = true;}

	return bResult;
}

void Level::UpdateWindowPos(float winX, float winY)
{
	m_fWinPosX = winX;
	m_fWinPosY = winY;
}

void Level::StartEnergy(int cid)
{
	if (GetCharacter(cid)->GetStats()->GetEnergy() > 0)
	{
		if (cid <= cidPteras)
		{
			AddBullet(cid, true);
		}
		else
		{
			GetCharacter(cid)->SetIsUsingEnergy(true);
			if (cid == cidRedler) {GetCharacter(cid)->SetSurface("Images/RLS.png");}
		}
	}
}
void Level::StopEnergy(int cid)
{
	GetCharacter(cid)->SetIsUsingEnergy(false);
	if (cid == cidRedler) {GetCharacter(cid)->SetSurface("Images/RL.png");}
}

void Level::SetupMap(int mapID, int width, int height)
{
	string mapName = "MAP#"; char buffer[3] = {' ', ' ', ' '};
	mapName.replace(mapName.find("#"), 1, itoa(mapID, buffer, 10));

	m_pMap->SetupMap(width, height, mapName, m_vpObj);
	m_pPF->Init(width,height,Tile::GetSize());
	m_pPF->SetMap(m_pMap->GetWayStarData());
}

void Level::SetupPickups()
{
	//AddPickup(ptHealth, 250, 700);
	//AddPickup(ptAmmo, 700, 100);
	//AddPickup(ptEnergy, 850, 495);
	m_pMap->ResetPickupPoint(ttSpawnPoint);
	AddPickup(ptHealth);
	AddPickup(ptHealth);
	AddPickup(ptHealth);
	AddPickup(ptHealth);
	AddPickup(ptHealth);
	AddPickup(ptAmmo);
	AddPickup(ptAmmo);
	AddPickup(ptAmmo);
	AddPickup(ptAmmo);
	AddPickup(ptAmmo);
	AddPickup(ptEnergy);
	AddPickup(ptEnergy);
	AddPickup(ptEnergy);
	AddPickup(ptEnergy);
}

void Level::UpdateCharacterPos(int cid, float x, float y, float dir)
{
	Character* temp = GetCharacter(cid);
	temp->SetX(x);
	temp->SetY(y);
	temp->GetStats()->SetDirection(dir);
}

void Level::DrawZabatRadar(SDL_Surface* screen)
{
	static int siTimer = 0;
	float x = 0, y = 0, tempX = 0, tempY = 0;
	float realX = GetCharacter(cidZabat)->GetX();
	float realY = GetCharacter(cidZabat)->GetY();
	float degToTarget = 0;
	SDL_Rect dclip;
	SDL_Surface* temp = NULL;
	//Zabat Radar
	if (GetCharacter(cidZabat)->GetIsUsingEnergy() == true)
	{
		/*cout << "Original XY: ";
		for (int j = 0; j < 3; j++)
		{
			cout << " tempX[" << j << "]: " << tempX[j];
			cout << " tempY[" << j << "]: " << tempY[j];
		}
		cout << endl;*/
		if (siTimer == 0)
		{
			m_pSM->PlaySoundEffect(soundRadar, soundRadar);
			siTimer = 10;
		}
		else if (siTimer < 10)
			{siTimer--;}

		for (int i = 0; i < 5; i++)
		{
			//tempX[0] = realX; tempX[1] = realX - 10; tempX[2] = realX + 10;
			//tempY[0] = realY; tempY[1] = realY - 10; tempY[2] = realY - 10;
			x = GetCharacter(i)->GetX();
			y = GetCharacter(i)->GetY();
			
			degToTarget = atan2(y - realY, x - realX);
			degToTarget = degToTarget * (180 / M_PI) - 90;

			tempX = realX - (30 * sin(degToTarget * M_PI / 180));
			tempY = realY + (30 * cos(degToTarget * M_PI / 180));
			tempX -= m_fWinPosX;
			tempY -= m_fWinPosY;
			
			temp = rotozoomSurface(m_Arrow, -degToTarget, 1.0, SMOOTHING_ON);

			dclip.x = tempX - (temp->w/2);
			dclip.y = tempY - (temp->h/2);
			dclip.w = temp->w; dclip.h = temp->h;

			SDL_BlitSurface(temp, &temp->clip_rect, screen, &dclip);
			SDL_FreeSurface(temp);

			/*cout << "Updated XY: ";
			for (int j = 0; j < 3; j++)
			{
				cout << "tempX[" << j << "]: " << tempX[j];
				cout << " tempY[" << j << "]: " << tempY[j];
			}
			cout << endl;*/
		}
	}
	else
	{
		siTimer = 0;
	}
}

Map* Level::GetMap()
{
	return m_pMap;
}