enum COLORS{BLACK=30,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE};
#define bg(c) (c+10) //this macro 
#define BAR "\u2590" //define an unicode symbol

//function prototype
void displayBar(int, int);
void displayXY(char *s, int fg, int bg, int row, int col);
void gotoxy(int, int);
void clearScreen(void);
void setFgColor(int);
void setBgColor(int);
