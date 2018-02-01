#pragma once

#include <string>
using namespace std;
class Piece {

protected:
	bool m_isWhite;
	bool m_hasMoved;
	string name;
	string type;
	int m_file;
	int m_rank;
	//vector<pair<int,int> > a;


	// void available_moves();
	// 
	// virtual void draw_piece();
	// virtual bool clear_path(pair<int,int>, pair<int,int>);
	// virtual validDestination(pair<int,int>);
	 

public:
	Piece (bool val);
	bool isWhite();
	bool hasMoved();
	void setMove();
	friend ostream & operator << (ostream &out, const Piece &piece);

	void setName ();
	bool isPathClear(int file, int rank);
	bool moveTo( Piece* dst, bool turn );

};

ostream & operator << (ostream &out, const Piece &piece);


//Pawn Class
class Pawn: public Piece{

public:
	Pawn(bool val): Piece(val);

};



//King
class King: public Piece{
public:
	King(bool val): Piece(val);
	bool castle(Piece* rook);

};


// Queen
class Queen: public Piece{

public:
	Queen(bool val): Piece(val);

};



//Rook
class Rook: public Piece{

public:
	Rook(bool val): Piece(val);

};
 

//Knight
class Knight: public Piece{

public:
	Knight(bool val): Piece(val);

};



//Bishop
class Bishop: public Piece{

public:
	Bishop(bool val);

};