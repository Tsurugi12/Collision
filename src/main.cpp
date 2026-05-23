//Include général
#include <SFML/Graphics.hpp>
#include <vector>

//Include de mes librairies
#include "boule.h"
#include "rectangle.h"
#include "commande.h"

int main()    {
    //Création fenêtre
    sf::RenderWindow window(sf::VideoMode(800,600), "Collision simulator");

    //Importation police texte
    sf::Font font;
    font.loadFromFile("assets/fonts/Quicksand-Light.ttf");

    sf::Text mode;
    mode.setFont(font);
    mode.setCharacterSize(30);
    mode.setFillColor(sf::Color::Black);
    mode.setPosition(0,0);


    //Création vector Boule
    std::vector<Boule> mesBoules = {
        Boule({0.f, 0.f}, 40.f, sf::Color::Red, {1, 1}, 800, 600), 
        Boule({80.f, 0.f}, 30.f, sf::Color::Blue, {3, 3}, 800, 600)
    };

    //Création vector Rectangle
    std::vector<Rectangle> mesRectangles = {
        Rectangle({0.f, 0.f}, 60.f, 30.f, sf::Color::Red, {1, 3}, 800, 600), 
        Rectangle({80.f, 0.f}, 30.f, 60.f, sf::Color::Blue, {3, 3}, 800, 600)
    };


    //Pour gérer l'ordre d'affichage des boules
    std::vector<int> mesBoulesOrdre = {0, 1};
    int lastBoule = 0;

    //Pour gérer l'ordre d'affichage des rectangles
    std::vector<int> mesRectanglesOrdre = {0, 1};
    int lastRectangle = 0;


    //Vecteur qui gere le deplacment des 2 boules
    std::vector<sf::Vector2f> mesBoulesDeplacement = {{0,0}, {0,0}};

    //Vecteur qui gere le deplacment des 2 boules
    std::vector<sf::Vector2f> mesRectanglesDeplacement = {{0,0}, {0,0}};

    int indiceActuel = 0;


    /*Pour gérer le mode
        0: sans collision
        1: collision static
        2: collision qui déplace
        3: collision qui rebondit
    */
    int modeActifCollision = 0;

    /*Pour gérer les formes affichés
        0: boule
        1: rectangles
        2: TODO:personnage
    */
    int forme = 0;

    //Gerer vitesse par fps
    sf::Clock clock;    
    window.setFramerateLimit(60);   //60fps max

    //Boucle du jeu
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            //Vérifie fermeture
            if (event.type == sf::Event::Closed)
                window.close();

            //surveille + et - pour changer le mode et escape pour fermer
            if (event.type == sf::Event::KeyPressed)    {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                    window.close();
                    break;

                    case sf::Keyboard::Add:
                        modeActifCollision++;
                        modeActifCollision%=4;
                        break;

                    case sf::Keyboard::Subtract:
                        modeActifCollision--;
                        (modeActifCollision == -1)? modeActifCollision = 3 : modeActifCollision;
                        break;

                    case sf::Keyboard::Num0:
                        forme = 0;
                        break;

                    case sf::Keyboard::Num1:
                        forme = 1;
                        break;

                    case sf::Keyboard::Num2:
                        forme = 2;
                        break;

                    default:
                        break;
                }
            }
        }

        std::string formeActuel = (forme == 0) ?  "boule" : 
                                  (forme == 1) ?  "rectangle" : 
                                  (forme == 2) ?  "humanoide" : 
                                                  "";
        
        //Affiche les modes
        switch (modeActifCollision)  {
            case 0:
                mode.setString(std::to_string(modeActifCollision) + ") Sans collision (+/-) avec " + formeActuel + " numpad pour changer");
                break;

            case 1:
                mode.setString(std::to_string(modeActifCollision) + ") Collision statique (+/-) avec " + formeActuel + " numpad pour changer");
                break;

            case 2:
                mode.setString(std::to_string(modeActifCollision) + ") Collision mouvemente (+/-) avec " + formeActuel + " numpad pour changer");
                break;

            case 3:
                mode.setString(std::to_string(modeActifCollision) + ") Collision rebond (+/-) avec " + formeActuel + " numpad pour changer");
                break;
            
            default:
                mode.setString("+ ou - pour changer collision ou numpad pour changer forme");
                break;
        }

        float dt = clock.restart().asSeconds(); // 1/dt = fps actuel

        /////////////////////////////////////////////Gères les déplacements/////////////////////////////////////////////
        indiceActuel = 0;
        mesBoulesDeplacement[indiceActuel] = {0,0};
        mesRectanglesDeplacement[indiceActuel] = {0,0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))    {
            if (forme == 0) {
                mesBoulesDeplacement[indiceActuel].y -= 1;
                lastBoule = indiceActuel;
            }

            if (forme == 1) {
                mesRectanglesDeplacement[indiceActuel].y -= 1;
                lastRectangle = indiceActuel;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))    {
            if (forme == 0) {
                mesBoulesDeplacement[indiceActuel].y += 1;
                lastBoule = indiceActuel;
            }

            if (forme == 1) {
                mesRectanglesDeplacement[indiceActuel].y += 1;
                lastRectangle = indiceActuel;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))    {
            if (forme == 0) {
            mesBoulesDeplacement[indiceActuel].x -= 1;
            lastBoule = indiceActuel;
            }

            if (forme == 1) {
            mesRectanglesDeplacement[indiceActuel].x -= 1;
            lastRectangle = indiceActuel;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))    {
            if (forme == 0) {
            mesBoulesDeplacement[indiceActuel].x += 1;
            lastBoule = indiceActuel;
            }

            if (forme == 1) {
            mesRectanglesDeplacement[indiceActuel].x += 1;
            lastRectangle = indiceActuel;
            }
        }


        indiceActuel = 1;
        mesBoulesDeplacement[indiceActuel] = {0,0};
        mesRectanglesDeplacement[indiceActuel] = {0,0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    {
            if (forme == 0) {
            mesBoulesDeplacement[indiceActuel].y -= 1;
            lastBoule = indiceActuel;
            }

            if (forme == 1) {
            mesRectanglesDeplacement[indiceActuel].y -= 1;
            lastRectangle = indiceActuel;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))    {
            if (forme == 0) {
            mesBoulesDeplacement[indiceActuel].y += 1;
            lastBoule = indiceActuel;
            }

            if (forme == 1) {
            mesRectanglesDeplacement[indiceActuel].y += 1;
            lastRectangle = indiceActuel;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))    {
            if (forme == 0) {
            mesBoulesDeplacement[indiceActuel].x -= 1;
            lastBoule = indiceActuel;
            }

            if (forme == 1) {
            mesRectanglesDeplacement[indiceActuel].x -= 1;
            lastRectangle = indiceActuel;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))    {
            if (forme == 0) {
            mesBoulesDeplacement[indiceActuel].x += 1;
            lastBoule = indiceActuel;
            }

            if (forme == 1) {
            mesRectanglesDeplacement[indiceActuel].x += 1;
            lastRectangle = indiceActuel;
            }
        }

        //Methode non conventionel mais fonctionne pour ce cas.
        if (forme == 1) {
            //recupere taille max pour gerer sortie ecran
            float max_x = mesRectangles[0].get_w();
            float max_y = mesRectangles[0].get_h();
            for (Rectangle &r : mesRectangles)   {
                if (max_x < r.get_w())  max_x = r.get_w();
                if (max_y < r.get_h())  max_y = r.get_h();
            }
            for (Rectangle &r : mesRectangles)   r.max({max_x, max_y});
        }


        //Pour la priorité d'affichage des boules
        if (mesBoulesOrdre.back() != lastBoule) {
                mesBoulesOrdre.erase(std::find(mesBoulesOrdre.begin(), mesBoulesOrdre.end(), lastBoule));
                mesBoulesOrdre.push_back(lastBoule);
        }

        //Pour la priorité d'affichage des rectangles
        if (mesRectanglesOrdre.back() != lastRectangle) {
                mesRectanglesOrdre.erase(std::find(mesRectanglesOrdre.begin(), mesRectanglesOrdre.end(), lastRectangle));
                mesRectanglesOrdre.push_back(lastRectangle);
        }


        //Gere le deplacement boule
        if (forme == 0) {
            for (int i = 0 ; i < mesBoulesDeplacement.size() ; i++)   
                gererDeplacement(mesBoules, mesBoulesDeplacement[i] * dt * 100.f, i, i, modeActifCollision);
        }
        
        //Gere le deplacement boule
        if (forme == 1) {
            for (int i = 0 ; i < mesRectanglesDeplacement.size() ; i++)   
                gererDeplacement(mesRectangles, mesRectanglesDeplacement[i] * dt * 100.f, i, i, modeActifCollision);
        }


        //Nettoie fenetre
        window.clear(sf::Color::White);

        //affiches les boules
        if (forme == 0) {
            for (int b : mesBoulesOrdre)  {
                mesBoules[b].draw(window);
            }
        }

        //affiches les rectangles
        if (forme == 1) {
            for (int b : mesRectanglesOrdre)  {
                mesRectangles[b].draw(window);
            }
        }

        //affiche le texte
        window.draw(mode);
        
        // affiche
        window.display();
    }
}