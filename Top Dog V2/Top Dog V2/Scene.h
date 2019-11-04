//Blake Sullivan - Scene.h
#ifndef SCENE_H
#define SCENE_H

#include "SDL.h"   /* All SDL App's need this */
#include "SDL_gfxPrimitives.h"
#include "ScenePos.h"

class Scene
{
protected:
	int m_iIsRunning;
	bool m_bKeysHeld[323];
	bool m_bButtonHeld[13];
	bool m_bShiftMod;

public:
	Scene();
	~Scene() {};

	virtual void Init() = 0;
	virtual void Event(SDL_Surface* screen, SDL_Event *event, float fDeltaTime);
	virtual void Update(SDL_Surface* screen, float fDeltaTime) = 0;
	virtual void Draw(SDL_Surface* screen, float fDeltaTime) = 0;
	virtual int Status();
	virtual void Dispose() = 0;

	virtual void MouseUpEvent(SDL_Event* event);
	virtual void MouseDownEvent (SDL_Event* event);
	virtual void KeyUpEvent(SDL_Event* event);
	virtual void KeyDownEvent(SDL_Event* event);
	
};
#endif