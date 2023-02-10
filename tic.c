/************************************************************************
University of Leeds
School of Computing
COMP1711/XJCO1711- Procedural Programming
Coursework 2

I confirm that the following code has been developed and written by me and it is entirely the result of my own work.
I also confirm that I have not copied any parts of this program from another person or any other source or facilitated someone to copy this program from me.
I confirm that I will not publish the program online or share it with anyone without permission of the module leader.

Student Name: Liu Yunzhu
Student ID: 201388894
Email: sc192yl@leeds.ac.uk
Date Work Commenced: 11/7/2020
*************************************************************************/


// ********************************************************************************************************************
// DO NOT CHANGE ANYTHING IN THE FOLLOWING SECTION. IF YOU CHANGE ANYTHING, YOUR CODE WILL FAIL THE AUTOGRADER TESTS.
// However, please read through this section and look at the array declaration and other functions that you will use in your code

#include <stdio.h>
#include <stdlib.h>
#include "tic.h"

char grid[MaxGrid][MaxGrid]; 

int __Check_Count; 

// Function to prompt the user to enter the grid size to start a new game
void promptEnterGridSize ()
{
  printf ("Enter grid size (3-10):");
}

// Function to prompt the user to enter the winning length for the new game
// parameter: maximum winning length for this game
void promptEnterWinLength (int max_win_length)
{
	printf ("Enter winning length (3-%i):", max_win_length);
}

// Function to prompt the user to enter the location of the symbol
// Parameter: the symbol of the player to be prompted
void promptChooseLocation (char symbol)
{
	printf ("Player %c, Choose Location (row,col): ", symbol);
}

// Out of range message
void showErrIndex ()
{
  printf ("Index out of range, please re-enter\n");
}

// Location taken message
void showErrTaken ()
{
  printf ("This location is already taken\n");
}

// Win message
// Parameter: the symbol of the winner
void showWinMessage (char symbol)
{
	printf ("**************************\n");
	printf ("Player %c has won the game\n", symbol);
	printf ("**************************\n");
}

// Draw message
void showGameOverMessage ()
{
	printf ("Game over; there are no winners\n");
}

// Record message
void promptPlayBackGame ()
{
  printf ("\nWould you like to play back the recorded game? (y,n)?");
}

// Replay or exit message
void promptNextOrExit ()
{
  printf ("Next or Exit (n,e)?");
}

// Function to compare cell and symbol
// Also count the number of function calls
int check (int row, int col, char symbol)
{
	__Check_Count++;
	if (grid[row][col] == symbol)
		return 1;
	return 0;
}

// Don't use this function
int peek (int row, int col)
{
	return grid[row][col];
}


// END OF CODE SECTION THAT SHOULD NOT BE CHANGED
// ************************************************

// --------------------------------------------------------------------------------------------------
// GLOBAL VARIABLES
int max_win_length;
int grid_size;
int moveCount;



// END OF SECTION FOR DECLARRING ADDITIONAL GLOBAL VARIABLES
// ----------------------------------------------------------

// -------------------------------------------------------------------------------------------------

// Function to start a new game and initialse everything
int newGame (int gridsize, int winlength)
{
	grid_size=gridsize;
	// Determine the gridsize
	if ( (gridsize<3) || (gridsize>10) ){
		return 0;
	}

	// Determine the winlength
	if( (winlength<3) || (winlength>gridsize) ){
		return 0;

	// Initialise the grid
	}else{
		int i=0,j=0;
    	for(i=0;i<gridsize;i++){
        	for(j=0;j<gridsize;j++){
            	grid[i][j]='.';
        	}
    	}
	}

	return 1;
}

// Function to show the grid

// There is one empty line before the grid to make it stand out from text before it
// The column indices are printed at the top and the first one is indented by exactly one tab (\t); indices are separated by exactly one space
// The row indices are printed at the left followed by exactly one tab (\t)
// The grid symbols are separated by exactly one space
// There is one empty line after the grid to make it stand out from text after it
void showGrid (int gridsize)
{
	// One empty line before the grid
	printf("\n");
	// Print the header
	printf("\t");
	int i=0,j=0;
	for(i=0;i<gridsize;i++){
		printf("%i ",i);
	}
	printf("\n");
	// Print the grid
	for(i=0;i<gridsize;i++){
		printf("%i\t",i);
		for(j=0;j<gridsize;j++){
			printf("%c ",grid[i][j]);
		}
		printf("\n");
    }
	// One empty line after the grid
	printf("\n");
}

