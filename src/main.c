/*
sorting - an array sort visualization program in plain C & Raylib
free software (as in freedom)
*/

#include "raylib.h"
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARRAY_SIZE 			64
#define SQUARE_SIZE_PIXELS 	10
#define ARRAY_MAX			64

void draw_array(int numbers[ARRAY_SIZE], int windowHeight, int current_item);
void fill_consecutive_integer_array(int numbers[ARRAY_SIZE]);
void shuffle_array(int numbers[ARRAY_SIZE]);
void init_array(int numbers[ARRAY_SIZE]);
void bubblesort_step(int numbers[ARRAY_SIZE], int* pass, int* index);
char* get_string_by_sort_type(int sort_type);

enum SortTypes
{
	BUBBLE
};

enum Error
{
	ENOTYP	// error no sort type
};

int main(int argc, char* argv[])
{
	srand(time(NULL));
	int numbers[ARRAY_SIZE];
	int sort_type = BUBBLE;

	int windowHeight = ARRAY_MAX*SQUARE_SIZE_PIXELS;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(ARRAY_SIZE*SQUARE_SIZE_PIXELS, windowHeight, "sorting");

	int pass = 0;
    int index = 0;
	init_array(numbers);

	while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

		char* sort_type_string = get_string_by_sort_type(sort_type);
		if (!sort_type_string)
		{
			return -ENOTYP;
		}

        draw_array(numbers, windowHeight, index);
        DrawText(sort_type_string, 0, 0, 15, BLUE);
		DrawText(TextFormat("Pass: %i", pass+1), 0, 20, 15, pass == ARRAY_MAX ? GREEN : YELLOW); // makes sense only when complexity is O(n) right?

        if (IsKeyPressed(KEY_N))
        {
			init_array(numbers);
            pass = 0;
            index = 0;
        }

		switch(sort_type)
		{
			case BUBBLE:
				bubblesort_step(numbers, &pass, &index);
				break;
			default:
				return -ENOTYP;
		}

        EndDrawing();
    }

	CloseWindow();
	return 0;
}

void init_array(int numbers[ARRAY_SIZE])
{
	fill_consecutive_integer_array(numbers);
	shuffle_array(numbers);
}

/* 
basically:

- generate an array of integers between 0 and MAX (where each integer appears only once?)
- draw unsorted array to screen
- sort the array
- for each sort action draw something to screen and emit noise w/ frequency based on integer value
*/

// next up: multiple sort methods?
void bubblesort_step(int numbers[ARRAY_SIZE], int* pass, int* index)
{
	if (*pass < ARRAY_SIZE - 1) {
		if (*index < ARRAY_SIZE - 1 - *pass) {
			if (numbers[*index + 1] < numbers[*index]) {
				int temp = numbers[*index + 1];
				numbers[*index + 1] = numbers[*index];
				numbers[*index] = temp;
			}
			(*index)++;
		} else {
			*index = 0;
			(*pass)++;
		}
	}
}

char* get_string_by_sort_type(int sort_type)
{
	switch(sort_type)
	{
		case BUBBLE:
			return "bubble sort";
		default:
			return NULL;
	}
}

/*
Enforcing uniqueness:
- Generate an array of consecutive integers from 1 to n
- Shuffle the array using Fisher-Yates shuffle
*/

void fill_consecutive_integer_array(int numbers[ARRAY_SIZE])
{
	for (size_t i=0; i<ARRAY_SIZE; i++)
	{
		numbers[i] = i+1;
	}
}

void shuffle_array(int numbers[ARRAY_SIZE])
{
	for (size_t i=ARRAY_SIZE-1; i>0; i--)
	{
		size_t j = rand() % (i+1);
		int temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;
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