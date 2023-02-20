/* miniblocks Copyright (C) 2022 Hayden 
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
 * with miniblocks. If not, see <https://www.gnu.org/licenses/>.               */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ncurses.h>

#define WIDTH 64
#define HEIGHT 24

#define C_BORDER '+'
#define H_BORDER '-'
#define V_BORDER '|'

#define PLAYER 'X'
#define BLOCKS 15

#define TOP_LEFT_Y 3
#define TOP_LEFT_X 0
/* you can change these. */

#define MAP_SIZE WIDTH + (HEIGHT - 1) * WIDTH

#define RELATIVE_BLOCK(Y, X) map[(y_pos + Y) * WIDTH + (x_pos + X)]
#define PLACE_RELATIVE_BLOCK(Y, X) (RELATIVE_BLOCK(Y, X) == 0) ? held_block : 0
#define BLOCK_AT(Y, X) map[Y * WIDTH + X]
/* don't change these. */

int cursor_y;
int cursor_x;

int y_pos = 0;
int x_pos = 0;
uint8_t *map;
uint8_t held_block = 1;
char block[BLOCKS] = {' ', '#', '%', '*', '&', '$', '@', '+', '[', ']', '~', '-', '=', '_', '!'};

void draw_borders()
{
	int i;
	
	mvaddch(TOP_LEFT_Y, TOP_LEFT_X, C_BORDER);
	mvaddch(TOP_LEFT_Y, WIDTH + TOP_LEFT_X + 1, C_BORDER);
	mvaddch(HEIGHT + TOP_LEFT_Y + 1, TOP_LEFT_X, C_BORDER);
	mvaddch(HEIGHT + TOP_LEFT_Y + 1, WIDTH + TOP_LEFT_X + 1, C_BORDER);
	
	for (i = TOP_LEFT_X + 1; i <= WIDTH + TOP_LEFT_X; i++) {
		mvaddch(TOP_LEFT_Y, i, H_BORDER);
		mvaddch(HEIGHT + TOP_LEFT_Y + 1, i, H_BORDER);
	}

	for (i = TOP_LEFT_Y + 1; i <= HEIGHT + TOP_LEFT_Y; i++) {
		mvaddch(i, TOP_LEFT_X, V_BORDER);
		mvaddch(i, WIDTH + TOP_LEFT_X + 1, V_BORDER);
	}
}

void refresh_map()
{
	int i;
	int j;

	getyx(stdscr, cursor_y, cursor_x);

	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			mvaddch(i + TOP_LEFT_Y + 1, j + TOP_LEFT_X + 1, block[map[BLOCK_AT(i, j)]]);
		}
	}

	move(cursor_y, cursor_x);
}

void move_player(int relative_block_y, int relative_block_x, int *axis_as_position, bool condition, int position_increment)
{
	if (condition && RELATIVE_BLOCK(relative_block_y, relative_block_x) == 0) {
		mvaddch(cursor_y, cursor_x - 1, block[RELATIVE_BLOCK(0, 0)]);
		mvaddch(cursor_y + relative_block_y, cursor_x + relative_block_x - 1, PLAYER);
		
		*axis_as_position += position_increment;
	}
}

void place_block(int relative_block_y, int relative_block_x, bool condition)
{
	if (condition) {
		getyx(stdscr, cursor_y, cursor_x);
		mvaddch(cursor_y + relative_block_y, cursor_x + relative_block_x - 1, block[PLACE_RELATIVE_BLOCK(relative_block_y, relative_block_x)]);
		move(cursor_y, cursor_x);
		
		RELATIVE_BLOCK(relative_block_y, relative_block_x) = PLACE_RELATIVE_BLOCK(relative_block_y, relative_block_x);
	}
}

int main(){
	map = calloc(MAP_SIZE, sizeof (uint8_t));

	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);

	mvprintw(0, 0, "miniblocks v0.1.0 by Hayden");

	draw_borders();
	mvaddch(y_pos + TOP_LEFT_Y + 1, x_pos + TOP_LEFT_X + 1, PLAYER);

	while (1) {
		getyx(stdscr, cursor_y, cursor_x);
		move(1, 0);
		clrtoeol();
		mvprintw(1, 0, "X %d|Y %d|BLOCK %c", x_pos, y_pos, block[held_block]);
		move(cursor_y, cursor_x);

		switch (getch()) {
			case 'w':
			case KEY_UP:
				move_player(-1, 0, &y_pos, y_pos > 0, -1);
				break;
			case 's':
			case KEY_DOWN:
				move_player(1, 0, &y_pos, y_pos < HEIGHT - 1, 1);
				break;
			case 'a':
			case KEY_LEFT:
				move_player(0, -1, &x_pos, x_pos > 0, -1);
				break;
			case 'd':
			case KEY_RIGHT:
				move_player(0, 1, &x_pos, x_pos < WIDTH - 1, 1);
				break;
			case 'i':
				place_block(-1, 0, y_pos > 0);
				break;
			case 'k':
				place_block(1, 0, y_pos < HEIGHT - 1);
				break;
			case 'j':
				place_block(0, -1, x_pos > 0);
				break;
			case 'l':
				place_block(0, 1, x_pos < WIDTH - 1);
				break;
			case 'f':
				held_block = (held_block - 1 + BLOCKS) % BLOCKS;
				break;
			case 'h':
				held_block = (held_block + 1 + BLOCKS) % BLOCKS;
				break;
			case ' ':
				refresh_map();
				break;
		}
	}

	endwin();

	free(map);
	return 0;
}
