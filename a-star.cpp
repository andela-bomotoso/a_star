/* A program to solve the 8 puzzle Game problem using various seach strategies
	CSCI 5350 OLA1
	Author: Bukola Grace Omotoso
	MNummber: 01424979
*/
#include<stdio.h>
#include<cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <array>
#include <algorithm>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;
set <string> closed_list;


int heuristic;
int cost_per_step;
int num_of_steps;
int counter;
int V;
int N;
int depth;
int cur_depth;
string output_str;
int movecount = 0;
float Vs[1000];
float Ns[1000];
float bs[1000];
float ds[1000];
float EuclideanDistance(int board[]);
int initial_board[9];
int current_depth;
string previous;


struct node {
  int nodeid;
  int cost;
  int depth;
  int board[9];
  string prev;

  node(int a, int b, int d, int myboard[], string prev) {
    nodeid = a;
    cost = b;
    depth = d;
    for(int i = 0; i < 9; i++){
    	board[i] = myboard[i];
    }
    prev = prev;

  }

  bool operator<(const node& Rhs) const {
    if (cost < Rhs.cost)
      return true;
    else 
    	if (cost > Rhs.cost)
      return false;
    if (nodeid > Rhs.nodeid)
      return true;
    else
      return false;
  }


  void updatemoves() const	{
  	for(int i = 0; i < 9; i++)	{
		if(i % 3 == 0)
			output_str.append("\n");
		output_str.append(to_string(board[i]));
		output_str.append(" ");
	}
		output_str.append("\n");

  }

  void printDepth(int N) const{
  	 cout << "d="<<depth<<"\n";
  	cout << "b="<<pow(N, (1.0/depth));
  	cout << endl;

  }

  void print() const {
    cout << "Node - id=" << nodeid << " cost=" << cost<<" ";
    for (int i = 0; i < 9; i++){
    	cout<<board[i]<<" ";
        }
    cout<<"\n";

  }

  void cloneBoard (int newBoard[])const	{
	 for (int i = 0 ;i < 9; i++)	{
	 	newBoard[i] = board[i];
	 }
}

int getCurrentDepth() const{
	return depth;
}

int getNodeID() const{
	return nodeid;
}

int getCost() const{
	return cost;
}

string getPrevious() const{
	return prev;
}

  bool isGoalBoard()const	{
	for (int i = 0; i < 9 ; i++)	{
		if(board[i] != i)
			return false;
	}
	return true;
} 
};



struct nodeconnection{
	string child;
	string parent;

	nodeconnection(string thischild, string thisparent)
	{
		child = thischild;
		parent = thisparent;
	}

  bool operator<(const nodeconnection& Rhs) const {
    if (child > Rhs.child)
      return true;
    else 
      return false;
    
  }
};
set<node>set_of_nodes;
set<node>expanded_nodes;

int tilesDisplacedFromGoal(int board[]);
int mahattanFromGoal(int board[]);
float EuclideanDistance(int board[]);	
void printBoard(int board[]);
void swapvalues(int a, int b, int board[]);
int getCost(int board[], int depth);
void moveLeft(int a, int board[]);
void moveRight(int a, int board[]);
void moveUp(int a, int board[]);
void moveDown(int a, int board[]);
void getNeighbours(int board[]);
bool isGoalBoard(int board[] );
string appendCells(int board[]);
void solvePuzzle();
float minimum(float arr[]);
float maximum(float arr[]);
float median(float arr[]);
float mean(float arr[]);
float stdev(float arr[]);
int getUniformCost(int board[]);
int getGreedyCost(int board[]);
void cloneThisBoard(int board[], int newBoard[]);
void stringToBoard(string s);
stack <string> solutionStack; 
set <nodeconnection>set_of_connections;

int main(int argc, char** argv)
{

	
    heuristic = atoi(argv[1]);
    cost_per_step = atoi(argv[2]);
    for(int i = 0; i < 9; i++)
        cin >> initial_board[i];
 
    V = 0;// initial state visited
    N = 0;
    num_of_steps = 0;
    counter = 0;
    depth = 0;
    solvePuzzle();
	return 0;

}

