#include <SFML/Graphics.hpp>
#include "vertexes.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>

sf::Int8 velocity = 5;

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "SFML works!", sf::Style::Fullscreen);


    // define the level with an array of tile indices
    srand(time(0));
    int level_height = 100;
    int level_width = 100;
    int level[level_height*level_width];

    for(int i=0; i< level_height*level_width; i++)
    {
        level[i] = rand() % 4;
    }

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("./src/assets/tileset.png", sf::Vector2u(32, 32), level, 100, 100))
        return -1;

    sf::CircleShape player(20.f,3);
    player.setFillColor(sf::Color::Cyan); 
    //(level_height*32) tiles * pixels per tile
    player.setPosition((level_height*32)/2, (level_width*32)/2);

    // create a view with its center and size
    sf::View view(sf::FloatRect(window.getSize().x, window.getSize().y,window.getSize().x, window.getSize().y));
    view.setCenter((level_height*32)/2, (level_width*32)/2);

    while (window.isOpen())
    {
        sf::Event event;
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();

        //Change velocity

        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
        {
            velocity = 10;
        }
        else
        {
            velocity = 5;
        }

        //Movement Player
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
          view.move(0,-0.01 * velocity);
          player.move(0,-0.01 * velocity);  
        } 
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player.move(-0.01 * velocity,0);
            view.move(-0.01 * velocity,0);
        }
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            player.move(0,0.01 * velocity);
            view.move(0,0.01 * velocity);
        }
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.move(0.01 * velocity,0);
            view.move(0.01 * velocity,0);
        }

        // Zoom the view relatively to its current size (apply a factor 0.5, so its final size is 200x200)
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
        { 
            view.zoom(0.5f);
        }
        else
        {
            view.zoom(1.f);
        }

        window.clear(sf::Color::White);
        window.setView(view);
        window.draw(map);
        window.draw(player);
        window.display();
    }

    return 0;
}

