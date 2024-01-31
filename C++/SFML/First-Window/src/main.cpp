#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            printf("Botao A!!");
            shape.move( 1.0f,1.0f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}