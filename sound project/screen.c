#include <stdio.h>
#include "screen.h"


void displayBar(int x, int y){ //display vertical bar indicated by column X and top value of bar by y
	int i;

	for (i = 0; i < y/2; ++i)
	{
		gotoxy(50-i, x);

		if(i < 15){
			setFgColor(WHITE);
			printf("%s", BAR);
		}else if (i < 30)
		{
			setFgColor(BLUE):
			printf("%s", BAR);
		}else{
			setFgColor(RED);
			printf("%s", BAR);
		}
	}
}

void resetColor(void){
	printf("\033[0m");
	fflush(stdout);
}

void displayXY(char *s, int f, int b, int row, int col){
	gotoxy(row, col);
	setFgColor(f);
	setBgColor(b);

	printf("%s\n",s);

	resetColor();
}

void gotoxy(int row, int col){
	printf("\033[%d;%dH", row, col);
	fflush(stdout);
}

void clearScreen(void){
	printf("\033[2J");
	fflush(stdout);
}

void setFgColor(int a){
	printf("\033[1;%dm",a);//escape sequence to set FG color
	fflush(stdout); //force the attribute flush to the terminal
}

void setBgColor(int a){
	printf("\033[1;%dm",a);//escape sequence to set BG color
	fflush(stdout); //force the attribute flush to the terminal
}
