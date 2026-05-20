#include "boule.h"


//Constructeur
Boule::Boule(sf::Vector2f p_p, float p_r, sf::Color couleur, sf::Vector2f p_v, int p_resol_x, int p_resol_y)  {
    position = p_p;
    positionFantome = {-9999, -9999};
    positionFantome2 = {-9999, -9999};
    positionFantome3 = {-9999, -9999};

    rayon = p_r;
    vitesse = p_v; //vitesse max sans collision
    velocite = {0,0}; //vitesse réel quand on pousse la boule
    friction = 0.95;

    resol_x = p_resol_x;
    resol_y = p_resol_y;
    
    circle.setRadius(rayon);
    circle.setFillColor(couleur);
}

//Actualise position
void Boule::update(sf::Vector2f pos)    {
    circle.setPosition(pos);
}

//Gere les rebonds entre boule
void Boule::slide(sf::Vector2f force, bool sliding)   {
    rebond *= friction;
    if (velocite.x*velocite.x < 0.1 && velocite.y*velocite.y < 0.1)   velocite = {0,0};
    if (rebond.x*rebond.x < 0.1 && rebond.y*rebond.y < 0.1)   rebond = {0,0};

    static bool sticked = true;

    if (sliding)    {
        float acceleration = 0.2;
        velocite += ((force - velocite)  * acceleration);
        sticked = true;
    }   
    else    {
        if (sticked)
            rebond += force;
        sticked = false;
    }

    
}

//Affiche boule
void Boule::draw(sf::RenderWindow &window)  {
    update(position);
    window.draw(circle);

    //Affiche une boule fantome si on est au limite de l'écran
    if (positionFantome.x != -9999 && positionFantome.y != -9999)   {
        update(positionFantome);
        window.draw(circle);
    }

    //Affiche 2 boules fantomes si on est aux coins
    if (positionFantome2.x != -9999 && positionFantome2.y != -9999 && positionFantome3.x != -9999 && positionFantome3.y != -9999)   {
        update(positionFantome2);
        window.draw(circle);

        update(positionFantome3);
        window.draw(circle);
    }
}

//change la vitesse
void Boule::modify_v(sf::Vector2f p_v, bool add)  {
    if (add)    {
        vitesse.x += p_v.x;
        vitesse.y += p_v.y;
    }   
    else{
        vitesse = p_v;
    }
}

//change la position
void Boule::modify_pos(sf::Vector2f p_p, bool add)    {
    if (add)    {
        position.x += p_p.x;
        position.y += p_p.y;
    }   
    else{
        position = p_p;
    }
}

//change la vitesse actuel de deplacement
void Boule::modify_velocite(sf::Vector2f p_ve, bool add)   {
    if (add)    {
        velocite.x += p_ve.x;
        velocite.y += p_ve.y;
    }   
    else{
        velocite = p_ve;
    }
}

/////////////////////////////////////////////getters/////////////////////////////////////////////
const sf::Vector2f &Boule::get_pos()  const{
    return position;
}

const sf::Vector2f &Boule::get_v()  const{
    return vitesse;
}

const sf::Vector2f &Boule::get_ve() const{
    return velocite;
}

const sf::Vector2f &Boule::get_re() const{
    return rebond;
}

float Boule::get_r()  const{
    return rayon;
}


//Pour les limites de l'ecran
void Boule::sortieEcran()   {
    int diametre = rayon * 2;
    if (position.x < 0 - diametre) position.x += resol_x;
    if (position.y < 0 - diametre) position.y += resol_y;

    if (position.x > resol_x - diametre) position.x -= resol_x;
    if (position.y > resol_y - diametre) position.y -= resol_y;

    //Créér une illusion de deuxième balle ou plus (recupere coordonnées)
    positionFantome = {-9999, -9999};

    sortie_x = false;
    sortie_y = false;

    if ((position.x < 0) && (position.x >= 0 - diametre))    {  positionFantome = {position.x + resol_x, position.y};   sortie_x = true;   }
    if ((position.y < 0) && (position.y >= 0 - diametre))    {  positionFantome = {position.x, position.y + resol_y};   sortie_y = true;   }

    //et 2 autres boules fantome dans les angles
    positionFantome2 = {-9999, -9999};
    positionFantome3 = {-9999, -9999};
    if (sortie_x && sortie_y)   {
        positionFantome2 = {position.x + resol_x, position.y};
        positionFantome3 = {position.x + resol_x, position.y + resol_y};
    }
}

