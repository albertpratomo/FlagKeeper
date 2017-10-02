#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

class CButton{
protected:
	sf::Texture textureButton;
	sf::Sprite spriteButton;
	sf::Texture textureButton1;
	sf::Sprite spriteButton1;
	sf::Texture textureButton2;
	sf::Sprite spriteButton2;
	sf::Texture texturebackground;
	sf::Sprite spritebackground;
	sf::Texture texturehighscorebackground;
	sf::Sprite spritehighscorebackground;
	sf::Texture textureButtonBack;
	sf::Sprite spriteButtonBack;
	sf::Texture texturegameover;
	sf::Sprite spritegameover;
	sf::Texture texturebuttonok;
	sf::Sprite spritebuttonok;
	sf::Font fontButtonOK;
	sf::Text textButtonOK;
	sf::Font fontYourScore;
	sf::Text textYourScore;
	sf::Font fontScore;
	sf::Text textScore;

	
public:
	CButton(){
		textureButton.loadFromFile("resource/button.png");
		spriteButton.setTexture(textureButton);
		textureButton1.loadFromFile("resource/button.png");
		spriteButton1.setTexture(textureButton1);
		textureButton2.loadFromFile("resource/button.png");
		spriteButton2.setTexture(textureButton2);
		texturebackground.loadFromFile("resource/WIN.png");
		spritebackground.setTexture(texturebackground);

	}
    virtual void draw(sf::RenderWindow &window){
		/*window.draw(spritebackground);
		window.draw(spriteButton);
		window.draw(spriteButton1);
		window.draw(spriteButton2);*/
		
	}
	virtual void setPosition(float x, float y){
		spriteButton.setPosition(x, y);
		spriteButton1.setPosition(x, y+70);
		spriteButton2.setPosition(x, y+140);
		

		//textButton.setPosition(spriteButton.getGlobalBounds().left + spriteButton.getGlobalBounds().width / 2, spriteButton.getGlobalBounds().top + spriteButton.getGlobalBounds().height / 2);
	}
	
	float getX(){
		return spriteButton.getPosition().x;
	}
	float getY(){
		return spriteButton.getPosition().y;
	}
	virtual bool isClick(float x,float y){
		if(spriteButton.getGlobalBounds().contains(x,y))
		{
			return true;
		}
		return false;
	}
	bool isClick2(float x,float y){
		if(spriteButton1.getGlobalBounds().contains(x,y))
		{
			return true;
		}
		return false;
	}
	bool isClick3(float x,float y){
		if(spriteButton2.getGlobalBounds().contains(x,y))
		{
			return true;
		}
		return false;
	}
};

//class Highscore:public CButton
//{
//public :
//	Highscore()
//	{
//		texturehighscorebackground.loadFromFile("images/highscore.png");
//		spritehighscorebackground.setTexture(texturehighscorebackground);
//		textureButtonBack.loadFromFile("images/back.png");
//		spriteButtonBack.setTexture(textureButtonBack);
//	}
//	void draw(sf::RenderWindow &window){
//		window.draw(spritehighscorebackground);
//		window.draw(spriteButtonBack);
//	
//		
//	}
//	void setPosition(float x, float y){
//		spriteButtonBack.setPosition(x, y+80);
//	}
//	bool isClick(float x,float y){
//		if(spriteButtonBack.getGlobalBounds().contains(x,y))
//		{
//			return true;
//		}
//		return false;
//	}
//};

class GameOver:public CButton
{
public :
	GameOver(char *text,string score)
	{
		texturegameover.loadFromFile("resource/button.png");
		spritegameover.setTexture(texturegameover);
		texturebuttonok.loadFromFile("resource/button.png");
		spritebuttonok.setTexture(texturebuttonok);
		spritebuttonok.setScale(0.4,0.4);

		fontButtonOK.loadFromFile("resource/font.ttf");
		textButtonOK.setFont(fontButtonOK);
		textButtonOK.setString(text);
		textButtonOK.setColor(sf::Color::Red);
		textButtonOK.setOrigin(textButtonOK.getGlobalBounds().width / 2, textButtonOK.getGlobalBounds().height / 2);
		textButtonOK.setPosition(spriteButton.getGlobalBounds().left + spritebuttonok.getGlobalBounds().width / 2, spritebuttonok.getGlobalBounds().top + spritebuttonok.getGlobalBounds().height / 2);
	
		fontYourScore.loadFromFile("resource/font.ttf");
		textYourScore.setFont(fontYourScore);
		textYourScore.setString("YOUR SCORE : ");
		fontScore.loadFromFile("resource/font.ttf");
		textScore.setFont(fontScore);	
		textScore.setString(score);
		textYourScore.setCharacterSize(60);
		textScore.setCharacterSize(60);

	}
	void draw(sf::RenderWindow &window){
		window.draw(spritegameover);
		window.draw(spritebuttonok);
		window.draw(textButtonOK);
		window.draw(textYourScore);
		window.draw(textScore);
		
	}
	void setPosition(float x, float y){
		spritebuttonok.setPosition(x-20, y+300);
		spritegameover.setPosition(x-250,y-170);
		textYourScore.setPosition(x-250,y+50);
		textScore.setPosition(x-20,y+70);
		textButtonOK.setPosition(spritebuttonok.getGlobalBounds().left + spritebuttonok.getGlobalBounds().width / 2, spritebuttonok.getGlobalBounds().top + spritebuttonok.getGlobalBounds().height / 2);
	}
	bool isClick(float x,float y){
		if(spritebuttonok.getGlobalBounds().contains(x,y))
		{
			return true;
		}
		return false;
	}
};