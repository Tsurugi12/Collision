#include "boule.h"
#include <math.h>

//Constructeur
Boule::Boule(sf::Vector2f p_p, float p_r, sf::Color couleur, sf::Vector2f p_v, int p_resol_x, int p_resol_y)  {
    position = p_p;
    positionFantome = {-9999, -9999};
    rayon = p_r;
    vitesse = p_v;
    resol_x = p_resol_x;
    resol_y = p_resol_y;

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

    //Affiche une boule fantome si on est au limite de l'écran
    if (positionFantome.x != -9999 && positionFantome.y != -9999)   {
        circle.setPosition(positionFantome);
        window.draw(circle);

        //et 2 autres boules fantome dans les angles
        if (sortie_x)   {
            circle.setPosition(positionFantome.x + resol_x, positionFantome.y);
            window.draw(circle);

            circle.setPosition(positionFantome.x + resol_x, positionFantome.y - resol_y);
            window.draw(circle);
        }
    }
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

//Pour les limites de l'ecran
void Boule::sortieEcran(sf::RenderWindow &window)   {
    int diametre = rayon * 2;
    if (position.x < 0 - diametre) position.x = resol_x - diametre;
    if (position.y < 0 - diametre) position.y = resol_y - diametre;

    if (position.x > resol_x - diametre) position.x = 0 - diametre;
    if (position.y > resol_y - diametre) position.y = 0 - diametre;

    //Créér une illusion de deuxième balle (recupere coordonnées)
    positionFantome = {-9999, -9999};
    sortie_x = false;
    if ((position.x < 0) && (position.x >= 0 - diametre))    {  positionFantome = {position.x + resol_x, position.y};   sortie_x = true;   }
    if ((position.y < 0) && (position.y >= 0 - diametre))    {  positionFantome = {position.x, position.y + + resol_y};   }
}

//Vérifie la collision avec une autre boule
bool Boule::collision(const Boule &autreBoule)  const{
    float rayon_Tot = rayon + autreBoule.rayon;

    float distance = sqrt(pow((position.x - autreBoule.position.x),2) + pow((position.y - autreBoule.position.y),2));

    return distance < rayon_Tot;
}