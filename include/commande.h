#ifndef COMMANDE_H
#define COMMANDE_H

#include <vector>
#include "rectangle.h"
#include "human.h"
#include "SFML/System/Vector2.hpp"

class Boule;

//boule
void gererDeplacement(std::vector<Boule> &mesBoules, sf::Vector2f deplacement, int bouleActuel, int ancienneBoule, int modeActifCollision);
void gereCollision(std::vector<Boule> &mesBoules, sf::Vector2f deplacement, int bouleActuel, int ancienneBoule, int modeActifCollision);

//rectangles
void gererDeplacement(std::vector<Rectangle> &mesRectangles, sf::Vector2f deplacement, int RectangleActuel, int ancienRectangle, int modeActifCollision);
void gereCollision(std::vector<Rectangle> &mesRectangles, sf::Vector2f deplacement, int RectangleActuel, int ancienRectangle, int modeActifCollision);

//humans
void gererDeplacement(std::vector<Human> &mesHumains, sf::Vector2f deplacement, int HumanActuel, int ancienHuman, int modeActifCollision);
void gereCollision(std::vector<Human> &mesHumains, sf::Vector2f deplacement, int HumanActuel, int ancienHuman, int modeActifCollision);

#endif