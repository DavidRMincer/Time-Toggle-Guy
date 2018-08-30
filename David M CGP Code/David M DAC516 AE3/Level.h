#pragma once
#include <vector>
#include <string>
#include "Arena.h"
#include "Monster.h"
#include "Item.h"
#include "Door.h"

using namespace std;

struct SDL_Renderer;

class Level
{
private:
	vector<Monster*> m_VectorofMonsters;
	vector<Item*> m_VectorofItems;
	vector<Door*> m_VectorofDoors;
	Vector2D m_StartPoint;

public:
	Arena* LevelArena;

	Level(SDL_Renderer* renderer, vector<string> level, Player* player);
	void AddMonster(int x, int y, int speed, int damage,
		int FOV, Player* player, SDL_Renderer* renderer);
	vector<Monster*> GetMonsters(void);
	void AddItem(int x, int y, ITEM_TYPE type,
		int value, SDL_Renderer* renderer);
	void RemoveItem(int item);
	vector<Item*> GetItems(void);
	void AddDoor(int x, int y, 
		int doorNum, SDL_Renderer* renderer);
	vector<Door*> GetDoors(void);
	void ToggleDoorLocked(int door);
	Vector2D GetStartPoint(void);
	~Level();
};

