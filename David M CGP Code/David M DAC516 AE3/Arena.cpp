#include "Arena.h"



Arena::Arena(SDL_Renderer * renderer, vector<string> arena)
{
	m_Arena = arena;
	m_Renderer = renderer;

	m_FloorTexture = new Bitmap(
		m_Renderer,
		"../Assets/Bitmaps/Level/Floor.bmp",
		0,
		0,
		false
	);
	m_WallTexture = new Bitmap(
		m_Renderer,
		"../Assets/Bitmaps/Level/Wall.bmp",
		0,
		0,
		false
	);
	m_ExitTexture = new Bitmap(
		m_Renderer,
		"../Assets/Bitmaps/Level/Exit.bmp",
		0,
		0,
		false
	);

	//Set block dimensions as size of floor texture
	m_BlockDimensions.x = m_FloorTexture->GetDimensions().x;
	m_BlockDimensions.y = m_FloorTexture->GetDimensions().y;
}

int Arena::GetWidth(void)
{
	return m_Arena[0].length() * m_BlockDimensions.x;
}

int Arena::GetHeight(void)
{
	return m_Arena.size() * m_BlockDimensions.y;
}

char Arena::GetCharacter(int x, int y)
{
	x /= m_BlockDimensions.x;
	y /= m_BlockDimensions.y;

	return m_Arena [y] [x];
}

Vector2D Arena::GetCharPos(int x, int y)
{
	//Divide x and y by block dimensions
	x /= m_BlockDimensions.x;
	y /= m_BlockDimensions.y;

	//Multiply x and y by block dimensions
	x *= m_BlockDimensions.x;
	y *= m_BlockDimensions.y;

	Vector2D charPos;

	//Set char pos coords
	charPos.x = x;
	charPos.y = y;

	return charPos;
}

Vector2D Arena::GetBlockDimensions(void)
{
	return m_BlockDimensions;
}

vector<string> Arena::GetArena(void)
{
	return m_Arena;
}

void Arena::Draw(Vector2D viewportPos)
{
 	for (unsigned y = 0; y < m_Arena.size(); ++y)
	{
		for (unsigned x = 0; x < m_Arena[0].length(); ++x)
		{
			switch (GetCharacter(x * m_BlockDimensions.x, y * m_BlockDimensions.y))
			{
			case 'W':
				//Set wall texture position as x, y
				m_WallTexture->SetPos(
					x * m_BlockDimensions.x,
					y * m_BlockDimensions.y
				);
				//Draw wall
				m_WallTexture->Draw(viewportPos);
				break;
			case '!':
				//DRAW HOLE
				break;
			case 'X':
				//Set exit texture position as x, y
				m_ExitTexture->SetPos(
					x * m_BlockDimensions.x,
					y * m_BlockDimensions.y
				);
				//Draw exit
				m_ExitTexture->Draw(viewportPos);
				break;
			default:
				//Set floor texture position as x, y
				m_FloorTexture->SetPos(
					x * m_BlockDimensions.x,
					y * m_BlockDimensions.y
				);
				//Draw floor
				m_FloorTexture->Draw(viewportPos);
				break;
			}
		}
	}
}

Arena::~Arena()
{
	//Clean up bitmaps
	delete m_ExitTexture;
	m_ExitTexture = nullptr;
	
	delete m_WallTexture;
	m_WallTexture = nullptr;

	delete m_FloorTexture;
	m_FloorTexture = nullptr;

	// Delete arena
	for (auto x : m_Arena) x = nullptr;
	m_Arena.resize(0);
}
