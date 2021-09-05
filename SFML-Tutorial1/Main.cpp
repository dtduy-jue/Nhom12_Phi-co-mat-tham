
#include"Collision.h"
#include"NewDrawPauseEnd.h"
#include<cstdlib>
#include <sstream>
#include <string>
#include<fstream>
#include <chrono>
Texture retry, gameover, name;
Texture bgme, play, Exit;
SoundBuffer music, menu, click, lose, boom, bigBoom, soundBullet, gameOver;
Texture player_aircraft[3], player11, player22, player33,  explosion, crosshair, background, bullet, airbullet, life, pause, unpause;
Texture enemy_aircraft[4];
Font font;
Player player;

void load_from_file() {
    name.loadFromFile("graphics/name.png");
    retry.loadFromFile("graphics/retry.png");
    gameover.loadFromFile("graphics/gameover.png");
    bgme.loadFromFile("graphics/backgroundmenu.jpg");
    play.loadFromFile("graphics/play.png");
    Exit.loadFromFile("graphics/exit.png");
    music.loadFromFile("sounds/music.wav");
    menu.loadFromFile("sounds/mainMenu.wav");
    click.loadFromFile("sounds/click.wav");
    lose.loadFromFile("sounds/gameOver.wav");
    boom.loadFromFile("sounds/soundBoom.wav");
    bigBoom.loadFromFile("sounds/soundBigBoom.wav");
    soundBullet.loadFromFile("sounds/soundBullet.wav");
    gameOver.loadFromFile("sounds/gameOver.wav");
    enemy_aircraft[0].loadFromFile("graphics/aircraft1.png");
    enemy_aircraft[1].loadFromFile("graphics/aircraft2.png");
    enemy_aircraft[2].loadFromFile("graphics/aircraft3.png");
    enemy_aircraft[3].loadFromFile("graphics/aircraft4.png");
    bullet.loadFromFile("graphics/bullet.png");
    airbullet.loadFromFile("graphics/airbullet.png");
    background.loadFromFile("graphics/background.jpg");
    player_aircraft[1].loadFromFile("graphics/player2.png");
    player_aircraft[0].loadFromFile("graphics/player1.png");
    player_aircraft[2].loadFromFile("graphics/player3.png");
    player22.loadFromFile("graphics/player2-1.png");
    player11.loadFromFile("graphics/player1-1.png");
    player33.loadFromFile("graphics/player3-1.png");
    explosion.loadFromFile("graphics/Explosition.png");
    crosshair.loadFromFile("graphics/crosshair.png");
    life.loadFromFile("graphics/life.png");
    pause.loadFromFile("graphics/pause.png");
    unpause.loadFromFile("graphics/unpause.png");

    font.loadFromFile("font/times.ttf");
}

//Ve do hoa ra man hinh
void draw(RenderWindow& window, vector<Planes>& planes, vector<Bullet>& air_shoot, vector<Bullet>& m_shoot,
    vector< Explosion>& big_explosion, vector< Explosion>& small_explosion, bool& is_game_paused,
    Sprite mouse, Sprite Life, Sprite pause_button, Text text_score, Text text_high_score) 
{
    //Xoa dan cua nguoi choi
    if (m_shoot.size() > 0) 
    {
        for (int j = 0; j < m_shoot.size(); j++) {
            if (m_shoot[j].isInFlight() == false) {
                m_shoot.erase(m_shoot.begin() + j);
            }
            else {
                m_shoot[j].draw(&window);
            }
        }
    }

    if (air_shoot.size() > 0) {
        for (int i = 0; i < air_shoot.size(); i++) {
            if (air_shoot[i].isInFlight() == false) {
                air_shoot.erase(air_shoot.begin() + i);
            }
            else {
                air_shoot[i].draw(&window);
            }
        }
    }

    if (planes.size() > 0) {
        for (int j = 0; j < planes.size(); j++) {
            if (planes[j].getLive() == false) {
                planes.erase(planes.begin() + j);
            }
            else {
                planes[j].draw(&window);
            }
        }
    }

    if (player.isAlive() == true) {
        player.draw(&window);
    }

    if (big_explosion.size() > 0) {
        for (int i = 0; i < big_explosion.size(); i++) {
            if (big_explosion[i].exploding() == true)
                big_explosion[i].draw(&window);
            else {
                big_explosion.erase(big_explosion.begin() + i);
            }
        }
    }

    if (small_explosion.size() > 0) {
        for (int i = 0; i < small_explosion.size(); i++) {
            if (small_explosion[i].exploding() == true)
                small_explosion[i].draw(&window);
            else {
                small_explosion.erase(small_explosion.begin() + i);
            }
        }
    }

    if (!is_game_paused)
        window.draw(mouse);
    window.draw(text_score);
    window.draw(text_high_score);
    window.draw(Life);
    window.draw(pause_button);

}

