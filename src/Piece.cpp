#include <fstream>
#include "Piece.hpp"
#include "Log.hpp"

void Piece::readWallKicks(std::string fileName){
    m_srsData = new ListVect2i[8];
    std::ifstream file;
    file.open(fileName);
    if(file.is_open()){
        Log::debug("Fichier SRS data ouvert correctement.");
        std::string head;
        int count;
        while(file.good()){
            file >> head >> count;
            int index = getIndexFromRotationStates(getRotationStateFromLetter(head[0]), getRotationStateFromLetter(head[1]));
            m_srsData[index].count = count;
            for(int i = 0; i < count; ++i){
               file >> m_srsData[index].points[i].x >> m_srsData[index].points[i].y;
            }
        }
    }else{
        Log::error("Le fichier SRS data n'a pas pu s'ouvrir.");
    }
}

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
    m_rotationCenter = mold.rotationCenter+static_cast<sf::Vector2f>(mold.spawnOffset);
    m_rotState = Initial;
    this->readWallKicks("assets/wallKicksData.txt");
}

bool Piece::tryMove(sf::Vector2i vector, sf::Vector2i gridSize, std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy) {
    if(isValid(getMovedPositions(this->getPositions(), vector), gridSize, gridOccupancy))
    {
        for(int i = 0; i < m_nbBricks; ++i){
            m_bricks[i].moveBrick(vector);
        }
        m_rotationCenter += static_cast<sf::Vector2f>(vector);
        Log::info("Piece déplacée");
        return true;
    }else{
        Log::warn("La pièce n'a pas pu se déplacée");
        return false;
    }
        
}

bool Piece::tryRotate(bool doClockwise, sf::Vector2i gridSize, std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy)
{
    ListVect2i posAfterRot = getRotatedPositions(this->getPositions(), m_rotationCenter, doClockwise);
    
    rotationState nextRotationState = getNextRotationState(m_rotState, doClockwise);
    ListVect2i offsetsToTry = m_srsData[getIndexFromRotationStates(m_rotState, nextRotationState)];
    int countOffsetTry = 0;
    while(countOffsetTry < offsetsToTry.count and not isValid(getMovedPositions(posAfterRot, offsetsToTry.points[countOffsetTry]), gridSize, gridOccupancy))
    {
        Log::info("Offset tried but not valid.");
        std::cout << offsetsToTry.points[countOffsetTry].x <<", "<< offsetsToTry.points[countOffsetTry].y<<std::endl;
        ++countOffsetTry;
    }
    if(countOffsetTry < offsetsToTry.count)
    {
        ListVect2i newPositions = getMovedPositions(posAfterRot, offsetsToTry.points[countOffsetTry]);
        for(int i = 0; i < newPositions.count; ++i){
            m_bricks[i].setGridPos(newPositions.points[i]);
        }
        m_rotationCenter += sf::Vector2f{offsetsToTry.points[countOffsetTry]};
        m_rotState = getNextRotationState(m_rotState, doClockwise);
        Log::info("Piece tournée avec offset");
        std::cout << offsetsToTry.points[countOffsetTry].x <<", "<< offsetsToTry.points[countOffsetTry].y<<std::endl;
        return true;
    }else{
        Log::warn("La pièce n'a pas pu tournée");
        return false;
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