#pragma once

#include <SFML/Graphics.hpp>
#include "Utils.hpp"
#include <array>

#include "Brick.hpp"



const int NMax = 9;

class Piece
{
private:
    // Briques enfants de la pièce 
    std::array<Brick, NMax> m_bricks;
    // Nombre de briques de la pièce
    int m_nbBricks;
    // Pointeur vers la texture des briques de la pièce
    const sf::Texture* m_bricksTexture;
    sf::Color m_bricksColor;
    sf::Vector2f m_bricksSize;
    sf::Vector2f m_rotationCenter;
    rotationState m_rotState;

public:
    Piece() = default;

    Piece(PieceMold Mold, sf::Vector2f brick_sizes, const sf::Texture &brick_texture);
    
    // Change la position des briques de la pièce
    bool tryMove(sf::Vector2i vector, sf::Vector2i gridSize, std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy);

    bool tryRotate(int side, sf::Vector2i gridSize, std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy);

    void draw(sf::RenderWindow& window);
    
    int getNbBricks();

    ListVect2i getPositions();

    std::array<Brick, NMax> getBricksList();
};