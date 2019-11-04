//Blake Sullivan - Button.cpp
#include "Button.h"

Button::Button(unsigned int width, unsigned int height): C_UIWIDTH(width), C_UIHEIGHT(height)
{
	SetX(0);
	SetY(0);
	SetID(0);
	SetState(0);
	SetText(" ");
	SetPressed(false);
	SetBlackText(false);
	for (int i = 0; i < 3; i++)
	{
		SetRed(i, i * 75);
		SetGreen(i, i * 75);
		SetBlue(i, i * 75);
		SetAlpha(i, 255);
	}
}
//Button::Button(const Button& b): C_UIWIDTH(b.GetWidth()), C_UIHEIGHT(b.GetHeight())
//{
//	SetX(b.GetX());
//	SetY(b.GetY());
//	SetID(b.GetID());
//	SetState(b.GetState());
//	SetText(b.GetText());
//	SetPressed(false);
//	for (int i = 0; i < 3; i++)
//	{
//		SetRed(i, b.GetRed(i));
//		SetGreen(i, b.GetGreen(i));
//		SetBlue(i, b.GetBlue(i));
//	}
//}

void Button::Init(int x, int y, unsigned int id)
{
	SetX(x);
	SetY(y);
	SetID(id);
	SetState(0);
	SetClickable(true);
	SetOutlined(true);
	SetBlackText(false);
}
void Button::Init(int x, int y, unsigned int id, std::string t)
{
	SetX(x);
	SetY(y);
	SetID(id);
	SetText(t);
	SetState(0);
	SetClickable(true);
	SetOutlined(true);
	for (int i = 0; i < 3; i++)
	{
		SetRed(i, i * 75);
		SetGreen(i, i * 75);
		SetBlue(i, i * 75);
		SetAlpha(i, 255);
	}
	SetBlackText(false);
}
void Button::Init(int x, int y, unsigned int id, std::string t, bool c, bool o, Colours cN, Colours cH, Colours cD, bool bt)
{
	SetX(x);
	SetY(y);
	SetID(id);
	SetText(t);
	SetState(0);
	SetClickable(c);
	SetOutlined(o);
	SetStateColours(buttonNorm, cN.iRed, cN.iGreen, cN.iBlue, cN.iAlpha);
	SetStateColours(buttonHighlight, cH.iRed, cH.iGreen, cH.iBlue, cH.iAlpha);
	SetStateColours(buttonDown, cD.iRed, cD.iGreen, cD.iBlue, cD.iAlpha);
	SetBlackText(bt);
}

void Button::SetX(int x)
{
	m_iX = x;
}
void Button::SetY(int y)
{
	m_iY = y;
}
void Button::SetID(unsigned int id)
{
	m_uiID = id;
}
void Button::SetState(unsigned int s)
{
	m_uiState = s;
}
void Button::SetText(std::string t)
{
	m_sText = t;
}
void Button::SetPressed(bool p)
{
	m_bPressed = p;
}
void Button::SetStateColours(int pos, int r, int g, int b, int a)
{
	SetRed(pos, r);
	SetGreen(pos, g);
	SetBlue(pos, b);
	SetAlpha(pos, a);
}
void Button::SetRed(int pos, int r)
{
	m_aColours[pos].iRed = r;
}
void Button::SetGreen(int pos, int g)
{
	m_aColours[pos].iGreen = g;
}
void Button::SetBlue(int pos, int b)
{
	m_aColours[pos].iBlue = b;
}
void Button::SetAlpha(int pos, int a)
{
	m_aColours[pos].iAlpha = a;
}
void Button::SetClickable(bool c)
{
	m_bClickable = c;
}
void Button::SetOutlined(bool o)
{
	m_bOutlined = o;
}
void Button::SetBlackText(bool bt)
{
	m_bBlackText = bt;
}

int Button::GetX()
{
	return m_iX;
}
int Button::GetY()
{
	return m_iY;
}
unsigned int Button::GetID()
{
	return m_uiID;
}
unsigned int Button::GetState()
{
	return m_uiState;
}
std::string Button::GetText()
{
	return m_sText;
}
bool Button::GetPressed()
{
	return m_bPressed;
}

unsigned int Button::GetWidth()
{
	return C_UIWIDTH;
}
unsigned int Button::GetHeight()
{
	return C_UIHEIGHT;
}

int Button::GetRed(int pos)
{
	return m_aColours[pos].iRed;
}
int Button::GetGreen(int pos)
{
	return m_aColours[pos].iGreen;
}
int Button::GetBlue(int pos)
{
	return m_aColours[pos].iBlue;
}
int Button::GetAlpha(int pos)
{
	return m_aColours[pos].iAlpha;
}
bool Button::GetClickable()
{
	return m_bClickable;
}
bool Button::GetOutlined()
{
	return m_bOutlined;
}
bool Button::GetBlackText()
{
	return m_bBlackText;
}