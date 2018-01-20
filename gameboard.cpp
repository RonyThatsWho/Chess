#include "pieces.cpp"

#define white true
#define	black false

struct move{
	int file0;
	int rank0;
	int file1;
	int rank1;

} 

class Gameboard {
	Piece* board[8][8];
	int turn;
	bool whites_turn;
	bool gameOver;
	bool drawAvailable;
	bool isWhiteWinner;
	bool draw;


public:
	Gameboard(){ //Initialize new game
		turn = 0;
		whites_turn = true;
		gameOver = false;


		//Spawn Black Pieces
		board[0][7] = new Rook(black);
		board[1][7] = new Knight(black);
		board[2][7] = new Bishop(black);
		board[3][7] = new Queen(black);
		board[4][7] = new King(black);
		board[5][7] = new Bishop(black);
		board[6][7] = new Knight(black);
		board[7][7] = new Rook(black);
		
		board[0][6] = new Pawn(black);
		board[1][6] = new Pawn(black);
		board[2][6] = new Pawn(black);
		board[3][6] = new Pawn(black);
		board[4][6] = new Pawn(black);
		board[5][6] = new Pawn(black);
		board[6][6] = new Pawn(black);
		board[7][6] = new Pawn(black);


		//Spawn White Pieces
		board[0][0] = new Rook(white);
		board[1][0] = new Knight(white);
		board[2][0] = new Bishop(white);
		board[3][0] = new Queen(white);
		board[4][0] = new King(white);
		board[5][0] = new Bishop(white);
		board[6][0] = new Knight(white);
		board[7][0] = new Rook(white);

		board[0][1] = new Pawn(white);
		board[1][1] = new Pawn(white);
		board[2][1] = new Pawn(white);
		board[3][1] = new Pawn(white);
		board[4][1] = new Pawn(white);
		board[5][1] = new Pawn(white);
		board[6][1] = new Pawn(white);
		board[7][1] = new Pawn(white);

	}

	void printSquare(int i, int j){
		if (board[i][j] != nullptr){
			cout << *(board[i][j]);
		}
		else if ((i+j)%2 == 0 ){
			cout << "##";
		}
		else cout << "  ";
	}

	void printBoard() {
		cout << endl;
		for (int j = 7; j > -1; j--){
			for (int i = 0; i < 8; i++){

				printSquare(i,j);
				if (i < 8) (cout << " ");

			}

			cout << j+1 << endl;
		}
		cout << " a  b  c  d  e  f  g  h" << endl << endl;;
	}

	void changePlayer() { 
		whites_turn = !whites_turn;
		turn++;

		printBoard();

	}

	void currentPlayer(){

		if (whites_turn){
			cout << "White's Move: " ;
		}
		else{
			cout << "Black's Move: ";
		}

	}

	bool tryMove(int file0, int rank0, int file1, int rank1){
		cout << "\033[1;32mtryMove() - Gameboard line 116:\033[0m " << endl;
		//cout << "fileRank on Board" << endl;
		Piece* src = board[file0][rank0];
		if (src == nullptr){
			cout << "\033[1;31mtryMove(): returning false (source is null)\033[0m" << endl;
			return false; 
		}


		cout << "Chosen Piece: " << *src << endl;
		Piece* dst = board[file1][rank1];
		cout << "Player Color: " << src->isWhite() << ", Piece Color: " << whites_turn << endl;
		if (src->isWhite() == whites_turn){	
			if (src->moveTo(dst, whites_turn)){
				return true;
			}

			cout << "\033[1;31mtryMove(): moveTo returned false (invalid dest?)\033[0m" << endl;
			return false;
		}
		cout << "\033[1;31mtryMove(): returning false (not piece owner)\033[0m" << endl;
		return false;
	}

	void resign(){
		if(!whites_turn){
			isWhiteWinner = true;
		}

		gameOver = true;
	}

	bool isGameOver(){
		if (gameOver){
			cout << "Game Over!" << endl;

			if (isWhiteWinner){
				cout << "White Wins!" << endl;
			}
			else if (draw){
				cout << "Draw!" << endl;
			}
			else{
				cout << "Black Wins!" << endl;
			}
		}

	return gameOver;
	}



};