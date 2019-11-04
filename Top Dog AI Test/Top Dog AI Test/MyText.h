//Modified from Rob Loachs' and Tim Campbells' simple example
#ifndef MYTEXT_H
#define MYTEXT_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
//extern SDL_Surface* screen;	

class MyText
{
private:
	std::string DefaultFont;
	int TTF_X;
	int TTF_Y;
	std::map<std::string, TTF_Font*> m_Fonts;
	//SDL_Surface* m_FontSurface;

public:
	MyText();
	~MyText();

	bool Initialize();	
	void Close();	

	// LoadFont - Loads a font into memory	
	//  Key - What you'll refer to the font as when using it (the name)	
	//  Filename - The filename of the font	
	//  FontSize - The size of the font	
	// Example:  LoadFont("bigfont","arial.ttf",72)	
	bool LoadFont(std::string key, std::string filename, int fontSize=16);	

	// CloseFont - Closes the font (not required as it is managed)	
	void CloseFont(std::string key);	
	void CloseFont(TTF_Font* font);

	// FontHeight - Returns the height of the font	
	int FontHeight(std::string key);

	// Print - Prints on the screen	
	//  x, y - The location to print	
	//  text - The text to write	
	//  r, g, b - The colour to paint	
	//  hAlignment - 0=left, 1=center, 2=right	
	//  vAlignment - 0=top, 1=center, 2=bottom	
	//  fontKey - The font to use (the name)	
	// Example: Print(40, 40, "Hi", 255,0,0, 1, 1, "bigfont"	
	bool Print(SDL_Surface* screen, int x = 0, int y = 0, std::string text = "Hello World", int r = 255, int g = 255, int b = 255, int halign = 0, int valign = 0, std::string fontKey = "default", float rotateAngle = 0);

	TTF_Font* GetFont(std::string key);
	SDL_Surface* MakeTextSurface(std::string text, TTF_Font* font, int r, int g, int b, float rotateAngle);
};
#endif