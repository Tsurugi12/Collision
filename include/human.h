#pragma once

#include <SFML/Graphics.hpp>
#include "boule.h"
#include "rectangle.h"

class Human {
    private:
        Boule tete;
        Rectangle cou;
        Rectangle torse;
        Rectangle brasGauche;
        Rectangle brasDroit;
        Rectangle jambeGauche;
        Rectangle jambeDroit;

        sf::Vector2f position;
        sf::Vector2f positionCou;
        sf::Vector2f positionTorse;
        sf::Vector2f positionBrasGauche;
        sf::Vector2f positionBrasDroit;
        sf::Vector2f positionJambeGauche;
        sf::Vector2f positionJambeDroit;

        sf::Vector2f vitesse;
        
        float multiplicateurTaille;
        float rayonTete;
        float largeurCou;
        float hauteurCou;
        float largeurTorse;
        float hauteurTorse;
        float largeurBras;
        float hauteurBras;
        float largeurJambe;
        float hauteurJambe;

        sf::Color couleurTete;
        sf::Color couleurCou;
        sf::Color couleurTorse;
        sf::Color couleurBras;
        sf::Color couleurJambe;

        int resol_x, resol_y;

    public:
        Human(sf::Vector2f p_p, sf::Vector2f p_v, float taille, sf::Color couleurTete, sf::Color couleurCou, sf::Color couleurTorse, sf::Color couleurBras, sf::Color couleurJambe, int resol_x, int resol_y);
};