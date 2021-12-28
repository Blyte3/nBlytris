#include <ncurses.h>

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

void ChangeColor(int piece){

	switch(piece){
	
		case 1:attron(COLOR_PAIR(1)); break;
		case 2:attron(COLOR_PAIR(2)); break;
		case 3:attron(COLOR_PAIR(3)); break;
		case 4:attron(COLOR_PAIR(4)); break;
		case 5:attron(COLOR_PAIR(5)); break;
		case 6:attron(COLOR_PAIR(6)); break;
		case 7:attron(COLOR_PAIR(7)); break;
		default:attron(COLOR_PAIR(8)); break;
	}
}

void PrintActive(){
	
	int r;
	
	for(r=0;r<4;r++){board[piecex[r]][piecey[r]]=activepiece+1;}
}

void RemoveActive(){

	int r;

	for(r=0;r<4;r++){board[piecex[r]][piecey[r]]=0;}
}

void PrintRow(int y){
	
	int r;
	
	ChangeColor(0);
	printw("|");
	
	for(r=0;r<10;r++){
	
		switch(board[r][y]){
        
        	case 0:
        		ChangeColor(0);
        		printw(". ");
        		break;
        	default:
        		ChangeColor(board[r][y]);
        		printw("x ");
        		break;
        }
	}
	ChangeColor(0);
	printw("|");
}

void PrintPiece(int piece, int part){
	
	int r;
	
	//handles the hold piece before there is one
	if(piece==-1){
		
   		printw("         ");
   		return;
	}
	
	ChangeColor(0);
	printw(" ");

	for(r=0;r<4;r++){
	
		if(PieceImage[piece][part][r]==1){
		
			ChangeColor(piece+1);
			printw("X ");
		}
		else{
			
			ChangeColor(0);
			printw("  ");
		}	
	}
}
	 
void PrintBoard(){
	
	clear();
	PrintActive();
	   
	int r,rt,rth;
	
	ChangeColor(0);
    printw("\n          ____________________\n");
    
   	PrintPiece(holdpiece,0);
   	PrintRow(20);
   	PrintPiece(queue[queueaccesspoint+1],0);
   	ChangeColor(0);
   	printw("\n");

   	PrintPiece(holdpiece,1);
   	PrintRow(19);
   	PrintPiece(queue[queueaccesspoint+1],1);
   	ChangeColor(0);
   	printw("\n");
    
    //these make sure queue is in right place and makes sure printed queue gets spaced correctly
   	rt=2;
   	rth=1;
   	
   	for(r=18;r>6;r--){
   		
   		ChangeColor(0);
   		printw("         ");
   		PrintRow(r);
   		
   		if(rt%3!=2){
   		
   			PrintPiece(queue[queueaccesspoint+rth],rt%3);
   		}
   		else{rth++;}
   		
   		rt++;
   		
   		ChangeColor(0);
   		printw("\n");
   	}
   	   		
	for(;r>-1;r--){
	
		ChangeColor(0);
   		printw("         ");
   		PrintRow(r);
   		
   		ChangeColor(0);
   		printw("\n");
	}
    
    ChangeColor(0);
    printw("          --------------------");
    
    refresh();
    RemoveActive();

}

void InitGraphics(){

	initscr();
	
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
	
	PrintActive();
	PrintBoard();
	refresh();
}
