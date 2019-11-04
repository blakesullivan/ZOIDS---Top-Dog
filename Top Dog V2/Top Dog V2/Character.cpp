//Blake Sullivan - Character.cpp
#include "Character.h"
#include "Pickup.h"
#include "Bullet.h"

Character::Character()
{
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
		m_cStats.SetBulletMax(30);
		m_cStats.SetMaxEnergy(10);
		SetSurfaceName("BE.bmp");
		SetSurface(GetSurfaceName());
		SetSize(96);
	break;
	case cidPteras: //Pteras
		m_cStats.SetRotateAngle(175);
		m_cStats.SetMoveSpeed(225);
		m_cStats.SetMaxHealth(100);
		m_cStats.SetBulletMax(100);
		m_cStats.SetMaxEnergy(10);
		SetSurfaceName("PT.bmp");
		SetSurface(GetSurfaceName());
		SetSize(96);
	break;
	case cidZabat: //Zabat
		m_cStats.SetRotateAngle(100);
		m_cStats.SetMoveSpeed(300);
		m_cStats.SetMaxHealth(100);
		m_cStats.SetBulletMax(50);
		m_cStats.SetMaxEnergy(100);
		SetSurfaceName("Z.bmp");
		SetSurface(GetSurfaceName());
		SetSize(96);
	break;
	case cidRedler: //Redler
		m_cStats.SetRotateAngle(150);
		m_cStats.SetMoveSpeed(265);
		m_cStats.SetMaxHealth(100);
		m_cStats.SetBulletMax(100);
		m_cStats.SetMaxEnergy(100);
		SetSurfaceName("RL.bmp");
		SetSurface(GetSurfaceName());
		SetSize(96);
	break;
	case cidStorm: //Stormsworder
		m_cStats.SetRotateAngle(120);
		m_cStats.SetMoveSpeed(330);
		m_cStats.SetMaxHealth(100);
		m_cStats.SetBulletMax(100);
		m_cStats.SetMaxEnergy(100);
		SetSurfaceName("SS.bmp");
		SetSurface(GetSurfaceName());
		SetSize(96);
	break;
	default: //Raynos
		m_cStats.SetRotateAngle(150);
		m_cStats.SetMoveSpeed(300);
		m_cStats.SetMaxHealth(120);
		m_cStats.SetBulletMax(50);
		m_cStats.SetMaxEnergy(100);
		SetSurfaceName("R.bmp");
		SetSurface(GetSurfaceName());
		SetSize(96);
	}
}

