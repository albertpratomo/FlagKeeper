#include "map.h"


class CPlayer{
    CNode *m_node;
    CPosition m_position;
    sf::Sprite m_sprite;
    sf::Texture texture;
    sf::Vector2i m_direction;
    bool m_move;
    float MOVE_TIME;
    float m_time;
	int count;
	float m_time2;
	int gerak_kaki;
public:
    CPlayer(){
        m_move=false;
        MOVE_TIME=0.3;
        gerak_kaki=6;
		count=0;
		
    }
    void setPosisi(){
        m_sprite.setPosition(m_position.m_x*48+106,m_position.m_y*48+126);
    }
    void setText(sf::Texture &textur){
        m_sprite.setTexture(textur);
        m_sprite.setTextureRect(sf::IntRect(48,48,48,48));
    }
    void SetDefaultPosition(CPosition x){
        m_position = x;
    }
    void SetNode(CNode *node){
        m_node = node;
    }
	void speedup(){
		MOVE_TIME=0.15;
		gerak_kaki=2;
	}
	void resetspeedup(){
		MOVE_TIME=0.3;
		gerak_kaki=6;
	}

    CNode* GetNode(){
        return m_node;
    }
    void update(float dt){
        if(m_move==true){
            m_time=m_time-dt;
			m_time2++;
			if(m_time2>=gerak_kaki){
				m_sprite.setTextureRect(sf::IntRect(48*count,m_direction.y*48,48,48));
				count+=2;
				if(count==4){count=0;}
			}

            if(m_direction.y==3){
                m_sprite.setPosition(m_position.m_x*48+106,m_position.m_y*48-((MOVE_TIME-m_time)/MOVE_TIME)*48+126);
			}

            if(m_direction.y==0){
                m_sprite.setPosition(m_position.m_x*48+106,m_position.m_y*48+((MOVE_TIME-m_time)/MOVE_TIME)*48+126);
			}

            if(m_direction.y==2){
                m_sprite.setPosition((m_position.m_x*48+106-((MOVE_TIME-m_time)/MOVE_TIME)*48) ,m_position.m_y*48+126);
            }

            if(m_direction.y==1){
                m_sprite.setPosition((m_position.m_x*48+((MOVE_TIME-m_time)/MOVE_TIME)*48)+106 ,m_position.m_y*48+126);
			}


            if(m_time<=0.0){

                m_move=false;
				m_sprite.setTextureRect(sf::IntRect(48*count,m_direction.y*48,48,48));
				m_time2=0;
                if(m_direction.y==3){
                    m_position.m_y--;
                }

	            if(m_direction.y==2){
                    m_position.m_x--;
                }

                if(m_direction.y==1){
                    m_position.m_x++;
                }

                if(m_direction.y==0){
                    m_position.m_y++;
                }

            }


        }


    }

