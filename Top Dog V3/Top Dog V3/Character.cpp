//Blake Sullivan - Character.cpp
#include "Character.h"
#include "Pickup.h"
#include "Bullet.h"

Character::Character()
{
	//m_pLevel = level;
	SetX(0);
	SetY(0);
	m_cStats.SetChangeAngle(0);
	m_cStats.SetDirection(0);
	m_cStats.SetRotateAngle(0);
	m_cStats.SetMoveSpeed(0);
	SetCharID(-1);
	SetInGame(false);
	SetIsBot(false);
	SetName(" ");
	SetIsUsingEnergy(false);
	SetFired(false);
}

void Character::Init(int cID, float x, float y, std::string name, bool bot)
{
	SetX(x);
	SetY(y);
	//cout << "In Char Init. Name: " << name << endl;
	SetName(name);
	//cout << "In Char Init. GetName(): " << GetName() << endl;
	SetCharID(cID);
	SetID(cID);
	m_cStats.SetChangeAngle(0);
	m_cStats.SetDirection(0);
	SetIsBot(bot);

	LoadCharDiff(GetCharID());

	SetIsUsingEnergy(false);
	SetFired(false);

	//m_pFSM = new FSM(this, m_pLevel);
}

void Character::LoadCharDiff(int cID)
{
	//m_cStats.SetBulletsLeft(20);
	switch (cID)
	{
	case cidBuster:	//Buster Eagle
		m_cStats.SetRotateAngle(120);
		m_cStats.SetMoveSpeed(180);
		m_cStats.SetMaxHealth(150);
		m_cStats.SetBulletType(btBullet);
		m_cStats.SetBulletMax(30);
		m_cStats.SetMaxEnergy(10);
		m_cStats.SetRateOfFire(1);
		SetSurfaceName("Images/BE.png");
		SetSurface(GetSurfaceName());
		SetSize(96);
	break;
	case cidPteras: //Pteras
		m_cStats.SetRotateAngle(175);
		m_cStats.SetMoveSpeed(225);
		m_cStats.SetMaxHealth(100);
		m_cStats.SetBulletType(btBullet);
		m_cStats.SetBulletMax(100);
		m_cStats.SetMaxEnergy(30);
		m_cStats.SetRateOfFire(0.5);
		SetSurfaceName("Images/PT.png");
		SetSurface(GetSurfaceName());
		SetSize(96);
	break;
	case cidZabat: //Zabat
		m_cStats.SetRotateAngle(100);
		m_cStats.SetMoveSpeed(300);
		m_cStats.SetMaxHealth(120);
		m_cStats.SetBulletType(btLaser);
		m_cStats.SetBulletMax(50);
		m_cStats.SetMaxEnergy(100);
		m_cStats.SetRateOfFire(2);
		SetSurfaceName("Images/Z.png");
		SetSurface(GetSurfaceName());
		SetSize(96);
	break;
	case cidRedler: //Redler
		m_cStats.SetRotateAngle(150);
		m_cStats.SetMoveSpeed(265);
		m_cStats.SetMaxHealth(120);
		m_cStats.SetBulletType(btBullet);
		m_cStats.SetBulletMax(100);
		m_cStats.SetMaxEnergy(100);
		m_cStats.SetRateOfFire(0.5);
		SetSurfaceName("Images/RL.png");
		SetSurface(GetSurfaceName());
		SetSize(96);
	break;
	case cidStorm: //Stormsworder
		m_cStats.SetRotateAngle(120);
		m_cStats.SetMoveSpeed(330);
		m_cStats.SetMaxHealth(150);
		m_cStats.SetBulletType(btBullet);
		m_cStats.SetBulletMax(100);
		m_cStats.SetMaxEnergy(100);
		m_cStats.SetRateOfFire(0.5);
		SetSurfaceName("Images/SS.png");
		SetSurface(GetSurfaceName());
		SetSize(96);
	break;
	default: //Raynos
		m_cStats.SetRotateAngle(150);
		m_cStats.SetMoveSpeed(300);
		m_cStats.SetMaxHealth(100);
		m_cStats.SetBulletType(btLaser);
		m_cStats.SetBulletMax(50);
		m_cStats.SetMaxEnergy(100);
		m_cStats.SetRateOfFire(2);
		SetSurfaceName("Images/R.png");
		SetSurface(GetSurfaceName());
		SetSize(96);
	}
	SetDamage(1);
}

