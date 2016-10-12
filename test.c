#include <stdlib.h>
#include <stdio.h>
#include <termgfx.h>

int main(int argc, char **argv)
{
	clearscr();

	textXYcolor("This is a colored text", 20, 5, MAG, BGCYN);

	drawBar(40, 10, 15, 3, BGBLU);

	textXY("This is a box", 41, 11);

	return 0;
}