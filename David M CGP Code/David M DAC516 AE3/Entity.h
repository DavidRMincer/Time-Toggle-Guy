#pragma once
#include <vector>
#include "Vector2D.h"
#include "Bitmap.h"

using namespace std;

class Entity
{
protected:
	Vector2D m_Pos,
		m_Dimensions;
	vector<Bitmap*> m_Frames;
	int m_CurrentFrame{ 0 };
	SDL_Renderer* m_Renderer;

public:
	Entity(int x, int y, SDL_Renderer* renderer);
	Vector2D GetPos(void);
	void SetPos(int x, int y);
	Vector2D GetDimensions(void);
	void SetDimensions(int x, int y);
	Vector2D GetTopLeft(void);
	Vector2D GetTopRight(void);
	Vector2D GetBotLeft(void);
	Vector2D GetBotRight(void);
	Vector2D GetCentre(void);
	void NextFrame(void);
	void SetFrame(int frame);
	void AddFrame(SDL_Renderer* renderer, string fileName);
	void Draw(Vector2D viewportPos);
	~Entity();
};

