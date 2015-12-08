/*
*
* Terminal Tracker version 1.0
* Author: Simon Howden
* Date: December 2015
*
*
*
*/

#include <signal.h>
#include <stdlib.h>
#include <ctype.h>
#include <curses.h>

#include "parent.h"

void init() {
	printf("Init function\n");
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, winHeight, winWidth);

	if(!stdscr) {
		fprintf(stderr, "Error ncurses initialization error\n");
		exit(EXIT_FAILURE);
	}
}

void resizeHandler(int sig) {
	getmaxyx(stdscr, winHeight, winWidth);
	refreshWindow();
}

void cleanup() {
	delwin(stdscr);
	endwin();
	printf("Cleanup function\n");
}

void refreshWindow() {
	wrefresh(stdscr);
}

int main(void) {
	/* start program */
	init();
	signal(SIGWINCH, resizeHandler);	
	refreshWindow();
	getch();	
	/* exit program */
	cleanup();
	return 1;	
}
