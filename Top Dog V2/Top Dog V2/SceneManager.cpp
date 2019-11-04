//Blake Sullivan - SceneManager.cpp
#include "SceneManager.h"
#include "Splash.h"
#include "Options.h"
#include "Play.h"
#include "Menu.h"
#include "Host.h"
#include "Join.h"
#include "Result.h"
#include "CharacterSelect.h"

SceneManager::SceneManager()
{
	Init();
	Run();
}

SceneManager::~SceneManager()
{
	mt->Close();
	SDL_Quit();
}

void SceneManager::Init()
{
	screen = NULL;
	m_bIsRunning = true;
	//Initialize all SDL subsystems 
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) 
		{m_bIsRunning = false;} 
    //Set up the screen 
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );//| SDL_FULLSCREEN ); 
	//If there was an error in setting up the screen 
	if( screen == NULL ) {m_bIsRunning = false;} 
	//Set the window caption
	SDL_WM_SetCaption( "ZOIDS - Zoids Operation: Imperial Defense System", NULL ); 

	mt = new MyText;
	mt->Initialize();
	std::string stemp = getenv("windir"); 
	stemp += "/Fonts/Arial.ttf";
	mt->LoadFont("MyFont", stemp, 18);

	myScene = new Splash();
}

void SceneManager::Run()
{
	SDL_Event event;

	float fDeltaTime = 0;
	int iThisTime = 0, iLastTime = 0;
     
	while (m_bIsRunning)
	{	// check for any events from the user or the system
		//SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) ); 

		iThisTime = SDL_GetTicks();
		fDeltaTime = static_cast<float>(iThisTime - iLastTime) / 1000;
		iLastTime = iThisTime;

		myScene->Event(screen, &event, fDeltaTime);
		myScene->Update(screen, fDeltaTime);
		myScene->Draw(screen, fDeltaTime);

		if (myScene->Status() != sceneRunning)
		{
			ChangeScene(myScene->Status());
		}
    	//Update the screen 
		if( SDL_Flip( screen ) == -1 ) {m_bIsRunning = false;} 
	}
}

void SceneManager::ChangeScene(int iChangeTo)
{
	myScene->Dispose();
	delete myScene;
	switch (iChangeTo)
	{
	case sceneSplash:
		myScene = new Splash();
	break;
	case sceneMenu:
		myScene = new Menu(mt);
	break;
	case sceneOptions:
		myScene = new Options(mt);
	break;
	case scenePlay:
		myScene = new Play(mt);
	break;
	case sceneHost:
		myScene = new Host(mt);
	break;
	case sceneJoin:
		myScene = new Join(mt);
	break;
	case sceneCharacter:
		myScene = new CharacterSelect(mt);
	break;
	case sceneResult:
		myScene = new Result(mt);
	break;
	default:
		m_bIsRunning = false;
	}
}