#include "Brick.hpp"

Brick::Brick(sf::Vector2i gridPos, sf::Vector2f size, const sf::Texture &texture, sf::Color color)
: m_gridPos(gridPos)
{
    this->setTexture(texture);
    this->setColor(color);
    this->setScale(size.x/480, size.y/480);
    this->setPosition(gridPos.x*size.x, gridPos.y*size.y);
}

void Brick::moveBrick(sf::Vector2i vector){
    m_gridPos += vector;
    this->move(vector.x*this->getGlobalBounds().width, vector.y*this->getGlobalBounds().height);
}

sf::Vector2i Brick::getGridPos(){
    return m_gridPos;
}