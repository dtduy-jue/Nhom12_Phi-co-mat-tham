#pragma once
#include"Collision.h"
#include"GeneralData.h"
extern Texture pause, unpause;
extern Texture bgme, play, Exit, name, gameover, retry;
extern SoundBuffer music, menu, click, lose;

void new_game(RenderWindow& window);
void Pause(RenderWindow& window, bool& is_game_paused,Event& event, Sprite& pause_button);
void End_game(RenderWindow& window, bool& playagain);
