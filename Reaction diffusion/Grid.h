#pragma once
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
struct Cell
{
	double a;
	double b;
};
class Grid
{

public:
	
	Cell** Cells;
	int x;
	int y;
	int* palette_r;
	int* palette_g;
	int* palette_b;
	int* palette_a;
	Grid(int, int, int);
	~Grid();
	void DrawGrid(SDL_Renderer*, int scale);
	void DrawCell(SDL_Renderer*, int i, int o, int scale);
	void SetPalette(int c, int r, int g, int b, int a);
};

