
#ifndef PIECES_CPP
#define PIECES_CPP



#include <string>

using namespace std;


class Piece {

protected:
	int color;
	string name;
	string type;
	pair<int,int> position;
	//vector<pair<int,int> > a;


	// void available_moves();
	// 
	// virtual void draw_piece();
	// virtual bool clear_path(pair<int,int>, pair<int,int>);
	// virtual validDestination(pair<int,int>);
	// virtual void move_to();

public:
	Piece (int val): color(val) {setName();}
	int getColor() {return color;}
	
	friend ostream & operator << (ostream &out, const Piece &piece);
	void setName (){
		if (color){
			name = "w" + type;

		}
		else {
			name = "b" + type;
		}


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
	Pawn(int val): Piece(val){type = "p"; setName();}

	int has_moved(){
		return moved;
	}

};



//King
class King: public Piece{
	int moved;

public:
	King(int val): Piece(val){ type = "K"; setName();};

	int has_moved(){
		return moved;
	}

	void castle(){}

};


// Queen
class Queen: public Piece{

public:
	Queen(int val): Piece(val){type = "Q"; setName();};

};



//Rook
class Rook: public Piece{
	int moved;

public:
	Rook(int val): Piece(val){type = "R"; setName();};

	int has_moved(){
		return moved;
	}

	void castle(){

	}

};

//Knight
class Knight: public Piece{

public:
	Knight(int val): Piece(val){type = "N"; setName();};

};



//Bishop
class Bishop: public Piece{

public:
	Bishop(int val): Piece(val){type = "B"; setName();};

};


#endif
