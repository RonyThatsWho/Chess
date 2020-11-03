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

// struct move{
// 	int file;
// 	int rank;
// };
// class Pawn;
// class Rook;
// class King;
// class Queen;
// class Knight;
// class Bishop;

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
	virtual void setMoved(){ m_hasMoved = true; }
	string getType(){ return type;}


	friend ostream & operator << (ostream &out, const Piece &piece);

	
	void setName (){
		if (m_isWhite){	name = "\033[1;36mw" + type + "\033[0m"; }
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
	virtual vector<moveRule> getCaptureRules(){
		return rules;
	}

	friend Piece* pieceClone(Piece*);


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

		rules.push_back((moveRule){0, 1, 0});
		rules.push_back((moveRule){0, 2, 0});

		captureRules.push_back ((moveRule){1, 1, 1});
		
	}

	void setMoved() override{
		m_hasMoved = true;
		rules.erase(rules.begin()+1);

		//cout << "moved, rules size: " << rules.size() << endl; 

	}

	vector<moveRule> getCaptureRules() override {
		return captureRules;
	}


};



//King
class King: public Piece{

public:
	King(bool val, int file, int rank): Piece(val, file, rank){ 
		type = "K"; 
		setName();

		rules.push_back((moveRule) { 1,-1, 1}); //Diagnal 1 limit
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

		rules.push_back((moveRule) { 3, 3, 1}); //Diagnal Unlimited
		rules.push_back((moveRule) { 3, 0, 0}); //Vertical Unlimited
		rules.push_back((moveRule) { 0, 3, 0}); //Horizontal Unlimited
	};

};



//Rook
class Rook: public Piece{

public:
	Rook(bool val, int file, int rank): Piece(val, file, rank){
		type = "R";
		setName();

		rules.push_back((moveRule) { 3, 0, 0}); //Vertical Unlimited
		rules.push_back((moveRule) { 0, 3, 0}); //Horizontal Unlimited
	};

};
 

//Knight
class Knight: public Piece{

public:
	Knight(bool val, int file, int rank): Piece(val, file, rank){ 
		type = "N";
		setName();

		rules.push_back((moveRule){ 2,-1, 3}); // 
		rules.push_back((moveRule){ 1,-2, 3});

	};

};



//Bishop
class Bishop: public Piece{

public:
	Bishop(bool val, int file, int rank): Piece(val, file, rank){
		type = "B";
		setName();

		rules.push_back((moveRule) { 3, 3, 1}); //Diagnal Unlimited
	};

};


Piece* pieceClone(Piece* src){
	Piece* copy;
	auto test = src->getType();

	switch (test[0]){

		

		case 'p':
			copy = new Pawn (src->isWhite(), src->getFile(), src->getRank());
			break;
		case 'K':
			copy = new King (src->isWhite(), src->getFile(), src->getRank());
			break;
		case 'Q':
			copy = new Queen (src->isWhite(), src->getFile(), src->getRank()); 
			break;
		case 'R':
			copy = new Rook (src->isWhite(), src->getFile(), src->getRank()); 
			break;
		case 'N':
			copy = new Knight (src->isWhite(), src->getFile(), src->getRank());
			break;
		case 'B':
			copy = new Bishop (src->isWhite(), src->getFile(), src->getRank());
			break;

	}


	copy->m_hasMoved = src->hasMoved();

	copy->rules = src->rules;
	copy->captureRules = src->captureRules; 

	return copy;
}



#endif