void Character::Draw(SDL_Surface* screen, float fDeltaTime, float winX, float winY)
{
	if (GetState() == stateAlive)
	{
		//cout << "Direction: " << GetStats()->GetDirection() << endl;
		SDL_Rect dclip;
		SDL_Surface* temp = NULL;
		temp = rotozoomSurface(GetSurface(), GetStats()->GetDirection(), 1.0, SMOOTHING_ON);
		SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 255, 0, 255));

		int realX = GetX() - (temp->w/2) - winX;
		int realY = GetY() - (temp->h/2) - winY;

		dclip.x = realX;
		dclip.y = realY;
		dclip.w = temp->w; dclip.h = temp->h;

		SDL_BlitSurface(temp, &temp->clip_rect, screen, &dclip);
		SDL_FreeSurface(temp);

		int iCentreX = realX + (dclip.w / 2), iCentreY = realY + (dclip.h / 2);
		//circleRGBA(screen, dclip.x + (96/2), dclip.y + (96/2), 30, 255, 0, 0, 255);
		/*rectangleRGBA(screen, iCentreX - 16, iCentreY - 16, iCentreX + 16, iCentreY + 16, 255, 0, 0, 255);
		rectangleRGBA(screen, iCentreX - (16 + 32), iCentreY - 16, iCentreX - 16, iCentreY + 16, 255, 0, 0, 255);
		rectangleRGBA(screen, iCentreX + 16, iCentreY - 16, iCentreX + (16 + 32), iCentreY + 16, 255, 0, 0, 255);
		rectangleRGBA(screen, iCentreX - 16, iCentreY - (16 + 32), iCentreX + 16, iCentreY - 16, 255, 0, 0, 255);
		rectangleRGBA(screen, iCentreX - 16, iCentreY + 16, iCentreX + 16, iCentreY + (16 + 32), 255, 0, 0, 255);*/

		//rectangleRGBA(screen, GetX() - (GetSize() / 2), GetY() - (GetSize() / 2), GetX() + (GetSize() / 2), GetY() + (GetSize() / 2), 0, 0, 0, 255);
		if (GetCharID() == cidPteras)
		{
			//cout << "Character: " << GetCharID() << " dclip.x: " << dclip.x << " dclip.y: " << dclip.y << " iCentreX: " << iCentreX << " iCentreY: " << iCentreY << endl;
		}

		//if (iCentreX - 50 > 0 && iCentreX + 50 < screen->clip_rect.w && iCentreY + 50 > 0)
		//{
		boxRGBA(screen, iCentreX - 50, iCentreY + 50, iCentreX - 50 + ((GetStats()->GetHealth() / GetStats()->GetMaxHealth()) * 100), iCentreY + 56, 255, 0, 0, 255);
		rectangleRGBA(screen, iCentreX - 50, iCentreY + 50, iCentreX + 50, iCentreY + 56, 0,0,0,255);
		//}
	}
}
void Character::Update(float fDeltaTime)
{
	if (GetState() == stateDead)
		{SetState(stateRespawn);}
}
void Character::Collide(Object* obj)
{
	//cout << "Character Collided" << endl;
	int tempHealth = GetStats()->GetHealth();
	tempHealth -= obj->GetDamage();

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
	switch (cDir)
	{
	case 'u':
		MoveUp(fdt, 1);
	break;
	case 'd':
		MoveDown(fdt, 1);
	break;
	case 'l':
		MoveLeft(fdt, 1);
	break;
	case 'r':
		MoveRight(fdt, 1);
	break;
	case 'q':
		RotateLeft(fdt, 1);
	break;
	case 'e':
		RotateRight(fdt, 1);
	break;
	}
}
void Character::MoveLeft(float fdt, int speedMult)
{
	float tempX = 0, tempY = 0;
	float tempSpeedMult = 0.5;
	tempX = GetX() - ((m_cStats.GetMoveSpeed() * tempSpeedMult) * fdt);
	tempY = GetY();
	SetX(tempX);
	SetY(tempY);
}
void Character::MoveRight(float fdt, int speedMult)
{
	float tempX = 0, tempY = 0;
	float tempSpeedMult = 0.5;
	tempX = GetX() + ((m_cStats.GetMoveSpeed() * tempSpeedMult) * fdt);
	tempY = GetY();
	SetX(tempX);
	SetY(tempY);
}
void Character::MoveUp(float fdt, int speedMult)
{
	float tempX = 0, tempY = 0;
	tempX = GetX() - (((m_cStats.GetMoveSpeed() * speedMult) * fdt) * sin(m_cStats.GetDirection() * M_PI / 180));
	tempY = GetY() - (((m_cStats.GetMoveSpeed() * speedMult) * fdt) * cos(m_cStats.GetDirection() * M_PI / 180));
	SetX(tempX);
	SetY(tempY);
}
void Character::MoveDown(float fdt, int speedMult)
{
	float tempX = 0, tempY = 0;
	tempX = GetX() + ((m_cStats.GetMoveSpeed() * speedMult) * fdt) * sin((m_cStats.GetDirection() * M_PI) / 180);
	tempY = GetY() + ((m_cStats.GetMoveSpeed() * speedMult) * fdt) * cos((m_cStats.GetDirection() * M_PI) / 180);
	SetX(tempX);
	SetY(tempY);
}
void Character::RotateLeft(float fdt, int speedMult)
{
	float caTemp = m_cStats.GetDirection();
	caTemp += (m_cStats.GetRotateAngle() * speedMult) * fdt;
	if (caTemp > 360) {caTemp -= 360;}
	if (caTemp < 0) {caTemp += 360;}
	m_cStats.SetDirection(caTemp);
}
void Character::RotateRight(float fdt, int speedMult)
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