	bool getM_move(){
		return m_move;
	}
    void draw(sf::RenderWindow &wind){
        wind.draw(m_sprite);
    }
    int Move(CMap &map, int in, bool strength){
        
        int x = 0;
        int y = 0;
        bool cek = false;
        if(in==3){x=-1;if(m_position.m_x + x >= 0)cek = true;m_direction.y = 2;}
        if(in==2){y=1;if( m_position.m_y + y <= 11)cek = true;m_direction.y = 0;}
        if(in==1){x=1;if(m_position.m_x + x <= 23)cek = true;m_direction.y = 1;}
        if(in==0){y=-1;if(m_position.m_y + y >= 0)cek = true;m_direction.y = 3;}
        
        if(in != -1 && cek){
            if( map.GetMap(m_position.m_x+x, m_position.m_y+y) != 3 && map.GetMap(m_position.m_x+x, m_position.m_y+y) != 1){
                map.ClearPlayer();
                map.SetMap(m_position.m_x, m_position.m_y, 0);
                
                /*m_position.m_x = m_position.m_x + x;
                m_position.m_y = m_position.m_y + y;
                */
				m_move=true;
                m_time=MOVE_TIME;
                m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
                m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
                int z = map.GetMap(m_position.m_x + x, m_position.m_y+y ) - 5;
                if(z < 3){
                    map.SetMap(m_position.m_x + x, m_position.m_y+y, 4);
                }
                else{
                    //map.ClearPlayer();
                    m_position = map.GetPortal(z);
                }
                
                map.SetPlayer(m_position.m_x + x, m_position.m_y+y, 0);
                map.BFSPlayer(m_position.m_y+y, m_position.m_x + x);
                return z;
            }
			else if(map.GetMap(m_position.m_x+x, m_position.m_y+y) == 1 && strength==true){
				map.ClearPlayer();
				if(m_position.m_x+x+x >=0 && m_position.m_x+x+x <=23 && m_position.m_y+y+y>=0 && m_position.m_y+y+y <= 11 ){
					if(map.GetMap(m_position.m_x+x+x,m_position.m_y+y+y)==0){
						map.SetMap(m_position.m_x, m_position.m_y, 0);
						map.SetMap(m_position.m_x+x+x, m_position.m_y+y+y, 1);
						map.SetFinish(m_position.m_x+x+x, m_position.m_y+y+y, 300);
						m_move=true;
						m_time=MOVE_TIME;
						m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
						m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
					
						map.SetMap(m_position.m_x+x, m_position.m_y+y,4);
						map.SetPlayer(m_position.m_x + x, m_position.m_y+y, 0);
						map.BFSPlayer(m_position.m_y+y, m_position.m_x + x);
						map.BFSFinish();

					}
				}
			}
        }
        return -1;
    }
    CPosition getPos(){
        return m_position;
    }
};
class CGhost{
protected:
    bool m_health;
    int m_tipe;
    CNode *m_node;
    CPosition m_position;
    sf::Sprite m_sprite;
    sf::Texture texture;
    sf::Vector2i m_direction;
    
public:
    CGhost(){
        texture.loadFromFile("resource/ghost.png");
        setText(texture);
    }
    virtual void Move(bool &lose, CMap &map)=0;


