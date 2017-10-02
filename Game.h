#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
//#include "map.h"
#include "char.h"
#include "item.h"
#include "menu.h"
#include "buttom.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;




enum Direction
{
	Up, Down, Left, Right, None,
	UpLeft, UpRight, DownLeft, DownRight
};




class CGame
{
private:
	sf::RenderWindow window;

	//other
	CMap map;
	CPlayer player;
	CNode **temp_map;

	std::vector<sf::Sprite> map_image;
	sf::Texture floor_texture, pilar_texture, freeze_texture;
	sf::Texture player_texture;
	sf::Texture finish_texture;
	sf::Sprite finish_sprite;
	sf::Texture portal_texture;
	sf::Sprite portal_sprite;
	sf::Texture border_texture;
	sf::Sprite border_sprite;
	sf::Texture port_texture;
	sf::Sprite port_sprite;
	sf::Sprite win_sprite;

	sf::Texture item1;
	sf::Texture item2;
	sf::Texture item3;
	sf::Texture item4;
	sf::Texture item5;
	sf::Texture win_tet;


	sf::Time waktu;
	sf::Clock clock;
	sf::Time waktuGame;
	sf::Clock clockGame;

	sf::Font fontTime;
	sf::Text textTime;


	//tampilan atas item
	sf::Sprite stat_vision;
	sf::Sprite stat_speed;
	sf::Sprite stat_freeze;
	sf::Sprite stat_strength;

	sf::Font fontStat;
	sf::Text textVision;
	sf::Text textSpeed;
	sf::Text textFreeze;
	sf::Text textStrength;
	sf::Text textLamaRandomItem;


	sf::Text textAlt;
	sf::Text textEsc;
	sf::Text textSpace;

	int lamagame;
	int nyalalampu;
	int lamaspeed;
	int lamafreeze;
	int lamastrength;
	int lamarandomitem;

	int winG;


	sf::Music musicBackground;
	sf::Music musicMenu;
	sf::Music hurryUp;
	CGhost *ghost[3];
	float t_ghost;
	bool lose;
	bool lampu;
	bool freeze;
	bool strength;
	bool game_pause;
	LinkItem item;
	sf::Vector2f posisiItem;

