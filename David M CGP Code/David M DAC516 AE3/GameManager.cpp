#include "GameManager.h"



GameManager::GameManager(int width, int height)
{
	m_Window = nullptr;
	m_Renderer = nullptr;
	
	//Set viewport dimensions as window dimensions
	m_ViewportDimensions.x = width;
	m_ViewportDimensions.y = height;

	//Start up
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	m_Window = SDL_CreateWindow(
		"Time Toggle Guy",			//title
		250,						//initial x pos
		50,							//initial y pos
		width,						//width in pixels
		height,						//height in pixels
		0							//windo behaviour flags (ignore for now)
	);

	//If failed to create window
	if (!m_Window)
	{
		//Return error message
		cout << "WINDOW INITILIASATION FAILED: %s\n" << endl;
		cout << "Press any key to continue\n" << endl;
		getchar();
		return;
	}

	//create renderer
	m_Renderer = SDL_CreateRenderer(
		m_Window,					//link renderer to new window
		-1,							//index rendering driver (ignore for now)
		0							//renderer behaviour flags (ignore for now)
	);

	//If failed to create renderer
	if (!m_Renderer)
	{
		//Return error message
		cout << "RENDERER INITILIASATION FAILED: %s\n" << endl;
		cout << "Press any key to continue\n" << endl;
		getchar();
		return;
	}

	//Create Player
	m_Player = new Player(
		0,
		0,
		4,
		100,
		m_Renderer
	);

	//Create levels
	Level* L1Past = new Level(
		m_Renderer,
	{ "WWWWWWWWWWW",
	"WX.W...WP.W",
	"W..W.S.W..W",
	"W..W...W..W",
	"WQWW...W..W",
	"W......W..W",
	"WWWWWWWWWWW" },
		m_Player
	);
	Level* L1Future = new Level(
		m_Renderer,
	{ "WWWWWWWWWWW",
	"WX.W...W..W",
	"W..W.S.W..W",
	"W..W...W..W",
	"WWWWWWWW..W",
	"W.........W",
	"WWWWWWWWWWW" },
		m_Player
	);
	Level* L2Past = new Level(
		m_Renderer,
		{ "WWWWWWWWWWWWWWW",
		"W.X.W.........W",
		"W.H.W.........W",
		"WWQWWWWWWWWWWWW",
		"W......W......W",
		"W....M.W...M..W",
		"W......W......W",
		"WWWWW..W......W",
		"W.S.W..W......W",
		"WWWWWWWWWWWWWWW" },
		m_Player
	);
	Level* L2Future = new Level(
		m_Renderer,
		{ "WWWWWWWWWWWWWWW",
		"W.X.W.....W.H.W",
		"W...WP....W...W",
		"WWWWWWWWWWWWAWW",
		"W.............W",
		"W......W!!!!.!W",
		"W......W!!!!.!W",
		"WWWWW..W!!!!!!W",
		"W.S....W.....LW",
		"WWWWWWWWWWWWWWW" },
		m_Player
	);
	Level* L3Past = new Level(
		m_Renderer,
		{ "WWWWWWWWWWWWWWWWWWWW",
		"WS!!....W...M...W..W",
		"W!!!....WWWWQWWWW..W",
		"W.......W.......W..W",
		"WZWWAW..WWWWWWWWW..W",
		"WXW..W.............W",
		"WWWWWWWWWWWWWWWWWWWW" },
		m_Player
	);
	Level* L3Future = new Level(
		m_Renderer,
		{ "WWWWWWWWWWWWWWWWWWWW",
		"WS...W..WL......WP.W",
		"W....W..WWWWWWWWW..W",
		"W....W..W.......W..W",
		"WWWWWW..WW.....WW..W",
		"WXWK.W.............W",
		"WWWWWWWWWWWWWWWWWWWW" },
		m_Player
	);

	//Add levels to past and future level vectors
	m_PastLevels.push_back(L1Past);
	m_PastLevels.push_back(L2Past);
	m_PastLevels.push_back(L3Past);
	m_FutureLevels.push_back(L1Future);
	m_FutureLevels.push_back(L2Future);
	m_FutureLevels.push_back(L3Future);

	//Set current level as first
	m_CurrentLevel = m_FutureLevels[m_LevelCounter];

	//Player position set as current level start point
	m_Player->SetPos(m_CurrentLevel->GetStartPoint().x, m_CurrentLevel->GetStartPoint().y);
	m_Player->Update();

	//Start timer
	m_UpdateLogic = true;
	m_RenderFrame = true;
	m_ConsecutiveLogicUpdates = 0;
	m_GameTimer = SDL_AddTimer(
		MillisecsPerFrame,
		&GameManager::TimerCallback,
		this
	);
}

