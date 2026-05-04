#ifndef COMMANDE_H
#define COMMANDE_H

#include <vector>
#include "boule.h"

void gererDeplacement(std::vector<Boule> &mesBoules, int bouleActuel, int d_x, int d_y, int modeActifCollision);
void gereCollision(std::vector<Boule> &mesBoules, int bouleActuel, int d_x, int d_y, int modeActifCollision);

#endif