#pragma once
#pragma once
#include"GeneralData.h"
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

extern SoundBuffer soundBullet;
class Bullet {
private:
    Sprite bullet;
    bool life = false;
    Vector2f direction;
    Sound sound;
public:
    Bullet();
    Bullet(Vector2f a, SoundBuffer& sound_bullet);
    void setTexture(Texture& a);
    void Sfire(int speed, int &score);
    void Sfire0();
    Vector2f getPosition();
    void setPosition(Vector2f newPos);
    void draw(RenderWindow* window);
    bool isInFlight();
    void stop();
    void sound_play();
    FloatRect FloatRect();
};
Vector2f normalize(Vector2f a);
void new_bullet(Texture& texture, Vector2f a, Vector2f b, vector<Bullet>& shoot);