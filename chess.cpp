#include <iostream>
#include "pieces.cpp"
#include "gameboard.cpp"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool white_resigns = false;
bool black_resigns = false;


bool gameOver(){

	//Check if game over, if not over process nextTurn;

	static int count = 0;

	count++;
	if ((count % 2) == 0 ){
		cout << endl << "Black's Move: ";
	}
	else{
		cout <<  endl << "White's Move: ";
	}

	if (count < 50) { // 50 turns for testing
		return false;
	}

	return true;

}

void play(Gameboard* board){
	std::string input, token, src, dst, prmt;
	vector<string> tokens;
	int current_player = 0; 


	cout << "Welcome to Chess." << endl << endl;
	printBoard (board);
	
	while ( !gameOver() ){

		//Take in input, need 3rd for promoting 
		//cin >> src >> dst >> prmt;

		getline(cin, input);
		//cout << input << endl;
		istringstream iss(input);

		while (iss >> token)tokens.push_back(token);
		//cout << "tokens: " << tokens.size() << endl;

		

		if (tokens.size() > 3){ cout << "Incorrect Usage." << endl;}
		else if (tokens.size() == 2){
			
		//Check if valid move.
		
		/* 1. Needs to be valid source (player owned piece)
		   2. Destination not occupied by own piece
		*  3. Path is clear

		*

		*/

		}
		//Player has quit
		else if(tokens.size() == 1){
			if (tokens[0] == "resign") {
				cout << "Game Over" << endl;
			}			
		}
		cout << endl;

		//
		tokens.clear();
		printBoard (board);


	}


}



int main(){

	Gameboard* board = new Gameboard();
	play(board);


	return 0;
} 