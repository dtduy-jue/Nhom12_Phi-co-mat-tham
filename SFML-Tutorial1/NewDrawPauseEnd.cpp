#include"NewDrawPauseEnd.h"


void new_game(RenderWindow& window) {
    Sprite background_menu(bgme), play_button(play), exit_button(Exit);
    background_menu.setScale(1.9f, 2.31f);
    bgme.setSmooth(true);
    play_button.setPosition(750, 500);
    play_button.setScale(1.1f, 1.1f);
    play_button.setOrigin(128, 128);

    exit_button.setPosition(750, 600);
    exit_button.setScale(0.5, 0.5);
    exit_button.setOrigin(128, 128);



    Sound sound(music), soundMenu(menu), soundClick(click), soundLose(lose);
    soundMenu.play();
    soundMenu.setLoop(true);
    soundMenu.setVolume(70);
    sound.setVolume(0);
    soundClick.setVolume(100);
    soundLose.setVolume(60);



    Clock clock_menu;

    Sprite name_game;
    name_game.setTexture(name);
    Vector2u size = name.getSize();
    int i = 0;
    while (1)
    {
        Time time = clock_menu.getElapsedTime();
        if (time.asSeconds() >1.2*i) {
            name_game.setTextureRect(IntRect(size.x/5 * i, 0, size.x/5, size.y));
            name_game.setPosition(70, 50);
            name.setSmooth(true);
            if (i < 4) {
                i++;
            }
        }
        Event event;
        int h = 0;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                soundMenu.stop();
                window.close();
            }
            Vector2i mouse = Mouse::getPosition(window);
            if (mouse.x >= 620 && mouse.x <= 880 && mouse.y >= 465 && mouse.y <= 535)
            {
                play_button.setScale(1, 1);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    soundClick.play();
                    h = 1;
                    sleep(seconds(0.25));
                    soundMenu.stop();
                    sound.play();
                    sound.setLoop(true);
                    break;
                }
            }
            else
                play_button.setScale(1.1f, 1.1f);

            if (mouse.x >= 620 && mouse.x <= 880 && mouse.y >= 570 && mouse.y <= 640)
            {
                exit_button.setScale(1, 1);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    soundClick.play();
                    sleep(seconds(0.5));
                    window.close();
                    soundMenu.stop();
                }
            }
            else
            {
                exit_button.setScale(1.1f, 1.1f);
            }

        }
        if (h == 1)
            break;
        window.draw(background_menu);
        window.draw(play_button);
        window.draw(exit_button);
        window.draw(name_game);
        window.display();
    }
}

void Pause(RenderWindow& window, bool& is_game_paused, Event& event, Sprite& pause_button) {
    Sound sound(menu), soundClick(click);
    pause_button.setOrigin(35, 35);
    pause_button.setPosition(35, 35);
    bool is_mouse_in_pause_button_zone = false;
    if (Mouse::getPosition(window).x >= 0 && Mouse::getPosition(window).x <= 70
        && Mouse::getPosition(window).y >= 0 && Mouse::getPosition(window).y <= 70)
    {
        pause_button.setScale(0.9f, 0.9f);
        is_mouse_in_pause_button_zone = true;
    }
    else
    {
        pause_button.setScale(1.0f, 1.0f);
        is_mouse_in_pause_button_zone = false;
    }
    //

    // Bắt sự kiện
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            if (is_mouse_in_pause_button_zone == true)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    soundClick.play();
                    sound.stop();
                    is_game_paused = !is_game_paused;
                    if (is_game_paused == true)
                    {
                        pause_button.setTexture(unpause);
                        window.setMouseCursorVisible(true);
                    }
                    if (is_game_paused == false)
                    {
                        sound.play();
                        pause_button.setTexture(pause);
                        window.setMouseCursorVisible(false);
                    }
                }
            }break;
        default:
            break;
        }
    }
  //  window.draw(pause_button);
}

void End_game(RenderWindow& window, bool& playagain) {
    Sound sound(menu), soundClick(click);
    window.setMouseCursorVisible(true);
    //khi gameover
    Sprite Gameover;
    Gameover.setTexture(gameover);
    Gameover.setPosition(650, 450);
    Gameover.setOrigin(100, 60);
    Gameover.setScale(3, 3);
    gameover.setSmooth(true);

    Sprite retry_button(retry);
    retry_button.setPosition(550, 550);
    retry_button.setOrigin(128, 128);

    Sprite exit_button_gameover;
  //  bool is_play_sound_gameOver = true;
  //  Sound sound_gameOver(gameOver);
    exit_button_gameover.setTexture(Exit);
    exit_button_gameover.setPosition(950, 550);
    exit_button_gameover.setOrigin(128, 128);
    //
   
    sound.pause();
   // is_game_paused = true;
    Event eventEnd;
   
    while (window.pollEvent(eventEnd))
    {

        if (eventEnd.type == Event::Closed)
            window.close();
        Vector2i mouseEnd = Mouse::getPosition(window);

        if (mouseEnd.x >= 350 && mouseEnd.x <= 750 && mouseEnd.y >= 450 && mouseEnd.y <= 650)
        {
            retry_button.setScale(0.9f, 0.9f);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                soundClick.play();
                playagain = true;
                sleep(seconds(0.25));
                sound.play();
                sound.setLoop(true);
                break;
            }
        }
      //  else
      //      retry_button.setScale(1.1f, 1.1f);

        if (mouseEnd.x >= 750 && mouseEnd.x <= 1150 && mouseEnd.y >= 450 && mouseEnd.y <= 650)
        {
            exit_button_gameover.setScale(0.9f, 0.9f);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                soundClick.play();
                sleep(seconds(0.5));
                window.close();
            }
        }
     //   else
     //   {
     //       exit_button_gameover.setScale(1.1f, 1.1f);
     //   }
    }
   
        window.draw(Gameover);
        window.draw(retry_button);
        window.draw(exit_button_gameover);
    
}