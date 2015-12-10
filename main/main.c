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

void cleanup( WINDOW *chainWindow,
		WINDOW *score
	) {
	
	/* delete windows */
	delwin(stdscr);
	delwin(chainWindow);
	delwin(score);

	endwin();
	printf("Cleanup function\n");
}

void refreshWindow( WINDOW *chainWindow, 
		WINDOW *score
	) {
	
	/* refresh windows */
	wrefresh(stdscr);
	wrefresh(chainWindow);
	wrefresh(score);
}

void drawBorders(WINDOW *screen) {
	int x, y, i;
}

int main(void) {
	int x = 0, y = 0;
	
	init();

	WINDOW *chainWindow = newwin(4, winWidth - 1, 0, 1);
	WINDOW *score = newwin(3, winWidth - 1, winHeight - 3, 1);
	box(chainWindow, 0, 0);
	box(score, 0, 0);
	signal(SIGWINCH, resizeHandler);	
	
	mvwprintw(chainWindow, 0, 3, " Chains ");
	mvwprintw(score, 0, 3, " Score ");

	/* attempt at borders */

	refreshWindow(chainWindow, score);

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
	cleanup(chainWindow, score);
	return 1;	
}
