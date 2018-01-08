#include <string>
 


class Piece {

	int color;
	String description;
	pair<int,int> position;


	void available_moves();
	virtual draw_piece();
	virtual check_path(pair<int,int> src, pair<int,int> dst);
	virtual void move_to();

	Piece (int in_color){
		color = in_colors;

	}

}

//Pawn Class
class Pawn: Piece{
	int moved;

	int has_moved(){
		return moved;
	}


}

class King: Piece{
	int moved;

	int has_moved(){
		return moved;
	}


	castle(){


	}

}

class Queen: Piece{


}

class Rook: Piece{
	int moved;

	int has_moved(){
		return moved;
	}

	void castle(){

	}

}

class Knight: Piece{

}

class Bishop: Piece{

}
