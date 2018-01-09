
#ifndef PIECES_CPP
#define PIECES_CPP



#include <string>

using namespace std;


class Piece {

	int color;
	string description;
	pair<int,int> position;


	// void available_moves();
	// virtual void draw_piece();
	// virtual void check_path(pair<int,int>, pair<int,int>);
	// virtual void move_to();

public:
	Piece (int val): color(val), description("pwn") {}
	
	friend ostream & operator << (ostream &out, const Piece &piece);


};

ostream & operator << (ostream &out, const Piece &piece){

	out << piece.description; 

	return out;
};


//Pawn Class
class Pawn: public Piece{
	int moved;

public:
	Pawn(int val): Piece(val){}

	int has_moved(){
		return moved;
	}

};



//King
class King: public Piece{
	int moved;

public:
	King(int val): Piece(val){};

	int has_moved(){
		return moved;
	}

	void castle(){}

};


// Queen
class Queen: public Piece{

public:
	Queen(int val): Piece(val){};

};



//Rook
class Rook: public Piece{
	int moved;

public:
	Rook(int val): Piece(val){};

	int has_moved(){
		return moved;
	}

	void castle(){

	}

};

//Knight
class Knight: public Piece{

public:
	Knight(int val): Piece(val){};

};



//Bishop
class Bishop: public Piece{

public:
	Bishop(int val): Piece(val){};

};


#endif
