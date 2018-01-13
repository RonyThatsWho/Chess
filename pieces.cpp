
#ifndef PIECES_CPP
#define PIECES_CPP



#include <string>

using namespace std;


class Piece {

protected:
	bool m_isWhite;
	bool m_hasMoved;
	string name;
	string type;
	pair<int,int> position;
	//vector<pair<int,int> > a;


	// void available_moves();
	// 
	// virtual void draw_piece();
	// virtual bool clear_path(pair<int,int>, pair<int,int>);
	// virtual validDestination(pair<int,int>);
	 

public:
	Piece (bool val): m_isWhite(val) { setName(); }

	bool isWhite() { return m_isWhite; }
	bool hasMoved() { return m_hasMoved; }

	friend ostream & operator << (ostream &out, const Piece &piece);

	void setName (){
		if (m_isWhite){
			name = "w" + type;
		}
		else {
			name = "b" + type;
		}
	}

	bool move_to( Piece* dst, bool turn ){
		cout << "trying to move piece " << endl;
		if (dst == nullptr){
			cout << "Space Available, Check Path" << endl;
		}
		else if (dst->isWhite() != turn){
			cout << "Enemy Piece, Check Path" << endl;
		}
		else {
			cout << "Own Piece, attempting to castle?" << endl;
		}

		return true;

	}


};

ostream & operator << (ostream &out, const Piece &piece){

	out << piece.name; 
	return out;
};


//Pawn Class
class Pawn: public Piece{
	int moved;

public:
	Pawn(bool val): Piece(val){ type = "p"; setName(); }

	int has_moved(){
		return moved;
	}

};



//King
class King: public Piece{
	int moved;

public:
	King(bool val): Piece(val){ type = "K"; setName(); };

	int has_moved(){
		return moved;
	}

	void castle(){}

};


// Queen
class Queen: public Piece{

public:
	Queen(bool val): Piece(val){ type = "Q"; setName(); };

};



//Rook
class Rook: public Piece{
	int moved;

public:
	Rook(bool val): Piece(val){ type = "R"; setName(); };

	int has_moved(){
		return moved;
	}

	void castle(){

	}

};

//Knight
class Knight: public Piece{

public:
	Knight(bool val): Piece(val){ type = "N"; setName(); };

};



//Bishop
class Bishop: public Piece{

public:
	Bishop(bool val): Piece(val){ type = "B"; setName(); };

};


#endif
