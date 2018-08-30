#include "Bitmap.h"
#include <iostream>


Bitmap::Bitmap(SDL_Renderer * renderer, string fileName, int x, int y, bool Transparent)
{
	//Store renderer
	m_Renderer = renderer;
	//Create bitmap surface
	m_Surface = SDL_LoadBMP(fileName.c_str());

	//If bitmap not loaded
	if (!m_Surface)
	{
		//Output error
		cout << "SURFACE for bitmap '%s' not loaded! \n" << endl;
		cout << "%s\n" << SDL_GetError() << endl;
	}
	else
	{
		//If we use transparency
		if (Transparent)
		{
			//Colour key is magenta (r=255, g=0, b=255)
			Uint32 colourKey = SDL_MapRGB(m_Surface->format, 255, 0, 255);
			SDL_SetColorKey(m_Surface, SDL_TRUE, colourKey);
		}

		//Create texture
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
		//If texture not loaded
		if (!m_Texture)
		{
			//Output error
			cout << "TEXTURE for bitmap '%s' not loaded \n" << fileName.c_str() << endl;
			cout << "%s \n" << SDL_GetError() << endl;
		}
	}

	//Store width and height
	m_Dimensions.x = m_Surface->w;
	m_Dimensions.y = m_Surface->h;

	//store position vals
	m_Pos.x = x;
	m_Pos.y = y;
}

Vector2D Bitmap::GetPos(void)
{
	return m_Pos;
}

void Bitmap::SetPos(int x, int y)
{
	m_Pos.x = x;
	m_Pos.y = y;
}

void Bitmap::SetDimensions(Vector2D dimensions)
{
	m_Dimensions.x = dimensions.x;
	m_Dimensions.y = dimensions.y;
}

Vector2D Bitmap::GetDimensions(void)
{
	return m_Dimensions;
}

void Bitmap::Draw(Vector2D viewportPos)
{
	//render bitmap
	if (m_Texture)
	{
		SDL_Rect destRect = {
			m_Pos.x - viewportPos.x,
			m_Pos.y - viewportPos.y,
			m_Surface->w,
			m_Surface->h
		};
		SDL_RenderCopy(
			m_Renderer,
			m_Texture,
			NULL,
			&destRect
		);
	}
}

Bitmap::~Bitmap()
{
}
