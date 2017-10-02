
class Node{
private :
	int type;
	sf::Vector2f posisi;
	sf::Texture texture;
	sf::Sprite sprite;

	Node *_next;
public :
	Node(){
		_next=NULL;
		posisi.x=0;
		posisi.y=0;
	}
	void set(int tipe,sf::Vector2f x,sf::Texture textureT){

		type=tipe;
		posisi=x;
		texture=textureT;


	}
	sf::Vector2f GetPos(){
		return posisi;
	}
	int GetType(){
		return type;
	}
	void setTexture(){
		sprite.setTexture(texture);
	}
	void setTextureRect(){
		sprite.setTextureRect(sf::IntRect(0,0,48,48));
	}
	void setPosition(){
		sprite.setPosition(posisi.x*48+106,posisi.y*48+126);
	}
	void next(Node* val) { _next = val; };
	sf::Sprite getSprite(){
		return sprite;
	}
	Node* next(){ return _next; };

};
class LinkItem{
private:
	Node *head, *tail;
	int count;
public :
	LinkItem(){
		head = NULL;
		tail = NULL;
		count=0;
	}
	void push_back(int type,sf::Vector2f x,sf::Texture textureT){
		if(head == NULL){
			head = new Node();
			head -> set(type,x,textureT);			
			tail = head;
			count++;
		}
		else{
			Node *temp = new Node();
			temp -> set(type,x,textureT);

			tail -> next(temp);
			tail = temp;
			count++;
		}
	}
	int type(sf::Vector2f Pos){
		if(head != NULL){
			Node * i = head;
			while(i != NULL){
				if(Pos==i->GetPos())	
				{
					return i->GetType();
					break;
				}
				i = i->next();
			}
		}
	}

	Node *posisiPos(sf::Vector2f Pos){
		int count=0;
		if(head != NULL){
			Node * i = head;
			while(i != NULL){
				if(Pos==i->GetPos())	
				{
					return i;
					break;
				}
				count++;
				i = i->next();
			}
		}

	}

	void Delete(){
		srand(time(NULL));
		int r=rand()%count;
		for(int j=0; j<count; j++){
			if(j==0){
				if(head == tail){
					delete head;
					head = NULL;				
					tail = NULL;
				}
				else{
					Node* hapus = head;
					head = head->next();
					delete hapus;
				}

			}
			else if(j==count-1){
				if(head == tail){
					delete head;
					head = NULL;
					tail = NULL;
				}
				else{
					Node* hapus = tail;
					Node* i = head;
					while(i->next() != tail)
						i = i->next();
					i->next(NULL);
					delete hapus;
					tail = i;
				}			
			}


		}

	}



	void DeleteID(Node *t){
		if(t==head){

			if(head == tail){
				delete head;
				head = NULL;				
				tail = NULL;
			}
			else{
				Node* hapus = head;
				head = head->next();
				delete hapus;
			}


		}

		else if(t==tail){
			if(head == tail){
				delete head;
				head = NULL;
				tail = NULL;
			}
			else{
				Node* hapus = tail;
				Node* i = head;
				while(i->next() != tail)
					i = i->next();
				i->next(NULL);
				delete hapus;
				tail = i;
			}			
		}
		else{

			Node * i = head->next();
			Node *prev = head;
			while(i != NULL){
				if(t==i)	
				{
					prev->next(i->next());
					delete(i);
					i=NULL;
					break;
				}
				prev=i;
				i = i->next();
			}
		}


	}

	void DeleteAll(){
		Node *temp=head;
		for(int i=0;i<count;i++){
			DeleteID(temp);
			temp=head;
			
		}
		count=0;

	}

	int cekCollision(CPosition x){

		if(head != NULL){
			Node * i = head;
			while(i != NULL){
				if(float(x.m_x)==i->GetPos().x && float(x.m_y)==i->GetPos().y){

					int temp;
					temp=i->GetType();

					DeleteID(i);
					return temp;
				}


				i = i->next();
			}
			return -1;
		}
		else{
			return -1;
		}
	}
	int getCount(){
		return count;
	}
	bool cekLokasi(int x,int y){
		if(head != NULL){
			
			Node * i = head;
			while(i != NULL){
				//cout<<i->GetPos().x<<" = "<<float(x)<<endl;
				//cout<<i->GetPos().y<<" = "<<float(y)<<endl;
				//getch();
				if(i->GetPos().x==float(x) && i->GetPos().y==float(y)){
					//cout<<"MASUK BRO ITEM";
					//getch();
					return true;
				}
				i = i->next();
			}
			return false;
		}
	}
	void draw(sf::RenderWindow &window){
		if(head != NULL){
			Node * i = head;
			while(i != NULL){
				i->setTexture();
				i->setTextureRect();
				i->setPosition();
				window.draw(i->getSprite());
				i = i->next();
			}
		}
	}

};