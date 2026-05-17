#ifndef COMMANDE_H
#define COMMANDE_H

#include <vector>
#include "SFML/System/Vector2.hpp"

class Boule;


void gererDeplacement(std::vector<Boule> &mesBoules, sf::Vector2f deplacement, int bouleActuel, int ancienneBoule, int modeActifCollision);
void gereCollision(std::vector<Boule> &mesBoules, sf::Vector2f deplacement, int bouleActuel, int ancienneBoule, int modeActifCollision);

#endif