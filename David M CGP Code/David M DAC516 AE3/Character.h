#pragma once
#include "Entity.h"
#include "Arena.h"
#include <math.h>

class Character :
	public Entity
{
protected:
	Vector2D m_Direction;
	int m_Speed{ 0 };
	int m_Reach{ 0 };
	bool m_Moved{ false };
	bool m_Falling{ false };

public:
	Character(int x, int y, int speed, SDL_Renderer* renderer);
	void MoveLeft(void);
	void MoveRight(void);
	void MoveUp(void);
	void MoveDown(void);
	Vector2D GetDirection(void);
	void SetDirection(int x, int y);
	bool InReach(Entity* entity);
	bool Moved(void);
	void SetMoved(bool moved);
	bool Falling(Arena* level);
	virtual void Update(void);
	~Character();
};

