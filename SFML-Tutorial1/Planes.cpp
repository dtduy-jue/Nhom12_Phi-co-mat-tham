#include"Planes.h"

Planes::Planes() {
	hp = 0;
}

void Planes::setTexture(Texture& a, int air_hp) {
	planes.setTexture(a);
	size = a.getSize();
	planes.setOrigin(size.x / 2, size.y / 2);
	hp = air_hp;
}

void Planes::move(int speed, int score) {

	if (planes.getPosition().x + size.x / 2 < 0) life = false;
	if (life == true) {

		
		int straight_direction = rand() % 2; //Quyet dinh dich co di thang hay khong
		if (straight_direction == 1) {
			planes.move(-1.0f * speed * (1 + 0.08 * sqrt(score)), 0.0f);
		}
		else if (straight_direction == 0) {
			
			int flag = rand() % 2;

			if (flag == 0) //Di xuong
			{
				
				int sp = rand() % 3 + 1;
				if (planes.getPosition().y < HEIGHT - size.y/2) {
					planes.move(-1.f* speed, 1.f * (sp + 0.05 * sqrt(score)));
				}
				else {
					planes.move(-0.7f* speed, 0.f);
				}
			}
			else  //Di len
			{
				int sp = rand() % 3 + 1;
				if (planes.getPosition().y > size.y + 10) {
					planes.move(-1.0f * speed, -1.f * (sp + 0.05 * sqrt(score)));
				}
				else {
					planes.move(-0.7f * speed, 0.0f);
				}
			}
		}
	}
}

void Planes::draw(RenderWindow* window) {
	window->draw(planes);
}
void Planes::setPos(Vector2f newPos) {
	planes.setPosition(newPos.x, newPos.y);
	life = true;
}
bool Planes::getLive() {
	return life;
}
void Planes::hit() {
	hp = 0;
	life = false;
}
void Planes::update_hp() {
	hp--;
	if (hp == 0) {
		life = false;
	}
}
FloatRect Planes::FloatRect() {
	return planes.getGlobalBounds();
}
Vector2f Planes::getPosition() {
	return planes.getPosition();
}
void new_planes(vector<Planes>& planes, Clock& clock_planes, Texture aircraft[], int score) {
	Time time_next_planes = clock_planes.getElapsedTime();
	if (time_next_planes.asSeconds() > TIME_NEXT_PLANE - 0.075 * sqrt((double)score)) {
		Planes a;
		int y, x;
		srand((unsigned int)time(NULL));
		y = rand() % 8 + 2;
		x = rand() % 4;
		a.setTexture(aircraft[x], x + 1);
		a.setPos(Vector2f(1500.0f +aircraft[x].getSize().x/2 , 70 * (float)y));
		planes.push_back(a);
		clock_planes.restart();
	}
}