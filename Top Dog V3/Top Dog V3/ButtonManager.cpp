//Blake Sullivan - ButtonManager.cpp
#include "ButtonManager.h"
ButtonManager::ButtonManager()
{
	//m_vButtons.clear();
	//m_vButtons = new vector<Button>;
}
ButtonManager::ButtonManager(MyText* mt)
{
	m_pMT = mt;
	//m_vButtons.clear();
	//m_vButtons = new vector<Button>;
}

ButtonManager::~ButtonManager()
{
	m_vButtons.clear();
}

void ButtonManager::AddButton(int x, int y, std::string t, unsigned int w, unsigned int h, Colours cN, Colours cH, Colours cD)
{
	int id = 0;
	for (m_vButtonsIT = m_vButtons.begin(); m_vButtonsIT != m_vButtons.end(); m_vButtonsIT++)
		{id++;}

	Button temp(w, h);
	temp.Init(x, y, id, t);
	temp.SetStateColours(buttonNorm, cN.iRed, cN.iGreen, cN.iBlue, cN.iAlpha);
	temp.SetStateColours(buttonHighlight, cH.iRed, cH.iGreen, cH.iBlue, cH.iAlpha);
	temp.SetStateColours(buttonDown, cD.iRed, cD.iGreen, cD.iBlue, cD.iAlpha);
	m_vButtons.push_back(temp);
}
void ButtonManager::AddButton(int x, int y, std::string t, unsigned int w, unsigned int h, bool c, bool o, Colours cN, Colours cH, Colours cD, bool bt, int id)
{
	if (id == -1)
	{
		id = 0;
		for (m_vButtonsIT = m_vButtons.begin(); m_vButtonsIT != m_vButtons.end(); m_vButtonsIT++)
			{id++;}
	}

	Button temp(w, h);
	temp.Init(x, y, id, t, c, o, cN, cH, cD, bt);
	m_vButtons.push_back(temp);
}

void ButtonManager::AddColours(unsigned int id, int colState, int red, int green, int blue, int alpha)
{
	for (m_vButtonsIT = m_vButtons.begin(); m_vButtonsIT != m_vButtons.end(); m_vButtonsIT++)
	{
		if (m_vButtonsIT->GetID() == id)
		{
			m_vButtonsIT->SetStateColours(colState, red, green, blue, alpha);
			break;
		}
	}
}

void ButtonManager::UpdateButton(int mouseX, int mouseY)
{
	for (m_vButtonsIT = m_vButtons.begin(); m_vButtonsIT != m_vButtons.end(); m_vButtonsIT++)
	{
		if (m_vButtonsIT->GetState() != buttonDown && m_vButtonsIT->GetClickable() == true)
		{
			if (mouseX > m_vButtonsIT->GetX() && mouseX < m_vButtonsIT->GetX() + m_vButtonsIT->GetWidth())
			{
				if (mouseY > m_vButtonsIT->GetY() && mouseY < m_vButtonsIT->GetY() + m_vButtonsIT->GetHeight())
					{m_vButtonsIT->SetState(buttonHighlight);}
				else
					{m_vButtonsIT->SetState(buttonNorm);}
			}
			else
				{m_vButtonsIT->SetState(buttonNorm);}
		}
	}
}
void ButtonManager::ButtonPressed(int mouseX, int mouseY)
{
	for (m_vButtonsIT = m_vButtons.begin(); m_vButtonsIT != m_vButtons.end(); m_vButtonsIT++)
	{
		if (mouseX > m_vButtonsIT->GetX() && mouseX < m_vButtonsIT->GetX() + m_vButtonsIT->GetWidth())
		{
			if (mouseY > m_vButtonsIT->GetY() && mouseY < m_vButtonsIT->GetY() + m_vButtonsIT->GetHeight())
			{
				if (m_vButtonsIT->GetClickable() == true)
				{
					m_vButtonsIT->SetState(buttonDown);
					m_vButtonsIT->SetPressed(true);
					break;
				}
			}
		}
	}
}

int ButtonManager::CheckButtonPressed()
{
	for (m_vButtonsIT = m_vButtons.begin(); m_vButtonsIT != m_vButtons.end(); m_vButtonsIT++)
	{
		if (m_vButtonsIT->GetPressed() == true)
		{
			return m_vButtonsIT->GetID();
		}
	}
	return -1;
}

void ButtonManager::ButtonUnPressed(int id)
{
	for (m_vButtonsIT = m_vButtons.begin(); m_vButtonsIT != m_vButtons.end(); m_vButtonsIT++)
	{
		if (m_vButtonsIT->GetID() == id)
		{
			m_vButtonsIT->SetPressed(false);
			m_vButtonsIT->SetState(buttonNorm);
			break;
		}
	}
}

void ButtonManager::DrawButton(SDL_Surface* screen)
{
	Colours bc;
	bc.iAlpha = 255;
	for (m_vButtonsIT = m_vButtons.begin(); m_vButtonsIT != m_vButtons.end(); m_vButtonsIT++)
	{
		boxRGBA(screen, m_vButtonsIT->GetX(), m_vButtonsIT->GetY(), 
				m_vButtonsIT->GetX() + m_vButtonsIT->GetWidth(),
				m_vButtonsIT->GetY() + m_vButtonsIT->GetHeight(),
				m_vButtonsIT->GetRed(m_vButtonsIT->GetState()),
				m_vButtonsIT->GetGreen(m_vButtonsIT->GetState()),
				m_vButtonsIT->GetBlue(m_vButtonsIT->GetState()),
				m_vButtonsIT->GetAlpha(m_vButtonsIT->GetState())
				);
		//dt.DrawTextToSurface(screen, m_vButtonsIT->GetText().c_str(), m_vButtonsIT->GetX() + 5, m_vButtonsIT->GetY() + (m_vButtonsIT->GetHeight() / 4));
		
		if (m_vButtonsIT->GetBlackText() == true) 
			{bc.iRed = 0; bc.iGreen = 0; bc.iBlue = 0;}
		else
			{bc.iRed = 255; bc.iGreen = 255; bc.iBlue = 255;}

		m_pMT->Print(screen, m_vButtonsIT->GetX() + 10, m_vButtonsIT->GetY() + (m_vButtonsIT->GetHeight() / 4), m_vButtonsIT->GetText().c_str(), bc.iRed, bc.iGreen, bc.iBlue, 0, 0, "MyFont");

		if (m_vButtonsIT->GetOutlined() == true)
		{
			rectangleRGBA(screen, m_vButtonsIT->GetX(), m_vButtonsIT->GetY(), 
				m_vButtonsIT->GetX() + m_vButtonsIT->GetWidth(),
				m_vButtonsIT->GetY() + m_vButtonsIT->GetHeight(),
				0,0,0,255);
		}
		if (m_vButtonsIT->GetClickable() == false)
		{
			boxRGBA(screen, m_vButtonsIT->GetX(), m_vButtonsIT->GetY(), 
				m_vButtonsIT->GetX() + m_vButtonsIT->GetWidth(),
				m_vButtonsIT->GetY() + m_vButtonsIT->GetHeight(),
				100,100,100,200
				);
		}

	}
}
Button* ButtonManager::FindButton(int bID)
{
	for (m_vButtonsIT = m_vButtons.begin(); m_vButtonsIT != m_vButtons.end(); m_vButtonsIT++)
	{
		if (bID == m_vButtonsIT->GetID())
		{
			return &(*m_vButtonsIT);
		}
	}
	return &(*m_vButtons.begin());
}
