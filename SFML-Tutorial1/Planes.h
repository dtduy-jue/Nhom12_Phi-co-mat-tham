#pragma once
#include"GeneralData.h"
using namespace sf;
using namespace std;

class Planes {
private:
	Sprite planes;
	Vector2u size;
	bool life = false;
	int hp;
	
public:
	Planes();
	void bullet();
	void setTexture(Texture& a, int air_hp);
	void move(int speed, int score);
	void draw(RenderWindow* window);
	bool getLive();
	void hit();
	void update_hp();
	void setPos(Vector2f newPos);
	Vector2f getPosition();
	FloatRect FloatRect();
};
void new_planes(vector<Planes>& planes, Clock& clock_planes, Texture aircraft[], int score);