// Function to make a move
// Parameters: row, column, symbol
int makeMove(int row, int col, char symbol)
{
	if( (row >=0) && (row <grid_size) && (col >=0) && (col <grid_size) && (grid[row][col]!='X') && 
	(grid[row][col]!='O') && ( (symbol=='X') || (symbol=='O') ) ){
		grid[row][col]=symbol;
		return 1;
	}
	return 0;
	
}

// Function to check if the board is full

int boardIsFull()
{
	int i,j;
	for( i=0;i<grid_size;i++){
		for( j=0;j<grid_size;j++){
			if(grid[i][j]=='.'){
				return 0;
			}
		}
	}
	return 1;
}


// Function to check horizontal
// Parameters: symbol, length
int checkHorizontal (char symbol, int length)
{
	if( (length<3) || (length>grid_size) || ( (symbol!='X') && (symbol!='O') ) ){
		return -1;
	}
	int i=0, j=0;
	int count;
	// Check every row
	for(i=0;i<grid_size;i++){
        count=0;
		// Check every column in every row
		for(j=0;j<grid_size;j++){
			if(grid[i][j]==symbol){
				count++;
			}else{
				count=0;
			}
            if(count==length){
                break;
            }
		}
        if(count==length){
            break;
        }
	}

	if(count==length){
		return 1;
	}else{
		return 0;
	}

}

// Function to check vertical
// Parameters: symbol, length
int checkVertical (char symbol, int length)
{
	if( (length<3) || (length>grid_size) || ( (symbol!='X') && (symbol!='O') ) ){
		return -1;
	}
	int i=0, j=0, k=0;
	int count;
	// Check every column
	for(i=0;i<grid_size;i++){
		count=0;
		// Check every row in every column
		for(j=0;j<grid_size;j++){
			if(grid[j][i]==symbol){
				count++;
			}else{
				count=0;
			}
            if(count==length){
                break;
            }
		}
		if(count==length){
			break;
		}
	}

	if(count==length){
        return 1;
    }else{
        return 0;
    }
}

// Function to check diagonals
// Parameters: symbol, length
int checkDiagonals (char symbol, int length)
{
	if( (length<3) || (length>grid_size) || ( (symbol!='X') && (symbol!='O') ) ){
		return -1;
	}
	int count=0,i=0,j=0,k=0;

	// The starting value goes from (0,0) to horizontal up
	while(j<grid_size){
		i=0;
		k=j;
		count=0;
		// Find the points on the diagonals
		for(;i<grid_size&&k<grid_size;i++,k++){
			if(grid[i][k]==symbol){
				count++;
			}else{
				count=0;
			}

			if(count==length){
				break;
			}
		}

		if(count==length){
			break;
		}
		j++;
	}

	if(count==length){
	return 1;
	}else{
		i=1;
		// The starting value goes from (1,0) to vertical down
		while(i<grid_size){
			j=0;
			k=i;
			count=0;
			// Find the points on the diagonals
			for(;k<grid_size&&j<grid_size;k++,j++){
				if(grid[k][j]==symbol){
					count++;
				}else{
					count=0;
				}
			if(count>=length){
				break;
			}
			}

			if(count==length){
				break;
		}
		i++;
		}

	if(count==length){
		return 1;
	}else{
		return 0;
	}
}

}

// Function to check anti-diagonals
// Parameters: symbol, length
int checkAntiDiagonals (char symbol, int length)
{
	if( (length<3) || (length>grid_size) || ( (symbol!='X') && (symbol!='O') ) ){
		return -1;
	}
	int count=0,i=0,j=grid_size-1,k=0;

	// The starting value goes from (0,gridsize-1) to horizontally down
	while(j>=0){
        i=0;
		k=j;
        count=0;
		// Find the points on the anti-diagonal
		for(;i<grid_size&&k>=0;i++,k--){
			if(grid[i][k]==symbol){
				count++;
			}else{
				count=0;
			}
			if(count==length){
                break;
        	}
		}
		if(count==length){
            break;
        }
		j--;
	}
	if(count==length){
        return 1;
    }else{
		// The starting point goes from (1,gridsize-1) to vertically down
		i=1;
		while(i<=grid_size-1){
            j=grid_size-1;
			k=i;
            count=0;
			for(;k<=grid_size-1&&j>=0;k++,j--){
				if(grid[k][j]==symbol){
					count++;
				}else{
					count=0;
				}
				if(count==length){
					break;
				}
			}
			if(count==length){
				break;
			}
			i++;
		}

		if(count==length){
			return 1;
		}else{
			return 0;
		}
	}
}

