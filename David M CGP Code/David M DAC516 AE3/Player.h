#pragma once
#include "Character.h"
class Player :
	public Character
{
private:
	int m_Health{ 0 };
	int m_MaxHealth{ 0 };

public:
	Player(int x, int y, int speed, int maxHealth, SDL_Renderer* renderer);
	int GetHealth(void);
	void AddHealth(int health);
	int GetMaxHealth(void);
	void ResetHealth(void);
	~Player();
};

