#include"Player.h"

Player::Player() {
	hp = 0;
}

void Player::setTexture(Texture& texture) {
	player.setTexture(texture);
	size = texture.getSize();
	player.setTextureRect(IntRect(0, 0, size.x, size.y));
	player.setOrigin(size.x/2 , size.y / 2);
}
void Player::setPos(int m_hp) {
	life = true;
	hp = m_hp;
	player.setPosition(200, HEIGHT / 2);
}
void Player::setHP(int m_hp) {
	hp = m_hp;
}
Vector2f Player::getPosition() {
	return player.getPosition();
}
FloatRect Player::FloatRect() {
	return player.getGlobalBounds();
}
void Player::contact() {
	hp = 0;
	life = false;
}
void Player::update_hp() {
	hp--;
	if (hp == 0) {
		life = false;
	}
}
bool Player::isAlive() {
	return life;
}
void Player::move(Event event, int score) {
	if (Keyboard::isKeyPressed(Keyboard::Left) && player.getPosition().x - size.x / 2 > 0) {
		player.move(-1.0f  * M_SPEED * (0.9 + 0.01 * sqrt(score)), 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && player.getPosition().x + size.x / 2 < WIDTH) {
		player.move(1.0f * M_SPEED * (0.9 + 0.01 * sqrt(score)), 0.0f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) && player.getPosition().y - size.y / 2 - 90 > 0) {
		player.move(0.0f, -1.0f * M_SPEED * (0.9 + 0.01 * sqrt(score)));
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) && player.getPosition().y + size.y / 2 < HEIGHT) {
		player.move(0.0f, 1.0f * M_SPEED * (0.9 + 0.01 * sqrt(score)));
	}
}

void Player::rotate(Vector2i mousePosition) {
	Vector2f center = player.getPosition();
	Vector2f d = Vector2f(mousePosition) - center;
	const float Pi = 3.14159f;
	player.setRotation(atan2f(d.y, d.x) * 180 / Pi);
}
void Player::draw(RenderWindow* window) {
	window->draw(player);
}