void GameManager::Input(void)
{
	//On key down
	if (m_Event.type == SDL_KEYDOWN)
	{
		//Get input event
		SDL_Keycode KeyPressed = m_Event.key.keysym.sym;

		switch (KeyPressed)
		{
		case SDLK_UP:
		case SDLK_w:
			//Up button pressed
			m_Keys[UP] = true;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			//Down button pressed
			m_Keys[DOWN] = true;
			break;
		case SDLK_LEFT:
		case SDLK_a:
			//Left button pressed
			m_Keys[LEFT] = true;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			//Right button pressed
			m_Keys[RIGHT] = true;
			break;
		default:
			break;
		}
	}

	//On key up
	else if (m_Event.type == SDL_KEYUP)
	{
		SDL_Keycode KeyPressed = m_Event.key.keysym.sym;

		switch (KeyPressed)
		{
		case SDLK_UP:
		case SDLK_w:
			//Up button lifted
			m_Keys[UP] = false;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			//Down button lifted
			m_Keys[DOWN] = false;
			break;
		case SDLK_LEFT:
		case SDLK_a:
			//Left button lifted
			m_Keys[LEFT] = false;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			//Right button lifted
			m_Keys[RIGHT] = false;
			break;
		case SDLK_q:
			//Time toggle button lifted
			m_Keys[TOGGLE_TIME] = true;
			break;
		case SDLK_e:
			//Interaction button lifted
			m_Keys[INTERACT] = true;
			break;
		default:
			break;
		}
	}
}

void GameManager::AddtoInventory(Item * item)
{
	//Adds item to inventory
	m_Inventory.push_back(item);
}

void GameManager::FreeFromInventory(int item)
{
	//Remove item from inventory
	m_Inventory.erase(m_Inventory.begin() + item);
	m_Inventory.shrink_to_fit();
}

bool GameManager::ItemCollision(Item * item)
{
	//Returns true if colliding with item
	return (
		m_Player->GetTopLeft().x <= item->GetTopRight().x &&
		m_Player->GetTopRight().x >= item->GetTopLeft().x &&
		m_Player->GetTopLeft().y <= item->GetBotLeft().y &&
		m_Player->GetBotLeft().y >= item->GetTopLeft().y
		);
}

void GameManager::ToggleTimeState(void)
{
	//Switch time state
	m_TimeState = !m_TimeState;
}

void GameManager::EventHandler(void)
{
	while (
		SDL_PollEvent(&m_Event) != NULL &&
		m_Running
		)
	{
		//If the event is a key input
		if (
			m_Event.type == SDL_KEYDOWN ||
			m_Event.type == SDL_KEYUP
			) Input();

		//If the event is a user event
		else if (m_Event.type == SDL_USEREVENT) UpdateGame();
	}
}

void GameManager::PresentRenderer(void)
{
	//wipe display
	SDL_RenderClear(m_Renderer);
	
	//Update viewport
	UpdateViewport();

	//Draw section of level in viewport
	m_CurrentLevel->LevelArena->Draw(m_ViewportPos);

	//For each door in the level
	for (auto d : m_CurrentLevel->GetDoors())
	{
		//If door is in viewport, DRAW
		if (InViewport(d)) d->Draw(m_ViewportPos);
	}

	//For each item in the level
	for (auto i : m_CurrentLevel->GetItems())
	{
		//If item is in viewport, DRAW
		if (InViewport(i)) i->Draw(m_ViewportPos);
	}

	//For each monster in the level
	for (auto m : m_CurrentLevel->GetMonsters())
	{
		//Update animation if moved
		if (m->Moved()) m->NextFrame();

		//If monster is in viewport, DRAW
		if (InViewport(m)) m->Draw(m_ViewportPos);
	}

	//If player has moved
	if (m_Player->Moved())
	{
		//Update animation
		m_Player->NextFrame();
		//Set moved back to false
		m_Player->SetMoved(false);
	}
	//If player has not moved
	else
	{
		//Go to original frame
		m_Player->SetFrame(0);
	}

	//Draw player
	m_Player->Draw(m_ViewportPos);



	//show what was drawn
	SDL_RenderPresent(m_Renderer);
}

