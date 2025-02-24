/*
sorting
*/

#include "raylib.h"
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARRAY_SIZE 			64
#define SQUARE_SIZE_PIXELS 	10

void fill_random_array(int numbers[ARRAY_SIZE], int array_max);
void draw_array(int numbers[ARRAY_SIZE], int windowHeight);

int main(int argc, char* argv[])
{
	srand(time(NULL));
	int array_max = 30; // goes from 0 to this (x coord)
	int numbers[ARRAY_SIZE];
	fill_random_array(numbers, array_max);

	int windowHeight = array_max*SQUARE_SIZE_PIXELS;
	
	/* debug */
	for (size_t i=0; i<ARRAY_SIZE; i++)
	{
		printf("%d ", numbers[i]);
	}

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(ARRAY_SIZE*SQUARE_SIZE_PIXELS, windowHeight, "sorting");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		draw_array(numbers, windowHeight);
		DrawText("bubble sort", 0,0,15,BLUE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

/* 
basically:

- generate an array of integers between 0 and MAX (where each integer appears only once?)
- draw unsorted array to screen
- sort the array
- for each sort action draw something to screen and emit noise w/ frequency based on integer value
*/

void fill_random_array(int numbers[ARRAY_SIZE], int array_max)
{
	for (size_t i=0; i<ARRAY_SIZE; i++)
	{
		numbers[i] = rand() % (array_max + 1);
	}
}

void draw_array(int numbers[ARRAY_SIZE], int windowHeight)
{
	for (size_t i=0; i<ARRAY_SIZE; i++)
	{
		int rectHeight = numbers[i] * SQUARE_SIZE_PIXELS;
		int posX = i*SQUARE_SIZE_PIXELS;
		int posY = windowHeight-rectHeight;
		DrawRectangle(posX, posY, SQUARE_SIZE_PIXELS, rectHeight, WHITE);
	}
}