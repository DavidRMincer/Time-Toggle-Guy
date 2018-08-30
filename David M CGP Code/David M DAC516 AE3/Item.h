#pragma once
#include "Entity.h"
#include <string>

using namespace std;

enum ITEM_TYPE {
	KEY, HEALTH
};

class Item :
	public Entity
{
private:
	int m_Value{ 0 };
	ITEM_TYPE m_Type;

public:
	Item(int x, int y, ITEM_TYPE type, int value, SDL_Renderer* renderer);
	int GetValue(void);
	ITEM_TYPE GetType(void);
	~Item();
};

