#pragma once
#include "SDL.h"
#include "Player.h"
#include "Door.h"
#include "Item.h"
#include "Level.h"
#include "Bitmap.h"
#include <vector>
#include <iostream>
#include <conio.h>

using namespace std;

enum m_GameEvent
{
	GE_TIMER, NUM_GAME_EVENTS
};

enum m_KeysPressed
{
	UP, DOWN, LEFT, RIGHT, INTERACT, TOGGLE_TIME, CONFIRM, SIZE_OF_KEYS_PRESSED_ENUM
};

class GameManager
{
private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	bool m_UpdateLogic{ true },
		m_RenderFrame{ true },
		m_TimeState{ true },
		m_Running{ true };

	Vector2D m_BlockDimensions,
		m_ViewportPos,
		m_ViewportDimensions;
	Player* m_Player;
	int m_LevelCounter{ 0 },
		m_ConsecutiveLogicUpdates;
	SDL_Event m_Event;

	vector<Item*> m_Inventory;
	vector<Level*> m_FutureLevels,
		m_PastLevels;
	Level* m_CurrentLevel;

	Bitmap* m_InfoScreen;

	SDL_TimerID m_GameTimer;
	const int m_FramesPerSec{ 60 },
		MillisecsPerFrame{ 1000 / m_FramesPerSec },
		m_MaxLogicUpdates{ 10 };

public:
	bool m_Keys[SIZE_OF_KEYS_PRESSED_ENUM];

	GameManager(int width, int height);
	void Input(void);
	void AddtoInventory(Item* item);
	void FreeFromInventory(int item);
	bool ItemCollision(Item* item);
	void ToggleTimeState(void);
	void EventHandler(void);
	void PresentRenderer(void);
	void CreateTimerEvent(void);
	static Uint32 TimerCallback(Uint32 interval, void* gameObjectIn);
	void CheckEvents(void);
	void WallCollision(Character* character, Arena* level);
	void EntityCollision(Character* entity1, Entity* entity2);
	bool EndofLevel(void);
	void EndGame(bool victory);
	void UpdateViewport(void);
	bool InViewport(Entity* entity);
	void UpdateGame(void);
	void GameLoop(void);
	~GameManager();
};

