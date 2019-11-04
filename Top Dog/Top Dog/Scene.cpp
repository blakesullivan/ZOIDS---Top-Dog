//Blake Sullivan - Scene.cpp
#include "Scene.h"

Scene::Scene()
{
	m_iIsRunning = 0;
	for (int i = 0; i < 323; i++)
	{
		m_bKeysHeld[i] = false;
		if (i < 13) {m_bButtonHeld[i] = false;}
	}
}

void Scene::Event(SDL_Surface* screen, SDL_Event *event, float fDeltaTime)
{
	if (SDL_PollEvent(event))
	{
		if (event->type == SDL_QUIT)
			{m_iIsRunning = sceneQuit;}
		else
		{
			if (event->type == SDL_KEYDOWN)
				{KeyDownEvent(event);}
			if (event->type == SDL_KEYUP)
				{KeyUpEvent(event);}
			if (event->type == SDL_MOUSEBUTTONDOWN)
				{MouseDownEvent(event);}
			if (event->type == SDL_MOUSEBUTTONUP)
				{MouseUpEvent(event);}
		}
	}
}

int Scene::Status()
{
	return m_iIsRunning;
}

void Scene::MouseUpEvent(SDL_Event* event)
{
	m_bButtonHeld[event->button.button] = false;
}
void Scene::MouseDownEvent (SDL_Event* event)
{
	m_bButtonHeld[event->button.button] = true;
}
void Scene::KeyUpEvent(SDL_Event* event)
{
	m_bKeysHeld[event->key.keysym.sym] = false;
}
void Scene::KeyDownEvent(SDL_Event* event)
{
	m_bKeysHeld[event->key.keysym.sym] = true;
}