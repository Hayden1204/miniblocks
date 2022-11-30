/* Copyright 2022 Hayden
 *
 * This file is part of miniblocks.
 *
 * miniblocks is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * miniblocks is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with miniblocks. If not, see <https://www.gnu.org/licenses/>. */

#include <stdlib.h>
#include <ncurses.h>

#define WIDTH 32
#define HEIGHT 16

#define BLOCK_UP map[xPos + (yPos - 1) * WIDTH]
#define BLOCK_DOWN map[xPos + (yPos + 1) * WIDTH]
#define BLOCK_LEFT map[(xPos - 1) + yPos * WIDTH]
#define BLOCK_RIGHT map[(xPos + 1) + yPos * WIDTH]
#define BLOCK_STANDING map[xPos + yPos * WIDTH]

#define C_BORDER '#'
#define H_BORDER '-'
#define V_BORDER '|'

#define PLAYER 'X'
#define BLOCKS 12

int cursorX;
int cursorY;

char *map;
int yPos = 0;
int xPos = 0;
char heldBlock = 1;
char block[BLOCKS] = {' ', '#', '%', '*', '&', '+', '@', '[', ']', '~', '-', '='};

void drawBorders(){
	int a;
	
	mvaddch(3, 0, C_BORDER);
	mvaddch(3, WIDTH + 1, C_BORDER);
	mvaddch(HEIGHT + 4, 0, C_BORDER);
	mvaddch(HEIGHT + 4, WIDTH + 1, C_BORDER);
	
	for (a = 1; a <= WIDTH; a++){
		mvaddch(3, a, H_BORDER);
		mvaddch(HEIGHT + 4, a, H_BORDER);
	}

	for (a = 4; a <= HEIGHT + 3; a++){
		mvaddch(a, 0, V_BORDER);
		mvaddch(a, WIDTH + 1, V_BORDER);
	}
}

void movePlayerUp(){
	if (yPos > 0 && BLOCK_UP == 0){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY, cursorX - 1, block[BLOCK_STANDING]);
		mvaddch(cursorY - 1, cursorX - 1, PLAYER);
		
		yPos--;
	}
}

void movePlayerDown(){
	if (yPos < HEIGHT - 1 && BLOCK_DOWN == 0){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY, cursorX - 1, block[BLOCK_STANDING]);
		mvaddch(cursorY + 1, cursorX - 1, PLAYER);
		
		yPos++;
	}
}

void movePlayerLeft(){
	if (xPos > 0 && BLOCK_LEFT == 0){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY, cursorX - 1, block[BLOCK_STANDING]);
		mvaddch(cursorY, cursorX - 2, PLAYER);
		
		xPos--;
	}
}

void movePlayerRight(){
	if (xPos < WIDTH - 1 && BLOCK_RIGHT == 0){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY, cursorX - 1, block[BLOCK_STANDING]);
		mvaddch(cursorY, cursorX, PLAYER);
		
		xPos++;
	}
}

void placeBlockUp(){
	if (yPos > 0){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY - 1, cursorX - 1, block[heldBlock]);
		move(cursorY, cursorX);

		BLOCK_UP = heldBlock;
	}
}

void placeBlockDown(){
	if (yPos < HEIGHT - 1){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY + 1, cursorX - 1, block[heldBlock]);
		move(cursorY, cursorX);

		BLOCK_DOWN = heldBlock;
	}
}

void placeBlockLeft(){
	if (xPos > 0){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY, cursorX - 2, block[heldBlock]);
		move(cursorY, cursorX);

		BLOCK_LEFT = heldBlock;
	}
}

void placeBlockRight(){
	if (xPos < WIDTH - 1){
		getyx(stdscr, cursorY, cursorX);
		mvaddch(cursorY, cursorX, block[heldBlock]);
		move(cursorY, cursorX);

		BLOCK_RIGHT = heldBlock;
	}
}

int main(){
	map = calloc(WIDTH + (HEIGHT - 1) * WIDTH, sizeof (char));

	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);

	mvprintw(0, 0, "miniblocks v0.1.0 by Hayden");

	drawBorders();
	mvaddch(yPos + 4, xPos + 1, PLAYER);

	while (1){
		getyx(stdscr, cursorY, cursorX);
		move(1, 0);
		clrtoeol();
		mvprintw(1, 0, "X %d|Y %d|BLOCK %c", xPos, yPos, block[heldBlock]);
		move(cursorY, cursorX);

		switch (getch()){
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
			case '[':
				heldBlock = (heldBlock - 1 + BLOCKS) % BLOCKS;
				break;
			case ']':
				heldBlock = (heldBlock + 1 + BLOCKS) % BLOCKS;
				break;
		}
	}

	endwin();

	free(map);
	return 0;
}