void GameManager::CreateTimerEvent(void)
{
	SDL_Event event;
	SDL_UserEvent userEvent;

	//Set up user event
	userEvent.type = SDL_USEREVENT;
	userEvent.data1 = NULL;
	userEvent.data2 = NULL;

	userEvent.code = GE_TIMER;

	//Create event
	event.type = SDL_USEREVENT;
	event.user = userEvent;

	//Push event
	SDL_PushEvent(&event);
}

Uint32 GameManager::TimerCallback(Uint32 interval, void * gameObjectIn)
{
	if (gameObjectIn)
	{
		GameManager* gameObject = static_cast<GameManager*>(gameObjectIn);
		gameObject->CreateTimerEvent();
	}

	return interval;
}

void GameManager::CheckEvents(void)
{
	while (SDL_PollEvent(&m_Event))
	{
		switch (m_Event.type)
		{
		case SDL_USEREVENT:
		{
			if (m_Event.user.code == GE_TIMER)
			{
				if (++m_ConsecutiveLogicUpdates < m_MaxLogicUpdates)
					m_UpdateLogic = true;

				if (SDL_PeepEvents(
					NULL,
					1,
					SDL_PEEKEVENT,
					SDL_USEREVENT,
					SDL_USEREVENT
				) == 0)
				{
					m_RenderFrame = true;
					m_ConsecutiveLogicUpdates = 0;
				}
			}
		} break;
		}
	}
}

void GameManager::WallCollision(Character * character, Arena * level)
{
	int xDistance = 0,
		yDistance = 0;

	//X movement

	//If direction is going right
	if (character->GetDirection().x > 0)
	{
		//If top right corner collides
		if (level->GetCharacter(
			character->GetTopRight().x + character->GetDirection().x,
			character->GetTopRight().y
		) == 'W')
		{
			//Set distance as distance between character and wall
			xDistance = level->GetCharPos(
				character->GetTopRight().x + character->GetDirection().x,
				character->GetTopRight().y).x
				- character->GetTopRight().x
				- 1;
		}
		// If bottom right corner collides
		else if (level->GetCharacter(
			character->GetBotRight().x + character->GetDirection().x,
			character->GetBotRight().y
		) == 'W')
		{
			//Set distance
			xDistance = level->GetCharPos(
				character->GetBotRight().x + character->GetDirection().x,
				character->GetBotRight().y).x
				- character->GetBotRight().x
				- 1;
		}
		else
		{
			xDistance = character->GetDirection().x;
		}
	}
	//If direction is going left
	else if (character->GetDirection().x < 0)
	{
		//If top left corner collides
		if (level->GetCharacter(
			character->GetTopLeft().x + character->GetDirection().x,
			character->GetTopLeft().y
		) == 'W'
			)
		{
			//Set distance
			xDistance = level->GetCharPos(
				character->GetTopLeft().x + character->GetDirection().x,
				character->GetTopLeft().y).x
				- character->GetTopLeft().x
				+ level->GetBlockDimensions().x
				+ 1;
		}
		//If bottom left corner collides
		else if (level->GetCharacter(
			character->GetBotLeft().x + character->GetDirection().x,
			character->GetBotLeft().y
		) == 'W')
		{
			//Set distance
			xDistance = level->GetCharPos(
				character->GetBotLeft().x + character->GetDirection().x,
				character->GetBotLeft().y).x
				- character->GetBotLeft().x
				+ level->GetBlockDimensions().x
				+ 1;
		}
		else
		{
			xDistance = character->GetDirection().x;
		}
	}

	//Y movement

	//If direction is going down
	if (character->GetDirection().y > 0)
	{
		//If bottom left corner collides
		if (level->GetCharacter(
			character->GetBotLeft().x,
			character->GetBotLeft().y + character->GetDirection().y
		) == 'W')
		{
			//Set distance
			yDistance = character->GetBotLeft().y -
				level->GetCharPos(
					character->GetBotLeft().x,
					character->GetBotLeft().y + character->GetDirection().y).y
				- 1;
		}
		//If bottom right corner collides
		else if (level->GetCharacter(
			character->GetBotRight().x,
			character->GetBotRight().y + character->GetDirection().y
		) == 'W')
		{
			//Set distance
			yDistance = character->GetBotRight().y -
				level->GetCharPos(
					character->GetBotRight().x,
					character->GetBotRight().y + character->GetDirection().y).y
				- 1;
		}
		else
		{
			yDistance = character->GetDirection().y;
		}
	}
	//If direction is going up
	else if (character->GetDirection().y < 0)
	{
		//If top left corner collides
		if (level->GetCharacter(
			character->GetTopLeft().x,
			character->GetTopLeft().y + character->GetDirection().y
		) == 'W')
		{
			//Set distance
			yDistance = level->GetCharPos(
				character->GetTopLeft().x,
				character->GetTopLeft().y + character->GetDirection().y).y
				- character->GetTopLeft().y
				+ level->GetBlockDimensions().y
				+ 1;
		}
		//If top right corner collides
		else if (level->GetCharacter(
			character->GetTopRight().x,
			character->GetTopRight().y + character->GetDirection().y
		) == 'W')
		{
			//Set distance
			yDistance = level->GetCharPos(
				character->GetTopRight().x,
				character->GetTopRight().y + character->GetDirection().y).y
				- character->GetTopRight().y
				+ level->GetBlockDimensions().y
				+ 1;
		}
		else
		{
			yDistance = character->GetDirection().y;
		}
	}

	//Set direction x as distance to block
	character->SetDirection(xDistance, yDistance);
}

