#pragma once

#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<vector>
using namespace sf;
using namespace std;

class Explosion {
private:
	Sprite explosition;
	Sound sound;
	bool life;
	int count;
	int type;
	Clock clock;
	Time time;

public:
	Explosion();
	Explosion(Vector2f a, Texture& texture, SoundBuffer& soundBoom, int volume, int TYPE);
	void update(Texture& texture);
	void end();
	void sound_play();
	bool exploding();
	void draw(RenderWindow* window);
};
void new_explosion(vector<Explosion>& explosion, Texture& texture, SoundBuffer& boom, Vector2f vt, int volume, int type);