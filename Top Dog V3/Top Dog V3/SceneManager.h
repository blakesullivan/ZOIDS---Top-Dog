//Blake Sullivan - Application.h
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include "ScenePos.h"
#include "MyText.h"
#include "Scene.h"
#include "NetworkClient.h"
#include "SoundManager.h"

using namespace std;

class SceneManager
{
private:
	//enum scenePos {sceneQuit = -2, sceneRunning = -1, sceneSplash = 0, sceneMenu = 1, sceneOptions = 2, scenePlay = 3};
	//The attributes of the screen
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;
	const static int SCREEN_BPP = 32; //Bits Per Pixel

	SDL_Surface *screen; //the pointer to the screen in memory
	bool m_bIsRunning;

	Scene *myScene;
	MyText* m_pMT;
	NetworkClient* m_pNC;
	SoundManager* m_pSM;

public:
	SceneManager();
	~SceneManager();

	void Init();
	void Run();
	void ChangeScene(int iChangeTo);
};

#endif