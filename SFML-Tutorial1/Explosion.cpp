#include"Explosion.h"

Explosion::Explosion() {
    life = false;
    type = 0;
    count = 0;
}

Explosion::Explosion(Vector2f a, Texture& texture, SoundBuffer& soundBoom, int volume, int TYPE) {
    explosition.setTexture(texture);
    explosition.setTextureRect(IntRect(0, 0, 0, 0));
    explosition.setPosition(a);
    sound.setBuffer(soundBoom);
    sound.setVolume(volume*10.f);
    life = true;
    count = 0;
    type = TYPE;
}
void Explosion::update(Texture& texture) {
    time = clock.getElapsedTime();
    if (life == true) {
        if (time.asSeconds() > 0.05) {
            explosition.setTextureRect(IntRect(50 * count, 0, 50, 50));
            explosition.setOrigin(25, 25);
            if (type == 1) {
                explosition.setScale(6, 6);
            }
            texture.setSmooth(true);
            clock.restart();
            count++;


        }
    }
}



void Explosion::end() {
    if (count == 20) {
        count = 0;
        sound.stop();
        life = false;
    }
}
void Explosion::sound_play() {
    sound.play();
}
bool Explosion::exploding() {
    return life;
}
void Explosion::draw(RenderWindow* window) {
    window->draw(explosition);
}
void new_explosion(vector<Explosion>& explosion, Texture& texture, SoundBuffer& boom, Vector2f vt, int volume, int type ) {
    Explosion explos(vt, texture, boom, volume, type);
    explosion.push_back(explos);
    explosion.back().sound_play();
}

