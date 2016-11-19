#include <stdlib.h>
#include <stdio.h>
#include <termgfx.h>

void drawBar();

int main(int argc, char **argv)
{
	system("clear");

	window w[10];

	// window 0
	w[0].title = "Window 0";
	w[0].drawBorder = 1;
	w[0].titleColor = WHT;
	w[0].borderColor = BGBLU;
	w[0].drawBackground = 0;
	w[0].backgroundColor = BGWHT;
	w[0].x = 0;
	w[0].y = 2;
	w[0].width = (getTermWidth()/2)-1;
	w[0].height = getTermHeight()-3;

	// window 1
	w[1].title = "Window 1";
	w[1].drawBorder = 1;
	w[1].titleColor = YEL;
	w[1].borderColor = BGGRN;
	w[1].drawBackground = 0;
	w[1].backgroundColor = BGWHT;
	w[1].x = getTermWidth()/2;
	w[1].y = 2;
	w[1].width = getTermWidth()/2;
	w[1].height = getTermHeight()/2;

	// window 2
	w[2].title = "Window 2";
	w[2].drawBorder = 1;
	w[2].titleColor = GRN;
	w[2].borderColor = BGYEL;
	w[2].drawBackground = 0;
	w[2].backgroundColor = BGWHT;
	w[2].x = getTermWidth()/2;
	w[2].y = getTermHeight()/2;
	w[2].width = getTermWidth()/2;
	w[2].height = getTermHeight()/2;

	drawWindows(w, 3);

	return 0;
}