void Character::Draw(SDL_Surface* screen, float fDeltaTime, float winX, float winY)
{
	if (GetState() != stateDead)
	{
		//cout << "Direction: " << GetStats()->GetDirection() << endl;
		SDL_Rect dclip;
		SDL_Surface* temp = NULL;
		temp = rotozoomSurface(GetSurface(), GetStats()->GetDirection(), 1.0, SMOOTHING_ON);
		//SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 255, 0, 255));

		int realX = GetX() - winX;
		int realY = GetY() - winY;

		dclip.x = realX - (temp->w/2);
		dclip.y = realY - (temp->h/2);
		dclip.w = temp->w; dclip.h = temp->h;

		SDL_BlitSurface(temp, &temp->clip_rect, screen, &dclip);
		SDL_FreeSurface(temp);

		int iCentreX = realX, iCentreY = realY;

		if (GetState() == stateRespawn)
		{
			filledCircleRGBA(screen, GetX() - winX, GetY() - winY, GetSize() - (GetRespawnTimer() * 10), 200, 200, 200, 100);
		}

		//Hit boxes
		//filledCircleRGBA(screen, GetX() - winX, GetY() - winY, 10, 255, 0, 0, 255);
		//rectangleRGBA(screen, iCentreX - 16, iCentreY - 16, iCentreX + 16, iCentreY + 16, 255, 0, 0, 255);
		
		/*rectangleRGBA(screen, iCentreX - (16 + 32), iCentreY - 16, iCentreX - 16, iCentreY + 16, 255, 0, 0, 255);
		rectangleRGBA(screen, iCentreX + 16, iCentreY - 16, iCentreX + (16 + 32), iCentreY + 16, 255, 0, 0, 255);
		rectangleRGBA(screen, iCentreX - 16, iCentreY - (16 + 32), iCentreX + 16, iCentreY - 16, 255, 0, 0, 255);
		rectangleRGBA(screen, iCentreX - 16, iCentreY + 16, iCentreX + 16, iCentreY + (16 + 32), 255, 0, 0, 255);*/

		//rectangleRGBA(screen, GetX() - (GetSize() / 2), GetY() - (GetSize() / 2), GetX() + (GetSize() / 2), GetY() + (GetSize() / 2), 0, 0, 0, 255);
		/*if (GetCharID() == cidPteras)
		{
			//cout << "Character: " << GetCharID() << " dclip.x: " << dclip.x << " dclip.y: " << dclip.y << " iCentreX: " << iCentreX << " iCentreY: " << iCentreY << endl;
		}*/

		//Life Bar
		//if (iCentreX - 50 > 0 && iCentreX + 50 < screen->clip_rect.w && iCentreY + 50 > 0)
		//{
		boxRGBA(screen, iCentreX - 50, iCentreY + 50, iCentreX - 50 + ((GetStats()->GetHealth() / GetStats()->GetMaxHealth()) * 100), iCentreY + 56, 255, 0, 0, 255);
		rectangleRGBA(screen, iCentreX - 50, iCentreY + 50, iCentreX + 50, iCentreY + 56, 0,0,0,255);
		//}
	}
}
void Character::Update(float fDeltaTime)
{
	/*if (GetIsBot() == true)
	{m_pFSM->process();}*/

	if (GetFired() == true) {SetFired(false);}

	if (GetState() == stateDead)
	{
		SetState(stateRespawn);
	}
	else if (GetState() == stateRespawn && GetRespawnTimer() <= 5)
	{
		SetRespawnTimer(GetRespawnTimer() + fDeltaTime);
	}
	else if (GetState() == stateRespawn && GetRespawnTimer() > 5)
	{
		SetRespawnTimer(0);
		SetState(stateAlive);
		GetStats()->SetHealth(GetStats()->GetMaxHealth());
		GetStats()->SetBulletsLeft(GetStats()->GetBulletMax());
		GetStats()->SetEnergy(GetStats()->GetMaxEnergy());
		cout << "Player Alive Again." << endl;
	}

	if (GetIsUsingEnergy() == true)
	{
		int drainMult = 1;

		if (((GetCharID() == cidRedler || GetCharID() == cidZabat) && m_bMoved == true)  || (GetCharID() == cidRaynos || GetCharID() == cidStorm))
			{drainMult = 10;}
		if (GetCharID() == cidStorm) {SetDamage(10);}

		GetStats()->SetEnergy(GetStats()->GetEnergy() - (drainMult * fDeltaTime));

		if (GetStats()->GetEnergy() <= 0)
		{
			SetIsUsingEnergy(false);
			switch (GetCharID())
			{
			case cidRedler:
				{SetSurface("Images/RL.png");}
			break;
			case cidStorm:
				{SetDamage(1);}
			break;
			default:
			break;
			}
		}
	}

	if (GetIsUsingEnergy() == false && GetCharID() == cidStorm)
	{SetDamage(1);}

	if ((GetX() < 0 || GetX() > 2048 || GetY() < 0 || GetY() > 1536) && GetState() == stateAlive)
	{
		GetStats()->SetHealth(0);
		SetState(stateDead);
	}

	m_bMoved = false;
}
void Character::Collide(Object* obj)
{
	//cout << "Character Collided" << endl;
	float tempHealth = GetStats()->GetHealth();
	float tempDamage = obj->GetDamage();

	if (GetCharID() == cidStorm && GetIsUsingEnergy() == true) {tempDamage /= 2;}

	tempHealth -= tempDamage;

	if (obj->GetType() != typePickup)
	{
		if (obj->GetType() == typeBullet)
		{
			Bullet* b1 = dynamic_cast<Bullet*>(obj);
			if (b1->GetOwner() == GetCharID())
			{return;}
		}
		GetStats()->SetHealth(tempHealth);
	}
	else
	{
		Pickup* p1 = dynamic_cast<Pickup*>(obj);
		if (p1->GetPickupType() == ptHealth)
			{GetStats()->SetHealth(tempHealth);}
		else if (p1->GetPickupType() == ptAmmo)
			{GetStats()->SetBulletsLeft(GetStats()->GetBulletMax());}
		else if (p1->GetPickupType() == ptEnergy)
			{GetStats()->SetEnergy(GetStats()->GetMaxEnergy());}
	}

	if (GetStats()->GetHealth() <= 0)
		{SetState(stateDead);}
	else if (GetStats()->GetHealth() > GetStats()->GetMaxHealth())
		{GetStats()->SetHealth(GetStats()->GetMaxHealth());}
}
void Character::Dispose()
{
	SDL_FreeSurface(GetSurface());
}