	sf::Sprite coba;

public:
	CGame()
		: window(sf::VideoMode(1366,768), "Template", sf::Style::Fullscreen)
	{
		srand((time(NULL)));
		window.setKeyRepeatEnabled(false);


		//map
		lose=false;
		lampu=true;
		freeze=false;
		strength=false;
		game_pause=false;

		t_ghost=0;
		musicBackground.openFromFile("music/play.wav");
		hurryUp.openFromFile("music/hurryup.wav");
		musicMenu.openFromFile("music/menu.wav");
		player_texture.loadFromFile("resource/player.png");
		floor_texture.loadFromFile("resource/lantai.png");
		pilar_texture.loadFromFile("resource/pilar.png");
		finish_texture.loadFromFile("resource/finishflag.png");
		portal_texture.loadFromFile("resource/portal.png");
		border_texture.loadFromFile("resource/background.png");
		freeze_texture.loadFromFile("resource/freezearea.png");
		port_texture.loadFromFile("resource/black.png");
		item1.loadFromFile("resource/time.png");
		item2.loadFromFile("resource/mata.png");
		item3.loadFromFile("resource/bolt.png");
		item4.loadFromFile("resource/snow.png");
		item5.loadFromFile("resource/muscle.png");
		win_tet.loadFromFile("resource/WIN.png");
		win_sprite.setTexture(win_tet);



		fontTime.loadFromFile("resource/bold.ttf");
		textTime.setFont(fontTime);
		textTime.setCharacterSize(25);
		textTime.setPosition(70,20);
		textTime.setColor(sf::Color::Red);

		map_image.push_back(sf::Sprite(floor_texture));//0 floor
		map_image.push_back(sf::Sprite(pilar_texture));//1 pillar
		map_image.push_back(sf::Sprite(pilar_texture));

		finish_sprite.setTexture(finish_texture);
		finish_sprite.setTextureRect(sf::IntRect(0,0,48,96));
		portal_sprite.setTexture(portal_texture);
		border_sprite.setTexture(border_texture);
		port_sprite.setTexture(port_texture);
		port_sprite.setOrigin(1263.0,696.0);

		map_image.push_back(sf::Sprite(finish_sprite));//3 finish
		map_image.push_back(sf::Sprite(portal_sprite));//4 portal
		map_image.push_back(sf::Sprite(freeze_texture));//5 freeze area

		//tampilan stat
		fontStat.loadFromFile("resource/font.ttf");
		textVision.setFont(fontStat);
		textSpeed.setFont(fontStat);
		textFreeze.setFont(fontStat);
		textStrength.setFont(fontStat);
		textVision.setString("2");
		textSpeed.setString("3");
		textFreeze.setString("4");
		textStrength.setString("3");
		textVision.setPosition(1000,20);
		textVision.setCharacterSize(25);
		textSpeed.setPosition(1090,20);
		textSpeed.setCharacterSize(25);
		textFreeze.setPosition(1170,20);
		textFreeze.setCharacterSize(25);
		textStrength.setPosition(1260,20);
		textStrength.setCharacterSize(25);

		textAlt.setFont(fontStat);
		textAlt.setString("PRESS ALT TO PAUSE");
		textAlt.setPosition(500,700);

		textEsc.setFont(fontStat);
		textEsc.setString("PRESS ESC TO EXIT");
		textEsc.setPosition(500,700);

		textSpace.setFont(fontStat);
		textSpace.setString("PRESS SPACE TO CONTINUE");
		textSpace.setPosition(450,700);

		textLamaRandomItem.setFont(fontTime);
		textLamaRandomItem.setCharacterSize(25);
		textLamaRandomItem.setPosition(300,20);

		nyalalampu=2;
		lamaspeed=3;
		lamafreeze=4;
		lamastrength=4;
		lamagame=60;
		lamarandomitem=10;

		stat_vision.setTexture(item2);
		stat_vision.setTextureRect(sf::IntRect(0,0,48,48));
		stat_vision.setPosition(950,10);

		stat_speed.setTexture(item3);
		stat_speed.setTextureRect(sf::IntRect(0,0,48,48));
		stat_speed.setPosition(1040,10);

		stat_freeze.setTexture(item4);
		stat_freeze.setTextureRect(sf::IntRect(0,0,48,48));
		stat_freeze.setPosition(1120,10);

		stat_strength.setTexture(item5);
		stat_strength.setTextureRect(sf::IntRect(0,0,48,48));
		stat_strength.setPosition(1200,10);

		temp_map=map.getm_map();
		srand(time(NULL));
		int tipe;
		for(int i=0; i<30;i++){//jmlh item muncul pertama
			tipe=rand()%5;
			posisiItem.x=rand()%24;
			posisiItem.y=rand()%12;

			while(temp_map[int(posisiItem.y)][int(posisiItem.x)].GetMap()!=0 || item.cekLokasi(posisiItem.x,posisiItem.y)==true){
				posisiItem.x=rand()%24;
				posisiItem.y=rand()%12;
			}

			if(tipe==0){
				item.push_back(tipe,posisiItem,item1);
			}
			else if(tipe==1){
				item.push_back(tipe,posisiItem,item2);
			}
			else if(tipe==2){
				item.push_back(tipe,posisiItem,item3);
			}
			else if(tipe==3){
				item.push_back(tipe,posisiItem,item4);
			}
			else if(tipe==4){
				item.push_back(tipe,posisiItem,item5);
			}
		}

		player.setText(player_texture);
		player.SetDefaultPosition(map.GetPlayer());
		player.setPosisi();

		ghost[0]=new CSGhost;
		ghost[1]=new CBGhost;
		ghost[2]=new CFGhost;


		ghost[0]->SetDefaultPosition(map.GetGhost(0));
		ghost[1]->SetDefaultPosition(map.GetGhost(1));
		ghost[2]->SetDefaultPosition(map.GetGhost(2));
		for(int i=0;i<3;i++){
			ghost[i]->setPosisi();
		}


		map.BFSFinish();
		map.BFSPlayer(player.getPos().m_y,player.getPos().m_x);

		/*coba.setTexture(item1);
		coba.setTextureRect(sf::IntRect(0,0,48,48));
		coba.setPosition(3*48+106,5*48+126);
		*/
	}




	~CGame()
	{
	}




