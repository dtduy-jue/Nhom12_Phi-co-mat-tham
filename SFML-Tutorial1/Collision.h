#pragma once
#pragma once
#include"Bullet.h"
#include"Planes.h"
#include"Player.h"
#include"Explosion.h"
#include <SFML/Audio.hpp>
#include<math.h>

extern SoundBuffer bigBoom, boom;
extern Texture explosion;


void player_and_planes(Player& player, vector<Planes>& planes, int& die, int& score, Clock& clock_re_live, vector< Explosion>& big_explosion);
void player_and_air_bullet(Player& player, vector<Bullet>& air_shoot, int& die, Clock& clock_re_live, vector< Explosion>& big_explosion, vector< Explosion>&small_explosion);
void player_bullet_and_planes(vector<Bullet>& m_shoot, vector<Planes>& planes, int& score, vector< Explosion>& big_explosion, vector< Explosion>& small_explosion);
void player_bullet_and_air_bullet(vector<Bullet>& m_shoot, vector<Bullet>& air_shoot, vector< Explosion>& small_explosion);