#include "human.h"

Human::Human(sf::Vector2f p_p, sf::Vector2f p_v, float taille, sf::Color couleurTete, sf::Color couleurCou, sf::Color couleurTorse, sf::Color couleurBras, sf::Color couleurJambe, int resol_x, int resol_y) :
    tete(p_p, 0, couleurTete, p_v, resol_x, resol_y),
    cou(p_p, 0, 0, couleurCou, p_v, resol_x, resol_y),
    torse(p_p, 0, 0, couleurTorse, p_v, resol_x, resol_y),
    brasGauche(p_p, 0, 0, couleurBras, p_v, resol_x, resol_y),
    brasDroit(p_p, 0, 0, couleurBras, p_v, resol_x, resol_y),
    jambeGauche(p_p, 0, 0, couleurJambe, p_v, resol_x, resol_y),
    jambeDroit(p_p, 0, 0, couleurJambe, p_v, resol_x, resol_y)

{

}