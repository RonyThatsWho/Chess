#include <iostream>
#include "pieces.cpp"
#include "gameboard.cpp"
#include <string>

using namespace std;


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

		cin >> src >> dst;
		printBoard (board);


	}


}



int main(){

	Gameboard* board = new Gameboard();
	play(board);


	return 0;
} 