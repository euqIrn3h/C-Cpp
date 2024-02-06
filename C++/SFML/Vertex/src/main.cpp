#include <SFML/Graphics.hpp>
#include "vertexes.hpp"
#include <iostream>
#include <cmath>


int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "SFML works!", sf::Style::Default);

    // define the level with an array of tile indices
    const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load("./src/assets/tileset.png", sf::Vector2u(32, 32), level, 16, 8))
        return -1;

    sf::CircleShape player(20.f,3);
    player.setFillColor(sf::Color::Cyan); 
    player.setPosition(200,100);

    while (window.isOpen())
    {
        sf::Event event;
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();

        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player.move(0,-0.01);
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) player.move(-0.01,0);
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player.move(0,0.01);
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player.move(0.01,0);

        window.clear(sf::Color::White);
        window.draw(map);
        window.draw(player);
        window.display();
    }

    return 0;
}

