#pragma once

#include <SFML/Graphics.hpp>

class Brick: public sf::Sprite
{
private:
    sf::Vector2i m_gridPos;
public:
    Brick() = default;

    Brick(sf::Vector2i gridPos, sf::Vector2f brickSize, sf::Texture &texture, sf::Color brickColor);

    void moveBrick(sf::Vector2i vector);
};