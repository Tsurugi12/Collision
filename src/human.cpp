#include "human.h"

Human::Human(sf::Vector2f p_p, sf::Vector2f p_v, float p_taille, sf::Color p_couleurTete, sf::Color p_couleurCou, sf::Color p_couleurTorse, sf::Color p_couleurBras, sf::Color p_couleurJambe, int p_resol_x, int p_resol_y) :
    tete(p_p, 0, p_couleurTete, p_v, p_resol_x, p_resol_y),
    cou(p_p, 0, 0, p_couleurCou, p_v, p_resol_x, p_resol_y),
    torse(p_p, 0, 0, p_couleurTorse, p_v, p_resol_x, p_resol_y),
    brasGauche(p_p, 0, 0, p_couleurBras, p_v, p_resol_x, p_resol_y),
    brasDroit(p_p, 0, 0, p_couleurBras, p_v, p_resol_x, p_resol_y),
    jambeGauche(p_p, 0, 0, p_couleurJambe, p_v, p_resol_x, p_resol_y),
    jambeDroit(p_p, 0, 0, p_couleurJambe, p_v, p_resol_x, p_resol_y)

{
    position = p_p;
    vitesse = p_v;
    multiplicateurTaille = p_taille;
    couleurTete = p_couleurTete;
    couleurCou = p_couleurCou;
    couleurTorse = p_couleurTorse;
    couleurBras = p_couleurBras;
    couleurJambe = p_couleurJambe;
    resol_x = p_resol_x;
    resol_y = p_resol_y;

    modify_taille(p_taille);
    update(position, false);
}

void Human::update(sf::Vector2f pos, bool add)    {
    //Position tete
    if (add)    position += pos;
    else    position = pos;

    //Position cou
    positionCou.x = position.x + 0.55 * rayonTete;
    positionCou.y = position.y + 1.6 * rayonTete;

    //Position torse
    positionTorse.x = position.x - 0.2 * rayonTete;
    positionTorse.y = positionCou.y + hauteurCou;
        
    //Position Bras Gauche;
    positionBrasGauche.x = positionTorse.x - largeurBras;
    positionBrasGauche.y = positionTorse.y;

    //Position Bras Droit;
    positionBrasDroit.x = positionTorse.x + largeurTorse;
    positionBrasDroit.y = positionTorse.y;

    //Position Jambe Gauche
    positionJambeGauche.x = positionTorse.x;
    positionJambeGauche.y = positionTorse.y + hauteurTorse;

    //Position Jambe Droit
    positionJambeDroit.x = positionTorse.x + largeurTorse - largeurJambe;
    positionJambeDroit.y = positionTorse.y + hauteurTorse;

    //Actualise les position
    tete.modify_pos(position, false);
    cou.modify_pos(positionCou, false);
    torse.modify_pos(positionTorse, false);
    brasGauche.modify_pos(positionBrasGauche, false);
    brasDroit.modify_pos(positionBrasDroit, false);
    jambeGauche.modify_pos(positionJambeGauche, false);
    jambeDroit.modify_pos(positionJambeDroit, false);
}

void Human::modify_taille(float p_taille)  {
    multiplicateurTaille = p_taille;

    rayonTete = 10.f * multiplicateurTaille;
    largeurCou = 8.f * multiplicateurTaille;
    hauteurCou = 10.f * multiplicateurTaille;
    largeurTorse = 24.f * multiplicateurTaille;
    hauteurTorse = 40.f * multiplicateurTaille;
    largeurBras = 30.f * multiplicateurTaille;
    hauteurBras = 10.f * multiplicateurTaille;
    largeurJambe = 10.f * multiplicateurTaille;
    hauteurJambe = 35.f * multiplicateurTaille;

    tete.modify_rayon(rayonTete);
    cou.modify_dimension(hauteurCou, largeurCou);
    torse.modify_dimension(hauteurTorse, largeurTorse);
    brasGauche.modify_dimension(hauteurBras, largeurBras);
    brasDroit.modify_dimension(hauteurBras, largeurBras);
    jambeGauche.modify_dimension(hauteurJambe, largeurJambe);
    jambeDroit.modify_dimension(hauteurJambe, largeurJambe);
}

void Human::draw(sf::RenderWindow &window)  {
    brasDroit.draw(window);
    brasGauche.draw(window);
    jambeDroit.draw(window);
    jambeGauche.draw(window);
    cou.draw(window);
    torse.draw(window);
    tete.draw(window);
}

void Human::modify_v(sf::Vector2f p_v)   {
    vitesse = p_v;
}

const sf::Vector2f &Human::get_pos() const{
    return position;
}

const sf::Vector2f &Human::get_v() const{
    return vitesse;
}

float Human::get_taille() const{
    return multiplicateurTaille;
}