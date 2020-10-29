#ifndef PIECES_CPP
#define PIECES_CPP


#include <string>
#include <vector>
//#include "pieces.h"


//using namespace pieces;
using namespace std;

struct moveRule{
	int fileRule;
	int rankRule;
	int diagRule;

};

struct move{
	int file;
	int rank;
};


class Piece {

protected:
	bool m_isWhite;
	bool m_hasMoved;
	std::string name;
	std::string type;
	int m_file;
	int m_rank;

	vector<moveRule> rules;
	vector<moveRule> captureRules;


	//vector<moves> moveRules;


	//vector<move> *availableMoves;

	//Moves moveSet[];

	//vector<pair<int,int> > a;


	// void available_moves();
	// 
	// virtual void draw_piece();
	// virtual bool clear_path(pair<int,int>, pair<int,int>);
	// virtual validDestination(pair<int,int>);
	 

public:
	Piece (bool val, int file, int rank): m_isWhite(val) { 
		setName();
		setPlace(file, rank);
		m_hasMoved = false;

	}

	bool isWhite() { return m_isWhite; }
	bool hasMoved() { return m_hasMoved; }
	virtual void setMoved(){ m_hasMoved = true; cout << "pice has moved()" << endl;}
	string getType(){ return type;}


	friend ostream & operator << (ostream &out, const Piece &piece);

	void setName (){
		if (m_isWhite){	name = "\033[1;37mw" + type + "\033[0m"; }
		else { name =  "\033[1;34mb" + type + "\033[0m"; }
	}

	void setPlace (int file, int rank){

		m_file = file;
		m_rank = rank;

	}

	int getFile(){
		return m_file;
	}

	int getRank(){
		return m_rank;
	}

	vector<moveRule> getRules(){
		return rules;
	}

	// bool isPathClear(int file, int rank){
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



	// bool moveTo( Piece* dst, bool turn){
	// 	std::cout << "\033[1;32mmove_to(): Piece Line 93\033[0m " << std::endl;
	// 	if (dst == nullptr){
	// 		std::cout << "\033[1;36mEmpty Square,Need To Check Path\033[0m" << std::endl;
			
	// 		if (isPathClear(m_rank, m_file)){
	// 		//if (isPathClear(move)){

	// 			cout << "Board Passed in Move Structure" << endl;

	// 			//if true then movePiece.
	// 			//board points to piece
	// 			//old board location points to null.
	// 		}

	// 	}
	// 	else if (dst->isWhite() != turn){
	// 		std::cout <<  "\033[1;36mEnemy Piece Check Path \033[0m" << std::endl;
	// 	}
	// 	else {
	// 		std::cout << "\033[1;33mOwn Piece -> Castle Attempt?\033[0m" << std::endl;
	// 		if ((type == "K") && (dst->type == "R") ){
	// 			//Need to cast and call castle
	// 			//return (dynamic_cast<King*>(this))->castle(dst);


	// 		}
	// 		else {
	// 			std::cout << "\033[1;31mTargeting Own Piece, Cannot Castle\033[0m" << std::endl;
	// 			return false;
	// 		}
	// 	}

	// 	return true;

	// }


};

ostream & operator << (ostream &out, const Piece &piece){

	out << piece.name; 
	return out;
};


//Pawn Class
class Pawn: public Piece{

public:
	Pawn(bool val, int file, int rank): Piece(val, file, rank){ 
		type = "p"; 
		setName(); 
		//setPlace(file, rank);


		rules.push_back((moveRule){0,1,0});
		rules.push_back((moveRule){0,2,0});

		captureRules.push_back ((moveRule){1,1,1});
		
	}

	void setMoved() override{
		m_hasMoved = true;
		rules.erase(rules.begin()+1);

		cout << "moved, rules size: " << rules.size() << endl; 

	} 


};



//King
class King: public Piece{

public:
	King(bool val, int file, int rank): Piece(val, file, rank){ 
		type = "K"; 
		setName();

		rules.push_back((moveRule) { 1,-1, 2}); //Diagnal 1 limit
		rules.push_back((moveRule) { 1, 0, 0}); //Vertical Unlimited
		rules.push_back((moveRule) { 0,-1, 0}); //Horizontal Unlimited
	};


	bool castle(Piece* rook){
		if ( hasMoved() || rook->hasMoved()){
			return false;
		}


		setMoved();
		rook->setMoved();
		return true;



	}

};


// Queen
class Queen: public Piece{

public:
	Queen(bool val, int file, int rank): Piece(val, file, rank){ 
		type = "Q"; 
		setName();
		//setPlace(file, rank);

		rules.push_back((moveRule) { 3,3,2}); //Diagnal Unlimited
		rules.push_back((moveRule) { 3,0,0}); //Vertical Unlimited
		rules.push_back((moveRule) { 0,3,0}); //Horizontal Unlimited
	};

};



//Rook
class Rook: public Piece{

public:
	Rook(bool val, int file, int rank): Piece(val, file, rank){
		type = "R";
		setName();

		rules.push_back((moveRule) { 3,0,0}); //Vertical Unlimited
		rules.push_back((moveRule) { 0,3,0}); //Horizontal Unlimited
	};

};
 

//Knight
class Knight: public Piece{

public:
	Knight(bool val, int file, int rank): Piece(val, file, rank){ 
		type = "N";
		setName();

		rules.push_back((moveRule){ 2,-1,3}); // 
		rules.push_back((moveRule){ 1,-2,3});

	};

};



//Bishop
class Bishop: public Piece{

public:
	Bishop(bool val, int file, int rank): Piece(val, file, rank){
		type = "B";
		setName();

		rules.push_back((moveRule) { 3,3,2}); //Diagnal Unlimited
	};

};


#endif