void GameManager::EntityCollision(Character * entity1, Entity * entity2)
{
	int xDistance = 0,
		yDistance = 0;

	//Detect player and entity overlap
	if (
		entity1->GetTopLeft().x + entity1->GetDirection().x <= entity2->GetBotRight().x &&
		entity1->GetBotRight().x + entity1->GetDirection().x >= entity2->GetTopLeft().x &&
		entity1->GetTopLeft().y + entity1->GetDirection().y <= entity2->GetBotRight().y &&
		entity1->GetBotRight().y + entity1->GetDirection().y >= entity2->GetTopLeft().y
		)
	{
		
		//Player goes left
		if (entity1->GetDirection().x < 0)
		{
			//Set x distance as x distance between entities
			xDistance = entity2->GetBotRight().x - entity1->GetTopLeft().x + 1;
		}
		//Player goes right
		if (entity1->GetDirection().x > 0)
		{
			//Set x distance as x distance between entities
			xDistance = entity2->GetTopLeft().x - entity1->GetBotRight().x - 1;
		}
		//Player goes up
		if (entity1->GetDirection().y < 0)
		{
			//Set y distance as y distance between entities
			yDistance = entity2->GetBotRight().y - entity1->GetTopLeft().y + 1;
		}
		//Player goes down
		if (entity1->GetDirection().y > 0)
		{
			//Set y distance as y distance between entities
			yDistance = entity2->GetTopLeft().y - entity1->GetBotRight().y - 1;
		}

		//Set distance as distance from entity
		entity1->SetDirection(xDistance, yDistance);
	}
}

bool GameManager::EndofLevel(void)
{
	return (
		m_CurrentLevel->LevelArena->GetCharacter(m_Player->GetTopLeft().x, m_Player->GetTopLeft().y) == 'X' ||
		m_CurrentLevel->LevelArena->GetCharacter(m_Player->GetTopRight().x, m_Player->GetTopRight().y) == 'X' ||
		m_CurrentLevel->LevelArena->GetCharacter(m_Player->GetBotLeft().x, m_Player->GetBotLeft().y) == 'X' ||
		m_CurrentLevel->LevelArena->GetCharacter(m_Player->GetBotRight().x, m_Player->GetBotRight().y) == 'X'
		);
}

