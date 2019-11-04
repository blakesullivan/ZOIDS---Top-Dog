//Blake Sullivan - Splash.cpp
#include "Splash.h"

Splash::Splash()
{
	Init();
}

void Splash::Init()
{
	m_iIsRunning = sceneRunning;
	m_Background = NULL;
	m_Background = IMG_Load("Images/Splash.png");
}

void Splash::Update(SDL_Surface* screen, float fDeltaTime)
{
	if (m_bKeysHeld[SDLK_ESCAPE] == true)
		{m_iIsRunning = sceneQuit;}
	/*else if (m_bKeysHeld[SDLK_SPACE] == true || m_bKeysHeld[SDLK_RETURN] == true)
		{m_iIsRunning = sceneMenu;}*/
}
void Splash::Draw(SDL_Surface* screen, float fDeltaTime)
{
	//SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0, 200) ); 
	//stringRGBA(screen, 300, 290, "SPLASH!", 0, 0, 0, 255);
	SDL_BlitSurface(m_Background, NULL, screen, NULL);
	stringRGBA(screen, (screen->clip_rect.w / 2) - 130, 550, "Press any key to continue.", 0, 0, 0, 255);
}

//int Splash::Status()
//{
//	return m_iIsRunning;
//}

void Splash::Dispose()
{
	SDL_FreeSurface(m_Background);
}

void Splash::MouseUpEvent(SDL_Event* event)
{
	Scene::MouseUpEvent(event);
}
void Splash::MouseDownEvent (SDL_Event* event)
{
	Scene::MouseDownEvent(event);
	m_iIsRunning = sceneMenu;
}
void Splash::KeyUpEvent(SDL_Event* event)
{
	Scene::KeyUpEvent(event);
}
void Splash::KeyDownEvent(SDL_Event* event)
{
	Scene::KeyDownEvent(event);
	m_iIsRunning = sceneMenu;
}