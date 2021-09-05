#include"Bullet.h"

Bullet::Bullet() {
	//Sprite bullet;
	//bool life = false;

}
Bullet::Bullet(Vector2f a, SoundBuffer& sound_bullet) {
	direction = a;
	sound.setBuffer(sound_bullet);
	sound.setVolume(100.f);
}
void Bullet::setTexture(Texture& a) {
	bullet.setTexture(a);
	bullet.setOrigin(a.getSize().x/2, a.getSize().y / 2);
}
void Bullet::Sfire(int speed, int &score) {
	if (bullet.getPosition().x < 0 || bullet.getPosition().x>WIDTH || bullet.getPosition().y < 0 || bullet.getPosition().y>HEIGHT) {
		life = false;
	}
	if (life == true) {
		const float Pi = 3.14159f;
		bullet.setRotation(atan2f(direction.y, direction.x) * 180 / Pi);
		bullet.move(direction.x * speed * (1 + 0.1 * sqrt(score)), direction.y * speed * (1 + 0.1 * sqrt(score)));
	}
}
void Bullet::Sfire0() {
	if (bullet.getPosition().x < 0 || bullet.getPosition().x>WIDTH || bullet.getPosition().y < 0 || bullet.getPosition().y>HEIGHT) {
		life = false;
	}
	if (life == true) {
		bullet.setRotation(180);
		bullet.move(-1.0f * AIR_BULLET_SPEED, 0.0f);
	}
}
void Bullet::sound_play() {
	sound.play();
}
Vector2f Bullet::getPosition() {
	return bullet.getPosition();
}
void Bullet::draw(RenderWindow* window) {
	window->draw(bullet);
}
void Bullet::setPosition(Vector2f newPos) {
	bullet.setPosition(newPos);
	life = true;
}
bool Bullet::isInFlight() {
	return life;
}
void Bullet::stop() {
	life = false;
}
FloatRect Bullet::FloatRect() {
	return bullet.getGlobalBounds();
}
Vector2f normalize(Vector2f a) {
	Vector2f nomar;
	float lenght = sqrt(a.x * a.x + a.y * a.y);
	nomar.x = a.x / lenght;
	nomar.y = a.y / lenght;
	return nomar;
}
void new_bullet(Texture& texture, Vector2f a, Vector2f b, vector<Bullet>& shoot) {
	Vector2f vt_air_bullet;
	vt_air_bullet = normalize(a - b);
	Bullet new_shoot(vt_air_bullet, soundBullet);
	new_shoot.setTexture(texture);
	new_shoot.setPosition(b);
	shoot.push_back(new_shoot);
	shoot.back().sound_play();
}