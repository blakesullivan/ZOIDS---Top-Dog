//Blake Sullivan - ButtonManager.h
#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include "SDL_gfxPrimitives.h"
#include "Button.h"
#include "MyText.h"
#include <vector>
using namespace std;

class ButtonManager
{
private:
	vector<Button> m_vButtons;
	vector<Button>::iterator m_vButtonsIT;
	MyText* m_pMT;

public:
	ButtonManager();
	ButtonManager(MyText* mt);
	~ButtonManager();

	void AddButton(int x, int y, std::string t, unsigned int w, unsigned int h, Colours cN, Colours cH, Colours cD);
	void AddButton(int x, int y, std::string t, unsigned int w, unsigned int h, bool c, bool o, Colours cN, Colours cH, Colours cD, bool bt = false, int id = -1);
	void AddColours(unsigned int id, int colState, int red, int green, int blue, int alpha);
	void UpdateButton(int mouseX, int mouseY);
	void ButtonPressed(int mouseX, int mouseY);
	int CheckButtonPressed();
	void ButtonUnPressed(int id);
	void DrawButton(SDL_Surface* screen);
	Button* FindButton(int bID);

};
#endif