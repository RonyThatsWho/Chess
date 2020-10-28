#ifndef PIECES_H
#define PIECES_H

#include <string>
using namespace std;

typedef struct{
	int file;
	int rank;
} pPosition;


class Piece {

protected:
	bool m_isWhite;
	bool m_hasMoved;
	string name;
	string type;
	int m_file;
	int m_rank;


public:
	Piece (bool val);
	bool isWhite();
	bool hasMoved();
	void setMove();
	//friend ostream & operator << (ostream &out, const Piece &piece);

	void setName ();
	bool isPathClear(int file, int rank);
	bool moveTo( Piece* dst, bool turn );
	struct pPosition getPosition (){
		struct pPosition  currentPos = {m_file, m_rank};
		return currentPosition;
	}

};


//ostream & operator << (ostream &out, const Piece &piece);


//Pawn Class
class Pawn: public Piece{

public:
	Pawn(bool val);

};



//King
class King: public Piece{
public:
	King(bool val);
	bool castle(Piece* rook);

};


// Queen
class Queen: public Piece{

public:
	Queen(bool val);

};



//Rook
class Rook: public Piece{

public:
	Rook(bool val);

};
 

//Knight
class Knight: public Piece{

public:
	Knight(bool val);

};



//Bishop
class Bishop: public Piece{

public:
	Bishop(bool val);

};

#endif