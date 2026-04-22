#pragma once

#include <SFML/Graphics.hpp>
#include "Brick.hpp"
#include "Piece.hpp"
#include <array>
const int nbMaxCol = 40, nbMaxRow = 50;

class Grid
{
private:
    // Taille en pixels de la grille
    sf::Vector2f m_totalSize;
    // Dimensions de la grille (nb col, nb ligne)
    sf::Vector2i m_gridSize;
    // Taille en pixels des cellules de la grille
    sf::Vector2f m_tileSize;
    int m_lineWidth;
    sf::Color m_bgColor, m_lineColor;
    // Tableaux de booleens d'occupation des cellules de la grille
    std::array<std::array<bool, nbMaxRow>, nbMaxCol> m_occupancyGrid;
    // Tableaux de pointeurs vers les briques qui sont fixes dans la grille
    std::array<std::array<Brick*, nbMaxRow>, nbMaxCol> m_gridBricks;

public:
    Grid(sf::Vector2f totalSize, int nb_col, int nb_row);

    void draw(sf::RenderWindow& window);

    sf::Vector2f get_tileSize();

    void addPieceToBricks(Piece piece);

    sf::Vector2i getGridSize();
};
