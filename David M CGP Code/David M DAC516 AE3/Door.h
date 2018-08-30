#pragma once
#include "Entity.h"
class Door :
	public Entity
{
private:
	int m_DoorNum{ 0 };
	bool m_Locked{ true };

public:
	Door(int x, int y, int doorNum, SDL_Renderer* renderer);
	int GetDoorNum(void);
	bool GetLocked(void);
	void ToggleLocked(void);
	~Door();
};

