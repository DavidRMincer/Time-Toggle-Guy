#include "Monster.h"
#include <math.h>


Monster::Monster(int x, int y, int speed, int damage, int FOV, Player* player, SDL_Renderer* renderer)
	: Character(x, y, speed, renderer)
{
	m_Damage = damage;
	m_FOV = FOV;
	m_Target = player;

	//Add bitmap to frames
	AddFrame(m_Renderer, "../Assets/Bitmaps/Monster/MonsterFrame0.bmp");
	AddFrame(m_Renderer, "../Assets/Bitmaps/Monster/MonsterFrame1.bmp");
	AddFrame(m_Renderer, "../Assets/Bitmaps/Monster/MonsterFrame2.bmp");
	AddFrame(m_Renderer, "../Assets/Bitmaps/Monster/MonsterFrame3.bmp");
	AddFrame(m_Renderer, "../Assets/Bitmaps/Monster/MonsterFrame4.bmp");
	AddFrame(m_Renderer, "../Assets/Bitmaps/Monster/MonsterFrame5.bmp");
	AddFrame(m_Renderer, "../Assets/Bitmaps/Monster/MonsterFrame6.bmp");
	AddFrame(m_Renderer, "../Assets/Bitmaps/Monster/MonsterFrame7.bmp");
	AddFrame(m_Renderer, "../Assets/Bitmaps/Monster/MonsterFrame8.bmp");

	//Set dimensions as bitmap dimensions
	m_Dimensions.x = m_Frames[0]->GetDimensions().x;
	m_Dimensions.y = m_Frames[0]->GetDimensions().y;

	//Set reach to height * 1.5
	m_Reach = m_Dimensions.y;
}

void Monster::Follow(void)
{
	//X axis

	//Target is left of monster
	if (m_Target->GetPos().x < m_Pos.x)
	{
		//Move to the left
		MoveLeft();
	}
	//Target is right of monster
	else if (m_Target->GetPos().x > m_Pos.x)
	{
		//Move to the right
		MoveRight();
	}

	//Y axis

	//Target is above monster
	if (m_Target->GetPos().y < m_Pos.y)
	{
		//Move upwards
		MoveUp();
	}
	//Target is below monster
	else if (m_Target->GetPos().y > m_Pos.y)
	{
		//Move downwards
		MoveDown();
	}
}

void Monster::Attack(void)
{
	//Deal damage to target if in reach
	if (InReach(m_Target)) m_Target->AddHealth(-m_Damage);
}

void Monster::RandomMove()
{
	srand(static_cast<unsigned>(time(0)));

	//Monster not moving to a point
	if (!m_Moving)
	{
		//Set move point to random position within 10 of monster
		m_MoveDirection.x = rand() % 2;
		m_MoveDirection.y = rand() % 2;

		if (m_MoveDirection.x == 0) m_MoveDirection.x = -10;
		else m_MoveDirection.x = 10;
		if (m_MoveDirection.y == 0) m_MoveDirection.y = -10;
		else m_MoveDirection.y = 10;

		//Monster is moving
		m_Moving = true;
	}

	//Monster moving to a point
	else
	{
		//If point is right of monster
		if (m_MoveDirection.x > 0)
		{
			//Move right
			MoveRight();
			//Subtract 1 from x move direction
			--m_MoveDirection.x;
		}
		//If point is left of monster
		else if (m_MoveDirection.x < 0)
		{
			//Move left
			MoveLeft();
			//Add 1 to x move direction
			++m_MoveDirection.x;
		}
		
		//If point is below monster
		if (m_MoveDirection.y > 0)
		{
			//Move down
			MoveDown();
			//Subtract 1 from y move direction
			--m_MoveDirection.y;
		}
		//If point is above monster
		else if (m_MoveDirection.y < 0)
		{
			//Move up
			MoveUp();
			//Add 1 to y move direction
			++m_MoveDirection.y;
		}

		if (
			m_MoveDirection.x == 0 &&
			m_MoveDirection.y == 0
		)
		{
			m_Moving = false;
		}
	}
}

bool Monster::InFOV(void)
{
	float distance, x, y;

	//Set x and y as centre point - target's centre point
	x = static_cast<float>(GetCentre().x - m_Target->GetCentre().x);
	y = static_cast<float>(GetCentre().y - m_Target->GetCentre().y);

	//PYTHAGORAS
	//Set distance as square root of x^2 + y^2
	distance = sqrt((x * x) + (y * y));

	//Return true if distance is in FOV
	if (distance <= m_FOV) return true;

	//Return false if not in FOV
	return false;
}

void Monster::UpdateAI(void)
{
	//Player in FOV
	if (InFOV())
	{
		//Follow player
		Follow();
		//Attack player
		Attack();
	}

	//Move randomly if not in FOV
	else RandomMove();
}

Monster::~Monster()
{
	//Clean up player pointer
	delete m_Target;
	m_Target = nullptr;
}
