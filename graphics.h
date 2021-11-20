#include <ncurses.h>

//maybe make a seperate i and it instead of r and rt
void PrintStack(){
	
    printw("\n");
    
    for (r=24;r>-1;r--){
    
        for (rt=0;rt<10;rt++){printw("%d ",board [rt][r]);}
        
        printw("\n");
    }
}

void PrintActive(){
	
	for(r=0;r<4;r++){board[piecex[r]][piecey[r]]=1;}
}

void RemoveActive(){

	for(r=0;r<4;r++){board[piecex[r]][piecey[r]]=0;}
}

void PrintQueueAndHold(){

	for(r=0;r<7;r++){printw("%c ",piecechars[queue[queueaccesspoint+r]]);}
		
	printw("  hold:%c",piecechars[holdpiece]);
	printw("\n");
}