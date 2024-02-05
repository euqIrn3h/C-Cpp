#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class EllipseShape : public sf::Shape
{
public :

    explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0.f, 0.f)) :
    m_radius(radius)
    {
        update();
    }

    void setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        update();
    }

    const sf::Vector2f& getRadius() const
    {
        return m_radius;
    }

    virtual std::size_t getPointCount() const
    {
        return 30; // fixed, but could be an attribute of the class if needed
    }

    virtual sf::Vector2f getPoint(std::size_t index) const
    {
        static const float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x = std::cos(angle) * m_radius.x;
        float y = std::sin(angle) * m_radius.y;

        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }

private :

    sf::Vector2f m_radius;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Default);
    
    sf::CircleShape circle(10.f);
    circle.setPosition(10,10);
    circle.setFillColor(sf::Color::Green);

    // set a 10-pixel wide orange outline
    circle.setOutlineThickness(10.f);
    circle.setOutlineColor(sf::Color(250, 150, 100, 255));

    // define a triangle
    sf::CircleShape triangle(10.f, 3);
    triangle.setPosition(750,10);
    // define a square
    sf::CircleShape square(10.f, 4);
    square.setPosition(10,750);
    // define an octagon
    sf::CircleShape octagon(10.f, 8);
    octagon.setPosition(750,750);

    // create an empty shape
    sf::ConvexShape convex;
    // resize it to 5 points
    convex.setPointCount(5);
    // define the points
    convex.setPoint(0, sf::Vector2f(0.f, 0.f));
    convex.setPoint(1, sf::Vector2f(150.f, 10.f));
    convex.setPoint(2, sf::Vector2f(120.f, 90.f));
    convex.setPoint(3, sf::Vector2f(30.f, 100.f));
    convex.setPoint(4, sf::Vector2f(0.f, 50.f));
    convex.setPosition(150,150);

    //Line with thickness
    sf::RectangleShape line(sf::Vector2f(150.f, 1.f));
    line.rotate(45.f);
    line.setPosition(550,550);

    EllipseShape ellipse(sf::Vector2f(100,30));
    ellipse.setPosition(250,550);

    while (window.isOpen())
    {
        sf::Event event;
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();

        window.clear();
        window.draw(circle);
        window.draw(square);
        window.draw(triangle);
        window.draw(octagon);
        window.draw(convex);
        window.draw(line);
        window.draw(ellipse);
        window.display();
    }

    return 0;
}