    void SetDefaultPosition(CPosition pos){
        m_position = pos;
    }
    void setPosisi(){
        m_sprite.setPosition(m_position.m_x*48+106,m_position.m_y*48+126);
    }
    void setText(sf::Texture &textur){
        m_sprite.setTexture(textur);
        m_sprite.setTextureRect(sf::IntRect(48,48,48,48));
    }
    void SetNode(CNode *node){
        m_node = node;
    }
    void SetHealth(bool health){
        m_health = health;


    }
    bool GetHealth(){
        return m_health;
    }
    CNode* GetNode(){
        return m_node;
    }
    void draw(sf::RenderWindow &wind){
        wind.draw(m_sprite);
    }
};
class CSGhost:public CGhost{
public:
    CSGhost(){
        m_health = true;
        m_tipe = 5;
    }
	int Decide1(CMap map, bool &flag, bool cek[4], int x[4], int y[4], int finish){
		for(int i=0; i< 4 && flag; i++){
			if(cek[i]){    
				if(map.GetFinish(m_position.m_x + x[i], m_position.m_y + y[i]) < finish && map.GetFinish(m_position.m_x + x[i], m_position.m_y + y[i]) <=2 && map.GetPlayer(map.GetFinish().m_x, map.GetFinish().m_y) >= 2){
					flag = false;
					return i;
				}
			}
		}
		return -1;
	}
	int Decide2(CMap map, bool &flag, bool cek[4], int x[4], int y[4], int finish){       
		for(int i=0; i< 4 && flag; i++){  
			if(cek[i]){
				if(map.GetPlayer(m_position.m_x + x[i], m_position.m_y + y[i]) > 4){
					if(map.GetFinish(m_position.m_x + x[i], m_position.m_y + y[i]) < finish){//mendekat ke finish
						flag = false;
						return i;
					}
				}
			}
		}
		return -1;
	}
	int Decide3(CMap map, bool &flag, bool cek[4], int x[4], int y[4], int finish){
		for(int i=0; i< 4 && flag; i++){  
			if(cek[i]){  //kalau jauh dari player, dekat ke finish
				if((map.GetFinish(m_position.m_x + x[i], m_position.m_y + y[i]) - map.GetPlayer(m_position.m_x + x[i], m_position.m_y + y[i]))< (finish - map.GetPlayer(m_position.m_x, m_position.m_y))){
					flag = false;
					return i;
				}
			}
		}
		return -1;
	}
	int Decide4(CMap map, bool &flag, bool cek[4], int x[4], int y[4], int finish){

		int tempmove[4];
		for(int i=0; i<4;i++){
			tempmove[i] = 288;
		}

		for(int i=0; i< 4; i++){  
			if(cek[i]){ 
				if((map.GetFinish(m_position.m_x + x[i], m_position.m_y + y[i]) - map.GetPlayer(m_position.m_x + x[i], m_position.m_y + y[i])) == (finish - map.GetPlayer(m_position.m_x, m_position.m_y))){ 
					if(map.GetPlayer(m_position.m_x, m_position.m_y )<= 3){
						if(map.GetPlayer(m_position.m_x + x[i], m_position.m_y + y[i]) > map.GetPlayer(m_position.m_x, m_position.m_y)){//menjauh dari player & selama bukan tembok 
							tempmove[i] = map.GetFinish(m_position.m_x + x[i], m_position.m_y + y[i]);
						}
					}
					else if(map.GetPlayer(m_position.m_x+ x[i], m_position.m_y + y[i])>3 && map.GetPlayer(m_position.m_x+ x[i], m_position.m_y + y[i])< map.GetPlayer(m_position.m_x, m_position.m_y)){ 
						tempmove[i] = map.GetFinish(m_position.m_x + x[i], m_position.m_y + y[i]);
					}
					else{
						if(map.GetPlayer(m_position.m_x + x[i], m_position.m_y + y[i]) >= map.GetPlayer(m_position.m_x, m_position.m_y)){//menjauh dari player & selama bukan tembok 
							tempmove[i] = map.GetFinish(m_position.m_x + x[i], m_position.m_y + y[i]);
						}
					}
				}
			}
		}

		float min = 288;
		int index =-1;

		for(int i=0; i<4; i++){
			if(min >= tempmove[i] && cek[i]){
				min = tempmove[i];
				index = i;
			}
		}
		if(index != -1){
			flag = false;}
		return index;
	}

	void Move(bool &lose,CMap &map){
		bool flag = true;
		int finish = map.GetFinish(m_position.m_x, m_position.m_y);
		int x[4];
		int y[4];
		bool cek[4];
		bool cek2 = false;

		for(int i=0; i< 4; i++){
			cek[i] = false;
			cek2 = false;
			x[i]=0;
			y[i]=0;
			if(i == 0){y[i] = -1;if(m_position.m_y > 0){cek2 = true;}}
			if(i == 1){x[i] = 1;if(m_position.m_x < 23){cek2 = true;}}
			if(i == 2){y[i] = 1;if(m_position.m_y < 11){cek2 = true;}}
			if(i == 3){x[i] = -1;if(m_position.m_x > 0){cek2 = true;}}

			if(cek2){
				if(map.GetMap(m_position.m_x + x[i] , m_position.m_y + y[i]) == 0 || map.GetMap(m_position.m_x + x[i], m_position.m_y + y[i]) == 3){
					cek[i] = true;
				}
			}
		}
		int i;
		if(flag)i = Decide1(map, flag,cek,x,y, finish);
		if(flag)i = Decide2(map, flag,cek,x,y, finish); 
		if(flag)i = Decide3(map, flag,cek,x,y, finish);
		if(flag)i = Decide4(map, flag,cek,x,y, finish); 

		if(i >= 0 && i <= 3){
			if(i == 0){m_direction.y = 3;}
			if(i == 1){m_direction.y = 2;}
			if(i == 2){m_direction.y = 0;}
			if(i == 3){m_direction.y = 1;}
			map.SetMap(m_position.m_x, m_position.m_y, 0);
			m_position.m_x += x[i];
			m_position.m_y += y[i];
			m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
			m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
			map.SetMap(m_position.m_x, m_position.m_y, m_tipe);
			if(m_position.m_x == map.GetFinish().m_x && m_position.m_y == map.GetFinish().m_y){
				lose = true;
				m_health = false;
			}
		}   

	}

