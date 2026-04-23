#include "Utils.hpp"

sf::Vector2f getRotatedPt(sf::Vector2f point, sf::Vector2f center, bool doClockwise){
    sf::Vector2f result;
    sf::Vector2f offsetPt = point-center;
    std::array<sf::Vector2f, 2> rotationMatrix = {sf::Vector2f(0, -1), sf::Vector2f(1, 0)};
    result.x = rotationMatrix[0].x*offsetPt.x + rotationMatrix[1].x*offsetPt.y;
    result.y = rotationMatrix[0].y*offsetPt.x + rotationMatrix[1].y*offsetPt.y;
    result += center;
    return result;
}

std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> getPosAfterMove(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> t_pos, int nb_pos, sf::Vector2i vector){
    std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> result;
    for(int i = 0; i < nb_pos; ++i){
        result[i] = t_pos[i] + vector;
    }
    return result;
}

std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> getPosAfterRotate(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> t_pos, int nb_pos, sf::Vector2f rotationCenter){
    std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> result;
    std::array<sf::Vector2f, NB_MAX_PIECE_BRICK> resultCenter;
    std::array<sf::Vector2f, NB_MAX_PIECE_BRICK> centerOfBricks;
    for(int i = 0; i < nb_pos; ++i){
        centerOfBricks[i] = static_cast<sf::Vector2f>(t_pos[i]) + sf::Vector2f(0.5, 0.5);
    }
    for(int i = 0; i < nb_pos; ++i){
        resultCenter[i] = getRotatedPt(centerOfBricks[i], rotationCenter, true);
    }
    for(int i = 0; i < nb_pos; ++i){
        result[i] = static_cast<sf::Vector2i>(resultCenter[i] - sf::Vector2f(0.5, 0.5));
    }
    return result;
}



bool isOutOfBounds(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> t_pos, int nb_pos, sf::Vector2i grid_size){
    int i = 0;
    while(i < nb_pos and t_pos[i].x >= 0 and t_pos[i].x < grid_size.x and t_pos[i].y >= 0 and t_pos[i].y < grid_size.y)
        ++i;
    return i < nb_pos;
}

bool isSpaceFree(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> t_pos, int nb_pos,  std::array<std::array<bool, nbMaxRow>, nbMaxCol> grid_occupancy){
    int i = 0;
    while(i < nb_pos and not grid_occupancy[t_pos[i].x][t_pos[i].y])
        ++i;
    return i == nb_pos;
}

bool isValid(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> t_pos, int nb_pos, sf::Vector2i grid_size, std::array<std::array<bool, nbMaxRow>, nbMaxCol> grid_occupancy){
    return not isOutOfBounds(t_pos, nb_pos, grid_size) and isSpaceFree(t_pos, nb_pos, grid_occupancy);
}