#pragma warning (disable : 4996)
#include<stdio.h>
#include<conio.h>
#include <time.h>
#include "Menu.h"
enum map_variables {
    empty = 0,
    wall = 1,
    apple = 2,      
    super_apple = 3, 
    annona_squamosa = 4,  
    quince = 5    
};
int main() {
	// while (1) {
		login();
		map_selection_menu();
	
	return 0;
}