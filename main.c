#include <stdlib.h>
#include <ncurses.h>

#define C_BORDER '#'
#define H_BORDER '-'
#define V_BORDER '|'
#define PLAYER_CHAR 'X'

int cursorX;
int cursorY;

char *map;
int yPos = 0;
int xPos = 0;
char heldBlock = 1;
char block[11] = {' ', '#', '%', '*', '&', '+', '@', '[', ']', '=', '-'};

void drawMap(){
	int a;
	
	mvaddch(3, 0, C_BORDER);
	mvaddch(3, 33, C_BORDER);
	mvaddch(20, 0, C_BORDER);
	mvaddch(20, 33, C_BORDER);
	
	for(a = 1; a <= 32; a++){
		mvaddch(3, a, H_BORDER);
		mvaddch(20, a, H_BORDER);
	}
	for(a = 4; a <= 19; a++){
		mvaddch(a, 0, V_BORDER);
		mvaddch(a, 33, V_BORDER);
	}
}

void movePlayerUp(){
	if(yPos > 0){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY, cursorX - 1, block[0]);
		mvaddch(cursorY - 1, cursorX - 1, PLAYER_CHAR);
		
		yPos--;
	}
}

void movePlayerDown(){
	if(yPos < 15){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY, cursorX - 1, block[0]);
		mvaddch(cursorY + 1, cursorX - 1, PLAYER_CHAR);
		
		yPos++;
	}
}

void movePlayerLeft(){
	if(xPos > 0){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY, cursorX - 1, block[0]);
		mvaddch(cursorY, cursorX - 2, PLAYER_CHAR);
		
		xPos--;
	}
}

void movePlayerRight(){
	if(xPos < 31){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY, cursorX - 1, block[0]);
		mvaddch(cursorY, cursorX, PLAYER_CHAR);
		
		xPos++;
	}
}

void placeBlockUp(){
	if(yPos > 0){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY - 1, cursorX - 1, block[heldBlock]);
		move(cursorY, cursorX);
	}
}

void placeBlockDown(){
	if(yPos < 15){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY + 1, cursorX - 1, block[heldBlock]);
		move(cursorY, cursorX);
	}
}

void placeBlockLeft(){
	if(xPos > 0){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY, cursorX - 2, block[heldBlock]);
		move(cursorY, cursorX);
	}
}

void placeBlockRight(){
	if(xPos < 31){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY, cursorX, block[heldBlock]);
		move(cursorY, cursorX);
	}
}

int main(){
	map = calloc(512, sizeof(char));

	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);

	mvprintw(0, 0, "miniblocks v0.1.0");
	mvprintw(1, 0, "X %d|Y %d|BLOCK %c", xPos, yPos, block[heldBlock]);

	drawMap();
	mvaddch(yPos + 4, xPos + 1, PLAYER_CHAR);

	while(1){
		switch(getch()){
			case 'w':
			case KEY_UP:
				movePlayerUp();
				break;
			case 'a':
			case KEY_LEFT:
				movePlayerLeft();
				break;
			case 's':
			case KEY_DOWN:
				movePlayerDown();
				break;
			case 'd':
			case KEY_RIGHT:
				movePlayerRight();
				break;
			case 'i':
				placeBlockUp();
				break;
			case 'j':
				placeBlockLeft();
				break;
			case 'k':
				placeBlockDown();
				break;
			case 'l':
				placeBlockRight();
				break;
		}
	}

	endwin();

	free(map);
	return 0;
}