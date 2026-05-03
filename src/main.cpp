//Include général
#include <SFML/Graphics.hpp>
#include <vector>

//Include de mes librairies
#include "boule.h"

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
        Boule({0.f, 0.f}, 40.f, sf::Color::Red, {1, 1}), 
        Boule({80.f, 0.f}, 30.f, sf::Color::Blue, {3, 3})
    };

    //Pour gérer l'ordre d'affichage
    std::vector<int> mesBoulesOrdre = {0, 1};
    int lastBoule = 0;

    /*Pour gérer le mode
        0: sans collision
        1: collision static
        2: collision qui déplace
        3: collision qui rebondit
    */
    int modeActifCollision = 0;

    //ToDo: ajouter carré
    //ToDo: ajouter plateforme

    //Boucle du jeu
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            //Vérifie fermeture
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Affiche les modes
        switch (modeActifCollision)  {
        case 0:
            mode.setString("Sans collision (+/-)");
            break;
        
        default:
            mode.setString("+ ou - pour changer");
            break;
        }

        /////////////////////////////////////////////Gères les déplacements/////////////////////////////////////////////
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))    {
            mesBoules[0].modify_pos({0, -mesBoules[0].get_v().y}, true);
            lastBoule = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))    {
            mesBoules[0].modify_pos({0, mesBoules[0].get_v().y}, true);
            lastBoule = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))    {
            mesBoules[0].modify_pos({-mesBoules[0].get_v().x, 0}, true);
            lastBoule = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))    {
            mesBoules[0].modify_pos({mesBoules[0].get_v().x, 0}, true);
            lastBoule = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    {
            mesBoules[1].modify_pos({0, -mesBoules[1].get_v().y}, true);
            lastBoule = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))    {
            mesBoules[1].modify_pos({0, mesBoules[1].get_v().y}, true);
            lastBoule = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))    {
            mesBoules[1].modify_pos({-mesBoules[1].get_v().x, 0}, true);
            lastBoule = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))    {
            mesBoules[1].modify_pos({mesBoules[1].get_v().x, 0}, true);
            lastBoule = 1;
        }

        //Pour la priorité d'affichage
        if (mesBoulesOrdre.back() != lastBoule) {
                mesBoulesOrdre.erase(std::find(mesBoulesOrdre.begin(), mesBoulesOrdre.end(), lastBoule));
                mesBoulesOrdre.push_back(lastBoule);
            }

        //Actualise positions boules et vérifie sortie
        for (Boule &b : mesBoules)  {
            b.sortieEcran(800, 600);
            b.update();
        }

        //Nettoie fenetre / affiches les boules / affiches le texte / affiche
        window.clear(sf::Color::White);

        for (int b : mesBoulesOrdre)  {
            mesBoules[b].draw(window);
        }
        window.draw(mode);
        window.display();
        sf::sleep(sf::milliseconds(10));
    }
}