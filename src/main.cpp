#include <SFML/Graphics.hpp>
#include <vector>

#include "boule.h"

int main()    {
    sf::RenderWindow window(sf::VideoMode(800,600), "Collision simulator");

    std::vector<Boule> mesBoules = {
        Boule({0.f, 0.f}, 40.f, sf::Color::Red, {1, 1}), 
        Boule({80.f, 0.f}, 30.f, sf::Color::Blue, {3, 3})
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))    mesBoules[0].modify_pos({0, -mesBoules[0].get_v().y}, true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))    mesBoules[0].modify_pos({0, mesBoules[0].get_v().y}, true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))    mesBoules[0].modify_pos({-mesBoules[0].get_v().x, 0}, true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))    mesBoules[0].modify_pos({mesBoules[0].get_v().x, 0}, true);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    mesBoules[1].modify_pos({0, -mesBoules[1].get_v().y}, true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))    mesBoules[1].modify_pos({0, mesBoules[1].get_v().y}, true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))    mesBoules[1].modify_pos({-mesBoules[1].get_v().x, 0}, true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))    mesBoules[1].modify_pos({mesBoules[1].get_v().x, 0}, true);


        for (Boule &b : mesBoules)  {
            b.update();
        }

        window.clear(sf::Color::White);

        for (Boule &b : mesBoules)  {
            b.draw(window);
        }
        window.display();
        sf::sleep(sf::milliseconds(10));
    }
}