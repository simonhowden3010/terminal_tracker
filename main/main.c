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

void cleanup( WINDOW *mainWindow1,
		WINDOW *mainWindow2,
		WINDOW *score
	) {
	
	/* delete windows */
	delwin(stdscr);
	delwin(mainWindow1);
	delwin(mainWindow2);
	delwin(score);

	endwin();
	printf("Cleanup function\n");
}

void refreshWindow( WINDOW *mainWindow1, 
		WINDOW *mainWindow2,
		WINDOW *score
	) {
	
	/* refresh windows */
	wrefresh(stdscr);
	wrefresh(mainWindow1);
	wrefresh(mainWindow2);
	wrefresh(score);
}

void drawBorders(WINDOW *screen) {
	int x, y, i;
}

int main(void) {
	int x = 0, y = 0;
	
	init();

	WINDOW *mainWindow1 = newwin(winHeight-(winHeight/3), (winWidth / 2)-1, 3, 1);
	WINDOW *mainWindow2 = newwin(winHeight-(winHeight/3), winWidth/2, 3, (winWidth / 2)+1 );
	WINDOW *score = newwin(winHeight/4.5, winWidth - 1, (winHeight-(winHeight/3))+3, 1);
	box(mainWindow1, 0, 0);
	box(mainWindow2, 0, 0);
	box(score, 0, 0);
	signal(SIGWINCH, resizeHandler);	

	mvwprintw(stdscr, 1, 2, "MetaTracker v1.0 - Be all you can be");	
	mvwprintw(mainWindow1, 0, 3, " Window 1 ");
	mvwprintw(mainWindow2, 0, 3, " Window 2 ");
	mvwprintw(score, 0, 3, " Window 2 ");

	/* attempt at borders */

	refreshWindow(mainWindow1, mainWindow2, score);

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
	cleanup(mainWindow1, mainWindow2, score);
	return 1;	
}