	void draw(sf::Time wak, sf::RenderWindow &win, bool freeze){

		//cout<<endl<<endl;
		//cout<<player.getPos().m_x<<endl;
		//cout<<player.getPos().m_y<<endl;

		//map.PrintFinish();
		//cout << endl;
		//map.PrintPlayer();
		//cout << endl;
		//map.PrintMap();
		//cout << endl;

		for(int i=0;i<map.getrow();i++){
			for(int j=0;j<map.getcol();j++){


				if(freeze==true){
					map_image[5].setPosition(j*48+106,i*48+126);
					window.draw(map_image[5]);

				}
				else{
					map_image[0].setPosition(j*48+106,i*48+126);
					window.draw(map_image[0]);
				}
			}
			cout<<endl;
		}
		win.draw(border_sprite);
		item.draw(window);
		for(int i=0; i<3; i++){
			if(ghost[i]->GetHealth()==true)ghost[i]->draw(win);
		}
		player.update(wak.asSeconds());
		player.draw(win);

		for(int i=0;i<map.getrow();i++){
			for(int j=0;j<map.getcol();j++){
				if(temp_map[i][j].GetMap()>=8){
					map_image[4].setPosition(j*48+106,i*48+126);
					window.draw(map_image[4]);
				}
				if(temp_map[i][j].GetMap()<=3&& temp_map[i][j].GetMap()!=0){
					if(temp_map[i][j].GetMap()==1 ){
						map_image[temp_map[i][j].GetMap()].setPosition(j*48+106,i*48-48+126);}
					else if(temp_map[i][j].GetMap()==3){
						map_image[temp_map[i][j].GetMap()].setPosition(j*48+106,i*48-48+126);
					}
					else{
						map_image[temp_map[i][j].GetMap()].setPosition(j*48+106,i*48+126);
					}


					window.draw(map_image[temp_map[i][j].GetMap()]);
				}
			}
		}

		if(lampu==true){
			//win.draw(port_sprite);
		}


		for(int i=0;i<map.getrow();i++){
			for(int j=0;j<map.getcol();j++){	
				if(temp_map[i][j].GetMap()>=8){
					map_image[4].setPosition(j*48+106,i*48+126);
					window.draw(map_image[4]);
				}
			}
		}


		win.draw(textTime);
		if(nyalalampu!=2){
			win.draw(stat_vision);
			win.draw(textVision);
		}
		if(lamaspeed!=3){
			win.draw(stat_speed);
			win.draw(textSpeed);
		}
		if(lamafreeze!=4){
			win.draw(stat_freeze);
			win.draw(textFreeze);
		}
		if(lamastrength!=4){
			win.draw(stat_strength);
			win.draw(textStrength);
		}
		win.draw(textLamaRandomItem);
		win.draw(textAlt);

	}




	void menu(){
		sf::Texture textureBack[5];
		sf::Sprite spriteBack;
		sf::Clock clockAnimasi;
		sf::Time timeAnimasi;
		sf::Clock clockAnimasi2;
		sf::Time timeAnimasi2;
		timeAnimasi2 = sf::seconds(4);
		timeAnimasi = sf::seconds(0.3);
		textureBack[0].loadFromFile("resource/menu1.png");
		textureBack[1].loadFromFile("resource/menu2.png");
		textureBack[2].loadFromFile("resource/menu3.png");
		textureBack[3].loadFromFile("resource/menu4.png");
		textureBack[4].loadFromFile("resource/menu5.png");
		int i=0;
		//spriteBack.scale(1.4,1.2);

		float x=0.5,y=0.5;
		int counter=0;
		Menu MENU(window.getSize().x,window.getSize().y);

		musicMenu.play();

		while(window.isOpen()){
			if(i>4){
				i=0;
			}
			sf::Event event;
			while(window.pollEvent(event)){

				switch(event.type){
				case sf::Event::KeyReleased:
					switch(event.key.code){
					case sf::Keyboard::Up:
						MENU.MoveUp();
						break;

					case sf::Keyboard::Down:
						MENU.MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (MENU.GetPressedItem())
						{
						case 0:
							musicMenu.stop();
							loading();
							break;
						case 1:
							musicMenu.stop();
							highscore();
							break;
						case 2:
							musicMenu.stop();
							window.close();
							break;
						}

					}
				}

			}

			if(event.KeyPressed == sf::Keyboard::Escape){
				window.close();
			}
			if(event.type == sf::Event::Closed){
				window.close();
			}
			window.clear();
			if(clockAnimasi2.getElapsedTime()>=timeAnimasi2){
				i==0;
				clockAnimasi2.restart();
			}
			spriteBack.setTexture(textureBack[i]);
			window.draw(spriteBack);
			if(clockAnimasi.getElapsedTime()>=timeAnimasi){
				i++;
				clockAnimasi.restart();
			}
			MENU.draw(window);
			window.display();

		}
	}


