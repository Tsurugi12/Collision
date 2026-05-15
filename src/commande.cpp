#include "commande.h"
#include "boule.h"

//Fonction qui gère le déplacement
void gererDeplacement(std::vector<Boule> &mesBoules, int bouleActuel, sf::Vector2f deplacement, int modeActifCollision, int ancienneBoule, sf::RenderWindow &window) {
    mesBoules[bouleActuel].modify_pos({deplacement.x * mesBoules[ancienneBoule].get_v().x, deplacement.y * mesBoules[ancienneBoule].get_v().y}, true);
    
    //pour proteger collision avec balle fantome
    mesBoules[bouleActuel].sortieEcran(window);

    //Si mode collision
    if (modeActifCollision)
        gereCollision(mesBoules, bouleActuel, deplacement, modeActifCollision, ancienneBoule, window);

    //Vérifie les limites de l'ecran
    mesBoules[bouleActuel].sortieEcran(window);
}

//Fonction qui gère les collisions
/*Pour gérer le mode
        1: collision static
        2: collision qui déplace
        3: collision qui rebondit
*/
void gereCollision(std::vector<Boule> &mesBoules, int bouleActuel, sf::Vector2f deplacement, int modeActifCollision, int ancienneBoule, sf::RenderWindow &window)    {
    if (modeActifCollision == 1)    {
        for (int i = 0; i < mesBoules.size(); i++)   {
            if (i != bouleActuel)   {
                if (mesBoules[bouleActuel].collision(mesBoules[i]))
                    mesBoules[bouleActuel].modify_pos({-deplacement.x * mesBoules[bouleActuel].get_v().x, -deplacement.y * mesBoules[bouleActuel].get_v().y}, true);
            }
        }
    }

    if (modeActifCollision == 2)    {
        for (int i = 0; i < mesBoules.size(); i++)   {
            if (!(i == bouleActuel || i == ancienneBoule))   {
                if (mesBoules[bouleActuel].collision(mesBoules[i]))
                    gererDeplacement(mesBoules, i, deplacement, modeActifCollision, bouleActuel, window);
            }
        }
    }

    if (modeActifCollision == 3)    {
        for (int i = 0; i < mesBoules.size(); i++)   {
            if (!(i == bouleActuel || i == ancienneBoule))   {
                if (mesBoules[bouleActuel].collision(mesBoules[i])) {
                    mesBoules[bouleActuel].modify_velocite({0,0}, false);
                    mesBoules[i].rebond(mesBoules, {mesBoules[bouleActuel].get_v().x * deplacement.x, mesBoules[bouleActuel].get_v().y * deplacement.y}, i, bouleActuel, window);
                }  
            }
        }
    }
}