    void Move2(bool &lose,CMap &map){


        bool flag = true;
        int tempmove[4];
		for(int i=0; i<4;i++){
			tempmove[i] = 288;
		}




        int finish = map.GetFinish(m_position.m_x, m_position.m_y);
        int x;
        int y;
        bool cek = false;
        for(int i=0; i< 4; i++){
            cek = false;
            if(i == 0){x = 0;y = -1;if(m_position.m_y > 0){cek = true;m_direction.y=3;}}//atas 
            if(i == 1){x = 1;y = 0;if(m_position.m_x < 23){cek = true;m_direction.y=2;}}//kanan
            if(i == 2){x = 0;y = 1;if(m_position.m_y < 11 ){cek = true;m_direction.y=0;}}//bawah
            if(i == 3){x = -1;y = 0;if(m_position.m_x > 0){cek = true;m_direction.y=1;}}//kiri


            if(cek && flag){    
                if(map.GetMap(m_position.m_x + x , m_position.m_y + y) == 0 || map.GetMap(m_position.m_x + x, m_position.m_y + y) == 3 ){
                    //sangat dekat dengan finish
                    if(map.GetFinish(m_position.m_x + x, m_position.m_y + y) < finish && map.GetFinish(m_position.m_x + x, m_position.m_y + y) <=2 && map.GetPlayer(map.GetFinish().m_x, map.GetFinish().m_y) >= 2){
                        map.SetMap(m_position.m_x, m_position.m_y, 0);
                        m_position.m_x += x;
                        m_position.m_y += y;
                        m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
                        m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
                        map.SetMap(m_position.m_x, m_position.m_y, m_tipe);
                        flag = false;
                    }
                    //kalau masih jauh dari player, akan mendekati finish
                    else if(map.GetPlayer(m_position.m_x + x, m_position.m_y + y) > 4){
                        if(map.GetFinish(m_position.m_x + x, m_position.m_y + y) < finish){//mendekat ke finish
                            map.SetMap(m_position.m_x, m_position.m_y, 0);
                            m_position.m_x += x;
                            m_position.m_y += y;
                            m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
                            m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
                            map.SetMap(m_position.m_x, m_position.m_y, m_tipe);
                            flag = false;
                        }
                    }
                    //kalau jauh dari player, dekat ke finish
                    else if((map.GetFinish(m_position.m_x + x, m_position.m_y + y) - map.GetPlayer(m_position.m_x + x, m_position.m_y + y))< (finish - map.GetPlayer(m_position.m_x, m_position.m_y))){
                        map.SetMap(m_position.m_x, m_position.m_y, 0);
                        m_position.m_x += x;
                        m_position.m_y += y;
                        m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
                        m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
                        map.SetMap(m_position.m_x, m_position.m_y, m_tipe);
                        flag = false;
                    }
					else if((map.GetFinish(m_position.m_x + x, m_position.m_y + y) - map.GetPlayer(m_position.m_x + x, m_position.m_y + y)) == (finish - map.GetPlayer(m_position.m_x, m_position.m_y))){ 
						if(map.GetPlayer(m_position.m_x, m_position.m_y )<= 3){
							 if(map.GetPlayer(m_position.m_x + x, m_position.m_y + y) > map.GetPlayer(m_position.m_x, m_position.m_y) && map.GetMap(m_position.m_x + x, m_position.m_y + y)!= 1){//menjauh dari player & selama bukan tembok 
								 tempmove[i] = map.GetFinish(m_position.m_x + x, m_position.m_y + y);
							}
						}
						else if(map.GetPlayer(m_position.m_x+ x, m_position.m_y + y)>3 && map.GetPlayer(m_position.m_x+ x, m_position.m_y + y)< map.GetPlayer(m_position.m_x, m_position.m_y)){ 
							tempmove[i] = map.GetFinish(m_position.m_x + x, m_position.m_y + y);
						}
					}
                    //kalau player dekat dan menjauh dari finish
                    else{
                        if(map.GetPlayer(m_position.m_x + x, m_position.m_y + y) >= map.GetPlayer(m_position.m_x, m_position.m_y) && map.GetMap(m_position.m_x + x, m_position.m_y + y)!= 1){//menjauh dari player & selama bukan tembok 
                            tempmove[i] = map.GetFinish(m_position.m_x + x, m_position.m_y + y);
							m_health = false;
                        }
                    }
                }
            };        
        };
        
        if(flag){
            float min = 12*24;
            int index =-1;


            for(int i=0; i<4; i++){
				 if(i == 0){x = 0;y = -1;if(m_position.m_y > 0){cek = true;m_direction.y=3;}}//atas 
				if(i == 1){x = 1;y = 0;if(m_position.m_x < 23){cek = true;m_direction.y=2;}}//kanan
				if(i == 2){x = 0;y = 1;if(m_position.m_y < 11 ){cek = true;m_direction.y=0;}}//bawah
				if(i == 3){x = -1;y = 0;if(m_position.m_x > 0){cek = true;m_direction.y=1;}}//kiri
                if(cek && (map.GetMap(m_position.m_x + x , m_position.m_y + y) == 0 || map.GetMap(m_position.m_x + x, m_position.m_y + y) == 3)){
                    if(min >= tempmove[i]){
                        min = tempmove[i];
                        index = i;
                    }
                }
            }

			if(index!= -1){
				
				if(index == 0){x = 0;y = -1;if(m_position.m_y > 0){cek = true;m_direction.y=3;}}//atas 
				if(index == 1){x = 1;y = 0;if(m_position.m_x < 23){cek = true;m_direction.y=2;}}//kanan
				if(index == 2){x = 0;y = 1;if(m_position.m_y < 11 ){cek = true;m_direction.y=0;}}//bawah
				if(index == 3){x = -1;y = 0;if(m_position.m_x > 0){cek = true;m_direction.y=1;}}//kiri
                map.SetMap(m_position.m_x, m_position.m_y, 0);
                m_position.m_x += x;
                m_position.m_y += y;
                m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
                m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
                map.SetMap(m_position.m_x, m_position.m_y, m_tipe);
            }

        }
    }
};
class CBGhost:public CGhost{
public:
    CBGhost(){
        m_health = true;
        m_tipe = 6;
    }
    void Move(bool &lose, CMap &map){
        bool flag = true;
        int finish = map.GetFinish(m_position.m_x, m_position.m_y);
        int x;
        int y;
        bool cek = false;
        for(int i=0; i< 4; i++){
            cek = false;
            if(i == 0){x = 0;y = -1;if(m_position.m_y > 0)cek = true;m_direction.y=3;}//atas 
            if(i == 1){x = 1;y = 0;if(m_position.m_x < 23)cek = true;m_direction.y=2;}//kanan
            if(i == 2){x = 0;y = 1;if(m_position.m_y < 11 )cek = true;m_direction.y=0;}//bawah
            if(i == 3){x = -1;y = 0;if(m_position.m_x > 0)cek = true;m_direction.y=1;}//kiri


            if(cek && flag){    
                if(map.GetMap(m_position.m_x + x , m_position.m_y + y) == 0 || map.GetMap(m_position.m_x + x, m_position.m_y + y) == 3 ){
                    if(map.GetFinish(m_position.m_x + x, m_position.m_y + y) < finish){//mendekat ke finish
                        map.SetMap(m_position.m_x, m_position.m_y, 0);
                        m_position.m_x += x;
                        m_position.m_y += y;
                        m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
                        m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
                        map.SetMap(m_position.m_x, m_position.m_y, m_tipe);
                        flag = false;
                    }
                }
            }
        }


    
    
        if(m_position.m_x == map.GetFinish().m_x && m_position.m_y == map.GetFinish().m_y){
            lose = true;
        }
    }
};
class CFGhost:public CGhost{
public:
    CFGhost(){
        m_health = true;
        m_tipe = 7;
    }

