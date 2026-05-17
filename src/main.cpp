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

    //Création texte
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

    //Pour gérer l'ordre d'affichage
    std::vector<int> mesBoulesOrdre = {0, 1};
    int lastBoule = 0;

    //Vecteur qui gere le deplacment des 2 boules
    std::vector<sf::Vector2f> mesBoulesDeplacement = {{0,0}, {0,0}};

    int indiceActuel = 0;

    /*Pour gérer le mode
        0: sans collision
        1: collision static
        2: collision qui déplace
        3: collision qui rebondit
    */
    int modeActifCollision = 0;

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

                    default:
                        break;
                }
            }
        }

        //Affiche les modes
        switch (modeActifCollision)  {
            case 0:
                mode.setString(std::to_string(modeActifCollision) + ") Sans collision (+/-)");
                break;

            case 1:
                mode.setString(std::to_string(modeActifCollision) + ") Collision statique (+/-)");
                break;

            case 2:
                mode.setString(std::to_string(modeActifCollision) + ") Collision mouvemente (+/-)");
                break;

            case 3:
                mode.setString(std::to_string(modeActifCollision) + ") Collision rebond (+/-)");
                break;
            
            default:
                mode.setString("+ ou - pour changer");
                break;
        }

        float dt = clock.restart().asSeconds(); // 1/dt = fps actuel

        /////////////////////////////////////////////Gères les déplacements/////////////////////////////////////////////
        indiceActuel = 0;
        mesBoulesDeplacement[indiceActuel] = {0,0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))    {
            mesBoulesDeplacement[indiceActuel].y -= 1;
            lastBoule = indiceActuel;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))    {
            mesBoulesDeplacement[indiceActuel].y += 1;
            lastBoule = indiceActuel;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))    {
            mesBoulesDeplacement[indiceActuel].x -= 1;
            lastBoule = indiceActuel;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))    {
            mesBoulesDeplacement[indiceActuel].x += 1;
            lastBoule = indiceActuel;
        }

        indiceActuel = 1;
        mesBoulesDeplacement[indiceActuel] = {0,0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    {
            mesBoulesDeplacement[indiceActuel].y -= 1;
            lastBoule = indiceActuel;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))    {
            mesBoulesDeplacement[indiceActuel].y += 1;
            lastBoule = indiceActuel;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))    {
            mesBoulesDeplacement[indiceActuel].x -= 1;
            lastBoule = indiceActuel;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))    {
            mesBoulesDeplacement[indiceActuel].x += 1;
            lastBoule = indiceActuel;
        }

        //Pour la priorité d'affichage
        if (mesBoulesOrdre.back() != lastBoule) {
                mesBoulesOrdre.erase(std::find(mesBoulesOrdre.begin(), mesBoulesOrdre.end(), lastBoule));
                mesBoulesOrdre.push_back(lastBoule);
        }

        //Gere le deplacement
        for (int i = 0 ; i < mesBoulesDeplacement.size() ; i++)   
            gererDeplacement(mesBoules, mesBoulesDeplacement[i] * dt * 100.f, i, i, modeActifCollision);

        //Nettoie fenetre
        window.clear(sf::Color::White);

        //affiches les boules + le texte
        for (int b : mesBoulesOrdre)  {
            mesBoules[b].draw(window);
        }
        window.draw(mode);
        
        // affiche
        window.display();
    }
}