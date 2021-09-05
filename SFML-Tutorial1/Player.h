#pragma once
#include"GeneralData.h"

using namespace sf;
using namespace std;

class Player {
private:
	Sprite player;
	bool life = false;
	Vector2u size;
	int hp;
public:
	Player();
	void setTexture(Texture& texture);
	void setPos(int m_hp);
	void move(Event event, int score);
	void contact();
	void update_hp();
	bool isAlive();
	void setHP(int m_hp);
	Vector2f getPosition();
	FloatRect FloatRect();
	void rotate(Vector2i mousePosition);
	void draw(RenderWindow* window);
};
