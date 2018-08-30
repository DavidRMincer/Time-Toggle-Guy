#include "Item.h"



Item::Item(int x, int y, ITEM_TYPE type, int value, SDL_Renderer * renderer)
	: Entity(x, y, renderer)
{
	m_Value = value;
	m_Type = type;

	switch (type)
	{
	case KEY:
		//Add key bitmap to frames
		AddFrame(renderer, "../Assets/Bitmaps/Items/Key.bmp");
		break;
	case HEALTH:
		//Add health bitmap to frames
		AddFrame(renderer, "../Assets/Bitmaps/Items/Health.bmp");
		break;
	default:
		break;
	}

	//Set dimensions as size of bitmap
	m_Dimensions = m_Frames[0]->GetDimensions();
}

int Item::GetValue(void)
{
	//Return number value of item
	return m_Value;
}

ITEM_TYPE Item::GetType(void)
{
	return m_Type;
}

Item::~Item()
{
}
