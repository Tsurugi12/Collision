#include "boule.h"
#include <math.h>

//Constructeur
Boule::Boule(sf::Vector2f p_p, float p_r, sf::Color couleur, sf::Vector2f p_v)  {
    position = p_p;
    rayon = p_r;
    vitesse = p_v;

    circle.setRadius(rayon);
    circle.setFillColor(couleur);
}

//Actualise position
void Boule::update()    {
    circle.setPosition(position);
}

//Affiche boule
void Boule::draw(sf::RenderWindow &window)  {
    window.draw(circle);
}

//change la vitesse
void Boule::modify_v(sf::Vector2f p_v, bool add)  {
    if (add)    {
        vitesse.x += p_v.x;
        vitesse.y += p_v.y;
    }   
    else{
        vitesse.x = p_v.x;
        vitesse.y = p_v.y;
    }
}

//change la position
void Boule::modify_pos(sf::Vector2f p_p, bool add)    {
    if (add)    {
        position.x += p_p.x;
        position.y += p_p.y;
    }   
    else{
        position.x = p_p.x;
        position.y = p_p.y;
    }
}

/////////////////////////////////////////////getters/////////////////////////////////////////////
const sf::Vector2f &Boule::get_pos()  const{
    return position;
}

const sf::Vector2f &Boule::get_v()  const{
    return vitesse;
}

float Boule::get_r()  const{
    return rayon;
}

//Vérifie la collision avec une autre boule
bool Boule::collision(const Boule &autreBoule)  const{
    float rayon_Tot = rayon + autreBoule.rayon;

    float distance = sqrt(pow((position.x - autreBoule.position.x),2) + pow((position.y - autreBoule.position.y),2));

    return distance < rayon_Tot;
}