int main()
{
   
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "PHI CO MAT THAM", sf::Style::Close);
    window.setFramerateLimit(60);

    load_from_file();

    //Menu//
    new_game(window);

TryAgain:
    bool playagain = false;
    //mở file lấy điểm cao
    fstream FILE;
    int high_score;
    FILE.open("highScore.txt", ios::in);
    FILE >> high_score;
    FILE.close();
    //
    bool new_high_score = false;
    int score = 0;

    //tạo chữ hiện điểm và điểm cao
    Text text_score, text_high_score;
    string string_score, string_high_score;
    text_score.setFont(font);
    text_score.setCharacterSize(50);
    text_score.setFillColor(Color::Red);
    text_score.setPosition(300, 0);
    text_score.setStyle(sf::Text::Bold);

    text_high_score.setFont(font);
    text_high_score.setCharacterSize(50);
    text_high_score.setFillColor(Color::Red);
    text_high_score.setPosition(700, 0);
    text_high_score.setStyle(sf::Text::Bold);
    //
    Sprite Background(background);
    Background.setScale(1.5f, 1.2f);
    // cài đặt hiệu ứng chuột
    window.setMouseCursorVisible(false);
    Sprite mouse;
    mouse.setTexture(crosshair);
    mouse.setOrigin(25, 25);
    //

    // cài đặt thanh sinh mạng
    Sprite Life;
    Life.setTexture(life);
    Life.setPosition(1200, 0);
    //

    // cài đặt nút pause
    Sprite pause_button(pause);
    bool is_game_paused = false;
    //
    
    int die = 0;
    vector<Explosion>big_explosion;
    vector<Explosion>small_explosion;
    vector<Planes> planes;
    vector<Bullet>m_shoot;
    vector<Bullet>air_shoot;


  //  Player player;

    player.setPos(1);

    Clock clock_m_bullet;
    Clock clock_planes;
    Clock clock_bullet_planes[20];
    Clock clock_respawn;
    Time time_next_bullet_planes[20];


    Sound sound_gameOver(gameOver);
    bool is_play_sound_gameOver = true;
    while (window.isOpen())
    {
        window.clear();
        window.draw(Background);
        Life.setTextureRect(IntRect(0, 0, 270 - 90 * die, 66));
        if (die != DIE) {
            sf::Event event{};
            if (score > high_score) {
                high_score = score;
                new_high_score = true;
            }
            
         
            Pause(window, is_game_paused, event, pause_button);
            //

            if (!is_game_paused)
            {
                
                //chuyển điểm từ kiểu int sang string
                ostringstream convert_score, convert_high_score;
                convert_score << score;
                convert_high_score << high_score;
                string_score = convert_score.str();
                string_high_score = convert_high_score.str();
                //
                //cập nhập điểm hiển thị trên màn hình
                text_score.setString("Score: " + string_score);
                text_high_score.setString("High Score: " + string_high_score);
                //

                player.move(event, score);

                Time time_respawn = clock_respawn.getElapsedTime();
                if (score < LEVER1) {
                    player.setTexture(player_aircraft[0]);
                    if (score == 0) {
                        player.setTexture(player11);
                        
                        player.setHP(1);
                    }
                    if (player.isAlive() == false && time_respawn.asSeconds() >= 2) {
                        player.setPos(1);
                    }
                    if (time_respawn.asSeconds() <= 5) {
                        player.setTexture(player11);
                    }
                }
                else if (score >= LEVER1 && score < LEVER2) {
                    player.setTexture(player_aircraft[1]);
                    if (score == LEVER1) {
                        player.setTexture(player22);
                        player.setHP(2);
                    }
                    if (player.isAlive() == false && time_respawn.asSeconds() >= 2) {
                        player.setPos(2);
                    }
                    if (time_respawn.asSeconds() <= 5) {
                        player.setTexture(player22);
                    }
                }
                else if (score >= LEVER2) {
                    player.setTexture(player_aircraft[2]);
                    if (score == LEVER2) {
                        player.setTexture(player33);
                        player.setHP(3);
                    }
                    if (player.isAlive() == false && time_respawn.asSeconds() >= 2) {
                        player.setPos(3);
                    }
                    if (time_respawn.asSeconds() <= 5) {
                        player.setTexture(player33);
                    }
                }


                
                // lấy tọa độ của chuột và player
                Vector2i mousePosition = Mouse::getPosition(window);
                mouse.setPosition(Vector2f(mousePosition));
                player.rotate(mousePosition);
                Vector2f center = player.getPosition();
                //tạo máy bay mới
                new_planes(planes, clock_planes, enemy_aircraft, score);
                //đạn của người chơi di chuyển
                if (m_shoot.size() > 0) {
                    for (int i = 0; i < m_shoot.size(); i++) {
                        m_shoot[i].Sfire(M_BULLET_SPEED, score);
                    }
                }

                //sinh đạn mới của player
                Time time_m_bullet = clock_m_bullet.getElapsedTime();
                if (player.isAlive() == true && time_m_bullet.asSeconds() > TIME_NEXT_M_BULLET - 0.01 * sqrt((double)score)) {
                    new_bullet(bullet, Vector2f(mousePosition), center, m_shoot);
                    clock_m_bullet.restart();
                }

                if (planes.size() > 0) {
                    srand(time(NULL));
                    for (int i = 0; i < planes.size(); i++) {
                        planes[i].move(1, score);
                        if (score >= LEVER1) {
                            // sinh đạn của địch
                            time_next_bullet_planes[i] = clock_bullet_planes[i].getElapsedTime();
                            if (time_next_bullet_planes[i].asSeconds() > TIME_NEXT_PLANE_BULLET - 0.08 * sqrt((double)score)) {
                                if (planes[i].getLive() == true) {
                                    new_bullet(airbullet, center, planes[i].getPosition(), air_shoot);
                                }
                                clock_bullet_planes[i].restart();
                            }
                        }
                    }
                }

                // địch bắn đạn
                if (score >= LEVER1 && score < LEVER2) {
                    if (air_shoot.size() > 0) {
                        for (int i = 0; i < air_shoot.size(); i++) {
                            air_shoot[i].Sfire0();
                        }
                    }
                }
                else if (score >= LEVER2) {
                    if (air_shoot.size() > 0) {
                        for (int i = 0; i < air_shoot.size(); i++) {
                            air_shoot[i].Sfire(AIR_BULLET_SPEED, score);
                        }
                    }
                }
                //
                //collision
                // bullet and planes
                player_bullet_and_planes( m_shoot, planes, score, big_explosion, small_explosion);
                // bullet and bullet   
                player_bullet_and_air_bullet(m_shoot, air_shoot, small_explosion);
                //bullet and player
                player_and_air_bullet(player, air_shoot, die, clock_respawn, big_explosion, small_explosion);
                // player and planes
                player_and_planes(player, planes, die, score, clock_respawn, big_explosion);
                // Update quá trình nổ
                if(big_explosion.size()>0){
                    for (int i = 0; i < big_explosion.size(); i++) {
                        big_explosion[i].update(explosion);
                        big_explosion[i].end();
                    }
                }
                if (small_explosion.size() > 0) {
                    for (int i = 0; i < small_explosion.size(); i++) {
                        small_explosion[i].update(explosion);
                        small_explosion[i].end();
                    }
                }
            }
            draw(window, planes, air_shoot, m_shoot, big_explosion, small_explosion, 
                is_game_paused, mouse, Life, pause_button, text_score, text_high_score);
        }
        else {
            if (new_high_score == true) {
                FILE.open("highScore.txt", ios::trunc | ios::out);
                FILE << high_score;
                FILE.close();
            }
            
            End_game(window, playagain);
            if (playagain == true) {
                goto TryAgain;
            }
        }

        // vẽ ra màn hình
       
        window.display();
        //
    }

    return 0;
}