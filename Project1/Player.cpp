#include "stdafx.h"
#include <iostream>

void Play()
{
	music.openFromFile("Tiles/CoolSong.ogg");
	music.play();
	float playerSpeed = 3;
	playerCollider = sf::RectangleShape(Vector2f(50, 50));
	playerCollider.setPosition(heroSprite.getPosition());
	if (Keyboard::isKeyPressed(Keyboard::A) && move == true)
	{
		heroSprite.move(-playerSpeed, 0);
		//heroSprite.setPosition(Vector2f(pos.x, pos.y - playerSpeed));
	}
	if (Keyboard::isKeyPressed(Keyboard::W) && move == true)
	{
		heroSprite.move(0, -playerSpeed);
		//heroSprite.setPosition(Vector2f(pos.x - playerSpeed, pos.y));
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && move == true)
	{
		heroSprite.move(playerSpeed, 0);
		//heroSprite.setPosition(Vector2f(pos.x, pos.y + playerSpeed));
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && move == true)
	{
		heroSprite.move(0, playerSpeed);
		//heroSprite.setPosition(Vector2f(pos.x + playerSpeed, pos.y));
	}
}
