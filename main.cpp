#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
using namespace std;

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode({258u*3, 227u*3}), title);
    Texture blocksheet, gamescreen, obj4, obj5;

    //---Loading Textures from the Image Files---//
    blocksheet.loadFromFile("img/tiles.png");
    gamescreen.loadFromFile("img/gamescreen.png");
    obj4.loadFromFile("img/shadow.png");
    obj5.loadFromFile("img/bomb.png");

    //---Setting the Texture to the Sprites---//
    Sprite sprite(blocksheet), background(gamescreen), shadowsprite(obj4), bomb(obj5);
    background.setScale({3,3});

    int delta_x = 0, colorNum = 1;
    float timer = 0, delay = 0.3, delays = 0.3;
    bool rotate = 0;
    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        //---Event Listening Part---//
        while (auto e = window.pollEvent())
        {                               // Event is occurring - until the game is in running state
            if (e->is<Event::Closed>()) // If cross/close is clicked/pressed
                window.close();         // Opened window disposes
            if (e->is<Event::KeyPressed>())
            {                                                                // If any other key (not cross) is pressed
                if ((Keyboard::isKeyPressed(Keyboard::Key::Up)) && (n != 0)) // Check if the other key pressed is UP key
                    rotate = 1;                                              // Rotation gets on
                else if (Keyboard::isKeyPressed(Keyboard::Key::Left))        // Check if the other key pressed is LEFT key
                    delta_x = -1;                                            // Change in X-Axis - Negative
                else if (Keyboard::isKeyPressed(Keyboard::Key::Right))       // Check if the other key pressed is RIGHT key
                    delta_x = 1;
                gameGrids[M][N] = {0}; // Change in X-Axis - Positive
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Down)) // Just another way to detect key presses without event listener
            delay = 0.05;                                // If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05

        fallingPiece(timer, delay, colorNum, n);
        horizontalmovement(delta_x);
        rotation(rotate);
        Shadow(point_1s);
        linecheck();
        endcheck();

        window.clear(Color::Black);
        window.draw(background);

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (gameGrids[i][j] == 0)
                    continue;
                shadowsprite.setTextureRect(IntRect({gameGrids[i][j] * 18, 0}, {18, 18}));
                shadowsprite.setPosition({j * 18, i * 18});
                shadowsprite.move({288, 242}); // offset
                window.draw(shadowsprite);
            }
        }

        for (int i = 0; i < 4; i++)
        {
            shadowsprite.setTextureRect(IntRect({colorNum * 18, 0}, {18, 18}));
            shadowsprite.setPosition({point_1s[i][0] * 18, point_1s[i][1] * 18});
            shadowsprite.move({288, 242});
            window.draw(shadowsprite);
        }

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (gameGrid[i][j] == 0)
                    continue;
                sprite.setTextureRect(IntRect({gameGrid[i][j] * 18, 0}, {18, 18}));
                sprite.setPosition({j * 18, i * 18});
                sprite.move({288, 242}); // offset
                window.draw(sprite);
            }
        }
        
        for (int i = 0; i < 4; i++)
        {
            sprite.setTextureRect(IntRect({colorNum * 18, 0}, {18, 18}));
            sprite.setPosition({point_1[i][0] * 18, point_1[i][1] * 18});
            sprite.move({288, 242});
            window.draw(sprite);
        }

        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
    return 0;
}