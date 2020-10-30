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

	//cout << f << " " << r << endl;

	if ( ('a' <= f) && (f <= 'h') ){
		file = f - 'a';
	}
	else return false;

	if ( ('0' < r) && (r <= '8') ){
		rank = r - '1';
	}
	else return false;

	return true;
}

bool validInput(string src, string dst, int turn){

 return true;
}


// bool gameOver(Gameboard* board){

// 	//Check if game over, if not over process nextTurn;

// 	static int count = 0;

// 	count++;

// 	if ((count % 2) == 0 ){
// 		cout << endl << "Black's Move: ";
// 	}
// 	else{
// 		cout <<  endl << "White's Move: ";
// 	}
// 	board->changePlayer();

// 	if (count < 50) { // 50 turns for testing
// 		return false;
// 	}

// 	return true;

// }

void play(Gameboard* board){
	std::string input, token, src, dst, prmt;
	vector<string> tokens;
	int current_player = 0; 


	cout << "Welcome to Chess." << endl << endl;
	board->printBoard_();
	
	
	while ( !(board->isGameOver() ) ){

		board->currentPlayer();

		//Take in input, Strings pushed to vector
		getline(cin, input);
		istringstream iss(input);
		while (iss >> token)tokens.push_back(token);

		

		if (tokens.size() > 3){ cout << "Incorrect Usage." << endl;}
		else if (tokens.size() == 2){
			
		//Check if input valid, and then convert to positions
			if( (tokens[0].length() == 2) && (tokens[0].length() == 2 && (tokens[0] != tokens[1])) ){
				cout << "\033[;32mValid Length, Parsing Input... \033[0m" << endl;
				

				int file0, rank0, file1, rank1;


				if (parseInput(tokens[0], file0, rank0) && parseInput(tokens[1], file1, rank1)){
				// This point forward should be part of gameboard

					if (board->tryMove_(file0,rank0,file1,rank1)){  //if move valid change player
						board->changePlayer();  //Board should be changing player....
					}
					else { //Move Failed, Need to try again? Loop back to taking input

					}

				}
				

				//input needs to be in range

			//Check if valid move.
			/*  1. Needs to be valid source (player owned piece)
			 *  2. Destination not occupied by own piece
			 *  3. Path is clear
			 *
			 */




			}


			else if (tokens[0] == "pos"){
				int rank;
				int file;
				parseInput(tokens[1], file, rank);
				std::cout << file << " // " << rank << std::endl;

				
			}	
			else { //invalid input

				cout << "invalid" << endl;
			}


		}
		else if (tokens[0] == "valid"){
			//valid placement test

			int rank0;
			int file0;
			int file1;
			int rank1;
			string result = "false";

			parseInput(tokens[1], file0, rank0);
			parseInput(tokens[2], file1, rank1);

			Piece * src = board->board[file0][rank0];

			if (board->validPlacement(src, file1,rank1)){
				result = "true";
			}

			cout << "move: " << result << endl;

		}


		//Player has quit
		else if(tokens.size() == 1){
			if (tokens[0] == "resign") {
				board->resign();
			}

		}
		cout << endl;

		//
		tokens.clear();
		//printBoard (board);


	}


}



int main(){

	Gameboard* board = new Gameboard();
	play(board);

	return 0;
} 