#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define DIAGUP 0
#define RIGHT 1
#define DIAGDOWN 2
#define DOWN 3

char grid[20][20];
int allocated_size;

void fill_grid() {
	int i,j;
	for(i = 0; i < allocated_size; i++) {
		for(j = 0; j < allocated_size; j++) {
			if(grid[i][j] == '\0') {
				grid[i][j] = 'a' + (rand() % 26);
			}
		}
	}
}
void print_grid() {
	printf("\n");
	for(int i = 0; i < allocated_size; i++) {
		for(int j = 0; j < allocated_size; j++) {
			printf("%3c", grid[i][j]);
		}
		printf("\n");
	}
}

bool find_angle_for(char *wrd, int row, int col) {
	char word[strlen(wrd)];
	strcpy(word, wrd);
	bool first = 1;
	bool clear = 1;
	int start_angle = rand() % 4;
	int angle = start_angle;
	while(1) {
		if(first == 1) {
			first = 0;
		}
		else {
			if(angle == start_angle) {
				break;
			}
		}
		switch(angle) {
			case RIGHT:
				if(allocated_size - col >= sizeof(word)) {
					for(int i = 0; i < sizeof(word); i++) {
						if (grid[row][col + i] != '\0' && grid[row][col + i] != word[i])
						{
							clear = 0;
							break;
						}
					}
					if(clear) {
						for(int i = 0; i < sizeof(word); i++) {
							grid[row][col + i] = word[i];
						}
						return 1;
					}
				}
				break;
			case DOWN:
				if (allocated_size - row >= sizeof(word))
				{
					for (int i = 0; i < sizeof(word); i++)
					{
						if (grid[row + i][col] != '\0' && grid[row + i][col] != word[i])
						{
							clear = 0;
							break;
						}
					}
					if (clear)
					{
						for (int i = 0; i < sizeof(word); i++)
						{
							grid[row + i][col] = word[i];
						}
						return 1;
					}
				}
				break;
			case DIAGUP:
				if(allocated_size - col >= sizeof(word) && (row >= sizeof(word))) {
					for (int i = 0; i < sizeof(word); i++)
					{
						if (grid[row - i][col + i] != '\0' && grid[row - i][col + i] != word[i])
						{
							clear = 0;
							break;
						}
					}
					if (clear)
					{
						for (int i = 0; i < sizeof(word); i++)
						{
							grid[row - i][col + i] = word[i];
						}
						return 1;
					}
				}
				break;
			case DIAGDOWN:
				if (allocated_size - col >= sizeof(word) && (allocated_size - row >= sizeof(word)))
				{
					for (int i = 0; i < sizeof(word); i++)
					{
						if (grid[row + i][col + i] != '\0' && grid[row+i][col+i] != word[i])
						{
							clear = 0;
							break;
						}
					}
					if (clear)
					{
						for (int i = 0; i < sizeof(word); i++)
						{
							grid[row + i][col + i] = word[i];
						}
						return 1;
					}
				}
				break;
		}
		if(angle == 3) {
			angle = 0;
		}
		else {
			angle++;
		}
	}
	return 0;
}

bool fit_into_puzzle(char *word)
{
	bool first = 1;
	int rand_start_col = rand() % allocated_size;
	int rand_start_row = rand() % allocated_size;
	int current_col = rand_start_col;
	int current_row = rand_start_row;
	while(1) {
		if(first == 1) {
			first = 0;
		}
		else {
			if(current_col == rand_start_col && current_row == rand_start_row) {
				break;
			}
		}
		if(grid[current_row][current_col] == '\0') {
			if(find_angle_for(word, current_row, current_col)) {
				return 1;
			}
			else {
				current_col++;
				if (current_col == allocated_size)
				{
					current_row++;
					current_col = 0;
				}
				if (current_row == allocated_size)
				{
					current_row = 0;
				}
			}
		}
		else {
			current_col++;
			if(current_col == allocated_size) {
				current_row++;
				current_col = 0;
			}
			if(current_row == allocated_size) {
				current_row = 0;
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	allocated_size = atoi(argv[1]);
	char dupe_protection[argc - 2][30];
	int wordcount;
	for(wordcount = 2; wordcount < argc; wordcount++) {
		char *word = argv[wordcount];
		for (int i = 0; word[i]; i++)
		{
			word[i] = tolower(word[i]);
		}
		strcpy(dupe_protection[wordcount-2], word);
		for(int i = 0; i < sizeof(dupe_protection); i++) {
			if(i != wordcount-2 && strcmp(word, dupe_protection[i]) == 0) {
				printf("Please try again. The program does not accept duplicate parameters.\n");
				return 1;
			}
		}
		bool fits = fit_into_puzzle(argv[wordcount]);
		if(!fits) {
			printf("The word %s could not be fit within the puzzle. Program terminated.\n", argv[wordcount]);
			return 1;
		} 
	}
	fill_grid();
	print_grid();
	printf("\nWords Hidden:\n");
	for(int i = 2; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	return 0;
}


