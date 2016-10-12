/*
	Header file that allows:
		--> drawing certain UI elements within the terminal such as colored boxes
		--> moving the cursor within the terminal
		--> getting the width and height of the terminal in Lines and Columns
		--> clearing the screen

	Author: Chirculete Vlad Mihai
	Date (last edit): 12.10.2016
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

// text colors
#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"

// background colors
#define BGRED  "\x1B[41m"
#define BGGRN  "\x1B[42m"
#define BGYEL  "\x1B[43m"
#define BGBLU  "\x1B[44m"
#define BGMAG  "\x1B[45m"
#define BGCYN  "\x1B[46m"
#define BGWHT  "\x1B[47m"

// moves the cursor to X and Y in terminal
void gotoxy(int x,int y)
{
 	printf("%c[%d;%df",0x1B,y,x);
}


// get the terminal height in lines
int getTermHeight()
{
	// get the terminal height in lines
    int lines = 0;

	#ifdef TIOCGSIZE
    	struct ttysize ts;
    	ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    	lines = ts.ts_lines;
	#elif defined(TIOCGWINSZ)
	    struct winsize ts;
	    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
	    lines = ts.ws_row;
	#endif /* TIOCGSIZE */

	return lines;
}

int getTermWidth()
{
	// get the terminal width in columns

	int cols = 0;

	#ifdef TIOCGSIZE
    	struct ttysize ts;
    	ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    	cols = ts.ts_cols;
	#elif defined(TIOCGWINSZ)
	    struct winsize ts;
	    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
	    cols = ts.ws_col;
	#endif /* TIOCGSIZE */

	return cols;
}

// draws a filled bar and then moves the cursor to the bottom of the terminal
void drawBar(int x, int y, int width, int height, char *color)
{
	int bottom = getTermHeight();;

	width--;
	height--;

	int i, j=x;

	gotoxy(x, y);

	for(i=y; i<=y+height; i++)
	{
		gotoxy(x, i);
		j=x;
		while(j<=x+width)
		{
			printf("%s ", color);	j++;
		}
	}

	printf("%s", NRM);
	gotoxy(0, bottom);
}

// prints text at X and Y then moves the cursor to the bottom of the terminal
void textXY(char* text, int x, int y)
{
	int bottom = getTermHeight();;

	gotoxy(x, y);

	printf("%s", text);

	gotoxy(0, bottom);
}


// prints colored text at X and Y then moves the cursor to the bottom of the terminal
void textXYcolor(char* text, int x, int y, char* text_color, char* text_bg)
{
	int bottom = getTermHeight();

	gotoxy(x, y);

	printf("%s%s%s%s", text_color, text_bg, text, NRM);

	gotoxy(0, bottom);
}


// clear the screen
void clearscr()
{
	system("clear");
}