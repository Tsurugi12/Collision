#include "commande.h"
#include "boule.h"


//Boule

//Fonction qui gère le déplacement
void gererDeplacement(std::vector<Boule> &mesBoules, sf::Vector2f deplacement, int bouleActuel, int ancienneBoule, int modeActifCollision) {
    mesBoules[bouleActuel].slide({mesBoules[bouleActuel].get_v().x * deplacement.x, mesBoules[bouleActuel].get_v().y * deplacement.y}, true);
    mesBoules[bouleActuel].modify_pos(mesBoules[bouleActuel].get_ve() + mesBoules[bouleActuel].get_re(), true);
    
    //pour proteger collision avec balle fantome
    mesBoules[bouleActuel].sortieEcran();

    //Si mode collision
    if (modeActifCollision)
        gereCollision(mesBoules, deplacement, bouleActuel, ancienneBoule, modeActifCollision);

    //Vérifie les limites de l'ecran
    mesBoules[bouleActuel].sortieEcran();
}


//Fonction qui gère les collisions
/*Pour gérer le mode
        1: collision static
        2: collision qui déplace
        3: collision qui rebondit
*/
void gereCollision(std::vector<Boule> &mesBoules, sf::Vector2f deplacement, int bouleActuel, int ancienneBoule, int modeActifCollision)    {
    if (modeActifCollision == 1)    {
        for (int i = 0; i < mesBoules.size(); i++)   {
            if (i != bouleActuel)   {
                if (mesBoules[bouleActuel].collision(mesBoules[i])) {
                    if (deplacement.x * mesBoules[bouleActuel].get_ve().x >= 0 && deplacement.y * mesBoules[bouleActuel].get_ve().y >= 0)   {
                        mesBoules[bouleActuel].modify_velocite(-mesBoules[bouleActuel].get_ve(), false);
                        mesBoules[bouleActuel].modify_pos(mesBoules[bouleActuel].get_ve(), true);
                    }   
                    else{
                        mesBoules[bouleActuel].modify_pos(mesBoules[bouleActuel].get_ve(), true);
                    }
                }
            }
        }
    }

    if (modeActifCollision == 2)    {
        for (int i = 0; i < mesBoules.size(); i++)   {
            if (!(i == bouleActuel || i == ancienneBoule))   {
                if (mesBoules[bouleActuel].collision(mesBoules[i])) {
                    mesBoules[i].modify_pos(mesBoules[bouleActuel].get_ve(), true);
                    gereCollision(mesBoules, deplacement, i, bouleActuel, modeActifCollision);
                }
            }
        }
    }

    if (modeActifCollision == 3)    {
        for (int i = 0; i < mesBoules.size(); i++)   {
            if (!(i == bouleActuel || i == ancienneBoule))   {
                if (mesBoules[bouleActuel].collision(mesBoules[i])) {
                    mesBoules[i].slide(mesBoules[bouleActuel].get_ve(), false);
                    mesBoules[i].modify_pos(mesBoules[i].get_ve() + mesBoules[i].get_re(), true);
                    gereCollision(mesBoules, deplacement, i, bouleActuel, modeActifCollision);
                    mesBoules[bouleActuel].modify_velocite(mesBoules[bouleActuel].get_ve() / 2.f, false);
                }  
            }
        }
    }
}


//Rectangle

//Fonction qui gère le déplacement
void gererDeplacement(std::vector<Rectangle> &mesRectangles, sf::Vector2f deplacement, int RectangleActuel, int ancienRectangle, int modeActifCollision) {
    mesRectangles[RectangleActuel].slide({mesRectangles[RectangleActuel].get_v().x * deplacement.x, mesRectangles[RectangleActuel].get_v().y * deplacement.y}, true);
    mesRectangles[RectangleActuel].modify_pos(mesRectangles[RectangleActuel].get_ve() + mesRectangles[RectangleActuel].get_re(), true);

    mesRectangles[RectangleActuel].sortieEcran();
    
    //Si mode collision
    if (modeActifCollision)
        gereCollision(mesRectangles, deplacement, RectangleActuel, ancienRectangle, modeActifCollision);

    //Vérifie les limites de l'ecran
    mesRectangles[RectangleActuel].sortieEcran();
}


