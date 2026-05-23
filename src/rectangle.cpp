#include "rectangle.h"

//Constructeur
Rectangle::Rectangle(sf::Vector2f p_p, float p_h, float p_w, sf::Color couleur, sf::Vector2f p_v, int p_resol_x, int p_resol_y)  {
    position = p_p;

    height = p_h;
    width = p_w;
    vitesse = p_v; //vitesse max sans collision
    velocite = {0,0}; //vitesse réel
    rebond = {0,0}; // vitesse ajouté quand poussé
    friction = 0.95;

    resol_x = p_resol_x;
    resol_y = p_resol_y;
    
    rect.setSize({width, height});
    rect.setFillColor(couleur);
}

//Actualise position
void Rectangle::update(sf::Vector2f pos)    {
    rect.setPosition(pos);
}

//Gere les rebonds entre rectangle
void Rectangle::slide(sf::Vector2f force, bool sliding)   {
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

//Affiche rectangle
void Rectangle::draw(sf::RenderWindow &window)  {
    update(position);
    window.draw(rect);
}

//change la vitesse
void Rectangle::modify_v(sf::Vector2f p_v, bool add)  {
    if (add)    {
        vitesse.x += p_v.x;
        vitesse.y += p_v.y;
    }   
    else{
        vitesse = p_v;
    }
}

//change la position
void Rectangle::modify_pos(sf::Vector2f p_p, bool add)    {
    if (add)    {
        position.x += p_p.x;
        position.y += p_p.y;
    }   
    else{
        position = p_p;
    }
}

//change la vitesse actuel de deplacement
void Rectangle::modify_velocite(sf::Vector2f p_ve, bool add)   {
    if (add)    {
        velocite.x += p_ve.x;
        velocite.y += p_ve.y;
    }   
    else{
        velocite = p_ve;
    }
}

//Fonction à but non conventionel
void Rectangle::max(sf::Vector2f p_max)    {
    maxi = p_max;
}

/////////////////////////////////////////////getters/////////////////////////////////////////////
const sf::Vector2f &Rectangle::get_pos()  const{
    return position;
}

const sf::Vector2f &Rectangle::get_v()  const{
    return vitesse;
}

const sf::Vector2f &Rectangle::get_ve() const{
    return velocite;
}

const sf::Vector2f &Rectangle::get_re() const{
    return rebond;
}

float Rectangle::get_h()  const{
    return height;
}

float Rectangle::get_w()  const{
    return width;
}

//Pour les limites de l'ecran
void Rectangle::sortieEcran()   {
    if (position.x < 0 - maxi.x) position.x += resol_x + maxi.x;
    if (position.y < 0 - maxi.y) position.y += resol_y + maxi.y;

    if (position.x >= resol_x) position.x -= resol_x + maxi.x;
    if (position.y >= resol_y) position.y -= resol_y + maxi.y;
}

//Vérifie la collision avec un autre rectangle
bool Rectangle::collision(const Rectangle &autreRectangle)  const{
    float distance_x = position.x - autreRectangle.position.x;
    float distance_y = position.y - autreRectangle.position.y;

    bool collision_x = false;
    bool collision_y = false;

    //Collision en x
    if (distance_x >= 0)    {
        collision_x = autreRectangle.width >= distance_x;
    }
    if (distance_x < 0)    {
        collision_x = width > -distance_x;
    }
    //Verification supplémentaire sur les bords
    if (!collision_x)   {
        distance_x = position.x - resol_x - maxi.x - autreRectangle.position.x;
        collision_x = width >= (distance_x > 0) ? distance_x : -distance_x;
    }
    if (!collision_x)   {
        distance_x = position.x + resol_x + maxi.x - autreRectangle.position.x;
        //collision_x = autreRectangle.width < distance_x;
    }


    //Collision en y
    if (distance_y >= 0)    {
        collision_y = autreRectangle.height >= distance_y;
    }
    if (distance_y < 0)    {
        collision_y = height > -distance_y;
    }
    /*if (!collision_y)   {
        distance_y = position.y - resol_y - height - autreRectangle.position.y;
        if (distance_y >= 0)    {
            collision_y = autreRectangle.height >= distance_y;
        }

        if (distance_y < 0)    {
            collision_y = height > -distance_y;
        }
    }*/

    if (collision_x && collision_y) return true;
    else    return false;
}