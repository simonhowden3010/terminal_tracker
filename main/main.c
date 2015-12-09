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
#include <unistd.h>
#include "main.h"

void init() {
	printf("Init function\n");
	initscr();
	/* cbreak(); */
	noecho();
	curs_set(FALSE);
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

void cleanup( WINDOW *field,
		WINDOW *score
	) {
	
	/* delete windows */
	delwin(stdscr);
	delwin(field);
	delwin(score);

	endwin();
	printf("Cleanup function\n");
}

void refreshWindow( WINDOW *field, 
		WINDOW *score
	) {
	
	/* refresh windows */
	/* wrefresh(stdscr); */
	wrefresh(field);
	wrefresh(score);
}

int main(void) {
	int x = 0, y = 0;
	WINDOW *field = newwin(winHeight - 3, winWidth, 0, 0);
	WINDOW *score = newwin(3, winWidth, winHeight - 3, 0);
	
	/* start program */
	init();
	signal(SIGWINCH, resizeHandler);	
	
	mvwprintw(field, 0, 0, "Field");
	mvwprintw(score, 0, 0, "Score");

	refreshWindow(field, score);

	wrefresh(field);
	/*getch();*/
	sleep(5);
/*	
	while(1) {
		clear();
		mvprintw(y, x, "x");
		refresh();

		usleep(DELAY);
		x++;
	}
*/	
	/* exit program */
	cleanup(field, score);
	return 1;	
}