//Fonction qui gère les collisions
/*Pour gérer le mode
        1: collision static
        2: collision qui déplace
        3: collision qui rebondit
*/
void gereCollision(std::vector<Rectangle> &mesRectangles, sf::Vector2f deplacement, int RectangleActuel, int ancienRectangle, int modeActifCollision)    {
    if (modeActifCollision == 1)    {
        for (int i = 0; i < mesRectangles.size(); i++)   {
            if (i != RectangleActuel)   {
                if (mesRectangles[RectangleActuel].collision(mesRectangles[i])) {
                    if (deplacement.x * mesRectangles[RectangleActuel].get_ve().x >= 0 && deplacement.y * mesRectangles[RectangleActuel].get_ve().y >= 0)   {
                        mesRectangles[RectangleActuel].modify_velocite(-mesRectangles[RectangleActuel].get_ve(), false);
                        mesRectangles[RectangleActuel].modify_pos(mesRectangles[RectangleActuel].get_ve(), true);
                    }   
                    else{
                        mesRectangles[RectangleActuel].modify_pos(mesRectangles[RectangleActuel].get_ve(), true);
                    }
                }
            }
        }
    }

    if (modeActifCollision == 2)    {
        for (int i = 0; i < mesRectangles.size(); i++)   {
            if (!(i == RectangleActuel || i == ancienRectangle))   {
                if (mesRectangles[RectangleActuel].collision(mesRectangles[i])) {
                    mesRectangles[i].modify_pos(mesRectangles[RectangleActuel].get_ve(), true);
                    gereCollision(mesRectangles, deplacement, i, RectangleActuel, modeActifCollision);
                }
            }
        }
    }

    if (modeActifCollision == 3)    {
        for (int i = 0; i < mesRectangles.size(); i++)   {
            if (!(i == RectangleActuel || i == ancienRectangle))   {
                if (mesRectangles[RectangleActuel].collision(mesRectangles[i])) {
                    mesRectangles[i].slide(mesRectangles[RectangleActuel].get_ve(), false);
                    mesRectangles[i].modify_pos(mesRectangles[i].get_ve() + mesRectangles[i].get_re(), true);
                    gereCollision(mesRectangles, deplacement, i, RectangleActuel, modeActifCollision);
                    mesRectangles[RectangleActuel].modify_velocite(mesRectangles[RectangleActuel].get_ve() / 2.f, false);
                }  
            }
        }
    }
}

//Humans
void gererDeplacement(std::vector<Human> &mesHumains, sf::Vector2f deplacement, int HumanActuel, int ancienHuman, int modeActifCollision)   {
    mesHumains[HumanActuel].update({mesHumains[HumanActuel].get_v().x * deplacement.x, mesHumains[HumanActuel].get_v().y * deplacement.y}, true);
    mesHumains[HumanActuel].sortieEcran();

    //Si mode collision
    if (modeActifCollision)
        gereCollision(mesHumains, deplacement, HumanActuel, ancienHuman, modeActifCollision);

    mesHumains[HumanActuel].sortieEcran();
}


void gereCollision(std::vector<Human> &mesHumains, sf::Vector2f deplacement, int HumanActuel, int ancienHuman, int modeActifCollision)  {
    if (modeActifCollision == 1)    {
        for (int i = 0; i < mesHumains.size(); i++)   {
            if (i != HumanActuel)   {
                if (mesHumains[HumanActuel].collision(mesHumains[i])) {
                    mesHumains[HumanActuel].update({-mesHumains[HumanActuel].get_v().x * deplacement.x, -mesHumains[HumanActuel].get_v().y * deplacement.y}, true);
                }
            }
        }
    }

    if (modeActifCollision == 2)    {
        for (int i = 0; i < mesHumains.size(); i++)   {
            if (!(i == HumanActuel || i == ancienHuman))   {
                if (mesHumains[HumanActuel].collision(mesHumains[i])) {
                    mesHumains[i].update({mesHumains[HumanActuel].get_v().x * deplacement.x, mesHumains[HumanActuel].get_v().y * deplacement.y}, true);
                    gereCollision(mesHumains, deplacement, i, HumanActuel, modeActifCollision);
                }
            }
        }
    }
/*
    if (modeActifCollision == 3)    {
        for (int i = 0; i < mesHumains.size(); i++)   {
            if (!(i == HumanActuel || i == ancienHuman))   {
                if (mesHumains[HumanActuel].collision(mesHumains[i])) {
                    mesHumains[i].slide(mesHumains[HumanActuel].get_ve(), false);
                    mesHumains[i].modify_pos(mesHumains[i].get_ve() + mesHumains[i].get_re(), true);
                    gereCollision(mesHumains, deplacement, i, HumanActuel, modeActifCollision);
                    mesHumains[HumanActuel].modify_velocite(mesHumains[HumanActuel].get_ve() / 2.f, false);
                }  
            }
        }
    }*/
}