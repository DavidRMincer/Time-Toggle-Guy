#pragma once
#include "Character.h"
#include "Player.h"
#include <ctime>

class Monster :
	public Character
{
private:
	int m_Damage{ 0 };
	int m_FOV{ 0 };
	bool m_Moving{ false };
	Vector2D m_MoveDirection;

	Player* m_Target;

public:
	Monster(int x, int y, int speed, int damage,
		int FOV, Player* player, SDL_Renderer* renderer);
	void Follow(void);
	void Attack(void);
	void RandomMove(void);
	bool InFOV(void);
	void UpdateAI(void);
	~Monster();
};

