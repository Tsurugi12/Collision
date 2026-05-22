#ifndef COMMANDE_H
#define COMMANDE_H

#include <vector>
#include "rectangle.h"
#include "SFML/System/Vector2.hpp"

class Boule;


void gererDeplacement(std::vector<Boule> &mesBoules, sf::Vector2f deplacement, int bouleActuel, int ancienneBoule, int modeActifCollision);
void gereCollision(std::vector<Boule> &mesBoules, sf::Vector2f deplacement, int bouleActuel, int ancienneBoule, int modeActifCollision);

void gererDeplacement(std::vector<Rectangle> &mesRectangles, sf::Vector2f deplacement, int RectangleActuel, int ancienRectangle, int modeActifCollision);
void gereCollision(std::vector<Rectangle> &mesRectangles, sf::Vector2f deplacement, int RectangleActuel, int ancienRectangle, int modeActifCollision);

#endif