void GameManager::EndGame(bool victory)
{
	//Player wins
	if (victory)
	{
		m_InfoScreen = new Bitmap(
			m_Renderer,
			"../Assets/Bitmaps/Level/Victory.bmp",
			0,
			0,
			false
		);
	}
	//Player loses
	else
	{
		m_InfoScreen = new Bitmap(
			m_Renderer,
			"../Assets/Bitmaps/Level/Defeat.bmp",
			0,
			0,
			false
		);
	}

	//wipe display
	SDL_RenderClear(m_Renderer);
	
	//Draw end screen
	m_InfoScreen->Draw(m_InfoScreen->GetPos());

	//Present renderer
	SDL_RenderPresent(m_Renderer);

	//Stops game update
	m_RenderFrame = false;
	m_UpdateLogic = false;

	//Pauses for 3 secs
	SDL_Delay(3000);

	//Ends game
	m_Running = false;
}

void GameManager::UpdateViewport(void)
{
	//Set viewport position to player posiition
	m_ViewportPos.x = m_Player->GetCentre().x - (m_ViewportDimensions.x / 2);
	m_ViewportPos.y = m_Player->GetCentre().y - (m_ViewportDimensions.y / 2);

	if (m_ViewportPos.x < 0) m_ViewportPos.x = 0;
	else if (
		m_ViewportPos.x + m_ViewportDimensions.x > m_CurrentLevel->LevelArena->GetWidth()
		) m_ViewportPos.x = m_CurrentLevel->LevelArena->GetWidth() - m_ViewportDimensions.x;

	if (m_ViewportPos.y < 0) m_ViewportPos.y = 0;
	else if (
		m_ViewportPos.y + m_ViewportDimensions.y > m_CurrentLevel->LevelArena->GetHeight()
		) m_ViewportPos.y = m_CurrentLevel->LevelArena->GetHeight() - m_ViewportDimensions.y;
}

bool GameManager::InViewport(Entity * entity)
{
	//Set top, bottom, left and right edges of viewport
	int top = m_ViewportPos.y - entity->GetDimensions().y,
		bot = m_ViewportPos.y + m_ViewportDimensions.y + entity->GetDimensions().y,
		left = m_ViewportPos.x - entity->GetDimensions().x,
		right = m_ViewportPos.x + m_ViewportDimensions.x + entity->GetDimensions().x;

	//Return true if in viewport
	if (
		entity->GetTopLeft().x <= right &&
		entity->GetTopRight().x >= left &&
		entity->GetBotLeft().y >= top &&
		entity->GetTopLeft().y <= bot
		) return true;

	//Return false if not in viewport
	return false;
}

