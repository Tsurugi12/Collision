#ifndef BOULE_H
#define BOULE_H

#include <SFML/Graphics.hpp>

class Boule {
    private:
        sf::CircleShape circle;
        sf::Vector2f position;
        sf::Vector2f positionFantome;
        sf::Vector2f vitesse;
        float rayon;
        bool sortie_x, sortie_y;
        int resol_x, resol_y;

    public:
        Boule(sf::Vector2f p_p, float p_r, sf::Color couleur, sf::Vector2f p_v, int p_resol_x, int p_resol_y);

        void update();
        void draw(sf::RenderWindow &window);

        void modify_v(sf::Vector2f p_v, bool add);
        void modify_pos(sf::Vector2f p_p, bool add);

        const sf::Vector2f &get_pos() const;
        const sf::Vector2f &get_v() const;
        float get_r() const;

        void sortieEcran(sf::RenderWindow &window);
        bool collision(const Boule &autreBoule) const;
};

#endif