void Character::MoveCharacter(char cDir, float fdt)
{
	float moveUp = 1, moveElse = 1;
	if (GetIsUsingEnergy() == true)
	{
		if (GetCharID() == cidRaynos)
		{
			moveUp = 2;
			moveElse = 2;
		}
		else if (GetCharID() == cidStorm)
		{
			moveUp = 2;
			moveElse = 0.1;
		}
		else if (GetCharID() == cidRedler)
		{
			moveUp = 0.5;
			moveElse = 0.5;
		}
	}

	switch (cDir)
	{
	case 'u':
		MoveUp(fdt, moveUp);
	break;
	case 'd':
		MoveDown(fdt, moveElse);
	break;
	case 'l':
		MoveLeft(fdt, moveElse);
	break;
	case 'r':
		MoveRight(fdt, moveElse);
	break;
	case 'q':
		RotateLeft(fdt, moveElse);
	break;
	case 'e':
		RotateRight(fdt, moveElse);
	break;
	}

	m_bMoved = true;
}
void Character::MoveLeft(float fdt, float speedMult)
{
	float tempX = 0, tempY = 0;
	float tempSpeedMult = 0.5;
	tempX = GetX() - (((m_cStats.GetMoveSpeed() * tempSpeedMult * speedMult) * fdt) * sin((m_cStats.GetDirection() + 90) * M_PI / 180));
	tempY = GetY() - (((m_cStats.GetMoveSpeed() * tempSpeedMult * speedMult) * fdt) * cos((m_cStats.GetDirection() + 90) * M_PI / 180));
	
	SetX(tempX);
	SetY(tempY);
}
void Character::MoveRight(float fdt, float speedMult)
{
	float tempX = 0, tempY = 0;
	float tempSpeedMult = 0.5;
	tempX = GetX() - (((m_cStats.GetMoveSpeed() * tempSpeedMult * speedMult) * fdt) * sin((m_cStats.GetDirection() - 90) * M_PI / 180));
	tempY = GetY() - (((m_cStats.GetMoveSpeed() * tempSpeedMult * speedMult) * fdt) * cos((m_cStats.GetDirection() - 90) * M_PI / 180));
	SetX(tempX);
	SetY(tempY);
}
void Character::MoveUp(float fdt, float speedMult)
{
	float tempX = 0, tempY = 0;
	tempX = GetX() - (((m_cStats.GetMoveSpeed() * speedMult) * fdt) * sin((m_cStats.GetDirection() * M_PI) / 180));
	tempY = GetY() - (((m_cStats.GetMoveSpeed() * speedMult) * fdt) * cos((m_cStats.GetDirection() * M_PI) / 180));
	SetX(tempX);
	SetY(tempY);
}
void Character::MoveDown(float fdt, float speedMult)
{
	float tempX = 0, tempY = 0;
	tempX = GetX() + ((m_cStats.GetMoveSpeed() * speedMult) * fdt) * sin((m_cStats.GetDirection() * M_PI) / 180);
	tempY = GetY() + ((m_cStats.GetMoveSpeed() * speedMult) * fdt) * cos((m_cStats.GetDirection() * M_PI) / 180);
	SetX(tempX);
	SetY(tempY);
}
void Character::RotateLeft(float fdt, float speedMult)
{
	float caTemp = m_cStats.GetDirection();
	//if (GetCharID() == cidBuster) {cout << "Direction before Rotate: " << caTemp << endl;}
	caTemp += (m_cStats.GetRotateAngle() * speedMult) * fdt;
	if (caTemp > 360) {caTemp -= 360;}
	if (caTemp < 0) {caTemp += 360;}
	m_cStats.SetDirection(caTemp);
	//if (GetCharID() == cidBuster) {cout << "Direction after Rotate: " << caTemp << endl;}
}
void Character::RotateRight(float fdt, float speedMult)
{
	float caTemp = m_cStats.GetDirection();
	caTemp -= (m_cStats.GetRotateAngle() * speedMult) * fdt;
	if (caTemp > 360) {caTemp -= 360;}
	if (caTemp < 0) {caTemp += 360;}
	//m_cStats.SetChangeAngle(caTemp;);
	m_cStats.SetDirection(caTemp);
}