void GameManager::UpdateGame(void)
{
	//Update game logic
	if (m_UpdateLogic)
	{
		//If player is falling, SHRINK
		if (m_Player->Falling(m_CurrentLevel->LevelArena)) m_Player->AddHealth(-100);
		//Player input moves if not falling
		else
		{
			//If player presses up button - Move up
			if (m_Keys[UP]) m_Player->MoveUp();
			//If player presses down button - Move down
			if (m_Keys[DOWN]) m_Player->MoveDown();

			//If player presses left button - Move left
			if (m_Keys[LEFT]) m_Player->MoveLeft();
			//If player presses right button - Move right
			if (m_Keys[RIGHT]) m_Player->MoveRight();
		}

		//If player has moved, set moved to true
		if (
			m_Player->GetDirection().x != 0 ||
			m_Player->GetDirection().y != 0
			) m_Player->SetMoved(true);
		
		//If player presses toggle time button
		if (m_Keys[TOGGLE_TIME])
		{
			//Toggle time state
			ToggleTimeState();
			//Set toggle time as false
			m_Keys[TOGGLE_TIME] = false;
		}

		//Time state in future
		if (m_TimeState)
		{
			//Set current level to future state
			m_CurrentLevel = m_FutureLevels[m_LevelCounter];
		}
		//Time state in past
		else
		{
			//Set current level to past state
			m_CurrentLevel = m_PastLevels[m_LevelCounter];
		}

		//Runs player to wall collision
		WallCollision(m_Player, m_CurrentLevel->LevelArena);

		//For each monster in the current level
		for (auto m : m_CurrentLevel->GetMonsters())
		{
			//Update monster AI
			m->UpdateAI();
			//Run monster to wall collision
			WallCollision(m, m_CurrentLevel->LevelArena);

			//Monster to door collision
			for (auto d : m_CurrentLevel->GetDoors()) EntityCollision(m, d);

			//Update monster character
			m->Update();
		}

		//For each door in current level
		for (auto d : m_CurrentLevel->GetDoors())
		{
			//Player presses interact button
			if (
				m_Keys[INTERACT] &&
				m_Player->InReach(d)
				)
			{
				//For each inventory item
				for (auto i : m_Inventory)
				{
					//Toggle lock if key matches door
					if (i->GetValue() == d->GetDoorNum()) d->ToggleLocked();
					//Update door bitmap
					d->NextFrame();
				}
			}

			//Stop interact key input
			m_Keys[INTERACT] = false;

			//If door locked
			if (d->GetLocked())
			{
				//Run player to door collision
				EntityCollision(m_Player, d);
			}
		}

		//For each item in the current level
		for (
			int i = 0;
			i < static_cast<signed>(m_CurrentLevel->GetItems().size());
			i++
			)
		{
			//Sets item as pointer to current item
			Item* item = m_CurrentLevel->GetItems()[i];

			//Player with health under max collides with health
			if (
				ItemCollision(item) &&
				item->GetType() == HEALTH &&
				m_Player->GetHealth() < m_Player->GetMaxHealth()
				)
			{
				//Add item value to player health
				m_Player->AddHealth(item->GetValue());
				//Remove item from current level
				m_CurrentLevel->RemoveItem(i);
			}
			//Player collides with health
			else if (
				ItemCollision(item) &&
				item->GetType() == KEY
				)
			{
				//Add item to inventory
				AddtoInventory(item);
				//Remove item from current level
				m_CurrentLevel->RemoveItem(i);
			}
		}
		
		//Update player
		m_Player->Update();

		//If player dies, game lost
		if (m_Player->GetHealth() == 0) EndGame(false);
		//If player reaches end of level
		else if (EndofLevel())
		{
			//Add 1 to level counter
			++m_LevelCounter;

			//Empty inventory
			for (unsigned i = 0; i < m_Inventory.size(); i++) FreeFromInventory(i);
			
			//Level counter higher than number of levels
			if (m_LevelCounter >= static_cast<signed>(m_PastLevels.size()))
			{
				//VICTORY
				EndGame(true);
			}
			//Time state in future
			else if (m_TimeState)
			{
				//Load future level
				m_CurrentLevel = m_FutureLevels[m_LevelCounter];
			}
			//Time state in past
			else
			{
				//Load past level
				m_CurrentLevel = m_PastLevels[m_LevelCounter];
			}

			//Set Player position to start point
			m_Player->SetPos(m_CurrentLevel->GetStartPoint().x, m_CurrentLevel->GetStartPoint().y);
		}
	}

	//Render graphics
	if (m_RenderFrame)
	{
		PresentRenderer();
	}
}

void GameManager::GameLoop(void)
{
	//wipe display
	SDL_RenderClear(m_Renderer);

	//Set info screen as start screen
	m_InfoScreen = new Bitmap(
		m_Renderer,
		"../Assets/Bitmaps/Level/TitleScreen.bmp",
		0,
		0,
		false
	);

	//Display start screen
	m_InfoScreen->Draw(m_InfoScreen->GetPos());

	//show what was drawn
	SDL_RenderPresent(m_Renderer);

	//Wait for 3 secs
	SDL_Delay(3000);

	//Clean up info screen
	delete m_InfoScreen;
	m_InfoScreen = nullptr;

	//Loop while running is true
	do
	{
		//Run event handler
		EventHandler();
	} while (m_Running);
}

GameManager::~GameManager()
{
	//Clear up the renderer
	SDL_DestroyRenderer(m_Renderer);
	m_Renderer = nullptr;

	//Clear up the window
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
}
