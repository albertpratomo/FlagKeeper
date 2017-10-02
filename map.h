#include <SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include <vector>
#include <iomanip>
#include <queue>
#include <Windows.h>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <iostream>
using namespace std;


void gotoxy( int column, int line )


{


    COORD coord;


    coord.X = column;


    coord.Y = line;


    SetConsoleCursorPosition(


        GetStdHandle( STD_OUTPUT_HANDLE ),


        coord


        );


}


void setColor(short C) {
    /*
    1 = biru tua
    2 = hijau tua
    3 = hijau kebirubiruan
    4 = merah tua
    5 = magenta
    6 = abu abu
    7 = putih (warna default)
    8 = abu abu
    9 = biru
    10 = hijau cerah
    11 = cyan
    12 = merah cerah
    13 = pink
    14 = kuning 
    15 = putih cerah
    */
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, C);
}


struct CPosition{
    int m_x;
    int m_y;
    CPosition* m_next;
};


class QueueList{
    CPosition* m_head;
    CPosition* m_tail;
public:
    QueueList(){
        m_head = NULL;
        m_tail = NULL;
    }
    void enqueue(int y, int x){
        CPosition *late = new CPosition;
        late->m_x=x;
        late->m_y=y;
        late->m_next=NULL;


        if(!m_head)
        {
            m_head=late;
            m_tail=late;
        }
        else
        {
            m_tail->m_next=late;
            m_tail=late;
        }
    }
    CPosition dequeue(){
        if(m_head)
        {
            if(m_head == m_tail)
            {    
                CPosition temp;
                temp.m_x=m_tail->m_x;
                temp.m_y=m_tail->m_y;
                delete m_tail;
                m_head = NULL;
                m_tail = NULL;
                return temp;
            }
            else
            {
                CPosition temp;
                temp.m_x=m_head->m_x;
                temp.m_y=m_head->m_y;
                temp.m_next=m_head->m_next;
                delete m_head;
                m_head=temp.m_next;
                return temp;
            }
        }
    }
    bool isEmpty(){
        return m_head==NULL;
    }
    void print(){
        CPosition* temp=m_head;
        while(temp){
            cout << temp->m_y << "," << temp->m_x << " ";
            temp = temp->m_next;
        }
    };


};


class CNode{
    int m_finish;//aura finish
    int m_map;//apa yang ada di node
    int m_player;//aura player
    bool m_draw;
public:
    CNode(){
        m_finish = -1;
        m_player = 9;
        m_draw = true;
    }
    void SetDraw(bool draw){
        m_draw = draw;
    }
    bool GetDraw(){
        return m_draw;
    }
	void ResetMap(){
		m_map = 0;
	}
    void SetMap(int x){
		if(m_map <8){ //8 9 10 11 12 13 portal
            m_map = x;
        }
    }
    int GetMap(){
        return m_map;
    }
    void SetFinish(int x){
        if(x == -1){
            m_finish = x;
        } 
        else if(m_finish == -1){
            m_finish = x;}
    }
    void SetPlayer(int x){
        if(x == 9){
            m_player = 9;
        }
        else if(m_player == 9){
            m_player = x;
        }
    }
    int GetFinish(){
        return m_finish;
    }
    int GetPlayer(){
        return m_player;
    }
};