void solvePuzzle()	{
		if(!isGoalBoard(initial_board)){
		node newNode(N, getCost(initial_board, depth), depth, initial_board,"start");
		set_of_nodes.insert(newNode);
		nodeconnection connect(appendCells(initial_board), "start");
		set_of_connections.insert(connect);
	}

	while(!set_of_nodes.empty()){
       V++; 

	if(set_of_nodes.begin()->isGoalBoard())	{
		cout<<"V="<<V<<"\n";
	    cout<<"N="<<N<<"\n";
		set_of_nodes.begin()->printDepth(N);
		set_of_nodes.begin()->updatemoves();
		int newBoard[9];	
		set_of_nodes.begin()->cloneBoard(newBoard);
		string child, parent;
		solutionStack.push(appendCells(newBoard));
		solutionStack.push(previous);
		std::set<nodeconnection>::iterator it;
		do{
			  for (it=set_of_connections.begin(); it!=set_of_connections.end(); ++it){
					if(previous == it->child){
						solutionStack.push(it->parent);
						previous = it->parent;
						break;
					}
			}
		}
			while(previous != "start");
		
		solutionStack.pop();
	while(!solutionStack.empty())
	{
    	string s  = solutionStack.top();
    	solutionStack.pop();
    	stringToBoard(s);
}		
		break;
	}
	int newBoard[9];
	set_of_nodes.begin()->cloneBoard(newBoard);
	set_of_nodes.begin()->updatemoves();
	current_depth =  set_of_nodes.begin()->getCurrentDepth();
	string cur_prev = set_of_nodes.begin()->getPrevious();
	set_of_nodes.erase(set_of_nodes.begin());
	closed_list.insert(appendCells(newBoard));
	previous = appendCells(newBoard);
	getNeighbours(newBoard);	

}

}

void getNeighbours(int board[])	{
	depth = current_depth+1;

	int a = std::distance(board, std::find(board, board + 9, 0));
	 // check indexZero does not locates on the leftmost col
	 if((a % 3) != 0){
	 	int neighbourBoard[9];
	 	cloneThisBoard(board, neighbourBoard);
	 	moveLeft(a, neighbourBoard);
	 	const bool is_in = closed_list.find(appendCells(neighbourBoard)) != closed_list.end();
	 	if(!is_in){
	 			node newNode(N, getCost(neighbourBoard, depth), depth, neighbourBoard,previous);
	 		 set_of_nodes.insert(newNode);
	 		 nodeconnection connect(appendCells(neighbourBoard), previous);
	 		 set_of_connections.insert(connect);                                                   
	 		 	N++;
	 	}
	 
	 }

	 // check indexZero does not locates on the rightmost col
	  if(((a+1) % 3) != 0){
      int neighbourBoard[9];
	 cloneThisBoard(board, neighbourBoard);
	 moveRight(a, neighbourBoard);
	 	const bool is_in = closed_list.find(appendCells(neighbourBoard)) != closed_list.end();
	 	if(!is_in){
	 		node newNode(N, getCost(neighbourBoard, depth), depth, neighbourBoard,previous);
	 		set_of_nodes.insert(newNode);
	 		nodeconnection connect(appendCells(neighbourBoard), previous);
	 		 set_of_connections.insert(connect);     
	 		N++;

	 	}
	  }


	// check indexZero does not locates at the top row
	  if(a > 2){
	  	int neighbourBoard[9];
	 	cloneThisBoard(board, neighbourBoard);
	 	moveUp(a, neighbourBoard);
	 	const bool is_in = closed_list.find(appendCells(neighbourBoard)) != closed_list.end();
	 	if(!is_in){
	 		node newNode(N, getCost(neighbourBoard, depth), depth, neighbourBoard, previous);
	 		set_of_nodes.insert(newNode);
	 		nodeconnection connect(appendCells(neighbourBoard), previous);
	 		 set_of_connections.insert(connect);     
	 		 	 	N++;

	 	}
	  }

	 // check indexZero does not locates on the bottom col
	  if( a < 6){
	  	int neighbourBoard[9];
	 	cloneThisBoard(board, neighbourBoard);
	 	moveDown(a, neighbourBoard);
	 	const bool is_in = closed_list.find(appendCells(neighbourBoard)) != closed_list.end();
	 	if(!is_in){
	 		node newNode(N, getCost(neighbourBoard, depth), depth, neighbourBoard, previous);
	 		set_of_nodes.insert(newNode);
			nodeconnection connect(appendCells(neighbourBoard), previous);
	 		 set_of_connections.insert(connect);     
	 		N++;                                                                                                                        
	 	}
	  }
}

