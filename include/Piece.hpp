#pragma once

#include <SFML/Graphics.hpp>
#include "Brick.hpp"
#include <array>

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

public:
    Piece() = default;

    Piece(std::string pattern, sf::Color color, sf::Vector2f brick_sizes, const sf::Texture &brick_texture);
    
    // Change la position des briques de la pièce
    void move(sf::Vector2i vector);

    void draw(sf::RenderWindow& window);
    
    int getNbBricks();

    std::array<Brick, NMax> getBricksList();
};