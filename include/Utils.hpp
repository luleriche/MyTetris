#pragma once

#include <array>
#include <string>
#include <SFML/Graphics.hpp>

const sf::Color CYAN(0, 255, 255);
const sf::Color YELLOW(255, 255, 0);
const sf::Color PURPLE(255, 0, 255);
const sf::Color ORANGE(255, 127, 0);
const sf::Color BLUE(0, 0, 255);
const sf::Color RED(255, 0, 0);
const sf::Color GREEN(0, 255, 0);

struct PieceMold{
    std::string pattern;
    sf::Color color;
    sf::Vector2i spawnOffset;
    sf::Vector2f rotationCenter;
};

const PieceMold I = {"xxxx", CYAN, sf::Vector2i(2, 2), sf::Vector2f(2, 0)};
const PieceMold O = {"xx/xx", YELLOW, sf::Vector2i(2, 2), sf::Vector2f(1, 1)};
const PieceMold Z = {"xxo/oxx", RED, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};
const PieceMold S = {"oxx/xxo", GREEN, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};
const PieceMold J = {"xoo/xxx", BLUE, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};
const PieceMold L = {"xxx/xoo", ORANGE, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};
const PieceMold T = {"oxo/xxx", PURPLE, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};

const std::array<PieceMold, 7> basisMolds = {I, O, J, L, T, Z, S};

const int NB_MAX_PIECE_BRICK = 9;
const int nbMaxCol = 40, nbMaxRow = 50;

sf::Vector2f getRotatedPt(sf::Vector2f point, sf::Vector2f center, bool doClockwise);

std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> getPosAfterMove(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> pos, int nb_pos, sf::Vector2i vector);

std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> getPosAfterRotate(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> pos, int nb_pos, sf::Vector2f rotationCenter);

bool isOutOfBounds(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> t_pos, int nb_pos, sf::Vector2i grid_size);

bool isSpaceFree(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> t_pos, int nb_pos,  std::array<std::array<bool, nbMaxRow>, nbMaxCol> grid_occupancy);

bool isValid(std::array<sf::Vector2i, NB_MAX_PIECE_BRICK> t_pos, int nb_pos, sf::Vector2i grid_size, std::array<std::array<bool, nbMaxRow>, nbMaxCol> grid_occupancy);