#ifndef COMMANDE_H
#define COMMANDE_H

#include <vector>
#include "SFML/System/Vector2.hpp"

class Boule;
namespace sf{
    class RenderWindow; 
}

void gererDeplacement(std::vector<Boule> &mesBoules, int bouleActuel, sf::Vector2f deplacement, int modeActifCollision, int ancienneBoule, sf::RenderWindow &window);
void gereCollision(std::vector<Boule> &mesBoules, int bouleActuel, sf::Vector2f deplacement, int modeActifCollision, int ancienneBoule, sf::RenderWindow &window);

#endif