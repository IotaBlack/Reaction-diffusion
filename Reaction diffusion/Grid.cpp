#include "Grid.h"
#include <stdlib.h>
#include <iostream>


Grid::Grid(int a, int b, int s)
{
	x = a;
	y = b;
	Cells = (Cell**)malloc(x*s);
	for (int i = 0;i < x;i++)
	{
		Cells[i] = (Cell*)malloc(y*s);
	}
	for (int i = 0;i < x;i++)
	{
		for (int o = 0;o < y;o++)
		{
			Cells[i][o].a = 1;
			Cells[i][o].b = 0.0;
		}
	}
	palette_r = (int*)malloc(256 * s);
	palette_g = (int*)malloc(256 * s);
	palette_b = (int*)malloc(256 * s);
	palette_a = (int*)malloc(256 * s);
	for (int i = 0;i < 256;i++)
	{
		SetPalette(i, 255, 255, 255, 0);
	}
}


Grid::~Grid()
{
	free(Grid::Cells);
	free(Grid::palette_r);
	free(Grid::palette_g);
	free(Grid::palette_b);
	free(Grid::palette_a);
}


void Grid::DrawGrid(SDL_Renderer* renderer, int scale)
{
	for (int i = 0;i < x;i++)
	{
		for (int o = 0;o < x;o++)
		{
			int val = floor(Cells[i][o].b * 255);

			SDL_SetRenderDrawColor(renderer, palette_r[val], palette_g[val], palette_b[val], palette_a[val]);
			for (int ioff = 0;ioff < scale;ioff++) {
				for (int ooff = 0;ooff < scale;ooff++) {
					SDL_RenderDrawPoint(renderer, i*scale + ioff, o*scale + ooff);
				}
			}

		}
	}
}

void Grid::DrawCell(SDL_Renderer* renderer, int x, int y, int scale)
{
	double val2 = Cells[x][y].b;
	int val = floor(Cells[x][y].b * 255+0.1);
	//rectangleRGBA(renderer, x*scale, y*scale, (x+1)*scale,(y+1)*scale , palette_r[val], palette_g[val], palette_b[val], palette_a[val]);
	SDL_SetRenderDrawColor(renderer, palette_r[val], palette_g[val], palette_b[val], palette_a[val]);
	for (int ioff = 0;ioff < scale;ioff++) {
		for (int ooff = 0;ooff < scale;ooff++) {
			SDL_RenderDrawPoint(renderer, x*scale + ioff, y*scale + ooff);
		}
	}
}

void Grid::SetPalette(int c, int r, int g, int b, int a)
{
	palette_r[c] = r;
	palette_g[c] = g;
	palette_b[c] = b;
	palette_a[c] = a;
}
