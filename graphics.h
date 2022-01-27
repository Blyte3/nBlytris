#include <ncurses.h>

//prototypes

void PrintActive();
void PrintHold();
void PrintBoard();
void PrintPiece(WINDOW *window,int piece, int part);
void PrintQueue();
void PrintRow(int y);
void PrintAll();
void RemoveActive();
void ChangeColor(WINDOW *window,int piece);

//ijlostz order. pieces to be printed out in queue
int PieceImage[7][2][4]={
	{{1,1,1,1},
	 {0,0,0,0}},
	 
	{{1,0,0,0},
	 {1,1,1,0}},
	
	{{0,0,1,0},
	 {1,1,1,0}},
	
	{{1,1,0,0},
	 {1,1,0,0}},
	
	{{0,1,1,0},
	 {1,1,0,0}},
	
	{{0,1,0,0},
	 {1,1,1,0}},
	
	{{1,1,0,0},
	 {0,1,1,0}}
};

WINDOW *holdwin;
WINDOW *boardwin;
WINDOW *queuewin;

void InitGraphics(){

	initscr();
	noecho();
	curs_set(0);

	start_color();

	//sets white to orange
	init_color(COLOR_WHITE,850,850,100);

	//ijlostz, then border
	init_pair(1,COLOR_CYAN,COLOR_CYAN);
	init_pair(2,COLOR_BLUE,COLOR_BLUE);
	init_pair(3,COLOR_YELLOW,COLOR_YELLOW);
	init_pair(4,COLOR_WHITE,COLOR_WHITE);
	init_pair(5,COLOR_GREEN,COLOR_GREEN);
	init_pair(6,COLOR_MAGENTA,COLOR_MAGENTA);
	init_pair(7,COLOR_RED,COLOR_RED);
	init_pair(8,COLOR_CYAN,COLOR_BLACK);

	holdwin=newwin(7,10,2,4);
	//box(holdwin,0,0);

	boardwin=newwin(28,24,0,12);
	//box(boardwin,0,0);

	queuewin=newwin(18,10,1,36);
	//box(queuewin,0,0);

	PrintAll();
}

void ChangeColor(WINDOW *window,int piece){

	switch(piece){
	
		case 1:wattron(window,COLOR_PAIR(1)); break;
		case 2:wattron(window,COLOR_PAIR(2)); break;
		case 3:wattron(window,COLOR_PAIR(3)); break;
		case 4:wattron(window,COLOR_PAIR(4)); break;
		case 5:wattron(window,COLOR_PAIR(5)); break;
		case 6:wattron(window,COLOR_PAIR(6)); break;
		case 7:wattron(window,COLOR_PAIR(7)); break;
		default:wattron(window,COLOR_PAIR(8)); break;
	}
}

void PrintActive(){
	
	int r;
	
	for(r=0;r<4;r++) board[piecex[r]][piecey[r]]=activepiece+1;
}

void RemoveActive(){

	int r;

	for(r=0;r<4;r++) board[piecex[r]][piecey[r]]=0;
}

void PrintRow(int y){
	
	int r;
	
	ChangeColor(boardwin,0);
	wprintw(boardwin,"|");
	
	for(r=0;r<10;r++){
	
		switch(board[r][y]){
        
        	case 0:
        		ChangeColor(boardwin,0);
        		wprintw(boardwin,". ");
        		break;
        	default:
        		ChangeColor(boardwin,board[r][y]);
        		wprintw(boardwin,"x ");
        		break;
        }
	}
	ChangeColor(boardwin,0);
	wprintw(boardwin,"|");
}

void PrintBoard(){

	PrintActive();

	int r;
	
	ChangeColor(boardwin,0);

	wprintw(boardwin," ____________________\n");

	for (r=21;r>-1;r--){

		PrintRow(r);
		wprintw(boardwin,"\n");
	}

	ChangeColor(boardwin,0);
	
	wprintw(boardwin," --------------------");

	RemoveActive();
}

void PrintPiece(WINDOW *window,int piece, int part){
	
	int r;
	
	/*handles the hold piece before there is one*/
	if(piece==-1) return;
	
	for(r=0;r<4;r++){
	
		if(PieceImage[piece][part][r]==1){
		
			ChangeColor(window,piece+1);
			wprintw(window,"X ");
		}
		else{
			
			ChangeColor(window,0);
			wprintw(window,"  ");
		}	
	}
}

void PrintQueue(){

	int r;

	for(r=0;r<5;r++){

		PrintPiece(queuewin,queue[queueaccesspoint+1+r],0);
		wprintw(queuewin,"\n");
		PrintPiece(queuewin,queue[queueaccesspoint+1+r],1);
		wprintw(queuewin,"\n\n");
	}
}

void PrintHold(){

	PrintPiece(holdwin,holdpiece,0);
	wprintw(holdwin,"\n");
	PrintPiece(holdwin,holdpiece,1);
}

void PrintAll(){

	wclear(holdwin);
	wclear(boardwin);
	wclear(queuewin);

	PrintHold();
	PrintBoard();
	PrintQueue();

	wrefresh(holdwin);
	wrefresh(boardwin);
	wrefresh(queuewin);
}
