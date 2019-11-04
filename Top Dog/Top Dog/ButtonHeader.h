//Blake Sullivan - ButtonHeader.h
#ifndef BUTTONHEADER_H
#define BUTTONHEADER_H

#include "ScenePos.h"

enum buttonState 
{
	buttonNorm = 0, 
	buttonHighlight = 1, 
	buttonDown = 2
};
struct Colours
{
	int iRed;
	int iGreen;
	int iBlue;
	int iAlpha;
};
enum buttonDest
{
	buttonExit = -2,
	buttonClear = 1,
	buttonPlay = 2,
	buttonName = 4,
	buttonHost = 5,
	buttonJoin = 6
};
#endif