#include "pieces.cpp"

#define white true
#define	black false

// typedef struct move{
// 	int file0;
// 	int rank0;
// 	int file1;
// 	int rank1;

// } Move;


typedef enum{
	NW,
	N,
	NE,
	E,
	SE,
	S,
	SW,
	W
} Direction;



class Gameboard {
	//Piece* board[8][8];
	int turn;
	bool whites_turn;
	bool gameOver;
	bool drawAvailable;
	bool isWhiteWinner;
	bool draw;




public:
	Piece* board[8][8];

	Gameboard(){ //Initialize new game
		turn = 0;
		whites_turn = true;
		gameOver = false;

		//Board[file?][rank?]
		//Spawn Black Pieces
		board[0][7] = new Rook(black);
		board[1][7] = new Knight(black);
		board[2][7] = new Bishop(black);
		//board[3][7] = new Queen(black);
		board[4][7] = new King(black);
		board[5][7] = new Bishop(black);
		board[6][7] = new Knight(black);
		board[7][7] = new Rook(black);
		
		board[0][6] = new Pawn(black, 0, 6);
		board[1][6] = new Pawn(black, 1, 6);
		board[2][6] = new Pawn(black, 2, 6);
		board[3][6] = new Pawn(black, 3, 6);
		board[4][6] = new Pawn(black, 4, 6);
		board[5][6] = new Pawn(black, 5, 6);
		board[6][6] = new Pawn(black, 6, 6);
		board[7][6] = new Pawn(black, 7, 6);


		//Spawn White Pieces
		board[0][0] = new Rook(white);
		board[1][0] = new Knight(white);
		board[2][0] = new Bishop(white);
		//board[3][0] = new Queen(white);
		board[4][0] = new King(white);
		board[5][0] = new Bishop(white);
		board[6][0] = new Knight(white);
		board[7][0] = new Rook(white);

		board[0][1] = new Pawn(white, 0, 1);
		board[1][1] = new Pawn(white, 1, 1);
		//board[2][1] = new Pawn(white, 2, 1);
		board[3][1] = new Pawn(white, 3, 1);
		board[4][1] = new Pawn(white, 4, 1);
		board[5][1] = new Pawn(white, 5, 1);
		board[6][1] = new Pawn(white, 6, 1);
		board[7][1] = new Pawn(white, 7, 1);


		//TESTING
		board[2][1] = new Queen(white, 2, 1);
		board[5][4] = new Queen(black, 5, 4);

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


	int vectorize(int vector){
		//cout <<"vectorize: " << vector << ", abs: " << abs(vector) << endl;
		if (vector == 0) return 0;

		vector = vector / abs(vector);

		//cout << "vectorized: " << vector << endl;

		return vector;
	}

	Direction pathDirection(int fileDif, int rankDif){

		int fileVector = vectorize(fileDif);
		int rankVector = vectorize(rankDif);

		Direction direction;

		switch (fileVector){

			case (-1):
				if (rankVector == -1){ direction = NW; break;}
				else if (rankVector == 0){ direction = W; break;}
				else if (rankVector == 1){ direction = SW; break;}
			case (0):
				if (rankVector == -1){ direction = N; break;}
				else if (rankVector == 1){ direction = S; break;}
			case (1):
				if (rankVector == -1){ direction = NE; break;}
				else if (rankVector == 0){ direction = E; break;}
				else if (rankVector == 1){ direction = SE; break;}

		}

		return direction;

	}


	bool isPathClear(Piece* src, int file, int rank){
		

		if (src->getType() == "N") return true;

		int fileVector = vectorize(file-src->getFile());
		int rankVector = vectorize(rank-src->getRank());

		int fileCheck = src->getFile() + fileVector;
		int rankCheck = src->getRank() + rankVector;

		while ((fileCheck != file) && (rankCheck != rank) ){
			cout << "check path .... " << fileCheck << "  " << rankCheck << endl;
			if (board[fileCheck][rankCheck] != nullptr){
				cout << "square: "<< fileCheck <<"  " << rankCheck << " not NULL" << endl;
				printSquare(fileCheck,rankCheck);
				cout << endl;
				return false;
			}
			fileCheck += fileVector;
			rankCheck += rankVector;

		}
		cout << "PATH CLEAR!" << endl;

		return true;
	}



	// 	bool isPathClear(int file, int rank){
	// //bool isPathClear(Move move){

	// 	/*
	// 		Need to determine movement type based on Piece type and Destination
	// 		Horizontal, Vertical, Diagnal or L-Shape

	// 		input is destination

	// 		Need to have pointer to Board

	// 	*/

	// 	// int file = move.file1;
	// 	// int rank = move.rank1;

	// 	bool vert;
	// 	bool hor;
	// 	std::cout << "isPathClear() Pieces Line 43: " << file-m_file << " " << rank-m_rank << std::endl;
	// 	std::cout << "\tSource: " << m_file << " // " << m_rank << std::endl;
	// 	std::cout << "\tDest: " << file << " // " << rank << std::endl;




	// 	int vertDif = file-m_file;
	// 	int horDif = rank-m_rank;


	// 	//Vertical Movement Check
	// 	if (vertDif){
	// 		bool vert = true;
	// 		std::cout << "vert true" << std::endl;
	// 	}

	// 	//Horizontal Movement Check
	// 	if (horDif){
	// 		bool hor = true;
	// 		std::cout << "hor true" << std::endl;
	// 	}

	// 	if (vert && hor){ // Diag movement
	// 		if(vertDif == horDif ){
	// 			//check positions

	// 		}
	// 	}

	// 	// 
	// 	else if (1){
	// 		cout << " No condition. "  << endl; 
	// 	}



	// 	return true;

	// }



bool validFile(int fileMoveset, int file){
	switch (fileMoveset){
		case 0:
			if (file == 0) return true;
			else return false;
		case 1:
			if (abs(file) == 1) return true;
			else return false;
		case 2:
			if (abs(file) == 2) return true;
			else return false;
		default:
			return true;
	}
}

bool validRank(int rankMoveset, int rank){
	if (!whites_turn) { rank = -rank;}

	switch (rankMoveset){
		case -2:
			if (abs(rank) == 2) return true;
			else return false;
			break;

		case -1:
			if (abs(rank) == 1) return true;
			else return false;
			break;

		case 0:
			if (rank == 0) return true;
			else return false;
			break;

		case 1:
			if (abs(rank) == 1) return true;
			else return false;
			break;

		case 2:
			if (rank == 2) return true;
			else return false;
			break;

		default:
			return true;
	}
}




bool validPlacement (Piece* src, int file, int rank){ 

	int fileDif = src->getFile()-file;
	int rankDif = src->getRank()-rank;

	cout << "fileDif: " << fileDif << ", rankDif: " << rankDif << endl;

	for (auto rule: src->getRules()){
		if (validFile(rule.fileRule ,fileDif) && validRank(rule.rankRule, rankDif) ){

			switch(rule.diagRule){
				case 0:
					if (fileDif == 0 || rankDif == 0) return true;
					break;

				case 1:
					if ( abs(fileDif)  == abs(rankDif) ) return true;
					break;

				case 2:
					return true;
				default:
					return true;

			}

		}



	}
	return false;	

}


	bool moveTo(Piece* src, Piece* dst){
		std::cout << "\033[1;32mmove_to(): Piece Line 93\033[0m " << std::endl;
		if (dst == nullptr){
			std::cout << "\033[1;36mEmpty Square,Need To Check Path\033[0m" << std::endl;

			
			// if (isPathClear(m_rank, m_file)){
			// //if (isPathClear(move)){

			// 	cout << "Board Passed in Move Structure" << endl;

			// 	//if true then movePiece.
			// 	//board points to piece
			// 	//old board location points to null.
			// }

		}
		else if (dst->isWhite() != whites_turn){
			std::cout <<  "\033[1;36mEnemy Piece Check Path \033[0m" << std::endl;
		}
		else {
			std::cout << "\033[1;33mOwn Piece -> Castle Attempt?\033[0m" << std::endl;
			if ((src->getType() == "K") && (dst->getType() == "R") ){
				//Need to cast and call castle
				//return (dynamic_cast<King*>(this))->castle(dst);


			}
			else {
				std::cout << "\033[1;31mTargeting Own Piece, Cannot Castle\033[0m" << std::endl;
				return false;
			}
		}

		return true;

	}


	bool tryMove(int file0, int rank0, int file1, int rank1){
		//Basic checks to see if Piece owner

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

			//You are Piece owner, Is move within Rules
			if (!validPlacement(src, file1, rank1)){
				cout << "\033[1;31mtryMove(): validPlacement(), Movement breaks Piece rules \033[0m" << endl;
				return false;
			}

			//Is Path Clear
			if (!isPathClear(src, file1, rank1)){
				cout << "\033[1;31mtryMove(): isPathClea(), Path Not Clear \033[0m" << endl;
			}


			//redundant? could prob just directly return the return, but no logs possibly?
			//
			if (moveTo(src, dst)){
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