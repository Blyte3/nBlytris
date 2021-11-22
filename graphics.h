#include <ncurses.h>

const char piecechars[8]={"IJLOSTZ"};
int rf;

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

void PrintQueuePiece(){

	if(r%3){
	
		for(rth=0;rth<4;rth++){
	
			if(PieceImage[queue[queueaccesspoint+rf]][(3-(r%3))-1][rth]==1){printw("X ");}
			else{printw("  ");}
		}
	}
	else{rf++;}
}
	 
//maybe make a seperate i and it instead of r and rt
void PrintStack(){
	
	rf=1;
    printw("\n          ____________________\n");
    
    for(r=20;r>-1;r--){
    	
    	//print the hold piece
    	if((r==20 || r==19) && holdpiece>-1){
    		
    		printw(" ");
    		for(rth=0;rth<4;rth++){
    		
    			if(PieceImage[holdpiece][3-(r%3)-1][rth]){printw("X ");}
    			else{printw("  ");}
    		}	
    	}
    	else{printw("         ");}
    	
    	
    	printw("|");
    	//print the actual board
        for(rt=0;rt<10;rt++){
        	
        	switch(board[rt][r]){
        	
        		case 1:
        			printw("O ");
        			break;
        		case 0:
        			printw(". ");
        			break;
        		default:
        			printw("x ");
        	}
        }
        
        printw("| ");
        PrintQueuePiece();
        printw("\n");
    }
    printw("          --------------------");
}

void PrintActive(){
	
	for(r=0;r<4;r++){board[piecex[r]][piecey[r]]=2;}
}

void RemoveActive(){

	for(r=0;r<4;r++){board[piecex[r]][piecey[r]]=0;}
}