// Function to check won
int playerHasWon (char symbol , int length)
{
	if( (length<3) || (length>grid_size) || ( (symbol!='X') && (symbol)!='O') ){
		return -1;
	}
	if(checkHorizontal(symbol,length) || checkVertical(symbol,length) || checkDiagonals(symbol,length) || checkAntiDiagonals(symbol,length)){
		return 1;
	}else{
		return 0;
	}
}

// Function to check won efficiently
// Parameters: row, column of the last move, symbol, length
int effPlayerHasWon (int row, int col, char symbol , int length)
{
	if( (row<0) || (row>grid_size-1) || (col<0) || (col)>grid_size-1 ||( (symbol!='X') && (symbol)!='O') || (length<3) || (length>grid_size)){
		return -1;
	}

	check(row,col,symbol);
	if(checkHorizontal(symbol,length) || checkVertical(symbol,length) || checkDiagonals(symbol,length) || checkAntiDiagonals(symbol,length)){
		return 1;
	}else{
		return 0;
	}


	

	}

// IF YOU NEED ADDITIONAL FUNCTIONS YOU CAN DEFINE THEM BELOW THIS LINE
//----------------------------------------------------------------------
int outOfRange(int row, int col){
    if( (row>grid_size-1) || (col>grid_size-1) || (row<0) || (col<0)){
        return 1;
    }else{
        return 0;
    }
}

int locationTaken(int row, int col)
{
    if(grid[row][col]!='.'){
        return 1;
    }else{
        return 0;
    }
}

// Make move3 function





// DON'T CHANGE THE FOLLOWING 3 LINES
#ifndef TEST
int  main (int argc, char* argv[])
{
	// ENTER THE CODE OF YOUR main FUNCTION BELOW
	
	char symbol;
	int row,col,length;
	int rows[100];
	int cols[100];
	int index=0;
	
	// Enter the gridsize
	promptEnterGridSize ();
	scanf("%i",&grid_size);
	// Enter the win length
	promptEnterWinLength (max_win_length);
	scanf("%i",&max_win_length);
	// Show grid if the 
	newGame(grid_size,max_win_length);
	if(newGame(grid_size,max_win_length)){
		showGrid(grid_size);
	}
	int i=1;
	while(1){
		
		if(i%2==1){
			symbol='X';
		}else
		{
			symbol='O';
		}
		
		promptChooseLocation(symbol);
		scanf("%i,%i",&row,&col);

		while( (outOfRange(row,col)==1) || (locationTaken(row,col)==1)){
			while(outOfRange(row,col)==1){
				showErrIndex();
				promptChooseLocation(symbol);
				scanf("%i,%i",&row,&col);
			}

			while(locationTaken(row,col)==1){
				showErrTaken();
				promptChooseLocation(symbol);
				scanf("%i,%i",&row,&col);
			}
		}
		// Make move
		makeMove(row, col, symbol);
		rows[index]=row;
		cols[index]=col;
		index++;

		// Show grid
		showGrid(grid_size);

		// Check won
		if(playerHasWon(symbol,max_win_length)){
			showWinMessage(symbol);
			break;
		}else if(playerHasWon(symbol,max_win_length)==1){
			showGameOverMessage();
			break;
		}
		i++;
	}
		

	// Show if playback
	index=0;
	// Prompt the playback game
	promptPlayBackGame();
	char flag1;
	flag1='y';
	// Intialise the grid
	newGame(grid_size,max_win_length);
	getchar();
	scanf("%c",flag1);

	// Playback
	if(flag1=='y'){
		makeMove(rows[index],cols[index],'X');
		index++;
		showGrid(grid_size);
		while (1)
		{
			promptNextOrExit();
			getchar();
			char flag2='n';
			scanf("%c",flag2);
			if(flag2=='n'){
				i=1;
				if(i%2==1){
					symbol='O';
				}else{
					symbol='X';
				}
				grid[rows[index]][cols[index]]=symbol;
				index++;
				showGrid(grid_size);
			}else{
				break;
			}
		

		}
	}
	
	

// DON'T CHANGE THE FOLLOWING 3 LINES
  return 0;
}
#endif
// DON'T WRITE ANYTHING BELOW THIS LINE

