#ifndef GRID_HPP
#define GRID_HPP
#endif

#include <SFML/Graphics.hpp>

class Grid {

public:
    sf::Vector2f size;
    sf::Vector2f bricks_size;
    int nb_col, nb_row, l_width;
    sf::Color bg_color, l_color;

    Grid(sf::Vector2f size, int nb_col, int nb_row);

    void draw(sf::RenderWindow& window);

    sf::Vector2f get_bricks_size();

};
