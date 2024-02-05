#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

bool loadMedia();

//Globals

sf::Font font;
sf::Text text;
sf::Color windowColor;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!", sf::Style::Fullscreen);
    windowColor = sf::Color::Black;
    
    sf::CircleShape shape(10.f);
    shape.setPosition(200,200);
    shape.setFillColor(sf::Color::Green);

    if(!loadMedia()) printf("Unable to load Media Properly!\n");

    while (window.isOpen())
    {

        sf::Event event;
        while(window.pollEvent(event))
        {
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            shape.setFillColor(sf::Color::Cyan);
                            windowColor = sf::Color::Magenta;
                            break;
                        case sf::Mouse::Right:
                            shape.setFillColor(sf::Color::Magenta);
                            windowColor = sf::Color::Green;
                            break;
                        case sf::Mouse::Middle:
                            shape.setFillColor(sf::Color::Green);
                            windowColor = sf::Color::Red;
                            break;
                        case sf::Mouse::XButton1:
                            shape.setFillColor(sf::Color::Red);
                            windowColor = sf::Color::White;
                            break;
                        case sf::Mouse::XButton2:
                            shape.setFillColor(sf::Color::White);
                            windowColor = sf::Color::Black;
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) shape.move(0,-0.01);
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) shape.move(-0.01,0);
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) shape.move(0,0.01);
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) shape.move(0.01,0);

        window.clear(windowColor);
        window.draw(text);
        window.draw(shape);
        window.display();
    }

    return 0;
}

bool loadMedia()
{
    if (!font.loadFromFile("./src/assets/fonts/cour.ttf")) return false;

    // select the font
    text.setFont(font); // font is a sf::Font
    // set the string to display
    text.setString("Hello world");
    // set the character size
    text.setCharacterSize(24); // in pixels, not points!
    // set the color
    text.setFillColor(sf::Color::Red);
    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    return true;
}