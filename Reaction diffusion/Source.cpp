#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Grid.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int scl = 2;
const int gridsize = 200;
void Reactiondiffusion(Grid *C_G, Grid *N_G, int, int, int, int);
double Lapa(int x,int y,Grid*);
double Lapb(int x,int y,Grid*);
float Da = 1;
float Db = 0.5;
float Feed = 0.055;
float Kill = 0.062;
double sum = 0.1;
int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* renderer = NULL;
	bool QUIT = false;
	bool Draw = true;
	bool gen = false;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		QUIT = true;
	}

	window = SDL_CreateWindow("Game Of Life!", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		QUIT = true;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "renderer error: " << SDL_GetError();
		QUIT = true;
	}
	SDL_Event e;

	//Main loop
	Grid C_grid(gridsize, gridsize, sizeof(Cell));
	Grid N_grid(gridsize, gridsize, sizeof(Cell));
	for (int x = gridsize/2 -5;x < gridsize/2+6;x++) {
		for (int y = gridsize/2-5;y < gridsize/2+6;y++) {
			C_grid.Cells[x][y].b = 0.5;
		}
	}
	for (int i = 0;i < 256;i++)
	{
		C_grid.SetPalette(255 - i, i, i, i, 255);
}




	while (!QUIT)
	{
		// Event check
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				QUIT = true;
			case SDL_KEYDOWN:
				std::cout << e.key.keysym.sym;
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					QUIT = true;
					break;
				case SDLK_g:
					gen = !gen;
					break;
				}

			}
		}
		// End of events
		if (gen) {
			for (int i = 0;i < 10;i++) {
				Reactiondiffusion(&C_grid, &N_grid, 1, 1, C_grid.x - 1, C_grid.y - 1);
			}
		}
		if (true) {
			for (int x = 0;x < C_grid.x;x++) {
				for (int y = 0;y < C_grid.y;y++) {
					C_grid.DrawCell(renderer, x, y, scl);
				}
			}
		}
		SDL_RenderPresent(renderer);


	}
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}

void Reactiondiffusion(Grid *C_G, Grid *N_G, int x1, int y1, int x2, int y2)
{
//	std::cout << "diffuse";
	for (int x = x1;x < gridsize - 1;x++) {
		for (int y = y1;y < gridsize- 1;y++) {
			double a = C_G->Cells[x][y].a;
			double b = C_G->Cells[x][y].b;
			double abb = a*b*b;
			N_G->Cells[x][y].a = a + (Da*Lapa(x, y, C_G)) - abb + (Feed*(1 - a));
			N_G->Cells[x][y].b = b + ((Db*Lapb(x, y, C_G)) + abb - ((Kill + Feed)*b));
		}
	}

	Lapa(4, 5, C_G);
	C_G->Cells = N_G->Cells;
}

double Lapa(int x, int y, Grid *G) {
	sum = 0.0;

	sum = sum + (G->Cells[x][y].a * -1);
	sum = sum + (G->Cells[x+1][y].a * 0.2);
	sum = sum + (G->Cells[x-1][y].a * 0.2);
	sum = sum + (G->Cells[x][y+1].a * 0.2);
	sum = sum + (G->Cells[x][y-1].a * 0.2);
	sum = sum + (G->Cells[x+1][y+1].a * 0.05);
	sum = sum + (G->Cells[x+1][y-1].a * 0.05);
	sum = sum + (G->Cells[x-1][y+1].a * 0.05);
	sum = sum + (G->Cells[x-1][y-1].a * 0.05);
	sum = round(sum * 1000000) / 1000000;
	return sum;
}

double Lapb(int x, int y, Grid *G) {
	double sum = 0;
	sum += G->Cells[x][y].b * -1;
	sum += G->Cells[x + 1][y].b * 0.2;
	sum += G->Cells[x - 1][y].b * 0.2;
	sum += G->Cells[x][y + 1].b * 0.2;
	sum += G->Cells[x][y - 1].b * 0.2;
	sum += G->Cells[x + 1][y + 1].b * 0.05;
	sum += G->Cells[x + 1][y - 1].b * 0.05;
	sum += G->Cells[x - 1][y + 1].b * 0.05;
	sum += G->Cells[x - 1][y - 1].b * 0.05;
	return sum;
}