#include "Utils.hpp"

sf::Vector2f getRotatedPoint(sf::Vector2f point, sf::Vector2f center, bool doClockwise){
    sf::Vector2f result;
    sf::Vector2f offsetPt = point-center;
    if(doClockwise)
        result = {-offsetPt.y, offsetPt.x}; // Calcul mathématique pour une rotation de 90° sens horaire
    else
        result = {-offsetPt.y, -offsetPt.x}; // Calcul mathématique pour une rotation de 90° sens anti-horaire
    result += center;
    return result;
}

ListVect2i getRotatedPositions(ListVect2i positions, sf::Vector2f center, bool doClockwise){
    ListVect2i result;
    result.count = positions.count;
    sf::Vector2f brickCenter;
    for(int i = 0; i < positions.count; ++i){
        brickCenter = sf::Vector2f{positions.points[i]} + sf::Vector2f(0.5f, 0.5f);
        result.points[i] = sf::Vector2i{getRotatedPoint(brickCenter, center, doClockwise) - sf::Vector2f(0.5f, 0.5f)};
    }
    return result;
}


ListVect2i getMovedPositions(ListVect2i positions, sf::Vector2i offset){
    ListVect2i result;
    result.count = positions.count;
    for(int i = 0; i < positions.count; ++i){
        result.points[i] = positions.points[i] + offset;
    }
    return result;
}

bool isOutOfBounds(ListVect2i positions, sf::Vector2i gridSize){
    int i = 0;
    while(i < positions.count and positions.points[i].x >= 0 and positions.points[i].x < gridSize.x and positions.points[i].y >= 0 and positions.points[i].y < gridSize.y)
        ++i;
    return i < positions.count;
}

bool isSpaceFree(ListVect2i positions,  std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy){
    int i = 0;
    while(i < positions.count and not gridOccupancy[positions.points[i].x][positions.points[i].y])
        ++i;
    return i == positions.count;
}

bool isValid(ListVect2i positions, sf::Vector2i gridSize, std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy){
    return isSpaceFree(positions, gridOccupancy) and not isOutOfBounds(positions, gridSize);
}