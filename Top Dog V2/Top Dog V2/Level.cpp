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
	m_pMap->SetupMap(2048, 1536, "D1", m_vpObj);
	AddCharacter(cidBuster, 400, 250, "Raven Vega", stateAlive, false);
	AddCharacter(cidPteras, 1500, 200, "Brad Hunter", stateAlive, true);
	AddCharacter(cidRaynos, 600, 1200, "Bit Cloud", stateAlive, true);
	AddCharacter(cidRedler, 1200, 450, "Leena Tauros", stateAlive, true);
	AddCharacter(cidStorm, 1300, 1450, "Van Flyheight", stateAlive, true);	
	AddCharacter(cidZabat, 1024, 768, "Irvine Kinneas", stateAlive, true);
	m_HUD.Init(GetCharacter(myID));

	//AddPickup(ptHealth, 250, 700);
	//AddPickup(ptAmmo, 700, 100);
	//AddPickup(ptEnergy, 850, 495);
	AddPickup(ptHealth);
	AddPickup(ptAmmo);
	AddPickup(ptEnergy);
	AddPickup(ptHealth);
	AddPickup(ptAmmo);
	AddPickup(ptEnergy);
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

void Level::Draw(SDL_Surface* screen, float fDT)
{
	m_pMap->DrawMap(screen, m_fWinPosX, m_fWinPosY);
	for (int i = m_vpObj.size() - 1; i >= 0; i--)
	{
		if (m_vpObj[i]->GetState() == stateAlive)
			{m_vpObj[i]->Draw(screen, fDT, m_fWinPosX, m_fWinPosY);}
	}
	m_HUD.Draw(screen);
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
	Tile* tileTemp = m_pMap->FindEmptyPickupPoint();
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

	//cout << "In CheckCollision" << endl;
	int i1X = Obj1->GetX(), i1Y = Obj1->GetY();
	int i2X = Obj2->GetX(), i2Y = Obj2->GetY();
	int i1S = Obj1->GetSize(), i2S = Obj2->GetSize();

	if (Obj1->GetType() == typeCharacter)
	{
		i1X -= ((Obj1->GetSize() / 2) - (Obj1->GetSize() / 3)); 
		i1Y -= ((Obj1->GetSize() / 2) - (Obj1->GetSize() / 3));
		i1S /= 3;
	}
	else
		{i1X -= Obj1->GetSize() / 2; i1Y -= Obj1->GetSize() / 2;}

	if (Obj2->GetType() == typeCharacter)
	{
		i2X -= ((Obj2->GetSize() / 2) - (Obj2->GetSize() / 3)); 
		i2Y -= ((Obj2->GetSize() / 2) - (Obj2->GetSize() / 3));
		i2S /= 3;
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
		{bResult = true;}

	//cout << "Collision Result = " << bResult << endl;

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