#pragma once

#define FPS 60
#define EPS 60
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define BLOCK_SIZE 40
#define BLOCK_WIDTH_COUNT 10
#define BLOCK_HEIGHT_COUNT 10
#define BLOCK_TEXTURE_COMMON 0 
#define BLOCK_TEXTURE_ONE 0 
#define BLOCK_TEXTURE_TWO 0 
#define BLOCK_TEXTURE_FREE 0 
#define BLOCK_TEXTURE_BOMB 13 
#define BLOCK_TEXTURE_FLAG 10 

struct mainWindow
{
	int w, h;
	float scaleX, scaleY;
};

struct mainGameField
{
	int type;
	SDL_Rect hitbox;
};

struct mainRenderer
{
	SDL_Texture* texture;
	SDL_Rect textureSize;
	SDL_Rect frame;
	int frameTime;
};

struct mainMouseClick
{
	int x, y;
};
