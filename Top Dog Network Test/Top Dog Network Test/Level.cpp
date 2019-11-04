//Blake Sullivan - Level.cpp
#include "Level.h"

Level::Level()
{
	m_pMap = new Map();
	//Init();
}
Level::~Level()
{
	delete m_pMap;
}

void Level::Init(int myID)
{
	/*AddCharacter(cidBuster, 2*32, 3*32, "Raven Vega", stateAlive, false);
	AddCharacter(cidPteras, 31*32, 3*32, "Brad Hunter", stateAlive, true);
	AddCharacter(cidRaynos, 61*32, 3*32, "Bit Cloud", stateAlive, true);
	AddCharacter(cidRedler, 12*32, 44*32, "Leena Tauros", stateAlive, true);
	AddCharacter(cidStorm, 31*32, 44*32, "Van Flyheight", stateAlive, true);	
	AddCharacter(cidZabat, 61*32, 44*32, "Irvine Kinneas", stateAlive, true);*/
}

void Level::Draw(SDL_Surface* screen, float fDT)
{
	m_pMap->DrawMap(screen, m_fWinPosX, m_fWinPosY);
	for (int i = m_vpObj.size() - 1; i >= 0; i--)
	{
		if (m_vpObj[i]->GetState() == stateAlive)
			{m_vpObj[i]->Draw(screen, fDT, m_fWinPosX, m_fWinPosY);}
	}
}

void Level::Update(float fDeltaTime)
{
	CheckForCollisions();
	for (int i = m_vpObj.size() - 1; i >= 0; i--)
	{
		//if (m_vpObj[i]->GetState() == stateAlive)
		m_vpObj[i]->Update(fDeltaTime);
		if (m_vpObj[i]->GetState() == stateDead)
		{
			if (m_vpObj[i]->GetType() == typeBullet)
			{
				m_vpObj[i]->Dispose();
				m_vpObj.erase(m_vpObj.begin()+i);
				//cout << "Object Erased: " << i << endl;
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
}

void Level::AddBullet(int cID, bool bUseAlt)
{
	Character* c = GetCharacter(cID);
	if (c->GetStats()->GetBulletsLeft() > 0)
	{
		Bullet* temp;
		temp = new Bullet();
		int tempBT = c->GetStats()->GetBulletType();
		if (bUseAlt == true) {tempBT = btMissile;}
		temp->Init(cID, tempBT, c->GetX(), c->GetY(), c->GetStats()->GetDirection());
		temp->SetState(stateAlive);
		temp->SetType(typeBullet);
		m_vpObj.push_back(temp);
		c->GetStats()->SetBulletsLeft(c->GetStats()->GetBulletsLeft() - 1);
	}
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

Object* Level::FindNearestObject(int myX, int myY, int searchType, int id, int searchRadius)
{
	
	return NULL;
}

Object* Level::FindFurtherestObject(int myX, int myY, int id)
{
	return NULL;
}

void Level::CheckForCollisions()
{
	for (int i = m_vpObj.size() - 1; i > 0; i--)
	{
		if (m_vpObj[i]->GetState() != stateDead)
		{
			for (int j = i-1; j >= 0; j--)
			{
				if (m_vpObj[j]->GetState() != stateDead)
				{
					if (CheckCollision(m_vpObj[i], m_vpObj[j]) == true)
					{
						m_vpObj[j]->Collide(m_vpObj[i]);
						m_vpObj[i]->Collide(m_vpObj[j]);
					}
				}
			}
		}
	}
}

bool Level::CheckCollision(Object *Obj1, Object *Obj2)
{
	bool bResult = false;

	int i1X = Obj1->GetX(), i1Y = Obj1->GetY();
	int i2X = Obj2->GetX(), i2Y = Obj2->GetY();
	int i1S = Obj1->GetSize(), i2S = Obj2->GetSize();

	if (Obj1->GetType() == typeCharacter)
	{
		i1X -= 16;//= (i1X - (Obj1->GetSize() / 2)) + (Obj1->GetSize() / 3); 
		i1Y -= 16;//= (i1Y - (Obj1->GetSize() / 2)) + (Obj1->GetSize() / 3);
		i1S = 32; ///= 3;
	}
	else if (Obj1->GetType() != typeTile)
		{i1X -= Obj1->GetSize() / 2; i1Y -= Obj1->GetSize() / 2;}

	if (Obj2->GetType() == typeCharacter)
	{
		i2X -= 16; //= (i2X - (Obj1->GetSize() / 2)) + (Obj2->GetSize() / 3); 
		i2Y -= 16; //= (i2Y - (Obj1->GetSize() / 2)) + (Obj2->GetSize() / 3);
		i2S = 32;///= 3;
	}
	else if (Obj1->GetType() != typeTile)
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
	if (cid <= cidPteras)
	{
		AddBullet(cid, true);
	}
}
void Level::StopEnergy(int cid)
{

}

void Level::SetupMap(int mapID, int width, int height)
{
	string mapName = "MAP#"; char buffer[3] = {' ', ' ', ' '};
	mapName.replace(mapName.find("#"), 1, itoa(mapID, buffer, 10));

	m_pMap->SetupMap(width, height, mapName, m_vpObj);
}

void Level::SetupPickups()
{
	//AddPickup(ptHealth, 250, 700);
	//AddPickup(ptAmmo, 700, 100);
	//AddPickup(ptEnergy, 850, 495);
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