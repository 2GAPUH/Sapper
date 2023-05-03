#include <SDL.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "func.h"
#include "common_parameters.h"


SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Surface* winSurface = NULL;


int main(int argc, char* argv[])
{
	int seed = 100;
	srand(seed);
	bool isRunning = 1;
	SDL_Event ev;
	mainWindow window = {WINDOW_WIDTH, WINDOW_HEIGHT, 1, 1};
	mainGameField** gameField = NULL;
	mainRenderer tiles;
	mainMouseClick mouseClick = { NULL, NULL };

	gameField = (mainGameField**)malloc(sizeof(*gameField) * BLOCK_HEIGHT_COUNT);
	for (int i = 0; i < BLOCK_HEIGHT_COUNT; i++)
		gameField[i] = (mainGameField*)malloc(sizeof(mainGameField) * BLOCK_WIDTH_COUNT);

	for (int i = 0; i < BLOCK_HEIGHT_COUNT; i++)
		for (int j = 0;j < BLOCK_WIDTH_COUNT; j++)
		{
			gameField[i][j].type = rand() % (13 - 0 + 1) + 0;
		}



	Init(&win, &ren, &winSurface);

#pragma region COBBLESTONE TEXTURE
	SDL_Surface* surface = NULL;
	if ((surface = IMG_Load("tiles.png")) == NULL)
	{
		printf_s("Can't load image 'tiles.png'");
		system("pause");
	}

	tiles.texture = SDL_CreateTextureFromSurface(ren, surface);

	tiles.textureSize.x = NULL;
	tiles.textureSize.y = NULL;
	tiles.textureSize.w = surface->w;
	tiles.textureSize.h = surface->h;

	tiles.frame.w = surface->w;
	tiles.frame.h = surface->h;
	SDL_FreeSurface(surface);
#pragma endregion

	while(isRunning)
	{ 

		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_WINDOWEVENT:
				switch (ev.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					SDL_GetWindowSize(win, &window.w, &window.h);
					SDL_RenderSetScale(ren, window.scaleX = window.w / 1. / WINDOW_WIDTH, window.scaleY = window.h / 1. / WINDOW_HEIGHT);
					window.w /= window.scaleX;
					window.h /= window.scaleY;
				}
				break;



			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					isRunning = false;
					break;
				}
				break;



			case SDL_KEYUP:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_D:
					break;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (ev.button.button == SDL_BUTTON_X2)
				{
				
				}
				break;


			case SDL_MOUSEBUTTONUP:
				if (ev.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&mouseClick.x, &mouseClick.y);
				}
				break;
			}

		}

		int blockScaleX = (WINDOW_WIDTH / 2 - BLOCK_WIDTH_COUNT / 2 * BLOCK_SIZE);
		int blockScaleY = (WINDOW_HEIGHT / 2 - BLOCK_HEIGHT_COUNT / 2 * BLOCK_SIZE);

		SDL_SetRenderDrawColor(ren, 180, 180, 180, 255);
		for (int i = 0; i < BLOCK_HEIGHT_COUNT; i += 1)
			for (int j = 0; j < BLOCK_WIDTH_COUNT; j += 1)
			{
				SDL_Rect rect = { j * BLOCK_SIZE + blockScaleX, i * BLOCK_SIZE + blockScaleY, BLOCK_SIZE, BLOCK_SIZE };
				SDL_Rect currentTexture = { tiles.textureSize.h * gameField[i][j].type, 0, tiles.textureSize.h, tiles.textureSize.h};
				//SDL_RenderFillRect(ren, &rect);
				SDL_RenderCopy(ren, tiles.texture, &currentTexture, &rect);
			}





		SDL_RenderPresent(ren);
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);

		FPSControl();
	}

	for (int i = 0; i < BLOCK_HEIGHT_COUNT; i++)
		free(gameField[i]);
	free(gameField);

	DeInit(0, &win, &ren, &winSurface);

	return 0;
}