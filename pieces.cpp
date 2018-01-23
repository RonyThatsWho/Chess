
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
	int m_file;
	int m_rank;
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
	void setMove(){ m_hasMoved = true; }
	friend ostream & operator << (ostream &out, const Piece &piece);

	void setName (){
		if (m_isWhite){	name = "w" + type; }
		else { name = "b" + type; }
	}

	bool isPathClear(int file, int rank){

		/*
			Need to determine movement type based on Piece type and Destination
			Horizontal, Vertical, Diagnal or L-Shape

		*/

		bool vert;
		bool hor;
		cout << "isPathClear() - " << file-m_file << " " << rank-m_rank << endl;


		//Vertical Movement Check
		if (file-m_file){
			bool vert = true;
			cout << "vert true" << endl;
		}

		//Horizontal Movement Check
		if (rank-m_rank){
			bool hor = true;
			cout << "hor true" << endl;
		}



		return true;

	}

	bool moveTo( Piece* dst, bool turn ){
		cout << "\033[1;32mmove_to(): Piece Line 73\033[0m " << endl;
		if (dst == nullptr){
			cout << "\033[1;36mEmpty Square,Need To Check Path\033[0m" << endl;
			
			if (isPathClear(0,0)){

				//change
			}

		}
		else if (dst->isWhite() != turn){
			cout <<  "\033[1;36mEnemy Piece Check Path \033[0m" << endl;
		}
		else {
			cout << "\033[1;33mOwn Piece -> Castle Attempt?\033[0m" << endl;
			if ((type == "K") && (dst->type == "R") ){
				//Need to cast and call castle
				//return (dynamic_cast<King*>(this))->castle(dst);


			}
			else {
				cout << "\033[1;31mTargeting Own Piece, Cannot Castle\033[0m" << endl;
				return false;
			}
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

public:
	Pawn(bool val): Piece(val){ type = "p"; setName(); }

};



//King
class King: public Piece{

public:
	King(bool val): Piece(val){ type = "K"; setName(); };


	bool castle(Piece* rook){
		if ( hasMoved() || rook->hasMoved()){
			return false;
		}


		setMove();
		rook->setMove();
		return true;



	}

};


// Queen
class Queen: public Piece{

public:
	Queen(bool val): Piece(val){ type = "Q"; setName(); };

};



//Rook
class Rook: public Piece{

public:
	Rook(bool val): Piece(val){ type = "R"; setName(); };

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