	void win(int scoreGame){
		sf::Texture textureButtonNama;
		sf::Sprite spriteButtonNama;
		sf::Font fontNama;
		sf::Text textNama;
		sf::Font fontyourname;
		sf::Text textyourname;
		sf::Texture textureHighScore;
		sf::Sprite spriteHighScore;
		textureHighScore.loadFromFile("resource/new_highscore.png");
		spriteHighScore.setTexture(textureHighScore);
		textureButtonNama.loadFromFile("resource/button.png");
		spriteButtonNama.setTexture(textureButtonNama);
		spriteButtonNama.setPosition(400,500);
		fontNama.loadFromFile("resource/font.ttf");
		textNama.setFont(fontNama);
		textNama.setPosition(465,515);
		textNama.setCharacterSize(30);
		textyourname.setFont(fontNama);
		textyourname.setPosition(1366/2-200,768/2+90);
		char nama[100];
		int len=0;
		int cek_score=0;
		CButton *GO[1];
		stringstream totalscore;
		totalscore<<scoreGame;
		string Score=totalscore.str();
		GO[0]=new GameOver("OK",Score);
		GO[0]->setPosition(1366/2,636/2);
		bool cekscore=false;
		int index;
		textyourname.setString("ENTER YOUR NAME: ");
		Cuser User[5];
		ifstream file1;
		file1.open("highscore.txt",ios::binary);
		if(!file1.eof()){
			for(int i=0;i<5;i++)
			{
				file1.read((char*)&User[i],sizeof(Cuser));
			}
			file1.close();
		}


		for(int i=0; i<5; i++)
		{
			if(User[i].getscore()>=scoreGame)
			{
				cekscore=true;
				index=i;
			}

		}

		bool cekk = false;
		while (window.isOpen()){
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				
				if(event.type == sf::Event::TextEntered && cekscore==true)
				{
					if(event.text.unicode==8 && len>0)
					{
						len--;
						nama[len]='\0';

					}
					else if(event.text.unicode>=65 && event.text.unicode<=90 || event.text.unicode>=97 && event.text.unicode<=122)
					{
						nama[len]=(char)event.text.unicode;
						len++;
						nama[len]='\0';
					}
					textNama.setString(nama);
					textNama.setOrigin((textNama.getGlobalBounds().width)/2-200 ,textNama.getGlobalBounds().height/2-20);
				}

				if(event.type== sf::Event::KeyPressed){

					if(event.key.code== sf::Keyboard::Space){

						if(cekscore==true)
						{
							User[index].setall(nama,scoreGame);
							for(int i=5;i>0;i--){
								for(int j=0, k=1;k<i;j++,k++){
									if(User[j].getscore()>User[k].getscore())
									{
										Cuser swap=User[j];
										User[j]=User[k];
										User[k]=swap;
									}

								}

							}

							ofstream file;
							file.open("highscore.txt",ios::binary);

							for(int i=0;i<5;i++){
								file.write((char*)&User[i], sizeof(Cuser));

							}
							file.close();
						}
						menu();
					}
					cekk= true;
				}
			}

			window.clear();

			win_sprite.setPosition(0,0);
			if(cekscore==false){
				window.draw(win_sprite);
				window.draw(textSpace);}
			if(cekscore == true){
				window.draw(spriteHighScore);
			}



			if(cekscore==true){
				//GO[0]->draw(window);

				window.draw(textyourname);
				window.draw(textNama);
			}
			window.draw(textSpace);
			window.display();


		}


	}


	void loading(){
		sf::Texture texture_loading;
		sf::Sprite sprite_loading;
		texture_loading.loadFromFile("resource/loading.png");
		sprite_loading.setTexture(texture_loading);

		while(window.isOpen()){
			sf::Event event;

			while(window.pollEvent(event)){
				if(event.type== sf::Event::KeyPressed){
					if(event.key.code== sf::Keyboard::Space){
						play();
					}

				}

			}




			window.clear();
			window.draw(sprite_loading);
			window.display();

		}

	}

	void highscore(){
		sf::Event event;

		sf::Texture texture_highscore;
		sf::Sprite sprite_highscore;
		texture_highscore.loadFromFile("resource/highscore.png");
		sprite_highscore.setTexture(texture_highscore);
		sf::Text textnama[5];
		sf::Text textscore[5];
		sf::Text angka[5];
		sf::Text No;
		sf::Text Nama;
		sf::Text Score;
		string te;
		char score1[100];

		for(int i=0; i<5; i++)
		{

			angka[i].setFont(fontStat);
			angka[i].setColor(sf::Color::White);
			stringstream totalangkaText;
			int tempangkaText=i+1;
			totalangkaText<<tempangkaText;
			string angkaText=totalangkaText.str();
			angka[i].setString(angkaText);

		}
		for(int i=0; i<5; i++)
		{
			textnama[i].setFont(fontStat);
			textnama[i].setColor(sf::Color::White);
			textscore[i].setFont(fontStat);
			textscore[i].setColor(sf::Color::White);
		}

		No.setFont(fontStat);
		Nama.setFont(fontStat);
		Score.setFont(fontStat);

		No.setPosition(475,350);
		Nama.setPosition(580,350);
		Score.setPosition(810,350);
		No.setString("NO");
		Nama.setString("NAME");
		Score.setString("SECOND");

		angka[0].setPosition(480,400);
		angka[1].setPosition(480,450);
		angka[2].setPosition(480,500);
		angka[3].setPosition(480,550);
		angka[4].setPosition(480,600);
		textnama[0].setPosition(580,400);
		textnama[1].setPosition(580,450);
		textnama[2].setPosition(580,500);
		textnama[3].setPosition(580,550);
		textnama[4].setPosition(580,600);
		textscore[0].setPosition(810,400);
		textscore[1].setPosition(810,450);
		textscore[2].setPosition(810,500);
		textscore[3].setPosition(810,550);
		textscore[4].setPosition(810,600);


		Cuser User[5];
		ifstream file1;
		file1.open("highscore.txt",ios::binary);
		if(!file1.eof()){
			for(int i=0;i<5;i++)
			{
				file1.read((char*)&User[i],sizeof(Cuser));
			}
			file1.close();
		}

		for(int i=0; i<5; i++)
		{
			textnama[i].setString(User[i].getnama());
			sprintf(score1,"%d",User[i].getscore());
			textscore[i].setString(score1);

		}

		while(window.isOpen()){
			sf::Event event;

			while(window.pollEvent(event)){
				if(event.type== sf::Event::KeyPressed){
					if(event.key.code== sf::Keyboard::Escape){
						menu();
					}

				}

			}




			window.clear();
			window.draw(sprite_highscore);
			for(int i=0; i<5; i++)
			{
				window.draw(angka[i]);
				window.draw(textnama[i]);
				window.draw(textscore[i]);
			}
			window.draw(No);
			window.draw(Nama);
			window.draw(Score);
			window.draw(textEsc);
			window.display();

		}
	}

	void gameover(){
		/*musicMenu.stop();
		hurryUp.play();*/

		sf::SoundBuffer bufferGameOver;
		sf::Sound soundGameOver;
		bufferGameOver.loadFromFile("music/gameover.wav");
		soundGameOver.setBuffer(bufferGameOver);

		soundGameOver.play();
		
		sf::Texture texture_gameover;
		sf::Sprite sprite_gameover;
		texture_gameover.loadFromFile("resource/lose.png");
		sprite_gameover.setTexture(texture_gameover);

		while(window.isOpen()){
			sf::Event event;

			while(window.pollEvent(event)){

				if(event.type== sf::Event::KeyPressed){
					if(event.key.code== sf::Keyboard::Escape){
						soundGameOver.stop();
						menu();
					}

				}


			}





			window.clear();
			window.draw(sprite_gameover);
			window.draw(textEsc);
			window.display();

		}
	}

	void reset(){
		//map
		map.ClearFinish();
		map.ClearPlayer();
		map.ClearMap();
		map.LoadMap();

		lose=false;
		lampu=true;
		freeze=false;
		t_ghost=0;

		textTime.setFont(fontTime);
		textTime.setCharacterSize(25);
		textTime.setPosition(70,20);
		textTime.setColor(sf::Color::Red);

		map_image.push_back(sf::Sprite(floor_texture));//0 floor
		map_image.push_back(sf::Sprite(pilar_texture));//1 pillar
		map_image.push_back(sf::Sprite(pilar_texture));

		finish_sprite.setTexture(finish_texture);
		finish_sprite.setTextureRect(sf::IntRect(0,0,48,48));
		portal_sprite.setTexture(portal_texture);
		portal_sprite.setTextureRect(sf::IntRect(48*2,0,48,48));
		border_sprite.setTexture(border_texture);
		port_sprite.setTexture(port_texture);
		port_sprite.setOrigin(1263.0,696.0);


		//tampilan stat
		textVision.setFont(fontStat);
		textSpeed.setFont(fontStat);
		textFreeze.setFont(fontStat);
		textStrength.setFont(fontStat);
		textVision.setString("2");
		textSpeed.setString("3");
		textFreeze.setString("4");
		textStrength.setString("3");
		textVision.setPosition(1000,20);
		textVision.setCharacterSize(25);
		textSpeed.setPosition(1090,20);
		textSpeed.setCharacterSize(25);
		textFreeze.setPosition(1170,20);
		textFreeze.setCharacterSize(25);

		textLamaRandomItem.setFont(fontTime);
		textLamaRandomItem.setCharacterSize(25);
		textLamaRandomItem.setPosition(300,20);

		nyalalampu=2;
		lamaspeed=3;
		lamafreeze=4;
		lamagame=60;
		lamarandomitem=10;

		stat_vision.setTexture(item2);
		stat_vision.setTextureRect(sf::IntRect(0,0,48,48));
		stat_vision.setPosition(950,10);

		stat_speed.setTexture(item3);
		stat_speed.setTextureRect(sf::IntRect(0,0,48,48));
		stat_speed.setPosition(1040,10);

		stat_freeze.setTexture(item4);
		stat_freeze.setTextureRect(sf::IntRect(0,0,48,48));
		stat_freeze.setPosition(1120,10);


		temp_map=map.getm_map();
		srand(time(NULL));

		int tipe;
		item.DeleteAll();

		for(int i=0; i<30;i++){//jmlh item muncul pertama
			tipe=rand()%5;
			posisiItem.x=rand()%24;
			posisiItem.y=rand()%12;

			while(temp_map[int(posisiItem.y)][int(posisiItem.x)].GetMap()!=0 || item.cekLokasi(posisiItem.x,posisiItem.y)==true){
				posisiItem.x=rand()%24;
				posisiItem.y=rand()%12;
			}

			if(tipe==0){
				item.push_back(tipe,posisiItem,item1);
			}
			else if(tipe==1){
				item.push_back(tipe,posisiItem,item2);
			}
			else if(tipe==2){
				item.push_back(tipe,posisiItem,item3);
			}
			else if(tipe==3){
				item.push_back(tipe,posisiItem,item4);
			}
			else if(tipe==4){
				item.push_back(tipe,posisiItem,item5);
			}
		}

		player.setText(player_texture);
		player.SetDefaultPosition(map.GetPlayer());
		player.setPosisi();

		ghost[0]=new CSGhost;
		ghost[1]=new CBGhost;
		ghost[2]=new CFGhost;


		ghost[0]->SetDefaultPosition(map.GetGhost(0));
		ghost[1]->SetDefaultPosition(map.GetGhost(1));
		ghost[2]->SetDefaultPosition(map.GetGhost(2));
		for(int i=0;i<3;i++){
			ghost[i]->setPosisi();
		}


		map.BFSFinish();
		map.BFSPlayer(player.getPos().m_y,player.getPos().m_x);
	}
	void play()
	{
		reset();
		winG=0;
		lose=false;
		srand(time(NULL));
		window.setKeyRepeatEnabled(true);
		musicBackground.play();

		sf::Clock clock;
		sf::Time time;

		sf::Clock clock_port;
		sf::Time time_port;
		time_port = sf::seconds(2);

		sf::Clock clock_nyala;
		sf::Time time_nyala;
		time_nyala=sf::seconds(1);
		clockGame.restart();

		sf::Clock clockSpeedup;
		sf::Time timeSpeedup;

		sf::Clock clockfreeze;
		sf::Time timefreeze;


		sf::Clock clockstrength;
		sf::Time timestrength;

		sf::Clock clockLamaRandomItem;
		sf::Time timeLamaRandomItem;


		timeLamaRandomItem = sf::seconds(1);

		bool OnSpeed=false;

		sf::Clock clock_game;
		sf::Time time_game;
		sf::Clock clockgame;
		sf::Time timegame;

		time_game = sf::seconds(60);
		timegame = sf::seconds(1);


		timeSpeedup = sf::seconds(1);
		timefreeze = sf::seconds(1);
		timestrength = sf::seconds(1);

		waktuGame = sf::seconds(1);		

		sf::Clock cwaktu;
		sf::Time twaktu;
		twaktu=sf::seconds(1);
		cwaktu.restart();

		//efeksuara
		sf::SoundBuffer buffertime;
		sf::Sound soundtime;
		buffertime.loadFromFile("music/time.wav");
		soundtime.setBuffer(buffertime);

		sf::SoundBuffer buffervision;
		sf::Sound soundvision;
		buffervision.loadFromFile("music/vision.wav");
		soundvision.setBuffer(buffervision);

		sf::SoundBuffer bufferice;
		sf::Sound soundice;
		bufferice.loadFromFile("music/vision.wav");
		soundice.setBuffer(bufferice);

		sf::SoundBuffer bufferstrength;
		sf::Sound soundstrength;
		bufferstrength.loadFromFile("music/strength.wav");
		soundstrength.setBuffer(bufferstrength);

		sf::SoundBuffer bufferspeed;
		sf::Sound soundspeed;
		bufferspeed.loadFromFile("music/speed.wav");
		soundspeed.setBuffer(bufferspeed);

		sf::SoundBuffer buffergameover;
		sf::Sound soundgameover;
		buffergameover.loadFromFile("music/gameover.wav");
		soundgameover.setBuffer(buffergameover);


		int winx = 0;
		int x = -1;


		while(window.isOpen()){

			if(cwaktu.getElapsedTime()>=twaktu){
				winG++;
				cwaktu.restart();
			}

			stringstream totalWaktu;
			totalWaktu<<lamagame;
			string Score=totalWaktu.str();
			textTime.setString("TIME : "+Score);

			//timeStat
			stringstream totalVision;
			int tempVision=nyalalampu;
			totalVision<<tempVision;
			string Vision=totalVision.str();
			textVision.setString(Vision);

			stringstream totalSpeed;
			int tempSpeed=lamaspeed;
			totalSpeed<<tempSpeed;
			string Speed=totalSpeed.str();
			textSpeed.setString(Speed);

			stringstream totalFreeze;
			int tempFreeze=lamafreeze;
			totalFreeze<<tempFreeze;
			string Freeze=totalFreeze.str();
			textFreeze.setString(Freeze);

			stringstream totalStrength;
			int tempStrength=lamastrength;
			totalStrength<<tempStrength;
			string Strength=totalStrength.str();
			textStrength.setString(Strength);

			stringstream totalLamaRandom;
			int tempLamaRandom=lamarandomitem;
			totalLamaRandom<<tempLamaRandom;
			string LamaRandom=totalLamaRandom.str();
			textLamaRandomItem.setString("RANDOM ITEM : "+LamaRandom);


			sf::Event event;
			while(window.pollEvent(event)){
				if(event.type == sf::Event::Closed){
					window.close();
				}

				if(event.type== sf::Event::KeyPressed && player.getM_move()==false){
					if(game_pause==false){
						if(event.key.code== sf::Keyboard::Up){
							x = player.Move(map,0,strength);
						}


						if(event.key.code== sf::Keyboard::Left){
							x = player.Move(map,3,strength);
						}


						if(event.key.code== sf::Keyboard::Right){
							x = player.Move(map,1,strength);
						}


						if(event.key.code== sf::Keyboard::Down){
							x = player.Move(map,2,strength);
						}
						if(event.key.code== sf::Keyboard::P){
							play();
						}



						if(x >= 0 && x <= 2){
							ghost[x]->SetHealth(false);
							winx++;
						}
					}
					if(event.key.code== sf::Keyboard::LAlt){
						hurryUp.stop();
						if(game_pause==false){game_pause=true;}
						else{game_pause=false;}

					}
					if(event.key.code== sf::Keyboard::Escape){
						hurryUp.stop();
						menu();
					}
				}


				if(event.type == sf::Event::MouseMoved){
					sf::Vector2i mouse = sf::Mouse::getPosition(window);


				}
				if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{


				}


			}

			x = -1;


			if(winx==3){
				win(winG);
			}
			if(game_pause==false){
				if(lamagame==15){
					musicBackground.stop();
					hurryUp.play();
				}

				if(lamagame==0){
					lose=true;
					clock_game.restart();
				}

				if(clockgame.getElapsedTime()>=timegame){
					lamagame--;
					clockgame.restart();
				}


				if(clockLamaRandomItem.getElapsedTime()>=timeLamaRandomItem){
					lamarandomitem--;
					clockLamaRandomItem.restart();
				}
				if(lamarandomitem==0){
					lamarandomitem=10;
					item.Delete();
					int tipe;
					for(int i=0; i<2;i++){
						tipe=rand()%5;
						posisiItem.x=rand()%24;
						posisiItem.y=rand()%12;
						while(temp_map[int(posisiItem.y)][int(posisiItem.x)].GetMap()!=0){
							posisiItem.x=rand()%24;
							posisiItem.y=rand()%12;
						}
						if(tipe==0){
							item.push_back(tipe,posisiItem,item1);
						}
						else if(tipe==1){
							item.push_back(tipe,posisiItem,item2);
						}
						else if(tipe==2){
							item.push_back(tipe,posisiItem,item3);
						}
						else if(tipe==3){
							item.push_back(tipe,posisiItem,item4);
						}
						else if(tipe==4){
							item.push_back(tipe,posisiItem,item5);
						}
					}

				}




				port_sprite.setPosition(float(player.getPos().m_x)*48+106,float(player.getPos().m_y*48+126));
				int typeItem=-1;
				typeItem=item.cekCollision(player.getPos());

				if(typeItem==1){
					clock_port.restart();
					clock_nyala.restart();
					lampu=false;
					nyalalampu=1;
					soundvision.play();
				}
				else if(typeItem==0){lamagame+=5;soundtime.play();}
				else if(typeItem==2){player.speedup();clockSpeedup.restart();OnSpeed=true;lamaspeed=2;soundspeed.play();}
				else if(typeItem==3){freeze=true;clockfreeze.restart();lamafreeze=3;soundice.play();}
				else if(typeItem==4){strength=true;clockstrength.restart();lamastrength=3;soundstrength.play();}

				if(freeze==true){
					if(clockfreeze.getElapsedTime()>=timefreeze){
						lamafreeze--;
						clockfreeze.restart();
					}
				}
				if(strength==true){
					if(clockstrength.getElapsedTime()>=timestrength){
						lamastrength--;
						clockstrength.restart();
					}

				}
				if(OnSpeed==true){
					if(clockSpeedup.getElapsedTime()>=timeSpeedup){
						lamaspeed--;
						clockSpeedup.restart();
					}
				}

				if(lampu==false){
					if(clock_nyala.getElapsedTime()>=time_nyala){
						nyalalampu--;
						clock_nyala.restart();

					}
					if(clock_port.getElapsedTime()>=time_port){
						clock_port.restart();
						nyalalampu=2;
						lampu=true;
					}
				}

				if(nyalalampu<0){
					nyalalampu=2;
				}

				if(lamaspeed<0){
					OnSpeed=false;
					player.resetspeedup();
					lamaspeed=3;
				}

				if(lamafreeze<0){
					freeze=false;
					lamafreeze=4;
				}
				if(lamastrength<0){
					strength=false;
					lamastrength=4;
				}
				if(lamarandomitem<0){
					lamarandomitem=10;
				}


				waktu=clock.restart();
				if(freeze==false){t_ghost+=waktu.asSeconds();}
				cout<<t_ghost;
				if(t_ghost>=0.35 && freeze==false){
					for(int i=0;i<3;i++){
						if(ghost[i]->GetHealth()){
							ghost[i]->Move(lose,map);}
					}
					t_ghost=0;
				}

				if(lose==true){
					musicBackground.stop();
					gameover();
				}

				window.clear();
				draw(waktu,window,freeze);
				window.display();


			}
		}




	}






	/*sf::String getRemainingTime()
	{
	sf::String rem;
	char temp[3];
	int ss = (int)(m_time+0.5);
	rem += sf::String(itoa(ss/600, temp, 10));
	ss = ss % 600;
	rem += sf::String(itoa(ss/60, temp, 10));
	ss = ss % 60;
	rem += sf::String(":");
	rem += sf::String(itoa(ss/10, temp, 10));
	ss = ss % 10;
	rem += sf::String(itoa(ss, temp, 10));
	return rem;
	}
	bool isTimeUp()
	{
	return (m_time <= 0);
	}*/
};
