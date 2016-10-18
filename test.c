#include <stdlib.h>
#include <stdio.h>
#include "termgfx.h"

int main(int argc, char **argv)
{
	clearscr();

	textXYcolor("This is a colored text", 20, 5, MAG, BGCYN);

	drawBar(40, 10, 15, 3, BGBLU);

	textXYcolor("This is a bar", 41, 11, RED, BGBLU);

	drawBox(40, 20, 10, 6, BGRED);

	return 0;
}