#ifndef BOULE_H
#define BOULE_H

#include <SFML/Graphics.hpp>

class Boule {
    private:
        sf::CircleShape circle;
        sf::Vector2f position;
        sf::Vector2f vitesse;
        float rayon;

    public:
        Boule(sf::Vector2f p_p, float p_r, sf::Color couleur, sf::Vector2f p_v);

        void update();
        void draw(sf::RenderWindow &window);

        void modify_v(sf::Vector2f p_v, bool add);
        void modify_pos(sf::Vector2f p_p, bool add);

        const sf::Vector2f &get_pos() const;
        const sf::Vector2f &get_v() const;
        float get_r() const;

        void sortieEcran(int resol_x, int resol_y);
        bool collision(const Boule &autreBoule) const;
};

#endif