#include <SDL.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "func.h"
#include "common_parameters.h"


SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Surface* winSurface = NULL;


int main(int argc, char* argv[])
{
	bool isRunning = 1;
	SDL_Event ev;
	mainWindow window = {WINDOW_WIDTH, WINDOW_HEIGHT, 1, 1};

	Init(&win, &ren, &winSurface);

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
				SDL_RenderFillRect(ren, &rect);
			}

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		for (int i = 0; i < BLOCK_HEIGHT_COUNT; i += 1)
			for (int j = 0; j < BLOCK_WIDTH_COUNT; j += 1)
			{
				SDL_Rect rect = { j*BLOCK_SIZE + blockScaleX, i*BLOCK_SIZE + blockScaleY, BLOCK_SIZE, BLOCK_SIZE };
				SDL_RenderDrawRect(ren, &rect);
			}



		SDL_RenderPresent(ren);
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);

		FPSControl();
	}

	DeInit(0, &win, &ren, &winSurface);

	return 0;
}