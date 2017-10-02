#include "Game.h"

int main(){

	/*ofstream file;
	file.open("highscore.txt",ios::binary);
	Cuser user[5];
	for(int i=0;i<5;i++){
		user[i].setall("Antonio",100);

	}

	for(int i=0;i<5;i++){
		file.write((char*)&user[i], sizeof(Cuser));

	}
	file.close();*/

	CGame game;
	game.menu();
	return 0;
}