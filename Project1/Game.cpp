#include "stdafx.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <random>
//#include <SFML/FileInputStream.hpp>
#include <fstream>
#include <iostream>
#include <math.h> 
#include <SFML/Music.hpp>

//making code easier to type with "using namespace"
using namespace sf;

//making a bool to check if the users mouse is hovered over the sprite
bool isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp)
{
	if (sprite.contains(mp))
	{
		return true;
	}
	return false;
}
sf::Music music;
sf::RectangleShape playerCollider;
sf::RectangleShape redGemCollider;
Vector2f direction;
bool move = true;
void Play();
bool Intersect(const sf::RectangleShape& rec1, const sf::RectangleShape& rec2);
//using main to set up the game - used the timber tutorial
//to get the main function to display and close working
int main()
{

	//setting the users screen resolution
	hRes = 1920;
	vRes = 1500;
		
	//setting the pixel size of the tiles, 100x100
	tileSize = 100;

	VideoMode vm(hRes, vRes);

	RenderWindow window(vm, "Tile Editor", Style::Fullscreen);
	window.setFramerateLimit(0);
	window.setVerticalSyncEnabled(false);
	InitGame();

	Vector2f mp;

	//saving the users mouse position
	mp.x = Mouse::getPosition(window).x;
	mp.y = Mouse::getPosition(window).y;

	indX = 0;
	indY = 0;

	tileIndex = 0;

	bool drawHero = false;
	bool drawGem = true;

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			

			//creating my two buttons for loading and saving
			if (isSpriteHover(spriteLoadButton.getGlobalBounds(), Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
			{
				if (event.type == Event::MouseButtonReleased &&  event.mouseButton.button == Mouse::Left)
				{
					LoadData();
				}
			}

			//setting the save button up
			if (isSpriteHover(spriteSaveButton.getGlobalBounds(), Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
			{
				if (event.type == Event::MouseButtonReleased &&  event.mouseButton.button == Mouse::Left)
				{
					SaveData();
				}
			}

			if (isSpriteHover(spritePlayButton.getGlobalBounds(), Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
			{
				if (event.type == Event::MouseButtonReleased &&  event.mouseButton.button == Mouse::Left)
				{
					heroSprite.setPosition(100, 100);
					drawHero = true;
				}
			}

			//setting all the tiles to buttons
			for (int row = 0; row < tileWidth; row++)
			{
				for (int column = 0; column < tileHeight; column++)
				{
					//if the user clicks on one of the sprites it acts as a button and the code runs
					if (isSpriteHover(spriteTile[row][column].getGlobalBounds(), Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
					{
						if (event.type == Event::MouseButtonReleased &&  event.mouseButton.button == Mouse::Left)
						{
							//outputting the users mouse position for debugging
							std::cout << row;
							std::cout << column;

							spriteTile[row][column];

							//cycles through the different tile styles when the user
							//clicks on the tiles. If the current tile is the last
							//one then it will go back to the first tile style
							if (TileStyle[row][column] <= 9)
							{
								TileStyle[row][column] += 1;

								if (TileStyle[row][column] >= 9)
								{
									TileStyle[row][column] = 0;
								}
							}


						}
					}
				}
			}

		}

		

		//closing the editor when the user hits escape
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			music.stop();
			window.close();
		}

		window.clear();

		//setting up the tile position and saving in an 2D array
		for (row = 0; row < tileWidth; row++)
		{
			for (column = 0; column < tileHeight; column++)
			{
				setTileType(TileStyle[row][column], row, column);
				spriteTile[row][column].setPosition(row*tileSize, column*tileSize);
				window.draw(spriteTile[row][column]);

				redGemCollider = sf::RectangleShape(Vector2f(50, 50));
				for (int i = 1; i < 16;)
				{
					for (int j = 1; j < 16;)
					{
						redGemSprite.setPosition(i * 100, j * 100);
						redGemCollider.setPosition(i * 100, j * 100);
						if (drawGem)
						{
							//window.draw(redGemSprite);
						}
						j += 4;
					}
					i += 4;
				}				
					if (Intersect(redGemCollider, playerCollider))
					{
						drawGem = false;
						std::cout << "You Picked Up a gem";
					}
					else
					{
						drawGem = true;
					}			
			}
		}

		if (drawHero)
		{
			window.draw(heroSprite);
		}
		if (drawHero)
		{

		}
		//setting the positions for the save and load buttons

		spriteSaveButton.setPosition(3500, 450);
		window.draw(spriteSaveButton);

		spritePlayButton.setPosition(3500, 275);
		window.draw(spritePlayButton);

		spriteLoadButton.setPosition(3500, 100);
		window.draw(spriteLoadButton);

		window.display();
	}

	return 0;
}

void InitGame()
{
	//saving the textures in the tile array
	textureTile[0].loadFromFile("Tiles/LightGrass.png");
	textureTile[1].loadFromFile("Tiles/ConcretePath.png");
	textureTile[2].loadFromFile("Tiles/ConcretePath(H).png");
	textureTile[3].loadFromFile("Tiles/ConcreteTower.png");
	textureTile[4].loadFromFile("Tiles/ConcreteWall.png");
	textureTile[5].loadFromFile("Tiles/ConcreteWall(H).png");
	textureTile[6].loadFromFile("Tiles/ConcreteTile.png");
	textureTile[7].loadFromFile("Tiles/ConcretePath(I).png");
	textureTile[8].loadFromFile("Tiles/LightWater.png");

	//setting the tile types based on the amount of tile styles
	for (int i = 0; i < 9; i++)
	{
		tileType[i].setTexture(textureTile[i]);
	}

	
	//loading all the textures from images to sprites

	sprites s;

	redGemTexture.loadFromFile("Tiles/RedGem.png");
	redGemSprite.setTexture(redGemTexture);

	heroTexture.loadFromFile("Tiles/Character1.png");
	heroSprite.setTexture(heroTexture);
	
	textureSaveButton.loadFromFile("graphics/SaveButton.png");
	spriteSaveButton.setTexture(textureSaveButton);

	textureLoadButton.loadFromFile("graphics/LoadButton.png");
	spriteLoadButton.setTexture(textureLoadButton);

	texturePlayButton.loadFromFile("graphics/PlayButton.png");
	spritePlayButton.setTexture(texturePlayButton);

	textureLightGrass.loadFromFile("Tiles/LightGrass.png");
	spriteLightGrass.setTexture(textureLightGrass);	

	textureConcreteWall.loadFromFile("Tiles/ConcreteWall.png");
	spriteConcreteWall.setTexture(textureConcreteWall);

	textureConcreteWall_H.loadFromFile("Tiles/ConcreteWall(H).png");
	spriteConcreteWall_H.setTexture(textureConcreteWall_H);

	textureConcreteTower.loadFromFile("Tiles/ConcreteTower.png");
	spriteConcreteTower.setTexture(textureConcreteTower);

	textureConcretePath.loadFromFile("Tiles/ConcretePath.png");
	spriteConcretePath.setTexture(textureConcretePath);

	textureConcretePath_H.loadFromFile("Tiles/ConcretePath(H).png");
	spriteConcretePath_H.setTexture(textureConcretePath_H);

	textureConcretePath_I.loadFromFile("Tiles/ConcretePath(I).png");
	spriteConcretePath_I.setTexture(textureConcretePath_I);

	textureConcreteTile.loadFromFile("Tiles/ConcreteTile.png");
	spriteConcreteTile.setTexture(textureConcreteTile);

	textureLightWater.loadFromFile("Tiles/LightWater.png");
	spriteLightWater.setTexture(textureLightWater);


	for (int i = 0; i < 9; i++)
	{
		
	}
}

//setting each tile position to a tile type
void setTileType(int colour, int row, int column)
{
	spriteTile[row][column] = tileType[colour];
}

//displaying the tiles in an 16x16 grid
void setTileStyle()
{
	for (row = 0; row < tileWidth; row++)
	{
		for (column = 0; column < tileHeight; column++)
		{
			TileStyle[row][column] = rand() % 4;
		}
	}
}

//loading the data from a text file saved in the project folder
void LoadData()
{
	tileWidth = 16;
	tileHeight = 16;

	//loading from a .txt folder
	std::ifstream myData("userData/data.txt");

	char s;

	if (myData.is_open())
	{
		count = 0;
		tRow = 0;
		tCol = 0;

		while (myData.get(s))
		{
			fileData[count] = s - '0';

			tRow = count % tileWidth;
			tCol = count / tileHeight;

			TileStyle[tRow][tCol] = fileData[count];
			count++;
		}
	}

	else
	{

	}

	//closing the file once there is no more data to load
	myData.close();

}

//saving the tile data to a text file saved inside the project folder
void SaveData()
{
	//saving as a .txt name 'data'
	std::ofstream myfile;
	myfile.open("userData/data.txt");

	count = 0;

	for (row = 0; row < tileWidth; row++)
	{
		for (column = 0; column < tileHeight; column++)
		{
			fileData[count] = TileStyle[column][row];
			myfile << fileData[count];
			count++;
		}
	}

	//closing the file once there is no more data to save
	myfile.close();
}

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

bool Intersect(const sf::RectangleShape& rec1, const sf::RectangleShape& rec2)
{
	if (rec2.getPosition().y < rec1.getPosition().y + rec1.getSize().y && rec2.getPosition().y + rec2.getSize().y > rec1.getPosition().y && rec2.getPosition().x + rec2.getSize().x > rec1.getPosition().x && rec2.getPosition().x < rec1.getPosition().x + rec1.getSize().x)
		return true;

	return false;
}
