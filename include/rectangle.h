#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
class Boule;

class Rectangle{
    private:
        sf::RectangleShape rect;

        sf::Vector2f position;
        sf::Vector2f positionFantome;
        sf::Vector2f positionFantome2;
        sf::Vector2f positionFantome3;
        sf::Vector2f vitesse;
        sf::Vector2f velocite;
        sf::Vector2f rebond;
        sf::Vector2f maxi;

        float friction;
        float height;
        float width;

        int resol_x, resol_y;

        bool sortie_x, sortie_y;

    public:
        Rectangle(sf::Vector2f p_p, float p_h, float p_w, sf::Color couleur, sf::Vector2f p_v, int p_resol_x, int p_resol_y);

        void update(sf::Vector2f pos);
        void slide(sf::Vector2f force, bool sliding);
        void draw(sf::RenderWindow &window);

        void modify_v(sf::Vector2f p_v, bool add);
        void modify_pos(sf::Vector2f p_p, bool add);
        void modify_velocite(sf::Vector2f p_ve, bool add);
        void max(sf::Vector2f p_max);
        void modify_dimension(float p_h, float p_w);

        const sf::Vector2f &get_pos() const;
        const sf::Vector2f &get_v() const;
        const sf::Vector2f &get_ve() const;
        const sf::Vector2f &get_re() const;
        float get_h() const;
        float get_w() const;

        void sortieEcran();
        bool collision(const Rectangle &autreRectangle) const;
        void sortieEcranFantome();
        bool collisionFantome(const Rectangle &autreRectangle) const;
        bool collisionBoule(const Boule &boule)  const;
};