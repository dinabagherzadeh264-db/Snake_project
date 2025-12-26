#pragma warning (disable : 4996)
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Menu.h"
#include "Snake.h"
int map[20][60];
int snakeLen = 2, snakeHead = 12;
int annona_squamosa_active = 0;
clock_t annona_timer;
int quince_effect_active = 0;
clock_t quince_timer;
int gameSpeed = 100;
unsigned char headChar = 16;

int main()
{
	while (1) {
		current_user_best_score_map1 = 0;
		current_user_best_score_map2 = 0;
		login();
		map_selection_menu();
		system("cls");
	}
	return 0;
}

void set_cursor_visibility(bool visible) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(consoleHandle, &info); 
	info.bVisible = visible; 
	SetConsoleCursorInfo(consoleHandle, &info); 
}

void map_design(int selected_map) {
    for (int i = 0; i < map_height; i++)
		for (int j = 0; j < map_width; j++) {
			gotoxy(j + mokhtasat_x_map, i + mokhtasat_y_map);
			if (i == 0 || i == map_height - 1 || j == 0 || j == map_width - 1) {
				printf("%c", 219);
				map[i][j] = wall;
			}
			else if (selected_map == 2 && ( ((j >= map_width / 2 - 1 && j <= map_width / 2 + 1) && (i < 7 || i > 12)) || 
				((i == map_height / 2) && (j < 20 || j > 40)))) {
				printf("%c", 219);
				map[i][j] = wall;
			}
			else {
				printf(" ");
				map[i][j] = empty;
			}
        }
}
void run_snake_game(int selected_map) {
	snakeX = map_width / 2;
	snakeY = map_height / 2;

	for (int i = 0; i < map_height; i++)
		for (int j = 0; j < map_width; j++)
			map[i][j] = empty;

	score = 0;
	snakeLen = 2;
	gameSpeed = 100;
	int direction = right;

	system("cls");
	print_center(10, "LOADING GAME ========:> ", Green);
	print_center(15, "Press enter to start ", RESET);
	getch();
	system("cls");

	map_design(selected_map);

	map[snakeY][snakeX] = snakeHead;
	map[snakeY][snakeX - 1] = snakeHead - 1;


	srand(time(NULL));
	spawn_item(apple);
	set_cursor_visibility(false);

	while (1) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 224) {
				key = _getch();
				if (key == up && direction != down) {
					direction = up;
					headChar = 30;
				}
				else if (key == down && direction != up) {
					direction = down;
					headChar = 31;
				}
				else if (key == left && direction != right) {
					direction = left;
					headChar = 17;
				}
				else if (key == right && direction != left) {
					direction = right;
					headChar = 16;
				}
			}
		}
		int nextX = snakeX;
		int nextY = snakeY;
		if (direction == up)
			nextY--;
		else if (direction == down)
			nextY++;
		else if (direction == left)
			nextX--;
		else if (direction == right)
			nextX++;

		if (map[nextY][nextX] == apple) {
			score += 1;
			snakeLen++;
			Beep(700, 50);
			spawn_next();
		}
		else if (map[nextY][nextX] == super_apple) {
			score += 3;
			Beep(1000, 80);
			spawn_next();
		}
		else if (map[nextY][nextX] == annona_squamosa) {
			score += 5;
			snakeLen++;
			annona_squamosa_active = 0;
			Beep(1200, 100);
			spawn_next();
		}
		else if (map[nextY][nextX] == quince) {
			if (gameSpeed > 20) 
				gameSpeed -= 20;

			quince_timer = clock();
			quince_effect_active = 1;
			Beep(1500, 150);
			spawn_next();
		}
		else if (map[nextY][nextX] == wall || map[nextY][nextX] >= 10) {
			system("cls");
			printf(Red "GAME OVER! Score: %d" RESET, score);
			if (selected_map == 1) {
				if (score > user_best_scores_map1[logged_in_user_index]) {
					user_best_scores_map1[logged_in_user_index] = score;
					current_user_best_score_map1 = score;
				}
				if (score > best_score_among_all_users_map1) 
					best_score_among_all_users_map1 = score;
			}
			else if (selected_map == 2) {
				if (score > user_best_scores_map2[logged_in_user_index]) {
					user_best_scores_map2[logged_in_user_index] = score;
					current_user_best_score_map2 = score;
				}
				if (score > best_score_among_all_users_map2)
					best_score_among_all_users_map2 = score;
			}
			_getch();
			return;
		}
		snakeHead++;
		map[nextY][nextX] = snakeHead;
		snakeX = nextX;
		snakeY = nextY;

		gotoxy(mokhtasat_x_map, mokhtasat_y_map - 2);
		printf(Yellow "SCORE: %d    " RESET, score);

		gotoxy(mokhtasat_x_map + 20, mokhtasat_y_map - 2);
		if (selected_map == 1)
			printf(Green "HIGH SCORE: %d" RESET, current_user_best_score_map1);
		if (selected_map == 2)
			printf(Green "HIGH SCORE: %d" RESET, current_user_best_score_map2);

		for (int i = 0; i < map_height; i++) {
			for (int j = 0; j < map_width; j++) {

				if (map[i][j] >= 10) {
					if (map[i][j] <= snakeHead - snakeLen) {
						map[i][j] = empty;
						gotoxy(j + mokhtasat_x_map, i + mokhtasat_y_map);
						printf(" ");
					}
					else {
						gotoxy(j + mokhtasat_x_map, i + mokhtasat_y_map);
						if (map[i][j] == snakeHead)
							printf(Purple "%c" RESET, headChar);
						else
							printf(Purple "%c" RESET, 219);
					}
				}
				else if (map[i][j] != empty) {
					gotoxy(j + mokhtasat_x_map, i + mokhtasat_y_map);
					if (map[i][j] == apple)
						printf(Red "*");
					else if (map[i][j] == super_apple)
						printf(Pink "%c" RESET, 254);
					else if (map[i][j] == annona_squamosa)
						printf(Green "%c" RESET, 254);
					else if (map[i][j] == quince)
						printf(Yellow "%c" RESET, 254);
				}
			}
		}
		if (annona_squamosa_active && (clock() - annona_timer) > 5000) {
			for (int i = 0; i < map_height; i++) {
				for (int j = 0; j < map_width; j++) {
					if (map[i][j] == annona_squamosa) {
						map[i][j] = empty;
						gotoxy(j + mokhtasat_x_map, i + mokhtasat_y_map);
						printf(" ");
					}
				}
			}
			annona_squamosa_active = 0;
			spawn_item(apple);
		}
		Sleep(gameSpeed);
		gotoxy(mokhtasat_x_map, mokhtasat_y_map - 2);
		printf(Green "SCORE: %d    " RESET, score);
	}
}

void spawn_item(int type) {
	int item_x, item_y;
	do {
		item_x = (rand() % 58) + 1;
		item_y = (rand() % 18) + 1;
	} while (map[item_y][item_x] != empty);

	map[item_y][item_x] = type;
	if (type == annona_squamosa) {
		annona_timer = clock();  
		annona_squamosa_active = 1;  
	}
}

void spawn_next() {
	int chance = rand() % 100;

	if (chance < 70) {
		spawn_item(apple);
	}
	else if (chance < 80) {
		spawn_item(super_apple);
	}
	else if (chance < 90) {
		spawn_item(annona_squamosa);
	}
	else {
		spawn_item(quince); 
	}
}

