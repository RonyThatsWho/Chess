
#include <pieces.cpp>

#define white 0
#define	black 1


 

class Gameboard{
	Piece board[8][8] ;
	int turn;

	Gameboard(){
		turn = 0;
		//Spawn Black Pieces
		board[0][0] = new rook(black);
		board[0][1] = new rook(black);
		board[0][2] = new rook(black);
		board[0][3] = new rook(black);
		board[0][4] = new rook(black);
		board[0][5] = new rook(black);
		board[0][6] = new rook(black);
		board[0][7] = new rook(black);
		
		board[1][0] = new pawn(black);
		board[1][1] = new pawn(black);
		board[1][2] = new pawn(black);
		board[1][3] = new pawn(black);
		board[1][4] = new pawn(black);
		board[1][5] = new pawn(black);
		board[1][6] = new pawn(black);
		board[1][7] = new pawn(black);



		//Spawn White Pieces
		board[7][0] = new rook(white);
		board[7][1] = new rook(white);
		board[7][2] = new rook(white);
		board[7][3] = new rook(white);
		board[7][4] = new rook(white);
		board[7][5] = new rook(white);
		board[7][6] = new rook(white);
		board[7][7] = new rook(white);


		board[6][0] = new pawn(white);
		board[6][1] = new pawn(white);
		board[6][2] = new pawn(white);
		board[6][3] = new pawn(white);
		board[6][4] = new pawn(white);
		board[6][5] = new pawn(white);
		board[6][6] = new pawn(white);
		board[6][7] = new pawn(white);



	}



}