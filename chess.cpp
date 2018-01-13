#include <iostream>
#include "pieces.cpp"
#include "gameboard.cpp"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool white_resigns = false;
bool black_resigns = false;




bool parseInput(string input, int &file, int &rank ){
	char f = input[0];
	char r = input[1];

	cout << f << " " << r << endl;

	if ( ('a' <= f) && (f <= 'h') ){
		file = f - 'a';
	}
	else return false;

	if ( ('0' < r) && (r < '8') ){
		rank = r - '1';
	}
	else return false;

	return true;
}

bool validInput(string src, string dst, int turn){

 return true;
}


bool gameOver(Gameboard* board){

	//Check if game over, if not over process nextTurn;

	static int count = 0;

	count++;

	if ((count % 2) == 0 ){
		cout << endl << "Black's Move: ";
	}
	else{
		cout <<  endl << "White's Move: ";
	}
	board->changePlayer();

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
	
	while ( !gameOver(board) ){

		//Take in input, Strings pushed to vector
		getline(cin, input);
		istringstream iss(input);
		while (iss >> token)tokens.push_back(token);

		

		if (tokens.size() > 3){ cout << "Incorrect Usage." << endl;}
		else if (tokens.size() == 2){
			
		//Check if input valid, and then convert to positions
			if( (tokens[0].length() == 2) && (tokens[0].length() == 2) ){
				cout << "Both Good " << endl;
				//cout <<  tokens[0][0]  << "   " << tokens[0][1] << endl;

				int file0, rank0, file1, rank1;
				if (parseInput(tokens[0], file0, rank0) && parseInput(tokens[1], file1, rank1)){
					board->tryMove(file0,rank0,file1,rank1);

				}
				

				//input needs to be in range

			//Check if valid move.
			/*  1. Needs to be valid source (player owned piece)
			 *  2. Destination not occupied by own piece
			 *  3. Path is clear
			 *
			 */




			}
			else { //invalid input

				cout << "invalid" << endl;
			}


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