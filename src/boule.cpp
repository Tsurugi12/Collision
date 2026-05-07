#include "boule.h"

//Constructeur
Boule::Boule(sf::Vector2f p_p, float p_r, sf::Color couleur, sf::Vector2f p_v, int p_resol_x, int p_resol_y)  {
    position = p_p;
    positionFantome = {-9999, -9999};
    rayon = p_r;
    vitesse = p_v;
    resol_x = p_resol_x;
    resol_y = p_resol_y;
    friction = 0.95;
    velocite = {0,0};

    circle.setRadius(rayon);
    circle.setFillColor(couleur);
}

//Actualise position
void Boule::update()    {
    circle.setPosition(position);
}

//Gere les rebonds entre boule
void Boule::rebond(sf::Vector2f force, sf::RenderWindow &window, std::vector<Boule> &mesBoules)   {
    if (velocite.x < 0.1 && velocite.y < 0.1)   velocite = {0,0};

    velocite += force;
    
    modify_pos(velocite, true);
    sortieEcran(window);
    for (int i = 0; i < mesBoules.size(); i++)  {
        if (position != mesBoules[i].position)
            if (collision(mesBoules[i]))    velocite = {0,0};
    }

    velocite *= friction;
}

//Affiche boule
void Boule::draw(sf::RenderWindow &window)  {
    window.draw(circle);

    //Affiche une boule fantome si on est au limite de l'écran
    if (positionFantome.x != -9999 && positionFantome.y != -9999)   {
        circle.setPosition(positionFantome);
        window.draw(circle);

        //et 2 autres boules fantome dans les angles
        if (sortie_x && sortie_y)   {
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
    sortie_y = false;
    if ((position.x < 0) && (position.x >= 0 - diametre))    {  positionFantome = {position.x + resol_x, position.y};   sortie_x = true;   }
    if ((position.y < 0) && (position.y >= 0 - diametre))    {  positionFantome = {position.x, position.y + resol_y};   sortie_y = true;   }
}

//Vérifie la collision avec une autre boule
bool Boule::collision(const Boule &autreBoule)  const{
    float centre_x_1 = position.x + rayon;
    float centre_y_1 = position.y + rayon;
    float centre_x_2 = autreBoule.position.x + autreBoule.rayon;
    float centre_y_2 = autreBoule.position.y + autreBoule.rayon;

    float rayon_Tot = rayon + autreBoule.rayon;

    float d_x = centre_x_1 - centre_x_2;
    float d_y = centre_y_1 - centre_y_2;

    float collision = (d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot;

    if (collision)  return collision;
    else    {
        //Boule actuel fantome mais pas l'autre
        if (positionFantome.x != -9999 && positionFantome.y != -9999)   {
            if (autreBoule.positionFantome.x == -9999 && autreBoule.positionFantome.y == -9999)  {
                //fantome en x mais pas y
                if (position.x < 0 && position.y > 0) {
                    centre_x_1 = position.x + resol_x + rayon;
                    d_x = centre_x_1 - centre_x_2;
                }

                //fantome en y mais pas x
                if (position.y < 0 && position.x > 0) {
                    centre_y_1 = position.y + resol_y + rayon;
                    d_y = centre_y_1 - centre_y_2;
                }

                //fantome en x et y
                if (position.x < 0  && position.y < 0) {
                    //On vérifie en x
                    centre_x_1 = position.x + resol_x + rayon;
                    d_x = centre_x_1 - centre_x_2;
                    if ((d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot)    return true;

                    //On vérifie en x et en y
                    centre_y_1 = position.y + resol_y + rayon;
                    d_y = centre_y_1 - centre_y_2;
                    if ((d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot)    return true;

                    //On vérifie seulement en y
                    centre_x_1 = position.x + rayon;
                    d_x = centre_x_1 - centre_x_2;
                    if ((d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot)    return true;
                }
            }
        }
        

        //Autre boule fantome mais pas actuel
        if (autreBoule.positionFantome.x != -9999 && autreBoule.positionFantome.y != -9999)   {
            if (positionFantome.x == -9999 && positionFantome.y == -9999)   {
                //fantome en x
                if (autreBoule.position.x < 0 && autreBoule.position.y > 0) {
                    centre_x_2 = autreBoule.position.x + autreBoule.resol_x + autreBoule.rayon;
                    d_x = centre_x_1 - centre_x_2;
                }

                //fantome en y
                if (autreBoule.position.y < 0 && autreBoule.position.x > 0) {
                    centre_y_2 = autreBoule.position.y + autreBoule.resol_y + autreBoule.rayon;
                    d_y = centre_y_1 - centre_y_2;
                }

                //fantome en x et y
                if (autreBoule.position.x < 0  && autreBoule.position.y < 0) {
                    //On vérifie en x
                    centre_x_2 = autreBoule.position.x + autreBoule.resol_x + autreBoule.rayon;
                    d_x = centre_x_1 - centre_x_2;
                    if ((d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot)    return true;

                    //On vérifie en x et en y
                    centre_y_2 = autreBoule.position.y + autreBoule.resol_y + autreBoule.rayon;
                    d_y = centre_y_1 - centre_y_2;
                    if ((d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot)    return true;

                    //On vérifie seulement en y
                    centre_x_2 = autreBoule.position.x + autreBoule.rayon;
                    d_x = centre_x_1 - centre_x_2;
                    if ((d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot)    return true;
                }
            }
        }

        //Les 2 sont fantomes
        if (positionFantome.x != -9999 && positionFantome.y != -9999 && autreBoule.positionFantome.x != -9999 && autreBoule.positionFantome.y != -9999) {
            //fantome en x mais pas y
            if (position.x < 0 && position.y > 0) {
                centre_x_1 = position.x + resol_x + rayon;
                d_x = centre_x_1 - centre_x_2;
            }

            //fantome en y mais pas x
            if (position.y < 0 && position.x > 0) {
                centre_y_1 = position.y + resol_y + rayon;
                d_y = centre_y_1 - centre_y_2;
            }

            //fantome en x et y
            if (position.x < 0  && position.y < 0) {
                //On vérifie en x
                centre_x_1 = position.x + resol_x + rayon;
                d_x = centre_x_1 - centre_x_2;
                if ((d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot)    return true;

                //On vérifie en x et en y
                centre_y_1 = position.y + resol_y + rayon;
                d_y = centre_y_1 - centre_y_2;
                if ((d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot)    return true;

                //On vérifie seulement en y
                centre_x_1 = position.x + rayon;
                d_x = centre_x_1 - centre_x_2;
                if ((d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot)    return true;
            }

            //fantome en x mais pas y
            if (autreBoule.position.x < 0 && autreBoule.position.y > 0) {
                centre_x_2 = autreBoule.position.x + autreBoule.resol_x + autreBoule.rayon;
                d_x = centre_x_1 - centre_x_2;
            }

            //fantome en y mais pas x
            if (autreBoule.position.y < 0 && autreBoule.position.x > 0) {
                centre_y_2 = autreBoule.position.y + autreBoule.resol_y + autreBoule.rayon;
                d_y = centre_y_1 - centre_y_2;
            }

            //fantome en x et y
            if (autreBoule.position.x < 0  && autreBoule.position.y < 0) {
                //On vérifie en x
                centre_x_2 = autreBoule.position.x + autreBoule.resol_x + autreBoule.rayon;
                d_x = centre_x_1 - centre_x_2;
                if ((d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot)    return true;

                //On vérifie en x et en y
                centre_y_2 = autreBoule.position.y + autreBoule.resol_y + autreBoule.rayon;
                d_y = centre_y_1 - centre_y_2;
                if ((d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot)    return true;

                //On vérifie seulement en y
                centre_x_2 = autreBoule.position.x + autreBoule.rayon;
                d_x = centre_x_1 - centre_x_2;
                if ((d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot)    return true;
            }
        }
        return (d_x * d_x + d_y * d_y) < rayon_Tot * rayon_Tot;
    }
}