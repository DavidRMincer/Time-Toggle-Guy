#include "Level.h"



Level::Level(SDL_Renderer * renderer, vector<string> level, Player * player)
{
	//Sets arena vector as level
	LevelArena = new Arena(renderer, level);
	
	for (size_t y = 0; y < LevelArena->GetArena().size(); ++y)
	{
		for (size_t x = 0; x < LevelArena->GetArena()[0].length(); ++x)
		{
			switch (LevelArena->GetCharacter(x * LevelArena->GetBlockDimensions().x, y * LevelArena->GetBlockDimensions().y))
			{
			case 'S':
				m_StartPoint.x = x * LevelArena->GetBlockDimensions().x;
				m_StartPoint.y = y * LevelArena->GetBlockDimensions().y;
				break;
			case 'H':
				AddItem(
					x * LevelArena->GetBlockDimensions().x,
					y * LevelArena->GetBlockDimensions().y,
					HEALTH,
					25,
					renderer
				);
				break;
			case 'Q':
				AddDoor(
					x * LevelArena->GetBlockDimensions().x,
					y * LevelArena->GetBlockDimensions().y,
					1,
					renderer
				);
				break;
			case 'A':
				AddDoor(
					x * LevelArena->GetBlockDimensions().x,
					y * LevelArena->GetBlockDimensions().y,
					2,
					renderer
				);
				break;
			case 'Z':
				AddDoor(
					x * LevelArena->GetBlockDimensions().x,
					y * LevelArena->GetBlockDimensions().y,
					3,
					renderer
				);
				break;
			case 'P':
				AddItem(
					x * LevelArena->GetBlockDimensions().x,
					y * LevelArena->GetBlockDimensions().y,
					KEY,
					1,
					renderer
				);
				break;
			case 'L':
				AddItem(
					x * LevelArena->GetBlockDimensions().x,
					y * LevelArena->GetBlockDimensions().y,
					KEY,
					2,
					renderer
				);
				break;
			case 'K':
				AddItem(
					x * LevelArena->GetBlockDimensions().x,
					y * LevelArena->GetBlockDimensions().y,
					KEY,
					3,
					renderer
				);
			case 'M':
				AddMonster(
					x * LevelArena->GetBlockDimensions().x,
					y * LevelArena->GetBlockDimensions().y,
					2,
					1,
					LevelArena->GetBlockDimensions().x * 4,
					player,
					renderer
				);
				break;
			default:
				break;
			}
		}
	}
}

void Level::AddMonster(int x, int y, int speed, int damage, int FOV, Player * player, SDL_Renderer * renderer)
{
	//Create monster pointer
	Monster* monster = new Monster(
		x,
		y,
		speed,
		damage,
		FOV,
		player,
		renderer
	);

	//Push back new monster to vector of monsters
	m_VectorofMonsters.push_back(monster);
}

vector<Monster*> Level::GetMonsters(void)
{
	return m_VectorofMonsters;
}

void Level::AddItem(int x, int y, ITEM_TYPE type, int value, SDL_Renderer * renderer)
{
	//Create item pointer
	Item* item = new Item(
		x,
		y,
		type,
		value,
		renderer
	);

	//Add item to vector of items
	m_VectorofItems.push_back(item);
}

void Level::RemoveItem(int item)
{
	//Remove item from vector of items
	m_VectorofItems.erase(m_VectorofItems.begin() + item);
	m_VectorofItems.shrink_to_fit();
}

vector<Item*> Level::GetItems(void)
{
	return m_VectorofItems;
}

void Level::AddDoor(int x, int y, int doorNum, SDL_Renderer * renderer)
{
	//Create door pointer
	Door* door = new Door(
		x,
		y,
		doorNum,
		renderer
	);

	//Add door to vector of doors
	m_VectorofDoors.push_back(door);
}

vector<Door*> Level::GetDoors(void)
{
	return m_VectorofDoors;
}

void Level::ToggleDoorLocked(int door)
{
	//Toggle locked boolean on door
	m_VectorofDoors[door]->ToggleLocked();
}

Vector2D Level::GetStartPoint(void)
{
	return m_StartPoint;
}

Level::~Level()
{
	//Empty vector of doors
	for (auto d : m_VectorofDoors)
	{
		delete d;
		d = nullptr;
	}
	m_VectorofDoors.resize(0);
	
	//Empty vector of items
	for (auto i : m_VectorofItems)
	{
		delete i;
		i = nullptr;
	}
	m_VectorofItems.resize(0);

	//Empty vector of monsters
	for (auto m : m_VectorofMonsters)
	{
		delete m;
		m = nullptr;
	}
	m_VectorofMonsters.resize(0);

	//Delete arena
	delete LevelArena;
	LevelArena = nullptr;
}
