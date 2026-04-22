#pragma once

#include <array>
#include <SFML/Graphics.hpp>

const int NB_MAX_PIECE_BRICK = 9;

std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> getPosAfterMove(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> pos, int nb_pos, sf::Vector2i vector);

bool isOutOfBounds(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> t_pos, int nb_pos, sf::Vector2i grid_size);