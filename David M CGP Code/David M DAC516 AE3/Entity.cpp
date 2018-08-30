#include "Entity.h"



Entity::Entity(int x, int y, SDL_Renderer * renderer)
{
	m_Pos.x = x;
	m_Pos.y = y;

	m_Renderer = renderer;
}

Vector2D Entity::GetPos(void)
{
	//Return entity's position
	return m_Pos;
}

void Entity::SetPos(int x, int y)
{
	//Set x and y position
	m_Pos.x = x;
	m_Pos.y = y;
}

Vector2D Entity::GetDimensions(void)
{
	//Returns entity dimensions
	return m_Dimensions;
}

void Entity::SetDimensions(int x, int y)
{
	//Set width and height of entity
	m_Dimensions.x = x;
	m_Dimensions.y = y;

	//Set all bitmap dimensions to entity dimensions
	for (auto x : m_Frames) x->SetDimensions(m_Dimensions);
}

Vector2D Entity::GetTopLeft(void)
{
	//Returns position of corner
	return m_Pos;
}

Vector2D Entity::GetTopRight(void)
{
	//Set top right corner of entity
	Vector2D TR;

	TR.x = m_Pos.x + m_Dimensions.x - 1;
	TR.y = m_Pos.y;

	//Returns position of corner
	return TR;
}

Vector2D Entity::GetBotLeft(void)
{
	//Set bottom left corner of entity
	Vector2D BL;

	BL.x = m_Pos.x;
	BL.y = m_Pos.y + m_Dimensions.y - 1;

	//Returns position of corner
	return BL;
}

Vector2D Entity::GetBotRight(void)
{
	//Set bottom right corner of entity
	Vector2D BR;

	BR.x = m_Pos.x + m_Dimensions.x - 1;
	BR.y = m_Pos.y + m_Dimensions.y - 1;

	//Returns position of corner
	return BR;
}

Vector2D Entity::GetCentre(void)
{
	Vector2D centre;

	centre.x = m_Pos.x + (m_Dimensions.x / 2) - 1;
	centre.y = m_Pos.y + (m_Dimensions.y / 2) - 1;

	//Returns position of corner
	return centre;
}

void Entity::NextFrame(void)
{
	//Add 1 to current frame
	++m_CurrentFrame;

	//When current frame set to modular of number of frames
	m_CurrentFrame %= m_Frames.size();
}

void Entity::SetFrame(int frame)
{
	m_CurrentFrame = frame;

	//Check that current frame is less than size of frames
	if (m_CurrentFrame >= m_Frames.size()) m_CurrentFrame = m_Frames.size() - 1;
	//And at least 0 or higher
	if (m_CurrentFrame < 0) m_CurrentFrame = 0;
}

void Entity::AddFrame(SDL_Renderer * renderer, string fileName)
{
	//Create new bitmap
	Bitmap* Frame = new Bitmap(renderer, fileName, m_Pos.x, m_Pos.y, true);

	//Add frame to vector frames
	m_Frames.push_back(Frame);
}

void Entity::Draw(Vector2D viewportPos)
{
	//Draw current frame
	m_Frames[m_CurrentFrame]->Draw(viewportPos);
}

Entity::~Entity()
{
	//Delete frames
	for (auto x : m_Frames)
	{
		delete x;
		x = nullptr;
	}
	m_Frames.resize(0);
}
