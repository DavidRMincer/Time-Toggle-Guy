#include "Door.h"



Door::Door(int x, int y, int doorNum, SDL_Renderer* renderer)
	: Entity(x, y, renderer)
{
	m_DoorNum = doorNum;
	
	//Add door bitmaps to frames
	AddFrame(renderer, "../Assets/Bitmaps/Level/Door.bmp");
	AddFrame(renderer, "../Assets/Bitmaps/Level/DoorOpen.bmp");

	//Set bitmap positions as door position
	for (auto f : m_Frames) f->SetPos(x, y);

	//Set dimensions of door as dimensions of bitmap
	m_Dimensions.x = m_Frames[0]->GetDimensions().x;
	m_Dimensions.y = m_Frames[0]->GetDimensions().y;
}

int Door::GetDoorNum(void)
{
	//Returns value of DoorNum
	return m_DoorNum;
}

bool Door::GetLocked(void)
{
	//Return bool showing if door is locked
	return m_Locked;
}

void Door::ToggleLocked(void)
{
	//Toggle m_Locked bool
	m_Locked = !m_Locked;
}

Door::~Door()
{
}
