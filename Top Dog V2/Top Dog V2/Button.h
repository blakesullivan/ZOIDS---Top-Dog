//Blake Sullivan - Button.h
#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "ButtonHeader.h"

class Button
{
private:
	unsigned int C_UIWIDTH, C_UIHEIGHT;
	int m_iX, m_iY;
	unsigned int m_uiID, m_uiState;
	std::string m_sText;
	bool m_bPressed, m_bClickable, m_bOutlined, m_bBlackText;
	Colours m_aColours[3];

public:
	Button(unsigned int w = 100, unsigned int h = 40);
	~Button() {};
	//Button(const Button&);

	void Init(int x, int y, unsigned int id);
	void Init(int x, int y, unsigned int id, std::string t);
	void Init(int x, int y, unsigned int id, std::string t, bool c, bool o, Colours cN, Colours cH, Colours cD, bool bt = false);

	void SetX(int x);
	void SetY(int y);
	void SetID(unsigned int id);
	void SetState(unsigned int s);
	void SetText(std::string t);
	void SetPressed(bool p);
	void SetStateColours(int pos, int r, int g, int b, int a = 255);
	void SetRed(int pos, int r);
	void SetGreen(int pos, int g);
	void SetBlue(int pos, int b);
	void SetAlpha(int pos, int a);
	void SetClickable(bool c);
	void SetOutlined(bool o);
	void SetBlackText(bool bt);

	int GetX();
	int GetY();
	unsigned int GetID();
	unsigned int GetState();
	std::string GetText();
	bool GetPressed();

	unsigned int GetWidth();
	unsigned int GetHeight();

	int GetRed(int pos);
	int GetGreen(int pos);
	int GetBlue(int pos);
	int GetAlpha(int pos);

	bool GetClickable();
	bool GetOutlined();
	bool GetBlackText();
};

#endif