#include <time.h>
#include <stdlib.h>

//piece order is ijlostz   ex:spawnlocx[0] holds the x coordinates for i piece spawn
//the coordinates are x,y coordinates starting from the axis and then from up to down, left to right, except i and o, which also end with another axis point
const int spawnlocx[7][4]={{4,3,6,5},{4,3,3,5},{4,5,3,5},{4,5,4,5},{4,4,5,3},{4,4,3,5},{4,3,4,5}};
const int spawnlocy[7][4]={{19,19,19,19},{19,20,19,19},{19,20,19,19},{20,19,19,20},{19,20,20,19},{19,20,19,19},{19,20,20,19}};
const int kickx[5]={0,1, 1,0,1};
const int kicky[5]={0,0,-1,2,2};
const int kickydir[4]={1,-1,1,-1};
const int ikickx[5]={0,-2,1,-2,1};
const int ikickx2[5]={0,-1,2,-1,2};
const int ikicky[5]={0,0,0,-1,2};
const int ikicky2[5]={0,0,0,-2,1};
const char piecechars[8]={"ijlostz"};
int board[10][25];
int death=0;
int queue[14];
int queueaccesspoint;
int activepiece;
int bag[7];
int randpieces[7];
int randomnumber;
int piecex[4],piecey[4];
int tempx[4],tempy[4];
int kickxdir;
int eaxis;
int lastrot;
int rotnum;
int tempkickx,tempkicky;
int tempkickix[5], tempkickiy[5];
int idirx,idiry;
int holdpiece=-1;
char input;
int clearlines[4];
int ycleared[4];
int direction;
int rotdir;
int r,rt,rth;

#include"graphics.h"

//builds the matrix, fills it with zeroes
void BuildStack(){

	for (r=0;r<10;r++){
	
        for (rt=0;rt<25;rt++){board[r][rt]=0;}
    }
}

//generates a randomized bag and puts it in bag[]
void GenBag(){

	for(r=0;r<7;r++){
		randpieces[r]=r;
	}
	
	for(r=7;r>0;r--){
		
		randomnumber=rand()%r;
		bag[r-1]=randpieces[randomnumber];
		randpieces[randomnumber]=randpieces[r-1];
	}
}

//checks for line clears and clears if neccesary
void LineClear(){
		
	for(r=0;r<4;r++){
	
		for(rt=0;rt<10;rt++){
		
			if(board[rt][clearlines[r]]!=1){break;}
		}
		
		if(rt==10){
			
			for(rt=r+1;rt<4;rt++){
			
				if(clearlines[r]<clearlines[rt]){clearlines[rt]--;}
			}
			
			for(rt=0;rt<10;rt++){board[rt][clearlines[r]]=0;}
			
			for(rt=0;rt<10;rt++){
			
				for(rth=clearlines[r];rth<24;rth++){board[rt][rth]=board[rt][rth+1];}
			}
			
			for(rt=0;rt<10;rt++){board[rt][24]=0;}
		}
	}
}

//moves the queue forward and generates more queue if needed
void MoveQueue(){

	queueaccesspoint++;
	
	if (queueaccesspoint==7){
	
		for (r=0;r<7;r++){queue[r]=queue[r+7];}
		
		GenBag();
		
		for(r=0;r<7;r++){queue[r+7]=bag[r];}		
		
		queueaccesspoint=0;
	}	
	activepiece=queue[queueaccesspoint];
}

//creates an initial queue
void InitialQueue(){

	queueaccesspoint=0;
	
	GenBag();
	
	for(r=0;r<7;r++){queue[r]=bag[r];}
		
	GenBag();
	
	for(r=0;r<7;r++){queue[r+7]=bag[r];}
	
	activepiece=queue[queueaccesspoint];
}

//spawns in the next piece in the queue
void SpawnPiece(){

	for(r=0;r<4;r++){
		
		if(board[spawnlocx[activepiece][r]][spawnlocy[activepiece][r]]==1){death++;}
		
		piecex[r]=spawnlocx[activepiece][r];
		piecey[r]=spawnlocy[activepiece][r];
	}
	rotnum=0;
	lastrot=0;
}

//moves the piece side to side
void MovePiece(){
	
	for(r=0;r<4;r++){
	
		if(piecex[r]+direction==-1 || piecex[r]+direction==10){return;}
		
		if(board[piecex[r]+direction][piecey[r]]==1){return;}
	}
		
		for(r=0;r<4;r++){piecex[r]=piecex[r]+direction;}
}