//Vérifie la collision avec une autre boule
bool Boule::collision(const Boule &autreBoule)  const{
    //Centres des boules
    float centre_x_1 = position.x + rayon;
    float centre_y_1 = position.y + rayon;
    float centre_x_2 = autreBoule.position.x + autreBoule.rayon;
    float centre_y_2 = autreBoule.position.y + autreBoule.rayon;

    //distance absolue entre les 2 boules
    float d_x = centre_x_1 - centre_x_2;
    float d_y = centre_y_1 - centre_y_2;
    float distance = d_x * d_x + d_y * d_y;

    //collision si distance plus petit que rayon cumulé
    float rayon_Tot = rayon + autreBoule.rayon;
    bool collision = distance <= rayon_Tot * rayon_Tot;

    if (collision)  return collision;

    //boule actuel 1*fantome
    if (positionFantome.x != -9999 && positionFantome.y != -9999)   {
        centre_x_1 = positionFantome.x + rayon;
        centre_y_1 = positionFantome.y + rayon;
        d_x = centre_x_1 - centre_x_2;
        d_y = centre_y_1 - centre_y_2;
        distance = d_x * d_x + d_y * d_y;

        collision = distance <= rayon_Tot * rayon_Tot;
        if (collision)  return collision;
    }
    
    //boule actuel 3* fantome
    if (positionFantome.x != -9999 && positionFantome.y != -9999 && positionFantome2.x != -9999 && positionFantome2.y != -9999 && positionFantome3.x != -9999 && positionFantome3.y != -9999)   {
        centre_x_1 = positionFantome2.x + rayon;
        centre_y_1 = positionFantome2.y + rayon;
        d_x = centre_x_1 - centre_x_2;
        d_y = centre_y_1 - centre_y_2;
        distance = d_x * d_x + d_y * d_y;

        collision = distance <= rayon_Tot * rayon_Tot;
        if (collision)  return collision;

        centre_x_1 = positionFantome3.x + rayon;
        centre_y_1 = positionFantome3.y + rayon;
        d_x = centre_x_1 - centre_x_2;
        d_y = centre_y_1 - centre_y_2;
        distance = d_x * d_x + d_y * d_y;

        collision = distance <= rayon_Tot * rayon_Tot;
        if (collision)  return collision;
    }
    

    //autre boule 1*fantome
    if (autreBoule.positionFantome.x != -9999 && autreBoule.positionFantome.y != -9999)   {
        centre_x_2 = autreBoule.positionFantome.x + autreBoule.rayon;
        centre_y_2 = autreBoule.positionFantome.y + autreBoule.rayon;
        d_x = centre_x_1 - centre_x_2;
        d_y = centre_y_1 - centre_y_2;
        distance = d_x * d_x + d_y * d_y;

        collision = distance <= rayon_Tot * rayon_Tot;
        if (collision)  return collision;
    }
    
    //autre boule 3* fantome
    if (autreBoule.positionFantome.x != -9999 && autreBoule.positionFantome.y != -9999 && autreBoule.positionFantome2.x != -9999 && autreBoule.positionFantome2.y != -9999 && autreBoule.positionFantome3.x != -9999 && autreBoule.positionFantome3.y != -9999)   {
        centre_x_2 = autreBoule.positionFantome2.x + autreBoule.rayon;
        centre_y_2 = autreBoule.positionFantome2.y + autreBoule.rayon;
        d_x = centre_x_1 - centre_x_2;
        d_y = centre_y_1 - centre_y_2;
        distance = d_x * d_x + d_y * d_y;

        collision = distance <= rayon_Tot * rayon_Tot;
        if (collision)  return collision;

        centre_x_2 = autreBoule.positionFantome3.x + autreBoule.rayon;
        centre_y_2 = autreBoule.positionFantome3.y + autreBoule.rayon;
        d_x = centre_x_1 - centre_x_2;
        d_y = centre_y_1 - centre_y_2;
        distance = d_x * d_x + d_y * d_y;

        collision = distance <= rayon_Tot * rayon_Tot;
        if (collision)  return collision;
    }

    //les 2 boules sont 1*fantomes
    if (positionFantome.x != -9999 && positionFantome.y != -9999 && autreBoule.positionFantome.x != -9999 && autreBoule.positionFantome.y != -9999)   {
        centre_x_1 = position.x + rayon;
        centre_y_1 = position.y + rayon;
        d_x = centre_x_1 - centre_x_2;
        d_y = centre_y_1 - centre_y_2;
        distance = d_x * d_x + d_y * d_y;

        collision = distance <= rayon_Tot * rayon_Tot;
        if (collision)  return collision;
    }
    return false;
}