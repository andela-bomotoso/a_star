/* A program to solve the 8 puzzle Game problem using various seach strategies
	CSCI 5350 OLA1
	Author: Bukola Grace Omotoso
	MNummber: 01424979
*/

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

void move();
void swapvalues(int a, int b);
void printBoard();
bool isFirstColum(int a);
bool isLastColumn(int a);
bool isFirstRow(int a);
bool isLastRow(int a);

int board[9];
void move(){
	int move = int((4.0*random()) / (RAND_MAX + 1.0));
	int a = std::distance(board, std::find(board, board + 9, 0));
	int b;

	if(isFirstColum(a))	{ //cannot move to the left
		if(isFirstRow(a)) { //cannot move to the left and top
			move = move%2;
			if (move == 0) //move right
				b = a + 1;
			else
				b = a + 3; //move down
		}

		else if(isLastRow(a))	{
			move = move%2;
			if (move == 0) //move right
				b = a + 1;
			else
				b = a - 3; //move up
		} else{
			move = move%3;
			if(move == 0)
				b = a + 1; //move right
			else if(move ==1)
				b = a - 3; //move up
			else
				b = a + 3; //move down
		}

	}else if(isLastColumn(a))	{
		if(isFirstRow(a)) { //cannot move to the left and top
			move = move%2;
			if (move == 0) //move left
				b = a - 1;
			else
				b = a + 3; //move down
		}

		else if(isLastRow(a))	{
			move = move%2;
			if (move == 0) //move left
				b = a - 1;
			else
				b = a - 3; //move up
		} else{
			move = move%3;
			if(move == 0)
				b = a - 1; //move left
			else if(move ==1)
				b = a - 3; //move up
			else
				b = a + 3; //move down
		}
	}	else{
		if(isFirstRow(a))	{
			move = move % 3;
			if(move == 0)
				b = a - 1; //move left
			else if(move == 1)
				b = a + 1; //move right
			else
				b = a  + 3; //move down
		}	else if(isLastRow(a))	{
			if(move == 0)
				b = a - 1; //move left
			else if(move == 1)
				b = a + 1; //move right
			else
				b = a  - 3; //move up
		}	else{
				if (move == 0)
					b =  a - 1; //move left;
				else if(move == 1)
					b =  a + 1; //move right
				else if (move == 2)
					b =  a - 3; //move up
				else
					b = a + 3; //move down
		}
	}
   	swapvalues(a, b);
}

void swapvalues(int a, int b)	{
int temp = board[a];
board[a] = board[b];
board[b] = temp;
}

void printBoard()	{
	for(int i = 0; i < 9; i++)	{
		if(i % 3 == 0)
			cout<<"\n";
		cout << board[i] <<" ";
	}
	cout<<" \n";
}


int tilesDisplacedFromGoal()	{
	int counter = 0;
	for(int i = 0; i < 9; i++){
		if( board[i] == 0)
			continue;
		if(board[i] != i )
			counter++;
	}
	return counter;
}


bool isFirstRow(int a){
	return a < 3;
}

bool isLastRow(int a){
	return a >= 6 && a <= 8;
}

bool isFirstColum(int a)
{
	return a % 3 == 0;
}

bool isLastColumn(int a){
	return (a + 1) % 3 == 0;
}



int main(int argc, char** argv)
{
	int seed = atoi(argv[1]);
	int moves = atoi(argv[2]);
	srandom(seed);

	for(int i = 0; i < 9; i++)
		cin >> board[i];
	for(int i = 1; i <= moves; i++){
		move();
	}
	  printBoard();

return 0;
}
