#include <SDL.h>
#include<stdio.h>
#include<string.h>
#include "useSDL.h"
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

//The blocks of colors
SDL_Surface* blocks[8];

//The window to rendering
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;
void init()
{
	//Create window
	gWindow = SDL_CreateWindow("Drawing Maps", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
	//Get window surface
	gScreenSurface = SDL_GetWindowSurface(gWindow);	
}

void loadMedia()
{
	//Load images
	gHelloWorld = SDL_LoadBMP("images/border.bmp");
	
	blocks[0] = SDL_LoadBMP("images/blocks/blue.bmp");
	blocks[1] = SDL_LoadBMP("images/blocks/red.bmp");
	blocks[2] = SDL_LoadBMP("images/blocks/green.bmp");
	blocks[3]  = SDL_LoadBMP("images/blocks/yellow.bmp");
	blocks[4] = SDL_LoadBMP("images/blocks/rainbow.bmp");
	blocks[5] = SDL_LoadBMP("images/blocks/purple.bmp");
	blocks[6] = SDL_LoadBMP("images/blocks/orange.bmp");
	blocks[7] = SDL_LoadBMP("images/blocks/white.bmp");

	//Set cords of blocks to choose
	SDL_Rect cords[7];
	for (int i = 0; i < 7; i++)
	{
		cords[i].x = 990;
		cords[i].y = 40 + 70 * i;
		cords[i].w = 64;
		cords[i].h = 32;
	}

	//Visaul blocks to choose
	SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
	SDL_BlitSurface(blocks[0], NULL, gScreenSurface, & cords [0]);
	SDL_BlitSurface(blocks[1], NULL, gScreenSurface, &cords[1]);
	SDL_BlitSurface(blocks[2], NULL, gScreenSurface, &cords[2]);
	SDL_BlitSurface(blocks[3], NULL, gScreenSurface, &cords[3]);
	SDL_BlitSurface(blocks[4], NULL, gScreenSurface, &cords[4]);
	SDL_BlitSurface(blocks[5], NULL, gScreenSurface, &cords[5]);
	SDL_BlitSurface(blocks[6], NULL, gScreenSurface, &cords[6]);
	SDL_UpdateWindowSurface(gWindow);
}

void mainLoop(int mapImport[15][10], char nameFile[100])
{
	int quit = 0;
	int mouseX = 0, mouseY = 0;
	int actualcolor = 0;


	SDL_Event e;
	SDL_Rect actuallycords;
	SDL_Rect mapcords;
	mapcords.w = 64;
	mapcords.h = 32;
	actuallycords.x = 990; actuallycords.y = 670; actuallycords.w = 64; actuallycords.h = 32;
	SDL_BlitSurface(blocks[actualcolor], NULL, gScreenSurface, &actuallycords);
	SDL_UpdateWindowSurface(gWindow);

	int clicked = 0;

	while (!quit) //Main loop
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) //Click X to escape
				quit = 1;
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE) //Click Escape escape
					quit = 1;
			}
			if (e.type == SDL_MOUSEMOTION) //Follow actual position of mouse
			{
				mouseX = e.motion.x;
				mouseY = e.motion.y;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
				clicked = 1;
			if (e.type == SDL_MOUSEBUTTONUP)
				clicked = 0;
			if (clicked)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					for (int i = 0; i < 7; i++) // Drawing actually choosen block on screen
					{
						if (mouseX >= 990 && mouseX <= 1053)
								if (mouseY >= 40 + 70 * i && mouseY <= 40 + 70 * i + 31)
								{
									SDL_BlitSurface(blocks[i], NULL, gScreenSurface, & actuallycords);
									actualcolor = i;
									SDL_UpdateWindowSurface(gWindow);
								}
					}

					for (int i = 0; i < 15; i++) // Drawing choosen blocks on the screen and set table
					{
						for (int j = 0; j < 10; j++)
						{
							if (mouseX >= 5 + 64 * i && mouseX <= 5 + 64 * (i + 1) - 1)
							{
								if (mouseY >= 5 + 32 * j && mouseY <= 5 + 32 * (j + 1) - 1)
								{
									mapcords.x = 5 + 64 * i;
									mapcords.y = 5 + 32 * j;
									SDL_BlitSurface(blocks[actualcolor], NULL, gScreenSurface, &mapcords);
									SDL_UpdateWindowSurface(gWindow);
									mapImport[i][j] = actualcolor + 1;
								}
							}
						}
					}
				}

				if (e.button.button == 4 || e.button.button == 3)
				{
					for (int i = 0; i < 15; i++) // Clearing blocks from the screen and set table
					{
						for (int j = 0; j < 10; j++)
						{
							if (mouseX >= 5 + 64 * i && mouseX <= 5 + 64 * (i + 1) - 1)
							{
								if (mouseY >= 5 + 32 * j && mouseY <= 5 + 32 * (j + 1) - 1)
								{
									mapcords.x = 5 + 64 * i;
									mapcords.y = 5 + 32 * j;
									SDL_BlitSurface(blocks[7], NULL, gScreenSurface, &mapcords);
									SDL_UpdateWindowSurface(gWindow);
									mapImport[i][j] = 0;
								}
							}
						}
					}
				}
			}
		}
		
	}

}

void closing()
{
	//Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}