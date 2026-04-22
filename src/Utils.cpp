#include "Utils.hpp"

std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> getPosAfterMove(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> t_pos, int nb_pos, sf::Vector2i vector){
    std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> result;
    for(int i = 0; i < nb_pos; ++i){
        result[i] = t_pos[i] + vector;
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