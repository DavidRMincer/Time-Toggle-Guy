#pragma once
#include <string>
#include "SDL.h"
#include "Vector2D.h"
#include "SDL_render.h"

using namespace std;

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class Bitmap
{
private:
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Texture;
	SDL_Surface* m_Surface;

	Vector2D m_Pos,
		m_Dimensions;

public:
	Bitmap(SDL_Renderer* renderer, string fileName,
		int x, int y, bool Transparent);
	Vector2D GetPos(void);
	void SetPos(int x, int y);
	void SetDimensions(Vector2D dimensions);
	Vector2D GetDimensions(void);
	void Draw(Vector2D viewportPos);
	~Bitmap();
};