int tilesDisplacedFromGoal(int board[])	{
	int counter = 0;
	for(int i = 0; i < 9; i++){
		if(board[i]==0)
			continue;
		if(board[i] != i )
			counter++;
	}
	return counter;
}

int mahattanFromGoal(int board[])	{                                                                   
	    int counter = 0;
	    int num = 0;
        int exprow = 0;   // expected row
        int expcol = 0; // expected column
        int manhattancount = 0;
        int current = 0;
        for(int i =0; i<9; i++)

            {
                num = board[i];
                if(num == 0)
                    continue;

                exprow = (num)/3;
                if(num % 3 ==0)
                    expcol = 0;
                else
                    expcol = (num % 3)  ;

                int current_row = i / 3;
                int current_col = i % 3;

                current = abs(exprow-current_row)+ abs(expcol-current_col);
                manhattancount += current;
            }

        return manhattancount;
}

float EuclideanDistance(int board []){
	float x1, y1, x2, y2,  dist = 0.0;
	int xdistances[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
	int ydistances[] = {1, 1, 1, 0, 0, 0, -1, -1, -1};

	for(int i = 0; i < 9; i++){
	int idx = std::distance(board, std::find(board, board + 9, i));
	x1 = xdistances[idx];
	y1 = ydistances[idx];
	x2 = xdistances[board[i]];
	y2 = ydistances[board[i]];

	float ycord = (y2-y1)*(y2-y1);
	float xcord = (x2 - x1) *(x2-x1);

	dist =  dist + sqrt(ycord + xcord);

}
	return dist;
}

void printBoard(int board[])	{
	for(int i = 0; i < 9; i++)	{
		if(i % 3 == 0)
			cout<<"\n";
		cout << board[i] <<" ";
	}
	cout<<" \n";
}

void cloneThisBoard(int board[], int newBoard[])	{
	 for (int i = 0 ;i < 9; i++)	{
	 	newBoard[i] = board[i];
	 }
}

void moveLeft(int a, int board[]){
	swapvalues(a, (a-1), board);
}

void moveRight(int a, int board[])	{
	swapvalues(a, (a+1), board);
}

void moveUp(int a, int board[]){
	swapvalues(a, (a-3), board);
}

void moveDown(int a, int board[])	{
	swapvalues(a, (a+3), board);
}

void swapvalues(int a, int b, int board[])	{
int temp = board[a];
board[a] = board[b];
board[b] = temp;
}

int getCost(int board[], int depth)	{
	if (heuristic == 0){
		return depth*cost_per_step;
	}
	else if(heuristic == 1){

		return ( tilesDisplacedFromGoal(board) + (cost_per_step*depth));
	}
	else if (heuristic == 2){ 
		return (mahattanFromGoal(board) + (cost_per_step*depth));
	}else 
		return(EuclideanDistance(board) + (cost_per_step*depth));
}

int getUniformCost(int board[], int depth)	{
	return (cost_per_step*depth);
}

int getGreedyCost(int board[], int depth)	{
	if (heuristic == 0){
		return 0;
	}
	else if(heuristic == 1){

		return ( tilesDisplacedFromGoal(board));
	}
	else if (heuristic == 2){
		return (mahattanFromGoal(board));
	}else 
		return(EuclideanDistance(board));
}


bool isGoalBoard(int board[])	{
	for (int i = 0; i < 9 ; i++)	{
		if(board[i] != i)
			return false;
	}
	return true;
} 

string appendCells(int board[]){
std::string str;
	for (int i = 0 ; i < 9; i++)
		str.append(to_string(board[i]));
	return str;
}

void stringToBoard(string str){
	for (int i = 0; i < 9; i++){
		if((i % 3) == 0)
			cout<<endl;
		std::cout << str.at(i)<<" ";
		
	}
	cout<<endl;
}






