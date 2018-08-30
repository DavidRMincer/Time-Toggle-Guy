#include "Character.h"



Character::Character(int x, int y, int speed, SDL_Renderer * renderer)
	: Entity(x, y, renderer)
{
	m_Speed = speed;
}

void Character::MoveLeft(void)
{
	//Subtract speed from x direction
	m_Direction.x -= m_Speed;
}

void Character::MoveRight(void)
{
	//Add speed from x direction
	m_Direction.x += m_Speed;
}

void Character::MoveUp(void)
{
	//Subtract speed from y direction
	m_Direction.y -= m_Speed;
}

void Character::MoveDown(void)
{
	//Add speed from y direction
	m_Direction.y += m_Speed;
}

Vector2D Character::GetDirection(void)
{
	//Return direction vector
	return m_Direction;
}

void Character::SetDirection(int x, int y)
{
	m_Direction.x = x;
	m_Direction.y = y;
}

bool Character::InReach(Entity * entity)
{
	float distance, x, y;

	//Set x and y as centre point - target's centre point
	x = static_cast<float>(GetCentre().x - entity->GetCentre().x);
	y = static_cast<float>(GetCentre().y - entity->GetCentre().y);

	//PYTHAGORAS

	//Set distance as square root of x^2 + y^2
	distance = sqrt((x * x) + (y * y));

	//Return true if distance is in reach
	if (distance <= m_Reach) return true;

	//Return false if not in reach
	return false;
}

bool Character::Moved(void)
{
	return m_Moved;
}

void Character::SetMoved(bool moved)
{
	m_Moved = moved;
}

bool Character::Falling(Arena * level)
{
	//If character is over hole, return true
	return (level->GetCharacter(GetCentre().x, GetCentre().y) == '!');
}

void Character::Update(void)
{
	//If character moves
	if (
		m_Direction.x != 0 ||
		m_Direction.y != 0
		)
	{
		//Set moved to true
		m_Moved = true;

		//Move character
		m_Pos.x += m_Direction.x;
		m_Pos.y += m_Direction.y;
	}

	//Update position of frames
	for (auto f : m_Frames) f->SetPos(m_Pos.x, m_Pos.y);
	
	//Reser direction vector
	m_Direction.Reset();
}

Character::~Character()
{
}
