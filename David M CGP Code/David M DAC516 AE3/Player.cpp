#include "Player.h"



Player::Player(int x, int y, int speed, int maxHealth, SDL_Renderer * renderer)
	: Character(x, y, speed, renderer)
{
	m_MaxHealth = maxHealth;
	m_Health = maxHealth;

	//Adds bitmap to vector of frames
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame0.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame1.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame2.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame3.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame4.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame5.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame6.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame7.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame8.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame7.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame6.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame5.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame4.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame3.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame2.bmp");
	AddFrame(m_Renderer,
		"../Assets/Bitmaps/Player/PlayerFrame1.bmp");

	//Set dimensions as bitmap dimensions
	m_Dimensions.x = m_Frames[0]->GetDimensions().x;
	m_Dimensions.y = m_Frames[0]->GetDimensions().y;

	//Set reach to height * 1.5
	m_Reach = static_cast<int>(m_Dimensions.y * 1.5);
}

int Player::GetHealth(void)
{
	//Returns player's remaining health
	return m_Health;
}

void Player::AddHealth(int health)
{
	//Adds additional health to m_Health
	m_Health += health;

	//If health exceeds max health,
	//Set health as max health
	if (m_Health > m_MaxHealth) m_Health = m_MaxHealth;
	else if (m_Health < 0) m_Health = 0;
}

int Player::GetMaxHealth(void)
{
	return m_MaxHealth;
}

void Player::ResetHealth(void)
{
	//Resets health back to full
	m_Health = m_MaxHealth;
}

Player::~Player()
{
}
