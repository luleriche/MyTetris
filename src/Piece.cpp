#include <fstream>
#include "Piece.hpp"
#include "Log.hpp"

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
    m_srsOffsets = mold.srsOffsets;
}


bool Piece::tryMove(sf::Vector2i vector, sf::Vector2i gridSize, std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy) {
    if(isValid(getMovedPositions(this->getPositions(), vector), gridSize, gridOccupancy))
    {
        for(int i = 0; i < m_nbBricks; ++i){
            m_bricks[i].moveBrick(vector);
        }
        m_rotationCenter += static_cast<sf::Vector2f>(vector);
        Log::debug("Piece déplacée. Vecteur de déplacement : ");Log::debug(vector);
        return true;
    }else{
        Log::debug("Le déplacement est impossible. Vecteur de déplacement : ");Log::debug(vector);
        return false;
    }
        
}

bool Piece::tryRotate(bool doClockwise, sf::Vector2i gridSize, std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy)
{
    // Positions après une simple rotation, sans appliquer aucuns offsets
    ListVect2i positionsAfterRotation = getRotatedPositions(this->getPositions(), m_rotationCenter, doClockwise);
    rotationState nextRotationState = getNextRotationState(m_rotState, doClockwise);

    // Liste des offsets a tenté selon les données SRS
    ListVect2i offsetsToTry = m_srsOffsets[getSrsIndexFromRotationStates(m_rotState, nextRotationState)];
    
    // Calcul des positions après application du premier offset, souvent (0, 0)
    int countOffsetTry = 0;
    
    // Tant qu'on a pas testé tous les offsets et que le dernier n'est pas valide
    while(countOffsetTry < offsetsToTry.count and not isValid(getMovedPositions(positionsAfterRotation, offsetsToTry.points[countOffsetTry]), gridSize, gridOccupancy))
    {
        Log::debug("Offset tenté et non valide : ");Log::debug(offsetsToTry.points[countOffsetTry]);
        ++countOffsetTry;
    }
    
    // Si on les a pas tous essayé alors l'actuel est valide
    if(countOffsetTry < offsetsToTry.count)
    {
        // Changement de la position des briques
        ListVect2i newPositions = getMovedPositions(positionsAfterRotation, offsetsToTry.points[countOffsetTry]);
        for(int i = 0; i < newPositions.count; ++i){
            m_bricks[i].setGridPos(newPositions.points[i]);
        }
        // Décalage également du centre de rotation selon l'offset utilisé
        m_rotationCenter += sf::Vector2f{offsetsToTry.points[countOffsetTry]};
        m_rotState = nextRotationState;

        Log::debug("Piece tournée avec offset : ");Log::debug(offsetsToTry.points[countOffsetTry]);

        return true;
    }else{
        Log::warn("La pièce n'a pas pu tournée, tous les offsets ont été tentés.");
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

void Piece::setSrsOffsets(std::array<ListVect2i, 8> srsOffsets){
    m_srsOffsets = srsOffsets;
}