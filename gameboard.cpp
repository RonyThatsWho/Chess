#include "pieces.cpp"
#include <stack>

#define white true
#define	black false

typedef struct move{
	Piece* src;
	Piece* dst;

	int file;
	int rank;

} Move;



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

	Move lastMove;
	stack<Move> moves;


	Piece* whiteKing;
	Piece* blackKing;


public:
	//Currently Public for testing
	Piece* board[8][8];

	Gameboard(){ //Initialize new game
		turn = 0;
		whites_turn = true;
		gameOver = false;

		//Board[file?][rank?]
		//Spawn Black Pieces
		board[0][7] = new Rook(black, 0 ,7);
		board[1][7] = new Knight(black, 1, 7);
		board[2][7] = new Bishop(black, 2, 7);
		board[3][7] = new Queen(black, 3, 7);
		board[4][7] = new King(black, 4, 7);
		board[5][7] = new Bishop(black, 5, 7);
		board[6][7] = new Knight(black, 6, 7);
		board[7][7] = new Rook(black, 7, 7);
		
		board[0][6] = new Pawn(black, 0, 6);
		board[1][6] = new Pawn(black, 1, 6);
		board[2][6] = new Pawn(black, 2, 6);
		board[3][6] = new Pawn(black, 3, 6);
		board[4][6] = new Pawn(black, 4, 6);
		board[5][6] = new Pawn(black, 5, 6);
		board[6][6] = new Pawn(black, 6, 6);
		board[7][6] = new Pawn(black, 7, 6);


		//Spawn White Pieces
		board[0][0] = new Rook(white, 0, 0);
		board[1][0] = new Knight(white, 1, 0);
		board[2][0] = new Bishop(white, 2, 0);
		board[3][0] = new Queen(white, 3, 0);
		board[4][0] = new King(white, 4, 0);
		board[5][0] = new Bishop(white, 5, 0);
		board[6][0] = new Knight(white, 6, 0);
		board[7][0] = new Rook(white, 7, 0);

		board[0][1] = new Pawn(white, 0, 1);
		board[1][1] = new Pawn(white, 1, 1);
		board[2][1] = new Pawn(white, 2, 1);
		board[3][1] = new Pawn(white, 3, 1);
		board[4][1] = new Pawn(white, 4, 1);
		board[5][1] = new Pawn(white, 5, 1);
		board[6][1] = new Pawn(white, 6, 1);
		board[7][1] = new Pawn(white, 7, 1);

		blackKing = board[4][7];
		whiteKing = board[4][0];

		//cout << blackKing << endl;
		//cout << board[4][7] << endl;
		//TESTING
		// board[2][1] = new Queen(white, 2, 1);
		// board[5][4] = new Queen(black, 5, 4);

	}
	int getTurn(){
		return turn;
	}

	void undoMove(){
		//cout << "UNDOMOVE()" << endl;


		Move m = moves.top();

		board[m.src->getFile()][m.src->getRank()] = m.src;
		board[m.file][m.rank] = m.dst;



		if (m.src->getType()[0] == 'K'){
			//cout << "update King location (undo move)" << endl;
			if (m.src->isWhite()){
				whiteKing = board[m.src->getFile()][m.src->getRank()];
			}
			else{
				blackKing = board[m.src->getFile()][m.src->getRank()];
			}
		}

		if(m.dst != nullptr){
			if (m.dst->getType()[0] == 'K'){
				//cout << "update King location (undo move)" << endl;
				if (m.dst->isWhite()){
					whiteKing = board[m.file][m.rank];
				}
				else{
					blackKing = board[m.file][m.rank];
				}
			}
		}



		//cout << "White King (" << whiteKing->getFile() << ", " << whiteKing->getRank() << ")" << endl;
		//cout << "Black King (" << blackKing->getFile() << ", " << blackKing->getRank() << ")" << endl;
		moves.pop();
	}

	void undoMove_(){


		board[lastMove.src->getFile()][lastMove.src->getRank()] = lastMove.src;
		board[lastMove.file][lastMove.rank] = lastMove.dst;

		if (lastMove.src->getType()[0] == 'K'){
			
			if (lastMove.src->isWhite()){
				whiteKing = lastMove.src;
			}
			else{
				blackKing = lastMove.src;
			}
		}

		if(lastMove.dst != nullptr){
			if (lastMove.dst->getType()[0] == 'K'){
				if (lastMove.dst->isWhite()){
					whiteKing = lastMove.src;
				}
				else{
					blackKing = lastMove.src;
				}
			}
		}
	}


	void saveState(Piece* src, Piece* dst, int file, int rank){
		//cout << "saveState()" << endl;

		Move m;
		m.src = pieceClone(src);

		if (dst == nullptr){
			m.dst = nullptr;
		}
		else {
			m.dst = pieceClone(dst);
		}
		m.file = file;
		m.rank = rank;

		moves.push(m);

		//cout << "White King (" << whiteKing->getFile() << ", " << whiteKing->getRank() << ")" << endl;
		//cout << "Black King (" << blackKing->getFile() << ", " << blackKing->getRank() << ")" << endl;


	}

	void saveState_(Piece* src, Piece* dst, int file, int rank){

		lastMove.src = pieceClone (src);
		if (dst == nullptr){
			lastMove.dst = nullptr;
		}
		else {
			lastMove.dst = pieceClone(dst);
		}

		lastMove.file = file;
		lastMove.rank = rank;



	}
	void printKings(){
		cout << "White King " << whiteKing << " (" << whiteKing->getFile() << ", " << whiteKing->getRank() << ") " << endl;
		cout << "Black King " << blackKing << " (" << blackKing->getFile() << ", " << blackKing->getRank() << ") " << endl;
	}

	void printPosition (int i, int j){
		cout << (char)('a'+i) << j+1;
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
		cout << " a  b  c  d  e  f  g  h" << endl << endl;
	}

	void printSquare_(int i, int j){
		if (board[i][j] != nullptr){
			cout << *(board[i][j]);
		}
		else if ((i+j)%2 == 0 ){
			cout << "\033[;90m##\033[0m";
		}
		else cout << "  ";
	}


	void printBoard_() {
		string line = "+-----+-----+-----+-----+-----+-----+-----+-----+\n";
		cout << endl <<"   a     b     c     d     e     f     g     h" << endl;
		cout << line;
		for (int j = 7; j > -1; j--){
			cout << "|  ";
			for (int i = 0; i < 8; i++){

				printSquare_(i,j);
				cout << " | ";
				if (i < 8) (cout << " ");

			}

			cout << j+1 << endl;
			cout << line;
		}
		cout << "   a     b     c     d     e     f     g     h" << endl << endl;

	}


	void printBoard__() {
		string line = "   +-----+-----+-----+-----+-----+-----+-----+-----+\n";
		cout << endl <<"      a     b     c     d     e     f     g     h" << endl;
		cout << line;
		for (int j = 7; j > -1; j--){
			cout << j+1;
			cout << "  |  ";
			for (int i = 0; i < 8; i++){

				printSquare_(i,j);
				cout << " | ";
				if (i < 8) (cout << " ");

			}

			cout << j+1 << endl;
			cout << line;
		}
		cout << "      a     b     c     d     e     f     g     h" << endl << endl;

	}

	void changePlayer() { 
		whites_turn = !whites_turn;
		turn++;


		if (isKingChecked()){
			if(checkMate()){
				resign();
			}
		}

		printBoard__();

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

		//Knights do not require clear path, return true
		if (src->getType() == "N") return true;

		int fileVector = vectorize(file-src->getFile());
		int rankVector = vectorize(rank-src->getRank());

		int fileCheck = src->getFile() + fileVector;
		int rankCheck = src->getRank() + rankVector;
		// cout << "Path destination: " << file <<  " " << rank << endl;

		// cout << "Start: " << src->getFile() << " + " << fileVector << ",  " << src->getRank()  << " + " << rankVector <<endl;
		// cout << "while: " << fileCheck << " " << rankCheck << endl;

		while ((fileCheck != file) || (rankCheck != rank) ){
			// cout << "check path .... " << fileCheck << "  " << rankCheck << endl;
			if (board[fileCheck][rankCheck] != nullptr){
				//cout << "square: ("<< fileCheck <<",  " << rankCheck << ") not NULL piece: ";
				//printSquare(fileCheck,rankCheck);
				//cout << endl;
				return false;
			}
			fileCheck += fileVector;
			rankCheck += rankVector;

		}
		//cout << "\033[1;32mPATH CLEAR!\033[0m" << endl;

		return true;
	}







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

			case -1:
				if (abs(rank) == 1) return true;
				else return false;

			case 0:
				if (rank == 0) return true;
				else return false;

			case 1:
				if (rank == 1) return true;
				else return false;

			case 2:
				if (rank == 2) return true;
				else return false;

			default:
				return true;
		}
	}




	bool validPlacement (Piece* src, int file, int rank){ 

		int fileDif = file-src->getFile();
		int rankDif = rank-src->getRank();

		cout << "file) dst - src: " << file << " - " << src->getFile() << endl;
		cout << "rank) dst - src: " << rank << " - " << src->getRank() << endl; 
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

	bool validPlacement_ (Piece* src, vector<moveRule> rules, int file, int rank){ 

		int fileDif = file-src->getFile();
		int rankDif = rank-src->getRank();

		// cout << "file) dst - src: " << file << " - " << src->getFile() << endl;
		// cout << "rank) dst - src: " << rank << " - " << src->getRank() << endl; 
		// cout << "fileDif: " << fileDif << ", rankDif: " << rankDif << endl;

		for (auto rule: rules){
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



	void capturePiece(Piece* src, int file, int rank ){

	}





	bool moveTo(Piece* src, int file, int rank){

		Piece* dst = board[file][rank];
		std::cout << "\033[1;32mmove_to(): Piece Line 356\033[0m " << std::endl;
		if (dst == nullptr){
			std::cout << "\033[1;36mEmpty Square\033[0m" << std::endl;

			board[src->getFile()][src->getRank()] = nullptr;
			board[file][rank] = src;
			src->setPlace(file, rank);

			if (!src->hasMoved()){
				cout << "First time moving!" << endl;
				src->setMoved();
			}

			return true;


		}
		else if (dst->isWhite() != whites_turn){
			std::cout <<  "\033[1;36mEnemy Piece \033[0m" << std::endl;





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

	bool checkMate(){

		//cout << "CHECKMATE() Called " << endl;
		//cout << whiteKing->getFile() << ", " << whiteKing->getRank() << endl;
		//cout << "turn: " << whites_turn << endl << endl;

		// Piece* king;
		Piece* current;


		// if (whites_turn){ king = whiteKing; }
		// else { king = blackKing; }
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){

				current = board[i][j];
				if (current != nullptr){
					if (current->isWhite() == whites_turn){


						for (int k = 0; k < 8; k++){
							for (int l = 0; l < 8; l++){
								//cout << " (i: " << i << ", j: " << j << ") -->  (k: " << k << ", l: " << l << ") " << endl; 



								saveState(current, board[k][l], k, l);

								if (tryMove_(i,j,k,l)){
									//cout << "VALID MOVE FOUND! " << *current << "  (" << i << ", " << j << ") --> (" << k << ", " << l << ")" <<endl;

									undoMove();		
									return false;

								}
								undoMove();






							}
						}




					}
				}





			}
		}

		cout << "CHECKMATE!!" << endl;
		return true;
	}


	bool isKingChecked(){

		//cout << "is King Checked?" << endl;

		Piece* king;
		Piece* current;


		if (whites_turn){ king = whiteKing; }
		else { king = blackKing; }

		//cout << "Target: " << *king << " (" << king->getFile() << " " << king->getRank() << ")" << endl;

		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){

				//cout << "test: " << i << " " << j << endl;
			
				current = board[i][j];
				if (current != nullptr){
					//cout <<"Not Null: " << i << " " << j << endl;


					if (current->isWhite() != whites_turn){
						//cout << *current << " (" << i << ", " << j << ") "; printPosition(i,j); cout << endl;
						if (validPlacement_(current, current->getCaptureRules(), king->getFile(), king->getRank())){
							if (isPathClear(current, king->getFile(), king->getRank())){
								if (whites_turn){
									cout << "White is Checked!" << endl;
								}
								else {
									cout << "Black is Checked!" << endl;
								}
								return true;



							}
						}
						
						

					// 	if (validPlacement_(current, current->getCaptureRules(), king->getFile(), king->getRank()) &&
					// 		isPathClear(current, king->getFile(), king->getRank())) {
					// 		cout << "Check!" << endl; 
					// 		//return true;
					// 	}
					}

				}


			}
		}
		return false;

		//return false;
	}



	bool tryMove_(int file0, int rank0, int file1, int rank1){

		Piece* src = board[file0][rank0];
		if (src == nullptr){ return false; }

		if (src->isWhite() == whites_turn){	 // Piece Owner

			Piece* dst = board[file1][rank1];

			if (dst == nullptr){ // Empty Landing Space

				//Check if pawn attempting en-passant 


				if (!validPlacement_(src, src->getRules(), file1, rank1)) { return false; }
				if (!isPathClear(src, file1, rank1) ) { return false; }

				saveState(src, dst, file1, rank1);


				board[src->getFile()][src->getRank()] = nullptr;
				src->setPlace(file1, rank1);
				board[file1][rank1] = src;

				if (!src->hasMoved()){ src->setMoved(); }

				//Did the move, the player just made cause them to get checked?
				// if ( (file0 == 0) && (rank0 == 1) && (file1 == 0) && (rank1 == 2 ) ){
				// 	cout << " SUSPECT: King Checked? -> " << isKingChecked() << endl; 

				// }

				if (isKingChecked()){

					//cout << "King Checked!, UNDO!" << endl;
					undoMove();
					return false;
				}

				//changePlayer();

				return true;
			
			}
			else if (dst->isWhite() != whites_turn){ // Enemy on Land Space

				if (!validPlacement_(src, src->getCaptureRules(), file1, rank1)) { return false; }
				if (!isPathClear(src, file1, rank1) ) { return false; }

				saveState(src, dst, file1, rank1);

				board[src->getFile()][src->getRank()] = nullptr;
				src->setPlace(file1, rank1);
				board[file1][rank1] = src;

				if(isKingChecked()){

					//cout << "King Checked!, UNDO!" << endl;
					undoMove();
					return false;
				}
				//changePlayer();

				return true;

			}
			
			else { // Own Piece - Change this for Castling

				//std::cout << "\033[1;33mOwn Piece -> Castle Attempt?\033[0m" << std::endl;
				if ((src->getType() == "K") && (dst->getType() == "R") ){
					//Need to cast and call castle
					//return (dynamic_cast<King*>(this))->castle(dst);


				}
				else {
					std::cout << "\033[1;31mInvalid Move. Targeting Own Piece.\033[0m" << std::endl;
					return false;
				}
			}


		}

		else return false;


	return false;


	}



	bool tryMove(int file0, int rank0, int file1, int rank1){
		//Calls Functions to verify move is allowed
		cout << "\033[1;32mtryMove() - Gameboard line 116:\033[0m " << endl;


		Piece* src = board[file0][rank0];
		if (src == nullptr){
			cout << "\033[1;31mtryMove(): returning false (source is null)\033[0m" << endl;
			return false; 
		}


		cout << "Chosen Piece: " << *src << endl;
		Piece* dst = board[file1][rank1];


		cout << "Player Color: " << src->isWhite() << ", Piece Color: " << whites_turn << endl;

		//Are you piece owner
		if (src->isWhite() == whites_turn){	

			//Move allowed within the Piece Rules
			if (!validPlacement(src, file1, rank1)){
				cout << "\033[1;31mtryMove(): validPlacement(), Movement breaks Piece rules \033[0m" << endl;
				return false;
			}

			//Is Path Clear
			if (!isPathClear(src, file1, rank1)){
				cout << "\033[1;31mtryMove(): isPathClea(), Path Not Clear \033[0m" << endl;
				return false;
			}


			//redundant? could prob just directly return the return, but no logs possibly?
			//
			if (moveTo(src, file1, rank1)){
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