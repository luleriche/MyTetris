#pragma once

#include <SFML/Graphics.hpp>

class Grid
{
private:
    sf::Vector2f m_totalSize;
    sf::Vector2i m_gridSize;
    sf::Vector2f m_tileSize;
    int m_lineWidth;
    sf::Color m_bgColor, m_lineColor;

public:
    Grid(sf::Vector2f totalSize, int nb_col, int nb_row);

    void draw(sf::RenderWindow& window);

    sf::Vector2f get_tileSize();

};
