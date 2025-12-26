#pragma once
#include<stdio.h>
#include<string.h>
#include <conio.h>
#include <windows.h>
#include "Snake.h"
#define max_users 200
#define max_len 200
#define Red "\x1b[38;2;255;0;0m"
#define Green "\033[0;32m"
#define RESET "\x1b[0m"
#define Purple "\x1b[38;2;170;0;255m"
#define Pink   "\x1b[38;2;255;105;180m"
#define Blue   "\033[0;34m"
#define Yellow "\033[0;33m"
#define up    72
#define down  80
#define left  75
#define right 77
#define map_width 60  
#define map_height 20
#define mokhtasat_x_map 30 
#define mokhtasat_y_map 5
int snakeX = 20;
int snakeY = 15;
enum map_variables {
	empty = 0,
	wall = 1,
	apple = 2,
	super_apple = 3,
	annona_squamosa = 4,
	quince = 5
};
char usernames[max_users][max_len], passwords[max_users][max_len];
int user_best_scores_map1[max_users] = { 0 }, user_best_scores_map2[max_users] = { 0 };
int best_score_among_all_users_map1 = 0, best_score_among_all_users_map2 = 0;
int current_user_best_score_map1 = 0, current_user_best_score_map2 = 0;
int user_count = 0, score = 0;
int logged_in_user_index = -1;
void login();
void menu();
void map_selection_menu();
void sub_menu_map(int selected_map);
void print_boxed_center(int y, char* text, char* color);
void print_snake();

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void print_center(int y, char* text, char* color) {
	int len = strlen(text);
	int x = (120 - len) / 2; 
	gotoxy(x, y);
	printf("%s%s" RESET, color, text);
}
void menu() {
	int choice;
	while (1) {
		printf("");
	}
}
void login() {
	char username[200], password[200], confirm[200];
	int found = -1;
	system("cls");
	print_center(8, "--- WELCOME TO SNAKES WORLD LOGIN ---", Green);
	print_center(10, "Please enter your username:", RESET);
	gotoxy(55, 11);
	scanf("%99s", username);
	for (int i = 0; i < user_count; i++) {
		if (strcmp(usernames[i], username) == 0) {
			found = i;
			break;
		}
	}
	if (found != -1) {
		int y = 16;
		print_center(14, "you've already signed up. Now please enter your password:", RESET);
		gotoxy(55, 15);
		scanf("%99s", password);
		if (strcmp(passwords[found], password) == 0) {
			print_center(16, "Login successful!", Green);
			logged_in_user_index = found;
		}
		else {
			while (strcmp(passwords[found], password) != 0) {
				print_center(y, "Wrong password :( Try again\n", Red);
				y++;
				gotoxy(55, y);
				scanf("%99s", password);
				y++;
			}
			print_center(y, "Login successful!", Green);
			logged_in_user_index = found;
		}
	}
	else {
		print_center(14, "username not found! You should sign up.", Red);
		print_center(15, "Enter a password:", RESET);
		gotoxy(55, 16);
		scanf("%99s", password);
		print_center(17, "Confirm password:", RESET);
		gotoxy(55, 18);
		scanf("%99s", confirm);
		int y = 19;
		while (strcmp(password, confirm) != 0) {
			print_center(y, "Passwords you entered are not the same :( Try again.", Red);
			y++;
			gotoxy(55, y);
			scanf("%99s", confirm);
			y++;
		}
		strcpy(usernames[user_count], username);
		strcpy(passwords[user_count], password);
		user_count++;
		print_center(y, "Sign up successful!", Green);
		logged_in_user_index = user_count - 1;
	}
	Sleep(500);
}

void print_snake() {
	print_center(4, "  (0) (0)      _ _ _ _ _ _ ", Green);
	print_center(5, "   \\_ _ _/    /  _ _ _ _ _  \\", Green);
	print_center(6, "         \\_ _/            \\_/", Green);
}

void map_selection_menu() {
	int choice;
	while (1) {
		system("cls");
		print_snake();
		print_boxed_center(10, "SELECT YOUR MAP", Purple);

		print_center(15, "1. Map Number One", Pink);
		print_center(17, "2. Map Number Two", Pink);
		print_center(19, "3. Logout", Pink);

		print_center(24, "Choice: ", Blue);
		gotoxy(64, 24);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			sub_menu_map(1);
			break;
		case 2:
			sub_menu_map(2);
			break;
		case 3:
			return;
		default:
			print_center(20, "Invalid choice! Please enter 1, 2 or 3.", Red);
			Sleep(500);
		}
	}
}

void sub_menu_map(int selected_map) {
	int choice;
	char title[30];
	sprintf(title, "MAP %d OPTIONS", selected_map);
	while (1) {
		system("cls");
		print_boxed_center(6, title, Purple);

		print_center(11, "1. Start Game", Pink);
		print_center(13, "2. High Scores", Pink);
		print_center(15, "3. Back", Pink);

		print_center(20, "Choice: ", Blue);
		gotoxy(64, 20);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			run_snake_game(selected_map);
			break;
		case 2:
			system("cls");
			print_boxed_center(5, "High Scores", Purple);
			char describing_bestscore[200];

			if (selected_map == 1) {
				sprintf(describing_bestscore, "The best score among all users: %d", best_score_among_all_users_map1);
				print_center(11, describing_bestscore, Yellow);

				sprintf(describing_bestscore, "Your best score: %d", user_best_scores_map1[logged_in_user_index]);
				print_center(13, describing_bestscore, Yellow);
			}
			else {
				sprintf(describing_bestscore, "The best score among all users: %d", best_score_among_all_users_map2);
				print_center(11, describing_bestscore, Yellow);

				sprintf(describing_bestscore, "Your best score: %d", user_best_scores_map2[logged_in_user_index]);
				print_center(13, describing_bestscore, Yellow);
			}

			print_center(18, "Press enter to return...", RESET);
			getch();
			break;
		case 3:
			return;
		default:
			print_center(20, "Invalid choice! Please enter 1, 2 or 3.", Red);
			Sleep(500);
		}
	}
}

void print_boxed_center(int y, char* text, char* color) {
	int len = strlen(text);
	int x = (120 - (len + 4)) / 2; 

	gotoxy(x, y);
	printf("%s%c", color, 201); 
	for (int i = 0; i < len + 2; i++) printf("%c", 205); 
	printf("%c" RESET, 187); 

	gotoxy(x, y + 1);
	printf("%s%c " RESET "%s" "%s %c", color, 186, text, color, 186); 

	gotoxy(x, y + 2);
	printf("%s%c", color, 200); 
	for (int i = 0; i < len + 2; i++) printf("%c", 205); 
	printf("%c" RESET, 188); 
}