class CMap{
private:
    CNode **m_map;
    CPosition m_finish;
    int row, col;
    CPosition m_player;
    CPosition m_ghost[3];
    CPosition m_portal[6];
	
public:
    CMap(){
        row=12;
        col=24;
        m_map=new CNode*[row];
        for(int i=0;i<row;i++){
            m_map[i]= new CNode[col];


        }
        LoadMap();
    }

	
    void PrintMap(){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                cout << m_map[i][j].GetMap();
            }
            cout << endl;
        }
    }
        
    void PrintFinish(){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
				setColor(m_map[i][j].GetFinish());
				gotoxy(j,i);
                cout<< m_map[i][j].GetFinish();
            }
            cout << endl;
        }
    }

	void ClearMap(){
		for(int i=0; i<row; i++){
			for(int j=0;j<col;j++){
				m_map[i][j].SetMap(-1);
			}
		}
	}
    void PrintPlayer(){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
				gotoxy(j+30, i);
				setColor(m_map[i][j].GetPlayer());
                cout << m_map[i][j].GetPlayer();
            }
            cout << endl;
        }
    }

	void ResetMap(){
		for(int i=0; i<row;i++){
			for(int j=0; j< col;j++){
				m_map[i][j].ResetMap();
			}
		}
	}
    void LoadMap(){
        fstream fio;
		ResetMap();
		int r = rand()%5;
	
		string namafile;
		
		if(r==0){
			namafile = "map0.txt";
		}
		else if(r==1){
			namafile = "map1.txt";
		}
		else if(r==2){
			namafile = "map2.txt";
		}
		else if(r==3){
			namafile = "map3.txt";
		}
		else if(r==4){
			namafile = "map4.txt";
		}
		

        fio.open(namafile, ios::in);


        for(int i=0; i < 12; i++){
            for(int j=0; j< 24; j++){
                int x;
                fio >> x;
                m_map[i][j].SetMap(x);
				if(j == 2 && i == 11){  m_map[i][j].SetMap(0);}
                if(x==1){// tembok
                    m_map[i][j].SetFinish(300);//300 kan jauh dari finish, jadi hantu tidak memilih ke sana. kalau finishnya 300, tidak dimasukkan ke queue BFS
                    m_map[i][j].SetPlayer(300);
                }else if(x == 3){// finish
                    m_map[i][j].SetFinish(0);
                    m_finish.m_x=j;
                    m_finish.m_y=i;
                }else if(x == 4){// player
                    m_map[i][j].SetPlayer(0);
                    m_player.m_x = j;
                    m_player.m_y = i;
                }else if(x == 5){// smart ghost
                    m_ghost[0].m_x = j;
                    m_ghost[0].m_y = i;
                }else if(x == 6){// brave ghost
                    m_ghost[1].m_x = j;
                    m_ghost[1].m_y = i;
                }else if(x == 7){// fisher ghost
                    m_ghost[2].m_x = j;
                    m_ghost[2].m_y = i;
                }else if(x == 8){// portal 1
                    m_portal[0].m_x = j;
                    m_portal[0].m_y = i;
                    m_map[i][j].SetFinish(300);
                    m_map[i][j].SetPlayer(300);
                }else if(x == 9){// portal 2
                    m_portal[1].m_x = j;
                    m_portal[1].m_y = i;
                    m_map[i][j].SetFinish(300);
                    m_map[i][j].SetPlayer(300);
                }else if(x == 10){// portal 3
                    m_portal[2].m_x = j;
                    m_portal[2].m_y = i;
                    m_map[i][j].SetFinish(300);
                    m_map[i][j].SetPlayer(300);
                }else if(x == 11){// portal 3
                    m_portal[3].m_x = j;
                    m_portal[3].m_y = i;
                    m_map[i][j].SetFinish(300);
                    m_map[i][j].SetPlayer(300);
                }else if(x == 12){// portal 3
                    m_portal[4].m_x = j;
                    m_portal[4].m_y = i;
                    m_map[i][j].SetFinish(300);
                    m_map[i][j].SetPlayer(300);
                }else if(x == 13){// portal 3
                    m_portal[5].m_x = j;
                    m_portal[5].m_y = i;
                    m_map[i][j].SetFinish(300);
                    m_map[i][j].SetPlayer(300);
                }
            }
        }
        fio.close();
    }


    void draw(sf::RenderWindow &window){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){


            }


        }


    }


    CNode **getm_map(){
        return m_map;
    }

	void SetFinish(int x, int y, int z){
		m_map[y][x].SetFinish(z);
	}
    void SetMap(int x, int y, int z){
        if(m_map[y][x].GetMap() < 8 && m_map[y][x].GetMap() != 3){
            m_map[y][x].SetMap(z);
        }
    }


    int GetMap(int x, int y){
        return m_map[y][x].GetMap();
    }


    int GetFinish(int x, int y){
        return m_map[y][x].GetFinish();
    }


    int GetPlayer(int x, int y){
        return m_map[y][x].GetPlayer();
    }


    void SetPlayer(int x, int y, int z){
        m_map[y][x].SetPlayer(z);
    } 


    CPosition GetPortal(int x){
		if(x%2 == 1){
			return m_portal[x-3+1];
		}
		else{
			return m_portal[x-3-1];
		}
    }


    CPosition GetPlayer(){
        return m_player;
    }


    CPosition GetGhost(int i){
        return m_ghost[i];
    }


    CPosition GetFinish(){
        return m_finish;
    }
    int getcol(){
        return col;
    }
    int getrow(){
        return row;
    }




    void ClearPlayer(){
        for(int i=0; i<12;i++){
            for(int j=0; j<24;j++){
                m_map[i][j].SetPlayer(9);
            }
        }
    }


    void BFSFinish(){//mencari jarak dari hantu ke finish
        QueueList q;
        q.enqueue(m_finish.m_y,m_finish.m_x);


        while(!q.isEmpty()){
            CPosition another=q.dequeue();
            int thisFinish = m_map[another.m_y][another.m_x].GetFinish();
            if(another.m_y>0){
                if(m_map[another.m_y-1][another.m_x].GetFinish()==-1){ 
                    q.enqueue(another.m_y-1,another.m_x);
                    m_map[another.m_y-1][another.m_x].SetFinish(thisFinish+1);
                }
            }


            if(another.m_x<23){
                if(m_map[another.m_y][another.m_x+1].GetFinish()==-1){ 
                    q.enqueue(another.m_y,another.m_x+1);
                    m_map[another.m_y][another.m_x+1].SetFinish(thisFinish+1);
                }    
            }


            if(another.m_y<11){
                if(m_map[another.m_y+1][another.m_x].GetFinish()== -1 ){ 
                    q.enqueue(another.m_y+1,another.m_x);
                    m_map[another.m_y+1][another.m_x].SetFinish(thisFinish+1);            
                }
            }


            if(another.m_x>0){
                if(m_map[another.m_y][another.m_x-1].GetFinish()==-1 ){ 
                    q.enqueue(another.m_y,another.m_x-1);
                    m_map[another.m_y][another.m_x-1].SetFinish(thisFinish+1);
                }
            }
        }
    }

	void ClearFinish(){
		for(int i=0; i<row;i++){
			for(int j=0; j<col;j++){
				if(m_map[i][j].GetFinish() != 300){
					m_map[i][j].SetFinish(-1);
				}
			}
		}
	}
    void BFSPlayer(int playerY, int playerX){
        QueueList q;
        q.enqueue(playerY,playerX);


        while(!q.isEmpty()){
            CPosition another=q.dequeue();
            int thisPlayer = m_map[another.m_y][another.m_x].GetPlayer();
            if(another.m_y>0){
                if(m_map[another.m_y-1][another.m_x].GetPlayer()==9){ 
                   
					if(m_map[another.m_y-1][another.m_x].GetMap()==1){
						m_map[another.m_y-1][another.m_x].SetPlayer(300);
					}
					else{
						q.enqueue(another.m_y-1,another.m_x);
						m_map[another.m_y-1][another.m_x].SetPlayer(thisPlayer+1);
					}
                }
            }


            if(another.m_x<23){
                if(m_map[another.m_y][another.m_x+1].GetPlayer()==9){ 
					if(m_map[another.m_y][another.m_x+1].GetMap()==1){
						m_map[another.m_y][another.m_x+1].SetPlayer(300);
					}
					else{
						q.enqueue(another.m_y,another.m_x+1);
						m_map[another.m_y][another.m_x+1].SetPlayer(thisPlayer+1);
					}
				}
            }


            if(another.m_y<11){
                if(m_map[another.m_y+1][another.m_x].GetPlayer()==9){ 

					if(m_map[another.m_y+1][another.m_x].GetMap()==1){
					  m_map[another.m_y+1][another.m_x].SetPlayer(300);      
					}
					else{
						q.enqueue(another.m_y+1,another.m_x);
						m_map[another.m_y+1][another.m_x].SetPlayer(thisPlayer+1);            
					}
				}
            }


            if(another.m_x>0){
                if(m_map[another.m_y][another.m_x-1].GetPlayer()==9){ 
					if(m_map[another.m_y][another.m_x-1].GetMap()==1){
						m_map[another.m_y][another.m_x-1].SetPlayer(300);
					}
					else{
						q.enqueue(another.m_y,another.m_x-1);
						m_map[another.m_y][another.m_x-1].SetPlayer(thisPlayer+1);
					}
				}
            }
        }
    }

	

    void BFSClearPlayer(int playerY, int playerX){
        QueueList q;
        q.enqueue(playerY,playerX);


        while(!q.isEmpty()){
            CPosition another=q.dequeue();
            m_map[another.m_y][another.m_x].SetPlayer(9);
            
            if(another.m_y>0){
                if(m_map[another.m_y-1][another.m_x].GetPlayer()<9){ 
                    q.enqueue(another.m_y-1,another.m_x);
                }
            }


            if(another.m_x<23){
                if(m_map[another.m_y][another.m_x+1].GetPlayer()<9){ 
                    q.enqueue(another.m_y,another.m_x+1);
                }    
            }


            if(another.m_y<11){
                if(m_map[another.m_y+1][another.m_x].GetPlayer()<9){ 
                    q.enqueue(another.m_y+1,another.m_x);    
                }
            }
            
            if(another.m_x>0){
                if(m_map[another.m_y][another.m_x-1].GetPlayer()<9 ){ 
                    q.enqueue(another.m_y,another.m_x-1);
                }
            }
        }
    }
};