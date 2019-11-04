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
#include <exception>
using namespace std;

SceneManager::SceneManager()
{
	Init();
	Run();
}

SceneManager::~SceneManager()
{
	m_pMT->Close();
	m_pSM->CloseAudio();
	//delete[] m_pMT;
	//delete[] m_pNC;
	SDLNet_Quit();
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
	//screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_FULLSCREEN ); 
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE); 

	//If there was an error in setting up the screen
	if( screen == NULL ) {m_bIsRunning = false;}
	//Set the window caption
	SDL_WM_SetCaption( "ZOIDS - Zoids Operation: Imperial Defense System", NULL ); 

	m_pMT = new MyText;
	m_pMT->Initialize();
	std::string stemp = getenv("windir"); 
	stemp += "/Fonts/Arial.ttf";
	m_pMT->LoadFont("MyFont", stemp, 18);

	m_pNC = new NetworkClient();
	m_pNC->Init("", false, -1, false);

	m_pSM = new SoundManager();
	m_pSM->InitAudio();
	m_pSM->PlayMusic(musicMenus);

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

		try
		{
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
		catch (exception e)
		{
			cout << e.what() << endl;
		}
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
		m_pSM->PlayMusic(musicMenus);
		myScene = new Menu(m_pMT);
	break;
	case sceneOptions:
		myScene = new Options(m_pMT, m_pSM);
	break;
	case scenePlay:
		myScene = new Play(m_pMT, m_pNC, m_pSM);
	break;
	case sceneHost:
		myScene = new Host(m_pMT, m_pNC);
	break;
	case sceneJoin:
		myScene = new Join(m_pMT, m_pNC);
	break;
	case sceneCharacter:
		myScene = new CharacterSelect(m_pMT, m_pNC);
	break;
	case sceneResult:
		m_pSM->PlayMusic(musicResult);
		myScene = new Result(m_pMT);
	break;
	default:
		m_bIsRunning = false;
	}
}