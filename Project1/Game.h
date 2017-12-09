#pragma once
#include "stdafx.h" 
#include <SFML/Graphics.hpp>
#include <vector>
//making code easier to type with "using namespace"
using namespace sf;

//setting my functions inside the header file
void InitGame();
void setTileType(int, int, int);
void setTileStyle();
void SaveData();
void LoadData();

//setting all my variables that will be used inside 
//my Timber.cpp
int hRes;
int vRes;

int tileWidth;
int tileHeight;
int tileSize;

int row;
int column;

int count = 0;
int tRow = 0;
int tCol = 0;

int indX;
int indY;

int tileIndex;

int tileTypeNumber;

Texture textureButton;
Sprite spriteButton;

Sprite tileType[9];

struct sprites
{
	Sprite allSprites[9];
	float spriteID;
};

Texture textureTile[9];
Sprite spriteTile[16][16];

int TileStyle[16][16];
int fileData[256];


Texture redGemTexture;
Sprite redGemSprite;

Texture heroTexture;
Sprite heroSprite;

Texture textureSaveButton;
Sprite spriteSaveButton;

Texture texturePlayButton;
Sprite spritePlayButton;

Texture textureLoadButton;
Sprite spriteLoadButton;

Texture textureLightGrass;
Sprite spriteLightGrass;

Texture textureConcreteWall;
Sprite spriteConcreteWall;

Texture textureConcreteWall_H;
Sprite spriteConcreteWall_H;

Texture textureConcreteTower;
Sprite spriteConcreteTower;

Texture textureConcretePath;
Sprite spriteConcretePath;

Texture textureConcretePath_H;
Sprite spriteConcretePath_H;

Texture textureConcretePath_I;
Sprite spriteConcretePath_I;

Texture textureConcreteTile;
Sprite spriteConcreteTile;

Texture textureLightWater;
Sprite spriteLightWater;