#include "pieces.cpp"

#define white 0
#define	black 1


class Gameboard {
	Piece* board[8][8];
	int turn;
	bool whites_turn = true;


public:
	Gameboard(){
		turn = 0;


		//Spawn Black Pieces
		board[0][0] = new Rook(black);
		board[0][1] = new Knight(black);
		board[0][2] = new Bishop(black);
		board[0][3] = new Queen(black);
		board[0][4] = new King(black);
		board[0][5] = new Bishop(black);
		board[0][6] = new Knight(black);
		board[0][7] = new Rook(black);
		
		board[1][0] = new Pawn(black);
		board[1][1] = new Pawn(black);
		board[1][2] = new Pawn(black);
		board[1][3] = new Pawn(black);
		board[1][4] = new Pawn(black);
		board[1][5] = new Pawn(black);
		board[1][6] = new Pawn(black);
		board[1][7] = new Pawn(black);


		//Spawn White Pieces
		board[7][0] = new Rook(white);
		board[7][1] = new Knight(white);
		board[7][2] = new Bishop(white);
		board[7][3] = new Queen(white);
		board[7][4] = new King(white);
		board[7][5] = new Bishop(white);
		board[7][6] = new Knight(white);
		board[7][7] = new Rook(white);

		board[6][0] = new Pawn(white);
		board[6][1] = new Pawn(white);
		board[6][2] = new Pawn(white);
		board[6][3] = new Pawn(white);
		board[6][4] = new Pawn(white);
		board[6][5] = new Pawn(white);
		board[6][6] = new Pawn(white);
		board[6][7] = new Pawn(white);

	}

	void print(int i, int j){
		if (board[i][j] != nullptr){
			cout << *(board[i][j]);
		}
		else if ((i+j)%2 == 0 ){
			cout << "##";
		}
		else cout << "  ";
	}

	void changePlayer() { whites_turn = !whites_turn; }

	bool tryMove(int file0, int rank0, int file1, int rank1){
		cout << "trying move" << endl;
		if (board[file0][rank0]->getColor() && !whites_turn){
			cout << "player owned piece" << endl;
			return true;
		}
		return false;
	}

};



void printBoard(Gameboard* board) {

	for (int i = 7; i > -1; i--){
		for (int j = 0; j < 8; j++){

			board->print(i,j);
			if (i < 8) (cout << " ");

		}

		cout << i+1 << endl;
	}
	cout << " a  b  c  d  e  f  g  h" << endl << endl;;
}