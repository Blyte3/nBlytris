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
	 
//maybe make a seperate i and it instead of r and rt
void PrintStack(){
	
	int r,rt,rth;
	
	rth=1;
	ChangeColor(0);
    printw("\n          ____________________\n");
    
    for(r=20;r>-1;r--){
    	
    	//print the hold piece
    	if((r==20 || r==19) && holdpiece>-1){
    		
    		printw(" ");
    		
    		for(rt=0;rt<4;rt++){
    		
    			if(PieceImage[holdpiece][3-(r%3)-1][rt]){
    				
    				ChangeColor(holdpiece+1);
    				printw("X ");
    			}
    			else{
    				
    				ChangeColor(0);
    				printw("  ");
    			}
    		}	
    	}
    	else{printw("         ");}
    	
    	ChangeColor(0);
    	printw("|");
    	
    	//prints board
        for(rt=0;rt<10;rt++){
        	
        	switch(board[rt][r]){
        	
        		case 0:
        			ChangeColor(0);
        			printw(". ");
        			break;
        		default:
        			ChangeColor(board[rt][r]);
        			printw("x ");
        	}
        }
        
        ChangeColor(0);
        printw("| ");
        
        //prints the piece in the queue
        if(r%3){
	
			
	
			for(rt=0;rt<4;rt++){
	
				if(PieceImage[queue[queueaccesspoint+rth]][(3-(r%3))-1][rt]==1){
					
					ChangeColor(queue[queueaccesspoint+rth]+1);
					printw("X ");
				}
				else{
					
					ChangeColor(0);
					printw("  ");
				}	
			}
		}
		else{rth++;}
		
		ChangeColor(0);
        printw("\n");
    }
    
    ChangeColor(0);
    printw("          --------------------");
}

void PrintActive(){
	
	int r;
	
	for(r=0;r<4;r++){board[piecex[r]][piecey[r]]=activepiece+1;}
}

void RemoveActive(){

	int r;

	for(r=0;r<4;r++){board[piecex[r]][piecey[r]]=0;}
}

void InitGraphics(){

	initscr();
	
	start_color();
	init_color(COLOR_WHITE,850,850,100);
	init_pair(7,COLOR_RED,COLOR_RED);
	init_pair(4,COLOR_WHITE,COLOR_WHITE);
	init_pair(3,COLOR_YELLOW,COLOR_YELLOW);
	init_pair(5,COLOR_GREEN,COLOR_GREEN);
	init_pair(2,COLOR_BLUE,COLOR_BLUE);
	init_pair(1,COLOR_CYAN,COLOR_CYAN);
	init_pair(6,COLOR_MAGENTA,COLOR_MAGENTA);
	init_pair(8,COLOR_CYAN,COLOR_BLACK);
	
	PrintActive();
	PrintStack();
	refresh();
}
