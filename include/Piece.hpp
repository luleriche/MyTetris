#pragma once

#include <SFML/Graphics.hpp>
#include "Brick.hpp"
#include <array>

const int NMax = 9;

class Piece
{
private:
    int m_nbBricks;
    std::array<Brick, NMax> m_bricks;
    sf::Texture* m_bricksTexture;
    sf::Color m_bricksColor;
    sf::Vector2f m_bricksSize;
public:
    Piece() = default;

    Piece(std::string pattern, sf::Color color, sf::Vector2f brick_sizes, sf::Texture& brick_texture);

    void move(sf::Vector2i vector);

    void draw(sf::RenderWindow& window);

};