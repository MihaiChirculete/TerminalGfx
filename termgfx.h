/*
	Header file that allows:
		--> drawing certain UI elements within the terminal such as colored boxes
		--> moving the cursor within the terminal
		--> getting the width and height of the terminal in Lines and Columns
		--> clearing the screen

	Author: Chirculete Vlad Mihai
	Date (created): 12.10.2016
	Date (last edit): 19.11.2016
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

// text colors
#define NRM  "\x1B[0m"
#define BLK  "\x1B[30m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"

// background colors
#define BGBLK  "\x1B[40m"
#define BGRED  "\x1B[41m"
#define BGGRN  "\x1B[42m"
#define BGYEL  "\x1B[43m"
#define BGBLU  "\x1B[44m"
#define BGMAG  "\x1B[45m"
#define BGCYN  "\x1B[46m"
#define BGWHT  "\x1B[47m"

// other text attributes
#define BOLD_ON "\x1b[1m"		 // Bold on(enable foreground intensity)
#define UNDERLINE_ON "\x1b[4m"	 // Underline on
#define BLINK_ON "\x1b[5m"		 // Blink on(enable background intensity)
#define BOLD_OFF "\x1b[21m"		 // Bold off(disable foreground intensity)
#define UNDERLINE_OFF "\x1b[24m" //	Underline off
#define BLINK_OFF "\x1b[25m"	 // Blink off(disable background intensity)


typedef struct window window;

struct window
{
	int id;				// the id of the window
	char *title;		// the title of the window
	char *titleColor;	// color of the window's title

	int x, y;			// x and y coordinates of the top left corner of the window
	int width, height;	// the width and the height of the window

	int drawBorder;		// 1 or 0, enables/disables drawing of the border and title
	char *borderColor;	// color of the window's border

	int drawBackground;		// 1 or 0, enables/disables drawing of the window background 
	char *backgroundColor;	// background color of the box
};

// sets the window's title and enables border drawing
void setWindowTitle(window *w, char *title, char *title_color)
{
	(*w).title = title;
	(*w).titleColor = title_color;
	(*w).drawBorder = 1;
}

// sets the window's border color and enables border drawing
void setWindowBorderColor(window *w, char *color)
{
	(*w).borderColor = color;
	(*w).drawBorder = 1;
}



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

// draws a filled bar and then moves the cursor to the top of the terminal
void drawBar(int x, int y, int width, int height, char *color)
{
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
	gotoxy(0, 0);
}

// draws a box (different from a bar since it has no filling)  then moves the cursor to the top of the terminal
void drawBox(int x, int y, int width, int height, char *color)
{
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
			if(j==x || j==x+width || i==y || i == y+height) printf("%s ", color);	
			else printf("%s ", NRM);
			j++;
		}

		//printf("%s\n", NRM);
	}

	printf("%s", NRM);

	gotoxy(0, 0);
}

// prints text at X and Y then moves the cursor to the top of the terminal
void textXY(char* text, int x, int y)
{
	gotoxy(x, y);

	printf("%s", text);

	gotoxy(0, 0);
}


// prints colored text at X and Y then moves the cursor to the top of the terminal
void textXYcolor(char* text, int x, int y, char* text_color, char* text_bg)
{
	gotoxy(x, y);

	printf("%s%s%s%s", text_color, text_bg, text, NRM);

	gotoxy(0, 0);
}

// sets the current text color to TEXT_COLOR
void setTextColor(char* text_color)
{
	printf("%s", text_color);
}

// sets the current text background to TEXT_BG
void setTextBackground(char* text_bg)
{
	printf("%s", text_bg);
}

// sets text attributes
void setTextAttr(char* text_attr)
{
	printf("%s", text_attr);
}

// clear the screen
void clearscr()
{
	system("clear");
}

// draw a given window
void drawWindow(window w)
{
	int titlePosition;	// position on X axis where to start drawing the text

	titlePosition = (w.width / 2) - (strlen(w.title) / 2);

	// if border drawing is set to true (1), draw the border and the title
	if(w.drawBorder)
	{
		drawBox(w.x, w.y, w.width, w.height, w.borderColor);

		// set the bold and underline attributes to ON for title then switch it back off
		setTextAttr(BOLD_ON);	setTextAttr(UNDERLINE_ON);
		textXYcolor(w.title, w.x + titlePosition, w.y, w.titleColor, w.borderColor);
		setTextAttr(BOLD_OFF);	setTextAttr(UNDERLINE_OFF);
	}

	// if background drawing is set to true (1), draw the background
	if(w.drawBackground)
	{
		drawBar(w.x+1, w.y+1, w.width-1, w.height-1, w.backgroundColor);
	}
}

// draw a given array of windows
void drawWindows(window windows[], int n)
{
	int i;
	for(i=0; i<n; i++)
		drawWindow(windows[i]);
}