	int Decide1(CMap map, bool &flag, bool cek[4], int x[4], int y[4], int finish){
		for(int i=0; i< 4 && flag; i++){
			if(cek[i]){    
				if(map.GetFinish(m_position.m_x + x[i], m_position.m_y + y[i]) < finish && map.GetFinish(m_position.m_x + x[i], m_position.m_y + y[i]) < 3 && map.GetPlayer(map.GetFinish().m_x, map.GetFinish().m_y) > 1){
					flag = false;
					return i;
				}
			}
		}
		return -1;
	}
	int Decide2(CMap map, bool &flag, bool cek[4], int x[4], int y[4], int finish){
		for(int i=0; i< 4 && flag; i++){
			if(cek[i]){    
				if(map.GetPlayer(m_position.m_x, m_position.m_y) < 4){
					if(map.GetPlayer(m_position.m_x + x[i], m_position.m_y + y[i]) >= map.GetPlayer(m_position.m_x, m_position.m_y)){
						flag = false;
						return i;
					}
				}
			}
		}
		return -1;
	}
	int Decide3(CMap map, bool &flag, bool cek[4], int x[4], int y[4], int finish){
		for(int i=0; i< 4 && flag; i++){
			if(cek[i]){    
				if(map.GetPlayer(m_position.m_x, m_position.m_y) <9){
					if(map.GetPlayer(m_position.m_x + x[i], m_position.m_y + y[i]) < map.GetPlayer(m_position.m_x, m_position.m_y)){
						flag = false;
						return i;
					}
				}
			}
		}
		return -1;
	}
	int Decide4(CMap map, bool &flag, bool cek[4], int x[4], int y[4], int finish){
		for(int i=0; i< 4 && flag; i++){
			if(cek[i]){    
				if(map.GetFinish(m_position.m_x + x[i], m_position.m_y + y[i]) < finish){
					flag = false;
					return i;
				}
			}
		}
		return -1;
	}

