#include <iostream>
#include "pieces.cpp"
#include "gameboard.cpp"
#include <string>

using namespace std;

bool white_resigns = false;
bool black_resigns = false;


bool gameOver(){
	static int count = 0;

	count++;
	cout << "turn: " << count << endl;
	if (count < 50) { // 50 turns for testing
		return false;
	}

	return true;

}

void play(Gameboard* board){
	std::string src, dst;
	int current_player = 0; 


	cout << "Welcome to Chess." << endl << endl;
	printBoard (board);
	
	while ( !gameOver() ){

		//Take in input, need 3rd for promoting 
		cin >> src >> dst >> prmt;

		//

		//Check if valid move.
		
		/* 1. Needs to be valid source (player owned piece)
		   2. Destination not occupied by own piece
		*  3. Path is clear

		*

		*/
		printBoard (board);


	}


}



int main(){

	Gameboard* board = new Gameboard();
	play(board);


	return 0;
} 