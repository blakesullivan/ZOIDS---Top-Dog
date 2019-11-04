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
	buttonHost = 5,
	buttonJoin = 6,
	buttonDesert = 10,
	buttonForest = 11,
	buttonCity = 12,
	buttonLake = 13,
	buttonName = 14,
	buttonChat = 15,
	buttonRefresh = 16,
	buttonSendChat = 17,
	buttonCharBE = 20,
	buttonCharPT = 21,
	buttonCharRN = 22,
	buttonCharRD = 23,
	buttonCharSS = 24,
	buttonCharZB = 25,
	buttonMusic = 26,
	buttonSound = 27

};
#endif