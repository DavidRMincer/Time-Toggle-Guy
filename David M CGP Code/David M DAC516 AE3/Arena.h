#pragma once
#include <vector>
#include <string>
#include "SDL.h"
#include "Vector2D.h"
#include "Bitmap.h"

using namespace std;

struct SDL_Renderer;

class Arena
{
private:
	SDL_Renderer* m_Renderer;
	vector<string> m_Arena;
	Vector2D m_BlockDimensions;
	Bitmap* m_WallTexture;
	Bitmap* m_FloorTexture;
	Bitmap* m_BackgroundTexture;
	Bitmap* m_ExitTexture;

public:
	Arena(SDL_Renderer* renderer, vector<string> arena);
	int GetWidth(void);
	int GetHeight(void);
	char GetCharacter(int x, int y);
	Vector2D GetCharPos(int x, int y);
	Vector2D GetBlockDimensions(void);
	vector<string> GetArena(void);
	void Draw(Vector2D viewportPos);
	~Arena();
};

