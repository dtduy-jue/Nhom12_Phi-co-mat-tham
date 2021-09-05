#include"Collision.h"

void player_and_planes(Player& player, vector<Planes>& planes,
    int& die, int& score, Clock& clock_re_live, vector< Explosion>& big_explosion) {
    if (planes.size() > 0) {
        for (int i = 0; i < planes.size(); i++) {
            if (player.isAlive() == true && planes[i].getLive() == true) {
                if (planes[i].FloatRect().intersects(player.FloatRect())) {
                    planes[i].hit();
                    score += 10;
                    Time time_respawn = clock_re_live.getElapsedTime();
                    new_explosion(big_explosion, explosion, bigBoom, planes[i].getPosition(), BIG_EXPLOSION_VOLUME, BIG_EXPLOSION);
                    if (time_respawn.asSeconds() > 5) {
                        clock_re_live.restart();
                        player.contact();
                        die++;
                        new_explosion(big_explosion, explosion, bigBoom, player.getPosition(), BIG_EXPLOSION_VOLUME, BIG_EXPLOSION);
                    }
                }
            }
        }
    }
}
void player_and_air_bullet(Player& player, vector<Bullet>&air_shoot, int& die, Clock& clock_re_live, vector< Explosion>& big_explosion, vector< Explosion>& small_explosion) {
    if (air_shoot.size() > 0) {
        for (int j = 0; j < air_shoot.size(); j++) {
            if (air_shoot[j].isInFlight() == true && player.isAlive() == true) {
                if (player.FloatRect().intersects(air_shoot[j].FloatRect())) {
                    air_shoot[j].stop();
                    Time time_respawn = clock_re_live.getElapsedTime();
                    if (time_respawn.asSeconds() > 5) {
                        player.update_hp();
                    }
                    if (player.isAlive() == true) {
                        new_explosion(small_explosion, explosion, boom, air_shoot[j].getPosition(), SMALL_EXPLOSION_VOLUME, SMALL_EXPLOSION);
                    }

                    else {
                        die++;
                        new_explosion(big_explosion, explosion, bigBoom, player.getPosition(), BIG_EXPLOSION_VOLUME, BIG_EXPLOSION);
                        clock_re_live.restart();
                    }
                }
            }
        }
    }
}
void player_bullet_and_planes(vector<Bullet>&m_shoot, vector<Planes>& planes, int& score, vector<Explosion>& big_explosion, vector< Explosion>& small_explosion) {
    if (planes.size() > 0 && m_shoot.size()>0) {
        for (int i = 0; i < planes.size(); i++) {
            for (int j = 0; j < m_shoot.size(); j++) {
                if (m_shoot[j].isInFlight() == true && planes[i].getLive() == true) {
                    if (m_shoot[j].FloatRect().intersects(planes[i].FloatRect())) {
                        m_shoot[j].stop();
                        planes[i].update_hp();
                        if (planes[i].getLive()==true) {
                            new_explosion(small_explosion, explosion, boom, m_shoot[j].getPosition(), SMALL_EXPLOSION_VOLUME, SMALL_EXPLOSION);

                        }
                        else {
                            score += 10;
                            new_explosion(big_explosion, explosion, boom, planes[i].getPosition(), BIG_EXPLOSION_VOLUME, BIG_EXPLOSION);
                        }
                    }
                }
            }
        }
    }
}
void player_bullet_and_air_bullet( vector<Bullet>&m_shoot, vector<Bullet>& air_shoot, vector<Explosion>& small_explosion) {
    if (m_shoot.size() > 0 && air_shoot.size()>0) {
        for (int i = 0; i < m_shoot.size(); i++) {
            for (int n = 0; n < air_shoot.size(); n++) {
                if (m_shoot[i].isInFlight() == true && air_shoot[n].isInFlight() == true) {
                    if (m_shoot[i].FloatRect().intersects(air_shoot[n].FloatRect())) {
                        m_shoot[i].stop();
                        air_shoot[n].stop();
                        new_explosion(small_explosion, explosion, boom, m_shoot[i].getPosition(), SMALL_EXPLOSION_VOLUME, SMALL_EXPLOSION);
                    }
                }
            }
        }
    }
}