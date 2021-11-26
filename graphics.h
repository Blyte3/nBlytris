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
	 
//maybe make a seperate i and it instead of r and rt
void PrintStack(){
	
	int r,rt,rth;
	
	rth=1;
	
    printw("\n          ____________________\n");
    
    for(r=20;r>-1;r--){
    	
    	//print the hold piece
    	if((r==20 || r==19) && holdpiece>-1){
    		
    		printw(" ");
    		
    		for(rt=0;rt<4;rt++){
    		
    			if(PieceImage[holdpiece][3-(r%3)-1][rt]){printw("X ");}
    			else{printw("  ");}
    		}	
    	}
    	else{printw("         ");}
    	
    	printw("|");
    	
    	//prints board
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
        
        //prints the piece in the queue
        if(r%3){
	
			for(rt=0;rt<4;rt++){
	
				if(PieceImage[queue[queueaccesspoint+rth]][(3-(r%3))-1][rt]==1){printw("X ");}
				else{printw("  ");}	
			}
		}
		else{rth++;}
		
        printw("\n");
    }
    
    printw("          --------------------");
}

void PrintActive(){
	
	int r;
	
	for(r=0;r<4;r++){board[piecex[r]][piecey[r]]=2;}
}

void RemoveActive(){

	int r;

	for(r=0;r<4;r++){board[piecex[r]][piecey[r]]=0;}
}