//rotates the piece with SRS
void RotatePiece(){
	
	rotnum-=rotdir;
	
	if(rotnum==-1){rotnum=3;}
	if(rotnum==4){rotnum=0;}
	
	if(activepiece==0 || activepiece==3){
		
		//special rotation for i and o pieces
		if(rotdir==-1){eaxis=3;}
		else{eaxis=0;}
		
		for(r=0;r<4;r++){
		
			if(eaxis==r){
			
				tempx[r]=piecex[eaxis];
				tempy[r]=piecey[eaxis];
			}
			else{
			
				tempx[r]=(piecey[eaxis]-piecey[r])*rotdir+piecex[eaxis];
				tempy[r]=(piecex[eaxis]-piecex[r])*rotdir*(-1)+piecey[eaxis];
			}
		}
		
		switch(rotnum){
			
			case 0:
				for(r=0;r<4;r++){tempx[r]-=rotdir;}
			break;
		
			case 1:
				for(r=0;r<4;r++){tempy[r]+=rotdir;}
			break;
			
			case 2:
				for(r=0;r<4;r++){tempx[r]+=rotdir;}
			break;
			
			default:
				for(r=0;r<4;r++){tempy[r]-=rotdir;}
		}		
		
		//generates a full kick table before rotating
		if(lastrot==0 || rotnum==2){idirx=1;}		
		else{idirx=-1;}
		
		if(lastrot==3 || rotnum==1){idiry=1;}
		else{idiry=-1;}
		
		
		if(
			(lastrot==1 && rotnum==0) ||
			(lastrot==2 && rotnum==3) ||
			(lastrot==0 && rotnum==1) ||
			(lastrot==3 && rotnum==2))
		{
		
			for(r=0;r<5;r++){
			
				tempkickix[r]=ikickx[r]*idirx;
				tempkickiy[r]=ikicky[r]*idiry;
			}
		}
		else{
		
			for(r=0;r<5;r++){
			
				tempkickix[r]=ikickx2[r]*idirx;
				tempkickiy[r]=ikicky2[r]*idiry;
			}
		}
		
		//main rotation loop, rotates, checks if legal, moves forward in kick table, repeat
		for(r=0;r<5;r++){
			
			for(rt=0;rt<4;rt++){
			
				if(
					9<(tempx[rt]+tempkickix[r]) ||
					0>(tempx[rt]+tempkickix[r]) || 
					(24<(tempy[rt]+tempkickiy[r]) ||
					0>(tempy[rt]+tempkickiy[r])) ||
					(board[tempx[rt]+tempkickix[r]][tempy[rt]+tempkickiy[r]]==1))
				{break;}
			}
			
			if(rt==4){
		
				for(rt=0;rt<4;rt++){
				
					piecex[rt]=tempx[rt]+tempkickix[r];
					piecey[rt]=tempy[rt]+tempkickiy[r];
				}
				
				lastrot=rotnum;
				
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------
	//rotation for all other pieces
	else{
		
		if(rotnum==1 || lastrot==3){kickxdir=-1;}
		else{kickxdir=1;}
	
		tempx[0]=piecex[0];
		tempy[0]=piecey[0];
		
		for(r=1;r<4;r++){
		
			tempx[r]=(piecey[0]-piecey[r])*rotdir+piecex[0];
			tempy[r]=(piecex[0]-piecex[r])*rotdir*(-1)+piecey[0];
		}
		
		for(r=0;r<5;r++){
				
			tempkickx=kickx[r]*kickxdir;
			tempkicky=kicky[r]*kickydir[rotnum];
			
			for(rt=0;rt<4;rt++){
			
				if(
				9<(tempx[rt]+tempkickx) || 
				0>(tempx[rt]+tempkickx) || 
				24<(tempy[rt]+tempkicky) || 
				0>(tempy[rt])+tempkicky || 
				(board[tempx[rt]+tempkickx][tempy[rt]+tempkicky]==1))
				{
				
					break;
				}
			}
			
			if(rt==4){
				
				for(rt=0;rt<4;rt++){
				
					piecex[rt]=tempx[rt]+tempkickx;
					piecey[rt]=tempy[rt]+tempkicky;
				}
				
				lastrot=rotnum;
				
				return;
			}
		}
	}
	rotnum=lastrot;
}

//holds the piece
void HoldPiece(){

	if(holdpiece==-1){
	
		holdpiece=activepiece;
		MoveQueue();
		SpawnPiece();
	}
	else{
	
		activepiece=holdpiece;
		holdpiece=queue[queueaccesspoint];
		queue[queueaccesspoint]=activepiece;
		SpawnPiece();
	}
}

//drops the piece down
void HardDrop(){
	
	for(r=0;;r++){
	
		for(rt=0;rt<4;rt++){
			
			if(piecey[rt]-r==-1 || board[piecex[rt]][piecey[rt]-r]==1){
			
				for(rt=0;rt<4;rt++){
				
					board[piecex[rt]][piecey[rt]-r+1]=1;
					
					//makes a list of y values to check for line clears on
					clearlines[rt]=piecey[rt]-r+1;
				}
				LineClear();
				MoveQueue();
				SpawnPiece();
				return;
			}
		}
	}
}

//moves the piece downwards
void SoftDrop(){

	for(r=0;r<4;r++){
	
		if(board[piecex[r]][piecey[r]-1]==1 || (piecey[r]-1)<0){break;}
	}
	
	if(r==4){
	
		for(r=0;r<4;r++){piecey[r]--;}
	}
}

void main(){

	//set rng seed, initialize ncurses, initialize board and queue
	srand(time(0));
	initscr();		
	BuildStack();
	InitialQueue();
	SpawnPiece();
	
	while(!death){
		
		clear();
		RemoveActive();
			
		input=getchar();
		
		if(input==','){SoftDrop();}
		
		if(input=='d'){
		
			rotdir=-1;
			RotatePiece();
		}
		
		if(input=='s'){
		
			rotdir=1;
			RotatePiece();
		}
		
		if(input=='f'){HoldPiece();}
		
		if(input=='m'){
		
			direction=(-1);
			MovePiece();
		}
		
		if(input=='.'){
		
			direction=1;
			MovePiece();
		}
		
		if(input==' '){HardDrop();}
		
		if(input=='q'){death++; }
		
		PrintActive();
		PrintQueueAndHold();		
		PrintStack();
		refresh();
	}
	printw("\nGame Over\n");
	refresh();
	getchar();	
	endwin();	
}