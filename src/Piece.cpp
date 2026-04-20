#include "Piece.hpp"
#include "Brick.hpp"

Piece::Piece(std::string pattern, sf::Color color, sf::Vector2f bricksSize, sf::Texture &bricksTexture)
: m_bricksTexture(&bricksTexture) , m_bricksColor(color), m_bricksSize(bricksSize) {
    int x = 0;
    int y = 0;
    m_nbBricks = 0;
    for (unsigned int i = 0; i < pattern.length(); ++i) {
        if (pattern[i] == 'x') {
            sf::Vector2i gridPos(x, y);
            m_bricks[m_nbBricks] = Brick(gridPos, bricksSize, bricksTexture, color);
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
        m_bricks[i].moveBrick(vector);
    }
}

void Piece::draw(sf::RenderWindow& window) {
    for (int i = 0; i < m_nbBricks; ++i) {
        window.draw(m_bricks[i]);
    }
}