void Character::SetCharID(int id)
{
	m_iCharID = id;
}
void Character::SetName(string n)
{
	m_sName = n;
}
void Character::SetInGame(bool ig)
{
	m_bInGame = ig;
}
void Character::SetIsBot(bool b)
{
	m_bIsBot = b;
}
void Character::SetSurfaceName(string sn)
{
	m_sSurfaceName = sn;
}

int Character::GetCharID()
{
	return m_iCharID;
}
std::string Character::GetName()
{
	return m_sName;
}
CharStats* Character::GetStats()
{
	return &m_cStats;
}
bool Character::GetInGame()
{
	return m_bInGame;
}
bool Character::GetIsBot()
{
	return m_bIsBot;
}
string Character::GetSurfaceName()
{
	return m_sSurfaceName;
}

void Character::SetRespawnTimer(float rt)
{
	m_fRespawnTimer = rt;
}
float Character::GetRespawnTimer()
{
	return m_fRespawnTimer;
}

void Character::SetIsUsingEnergy(bool ue)
{
	m_bUsingEnergy = ue;
}

bool Character::GetIsUsingEnergy()
{
	return m_bUsingEnergy;
}

void Character::SetFired(bool f)
{
	m_bFired = f;
}

bool Character::GetFired()
{
	return m_bFired;
}