#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::Time t1 = sf::microseconds(10000);
    // sf::Time t2 = sf::milliseconds(10);
    // sf::Time t3 = sf::seconds(0.01f);

    printf("%lli\n",t1.asMicroseconds());
    printf("%i\n",t1.asMilliseconds());
    printf("%f\n",t1.asSeconds());

    sf::Time t2 = t1;
    sf::Time t3 = t1 + t2;
    sf::Time t4 = -t3;

    bool b1 = (t1 == t2);
    bool b2 = (t3 < t4);

    printf("%i\n", b1);
    printf("%i\n", b2);

    sf::Clock clock; // starts the clock
    for(int i=0; i<50; i++){

    }
    sf::Time elapsed1 = clock.getElapsedTime();

    sf::Time elapsedRestart = clock.restart();
    for(int i=0; i<1000; i++){

    }
    sf::Time elapsed2 = clock.getElapsedTime();

    printf("%f\n", elapsed1.asSeconds());
    printf("%f\n", elapsed2.asSeconds());
    printf("%f\n", elapsedRestart.asSeconds());

    return 0;
}