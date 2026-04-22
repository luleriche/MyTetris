#include "Piece.hpp"


Piece::Piece(PieceMold mold, sf::Vector2f bricksSize, const sf::Texture& bricksTexture)
: m_bricksTexture(&bricksTexture) , m_bricksColor(mold.color), m_bricksSize(bricksSize) {
    int x = 0;
    int y = 0;
    m_nbBricks = 0;
    for (unsigned int i = 0; i < mold.pattern.length(); ++i) {
        if (mold.pattern[i] == 'x') {
            sf::Vector2i gridPos(x+mold.spawnOffset.x, y+mold.spawnOffset.y);
            m_bricks[m_nbBricks] = Brick(gridPos, bricksSize, bricksTexture, m_bricksColor);
            ++m_nbBricks;
            ++x;
        }
        else if (mold.pattern[i] == '/') {
            ++y;
            x = 0;
        }
        else {
            ++x;
        }
    }
}

void Piece::tryMove(sf::Vector2i vector, sf::Vector2i gridSize, std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy) {

    if(isValid(getPosAfterMove(this->getAllBricksPos(), m_nbBricks, vector), m_nbBricks, gridSize, gridOccupancy))
        for(int i = 0; i < m_nbBricks; ++i){
            m_bricks[i].moveBrick(vector);
        }
}

void Piece::draw(sf::RenderWindow& window) {
    for (int i = 0; i < m_nbBricks; ++i) {
        window.draw(m_bricks[i]);
    }
}

int Piece::getNbBricks(){
    return m_nbBricks;
}

std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> Piece::getAllBricksPos(){
    std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> result;
    for(int i = 0; i < m_nbBricks; ++i){
        result[i] = m_bricks[i].getGridPos();
    }
    return result;
}

std::array<Brick, NMax> Piece::getBricksList(){
    return m_bricks;
}