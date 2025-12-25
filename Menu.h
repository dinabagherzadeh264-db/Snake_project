#pragma once
#include<stdio.h>
#include<string.h>
#include <conio.h>
#include <windows.h>
#define max_users 100
#define max_len 100
#define Red "\x1b[38;2;255;0;0m"
#define Green "\x1b[38;2;0;255;0m"
#define RESET "\x1b[0m"
#define Purple "\x1b[38;2;170;0;255m"
#define Pink   "\x1b[38;2;255;105;180m"
#define Cyan   "\x1b[38;2;0;255;255m"
#define Yellow "\033[0;33m"
char usernames[max_users][max_len], passwords[max_users][max_len];
int best_score_among_all_users = 0;
int current_user_best_score = 0;
int user_count = 0;
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
	char username[100], password[100], confirm[100];
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
	}
	Sleep(700);
}
void print_snake() {
	print_center(1, "  (0) (0)      _ _ _ _ _ _ ", Green);
	print_center(2, "   \\_ _ _/    /  _ _ _ _ _  \\", Green);
	print_center(3, "         \\_ _/            \\_/", Green);
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

		print_center(20, "Choice: ", Cyan);
		gotoxy(64, 20);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			system("cls");
			print_center(10, "LOADING GAME ========:> ", Green);
			print_center(15, "Press enter to start ", RESET);
			getch();
			break;
		case 2:
			system("cls");
			print_boxed_center(5, "High Scores", Purple);
			char describing_bestscore[30];

			sprintf(describing_bestscore, "The best score among all users: %d", best_score_among_all_users);
			print_center(11, describing_bestscore, Yellow);

			sprintf(describing_bestscore, "Your best score: %d", current_user_best_score);
			print_center(13, describing_bestscore, Yellow);

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
void map_selection_menu() {
	int choice;
	while (1) {
		system("cls");
		print_snake();
		print_boxed_center(6, "SELECT YOUR MAP", Purple);

		print_center(11, "1. Map Number One", Pink);
		print_center(13, "2. Map Number Two", Pink);
		print_center(15, "3. Logout", Pink);

		print_center(20, "Choice: ", Cyan);
		gotoxy(64, 20);
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

