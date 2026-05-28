#ifndef BOULE_H
#define BOULE_H

#include <SFML/Graphics.hpp>
#include <cmath>
class Rectangle;

class Boule {
    private:
        sf::CircleShape circle;

        sf::Vector2f position;
        sf::Vector2f positionFantome;
        sf::Vector2f positionFantome2;
        sf::Vector2f positionFantome3;
        sf::Vector2f vitesse;
        sf::Vector2f velocite;
        sf::Vector2f rebond;

        float friction;
        float rayon;
        int resol_x, resol_y;

        bool sortie_x, sortie_y;
        
    public:
        Boule(sf::Vector2f p_p, float p_r, sf::Color couleur, sf::Vector2f p_v, int p_resol_x, int p_resol_y);

        void update(sf::Vector2f pos);
        void slide(sf::Vector2f force, bool sliding);
        void draw(sf::RenderWindow &window);

        void modify_v(sf::Vector2f p_v, bool add);
        void modify_pos(sf::Vector2f p_p, bool add);
        void modify_velocite(sf::Vector2f p_ve, bool add);

        const sf::Vector2f &get_pos() const;
        const sf::Vector2f &get_v() const;
        const sf::Vector2f &get_ve() const;
        const sf::Vector2f &get_re() const;
        float get_r() const;

        void sortieEcran();
        bool collision(const Boule &autreBoule) const;
        bool collisionRectangle(const Rectangle &rectangle)  const;
};

#endif