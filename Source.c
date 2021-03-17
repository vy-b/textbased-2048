#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
const int m = 4;
const int n = 4;

// in order to not populate whenever no collapse is done, you need to write the logic in a way that makes sure
//the function does not run if the map is not collapsible.
void collapse_left(int tiles[4][4], int* collapsed) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (tiles[i][j] == 0) {
				int k = j;
				while (tiles[i][k] == 0 && k < 3) {
					k++;
				}
				tiles[i][j] = tiles[i][k];
				tiles[i][k] = 0;
			}
		}
}
void combine_left(int tiles[4][4]) {
	int combined = 0;
	for (int i = 0; i < 4; i++) {
		combined = 0;
		for (int j = 0; j < 4; j++) {
			//if tiles need to combine
			if (tiles[i][j] == tiles[i][j + 1] && j + 1 < 4) {
				//double the combined tile
				tiles[i][j] *= 2;
				combined = 1;
				//4ove all the tiles left
				int k = j + 1;
				while (k != 3) {
					tiles[i][k] = tiles[i][k + 1];
					++k;
				}
			}
			if (combined == 1) tiles[i][3] = 0;
		}

	}
}
void collapse_right(int tiles[4][4]) {
	for (int i = 0; i < 4; i++)
		for (int j = 3; j >= 0; j--) {
			if (tiles[i][j] == 0) {
				int k = j;
				while (tiles[i][k] == 0 && k > 0) {
					k--;
				}
				tiles[i][j] = tiles[i][k];
				tiles[i][k] = 0;
			}
		}
}
void combine_right(int tiles[4][4]) {
	int combined = 0;
	for (int i = 0; i < 4; i++) {
		combined = 0;
		for (int j = 3; j >= 0; j--) {
			//if tiles need to combine
			if (tiles[i][j] == tiles[i][j - 1] && j - 1 >= 0) {
				//double the combined tile
				tiles[i][j] *= 2;
				combined = 1;
				//move all the tiles left
				int k = j - 1;
				while (k != 0) {
					tiles[i][k] = tiles[i][k - 1];
					--k;
				}
			}
			if (combined == 1) tiles[i][0] = 0;
		}

	}
}
void collapse_down(int tiles[4][4]) {
	for (int i = 0; i < 4; i++)
		for (int j = 3; j >= 0; j--) {
			if (tiles[j][i] == 0) {
				int k = j;
				while (tiles[k][i] == 0 && k > 0) {
					k--;
				}
				tiles[j][i] = tiles[k][i];
				tiles[k][i] = 0;

			}
		}
}
void combine_down(int tiles[4][4]) {
	int combined = 0;
	for (int i = 0; i < 4; i++) {
		combined = 0;
		for (int j = 3; j >= 0; j--) {
			//if tiles need to combine
			if (tiles[j][i] == tiles[j - 1][i] && j - 1 >= 0) {
				//double the combined tile
				tiles[j][i] *= 2;
				combined = 1;
				//move all the tiles down
				int k = j - 1;
				while (k != 0) {
					tiles[k][i] = tiles[k - 1][i];
					--k;
				}
			}
			if (combined == 1) tiles[0][i] = 0;
		}

	}
}

void collapse_up(int tiles[4][4]) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (tiles[j][i] == 0) {
				int k = j;
				while (tiles[k][i] == 0 && k < 3) {
					k++;
				}
				tiles[j][i] = tiles[k][i];
				tiles[k][i] = 0;
			}
		}
}

void combine_up(int tiles[4][4]) {
	int combined = 0;
	for (int i = 0; i < 4; i++) {
		combined = 0;
		for (int j = 0; j < 4; j++) {
			//if tiles need to combine
			if (tiles[j][i] == tiles[j + 1][i] && j + 1 < 4) {
				//double the combined tile
				tiles[j][i] *= 2;
				combined = 1;
				//move all the tiles up
				int k = j + 1;
				while (k != 4) {
					tiles[k][i] = tiles[k + 1][i];
					++k;
				}
			}
			if (combined == 1) tiles[3][i] = 0;
		}

	}
}

void random_populate(int tiles[4][4]) {
	int full = 1;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (tiles[i][j] == 0)
				full = 0;
		}

	if (full == 0) {
		int i, j;
		i = rand() % 4;
		j = rand() % 4;
		while (tiles[i][j] != 0) {
			i = rand() % 4;
			j = rand() % 4;
		}
		tiles[i][j] = 2;
	}
	else { printf("map is full!\n"); }
}

void printMap(int tiles[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			int n = tiles[i][j];
			if (n < 10)
				printf("%d    ", tiles[i][j]);
			else if (n < 100)
				printf("%d   ", tiles[i][j]);
			else if (n < 1000)
				printf("%d  ", tiles[i][j]);
			else
				printf("%d ", tiles[i][j]);
		}
		printf("\n");
	}
}

// main
int main() {
	enum direction { left = 97, up = 119, right = 100, down = 115 };

	int tiles[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tiles[i][j] = 0;

	srand((unsigned)time(0));
	random_populate(tiles);
	random_populate(tiles);

	printf("use w,a,s,d to move and e to exit\n");
	printf("*********START***********\n");

	char key = 0;
	int collapsed = 0;
	while (key != 'e') {
		printMap(tiles);
		printf("\n");
		key= _getch();
		collapsed = 0;
		if (key == left) {
			collapse_left(tiles,&collapsed);
			combine_left(tiles);
		}

		if (key == right) {
			collapse_right(tiles);
			combine_right(tiles);
		}
		if (key == down) {
			collapse_down(tiles);
			combine_down(tiles);
		}
		if (key == up) {
			collapse_up(tiles);
			combine_up(tiles);
		}
		random_populate(tiles);
	}



}
