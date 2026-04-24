#include "Piece.hpp"


Piece::Piece(PieceMold mold, sf::Vector2f bricksSize, const sf::Texture& bricksTexture)
: m_bricksTexture(&bricksTexture) , m_bricksColor(mold.color), m_bricksSize(bricksSize), m_rotationCenter(mold.rotationCenter+static_cast<sf::Vector2f>(mold.spawnOffset)) {
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
    m_rotState = Initial;
}

bool Piece::tryMove(sf::Vector2i vector, sf::Vector2i gridSize, std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy) {

    if(isValid(getMovedPositions(this->getPositions(), vector), gridSize, gridOccupancy))
    {
        for(int i = 0; i < m_nbBricks; ++i){
            m_bricks[i].moveBrick(vector);
        }
        m_rotationCenter += static_cast<sf::Vector2f>(vector);
        return true;
    }else
        return false;
}

bool Piece::tryRotate(int side, sf::Vector2i gridSize, std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy){
    ListVect2i posAfterRot = getRotatedPositions(this->getPositions(), m_rotationCenter, true);
    if(isValid(posAfterRot, gridSize, gridOccupancy))
    {
        for(int i = 0; i < m_nbBricks; ++i){
            m_bricks[i].setGridPos(posAfterRot.points[i]);
        }
        return true;
    }else
        return false;

}

void Piece::draw(sf::RenderWindow& window) {
    for (int i = 0; i < m_nbBricks; ++i) {
        window.draw(m_bricks[i]);
    }
}

int Piece::getNbBricks(){
    return m_nbBricks;
}

ListVect2i Piece::getPositions(){
    ListVect2i result;
    result.count = m_nbBricks;
    for(int i = 0; i < m_nbBricks; ++i){
        result.points[i] = m_bricks[i].getGridPos();
    }
    return result;
}

std::array<Brick, NMax> Piece::getBricksList(){
    return m_bricks;
}