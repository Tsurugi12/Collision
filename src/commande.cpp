#include "commande.h"

//Fonction qui gère le déplacement
void gererDeplacement(std::vector<Boule> &mesBoules, int bouleActuel, int d_x, int d_y, int modeActifCollision, int ancienneBoule, sf::RenderWindow &window) {
    mesBoules[bouleActuel].modify_pos({d_x * mesBoules[ancienneBoule].get_v().x, d_y * mesBoules[ancienneBoule].get_v().y}, true);
    //Vérifie les limites de l'ecran
    mesBoules[bouleActuel].sortieEcran(window);

    //Si mode collision
    if (modeActifCollision)
        gereCollision(mesBoules, bouleActuel, d_x, d_y, modeActifCollision, ancienneBoule, window);
}

//Fonction qui gère les collisions
/*Pour gérer le mode
        1: collision static
        2: collision qui déplace
        3: collision qui rebondit
    */
void gereCollision(std::vector<Boule> &mesBoules, int bouleActuel, int d_x, int d_y, int modeActifCollision, int ancienneBoule, sf::RenderWindow &window)    {
    if (modeActifCollision == 1)    {
        for (int i = 0; i < mesBoules.size(); i++)   {
            if (i != bouleActuel)   {
                if (mesBoules[bouleActuel].collision(mesBoules[i]))
                    mesBoules[bouleActuel].modify_pos({-d_x * mesBoules[bouleActuel].get_v().x, -d_y * mesBoules[bouleActuel].get_v().y}, true);
            }
        }
    }

    if (modeActifCollision == 2)    {
        //FIXME: collision avec balle fantome dans coin et certains "event"
        for (int i = 0; i < mesBoules.size(); i++)   {
            //if (i != bouleActuel || i!= ancienneBoule)
            if (i != bouleActuel)   {
                if (mesBoules[bouleActuel].collision(mesBoules[i]))
                    gererDeplacement(mesBoules, i, d_x, d_y, modeActifCollision, bouleActuel, window);
            }
        }
    }
}