	void Move(bool &lose, CMap &map){
		bool flag = true;
		int finish = map.GetFinish(m_position.m_x, m_position.m_y);
		int x[4];
		int y[4];
		bool cek[4];
		bool cek2 = false;

		for(int i=0; i< 4; i++){
			cek[i] = false;
			cek2 = false;
			x[i]=0;
			y[i]=0;
			if(i == 0){y[i] = -1;if(m_position.m_y > 0){cek2 = true;}}
			if(i == 1){x[i] = 1;if(m_position.m_x < 23){cek2 = true;}}
			if(i == 2){y[i] = 1;if(m_position.m_y < 11){cek2 = true;}}
			if(i == 3){x[i] = -1;if(m_position.m_x > 0){cek2 = true;}}

			if(cek2){
				if(map.GetMap(m_position.m_x + x[i] , m_position.m_y + y[i]) == 0 || map.GetMap(m_position.m_x + x[i], m_position.m_y + y[i]) == 3){
					cek[i] = true;
				}
			}
		}

		int i;
		if(flag)i = Decide1(map, flag,cek,x,y, finish);
		if(flag)i = Decide2(map, flag,cek,x,y, finish); 
		if(flag)i = Decide3(map, flag,cek,x,y, finish);
		if(flag)i = Decide4(map, flag,cek,x,y, finish); 

		if(i != -1){
			if(i == 0){m_direction.y = 3;}
			if(i == 1){m_direction.y = 2;}
			if(i == 2){m_direction.y = 0;}
			if(i == 3){m_direction.y = 1;}
			map.SetMap(m_position.m_x, m_position.m_y, 0);
			m_position.m_x += x[i];
			m_position.m_y += y[i];
			m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
			m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
			map.SetMap(m_position.m_x, m_position.m_y, m_tipe);

			if(m_position.m_x == map.GetFinish().m_x && m_position.m_y == map.GetFinish().m_y){
				lose = true;
				m_health = false;
			}
		}      

		
	}
    void Move2(bool &lose, CMap &map){
        bool flag = true;
        int finish = map.GetFinish(m_position.m_x, m_position.m_y);
        int x;
        int y;
        bool cek = false;
        for(int i=0; i< 4; i++){
            cek = false;
            if(i == 0){x = 0;y = -1;if(m_position.m_y > 0)cek = true;m_direction.y=3;}//atas 
            if(i == 1){x = 1;y = 0;if(m_position.m_x < 23)cek = true;m_direction.y=2;}//kanan
            if(i == 2){x = 0;y = 1;if(m_position.m_y < 11 )cek = true;m_direction.y=0;}//bawah
            if(i == 3){x = -1;y = 0;if(m_position.m_x > 0)cek = true;m_direction.y=1;}//kiri




            if(cek && flag){    
                if(map.GetMap(m_position.m_x + x , m_position.m_y + y) == 0 || map.GetMap(m_position.m_x + x, m_position.m_y + y) == 3 ){
                    if(map.GetFinish(m_position.m_x + x, m_position.m_y + y) < finish && map.GetFinish(m_position.m_x + x, m_position.m_y + y) < 3 && map.GetPlayer(map.GetFinish().m_x, map.GetFinish().m_y) > 1){
                        map.SetMap(m_position.m_x, m_position.m_y, 0);
                        m_position.m_x += x;
                        m_position.m_y += y;
                        m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
                        m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
                        map.SetMap(m_position.m_x, m_position.m_y, m_tipe);
                        flag = false;
                    }
                    else if(map.GetPlayer(m_position.m_x, m_position.m_y) < 4){
                        //menjauh dari player
                        if(map.GetPlayer(m_position.m_x + x, m_position.m_y + y) >= map.GetPlayer(m_position.m_x, m_position.m_y)){
                            map.SetMap(m_position.m_x, m_position.m_y, 0);
                            m_position.m_x += x;
                            m_position.m_y += y;
                            m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
                            m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
                            map.SetMap(m_position.m_x, m_position.m_y, m_tipe);
                            flag = false;
                        }
                    }
                else if(map.GetPlayer(m_position.m_x, m_position.m_y) <9){
                        //mendekat ke player
                        if(map.GetPlayer(m_position.m_x + x, m_position.m_y + y) < map.GetPlayer(m_position.m_x, m_position.m_y)){
                            map.SetMap(m_position.m_x, m_position.m_y, 0);
                            m_position.m_x += x;
                            m_position.m_y += y;
                            m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
                            m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
                            map.SetMap(m_position.m_x, m_position.m_y, m_tipe);
                            flag = false;
                        }
                    }
                    else{
                        //mendekat finish
                        if(map.GetFinish(m_position.m_x + x, m_position.m_y + y) < finish){
                            map.SetMap(m_position.m_x, m_position.m_y, 0);
                            m_position.m_x += x;
                            m_position.m_y += y;
                            m_sprite.setTextureRect(sf::IntRect(48,m_direction.y*48,48,48));
                            m_sprite.setPosition(48*m_position.m_x+106,48*m_position.m_y+126);
                            map.SetMap(m_position.m_x, m_position.m_y, m_tipe);
                            flag = false;
                        }
                    }
                }
            };
        
        }


        


        if(m_position.m_x == map.GetFinish().m_x && m_position.m_y == map.GetFinish().m_y){
            lose = true;
        }
    }
};

class Cuser{
private:
	char nama[100];
	int skor;
public:
	Cuser(){
		skor=0;
	}
	void setall(char _nama[100],int _skor){
		strcpy(nama,_nama);
		skor=_skor;
	}
	int getscore(){
		return skor;
	}
	char* getnama(){
		return nama;
	}
};
