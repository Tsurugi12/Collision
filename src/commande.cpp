#include "commande.h"

//Fonction qui gère le déplacement
void gererDeplacement(std::vector<Boule> &mesBoules, int bouleActuel, int d_x, int d_y, int modeActifCollision) {
    mesBoules[bouleActuel].modify_pos({d_x * mesBoules[bouleActuel].get_v().x, d_y * mesBoules[bouleActuel].get_v().y}, true);

    //Si mode collision
    if (modeActifCollision)
        gereCollision(mesBoules, bouleActuel, d_x, d_y, modeActifCollision);
}

//Fonction qui gère les collisions
/*Pour gérer le mode
        1: collision static
        2: collision qui déplace
        3: collision qui rebondit
    */
void gereCollision(std::vector<Boule> &mesBoules, int bouleActuel, int d_x, int d_y, int modeActifCollision)    {
    if (modeActifCollision == 1)    {
        for (int i = 0; i < mesBoules.size(); i++)   {
            if (i != bouleActuel)   {
                if (mesBoules[bouleActuel].collision(mesBoules[i]))
                    mesBoules[bouleActuel].modify_pos({-d_x * mesBoules[bouleActuel].get_v().x, -d_y * mesBoules[bouleActuel].get_v().y}, true);
            }
        }
    }
}