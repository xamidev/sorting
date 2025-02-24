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
#define ARRAY_MAX			30

void fill_random_array(int numbers[ARRAY_SIZE], int array_max);
void draw_array(int numbers[ARRAY_SIZE], int windowHeight, int current_item);
void bubblesort(int numbers[ARRAY_SIZE], int windowHeight);

int main(int argc, char* argv[])
{
	srand(time(NULL));
	int array_max = ARRAY_MAX; // goes from 1 to this (x coord)
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
	//SetTargetFPS(2);

	int pass = 0;
    int index = 0;

	while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        draw_array(numbers, windowHeight, index);
        DrawText("bubble sort", 0, 0, 15, BLUE);

        if (IsKeyPressed(KEY_N))
        {
            fill_random_array(numbers, array_max);
            pass = 0;
            index = 0;
        }

        if (pass < ARRAY_SIZE - 1) {
            if (index < ARRAY_SIZE - 1 - pass) {
                if (numbers[index + 1] < numbers[index]) {
                    int temp = numbers[index + 1];
                    numbers[index + 1] = numbers[index];
                    numbers[index] = temp;
                }
                index++;
            } else {
                index = 0;
                pass++;
            }
        }

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
		numbers[i] = rand() % array_max + 1;
	}
}



/*
bubble sort basically:

- go through integer array
- if int[i+1] < int[i] : swap int[i] and int[i+1]
*/

void draw_array(int numbers[ARRAY_SIZE], int windowHeight, int current_item)
{
	for (size_t i=0; i<ARRAY_SIZE; i++)
	{
		int rectHeight = numbers[i] * SQUARE_SIZE_PIXELS;
		int posX = i*SQUARE_SIZE_PIXELS;
		int posY = windowHeight-rectHeight;
		
		if (i == current_item)
		{
			DrawRectangle(posX, posY, SQUARE_SIZE_PIXELS, rectHeight, RED);
		} else {
			DrawRectangle(posX, posY, SQUARE_SIZE_PIXELS, rectHeight, WHITE);
		}
	}
}