#include "Piece.hpp"

Piece::Piece(std::string pattern, sf::Color color, sf::Vector2f bricksSize, sf::Texture bricksTexture)
: m_bricksTexture(bricksTexture) , m_bricksColor(color), m_bricksSize(bricksSize) {
    int x = 0;
    int y = 0;
    m_nbBricks = 0;
    for (unsigned int i = 0; i < pattern.length(); ++i) {
        if (pattern[i] == 'x') {
            m_bricks[m_nbBricks] = sf::Sprite();
            m_bricks[m_nbBricks].setPosition((x+3)*bricksSize.x, (y+3)*bricksSize.y);
            m_bricks[m_nbBricks].setTexture(bricksTexture);
            m_bricks[m_nbBricks].setColor(color);
            m_bricks[m_nbBricks].setScale(sf::Vector2f(bricksSize.x / 480, bricksSize.y /480));
            ++m_nbBricks;
            ++x;
        }
        else if (pattern[i] == '/') {
            ++y;
            x = 0;
        }
        else {
            ++x;
        }
    }
}

void Piece::move(sf::Vector2i vector) {
    for(int i = 0; i < m_nbBricks; ++i){
        m_bricks[i].move(sf::Vector2f(vector.x*m_bricksSize.x, vector.y*m_bricksSize.y));
    }
}

void Piece::draw(sf::RenderWindow& window) {
    for (int i = 0; i < m_nbBricks; ++i) {
        window.draw(m_bricks[i]);
    }
}