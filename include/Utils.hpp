#pragma once

#include <array>
#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

struct ListVect2i{
    std::array<sf::Vector2i, 32> points;
    int count;
};

using ArrayVect2i = std::array<sf::Vector2i, 10>;
using ArrayVect2f = std::array<sf::Vector2f, 10>;

const sf::Color CYAN(0, 255, 255);
const sf::Color YELLOW(255, 255, 0);
const sf::Color PURPLE(255, 0, 255);
const sf::Color ORANGE(255, 127, 0);
const sf::Color BLUE(0, 0, 255);
const sf::Color RED(255, 0, 0);
const sf::Color GREEN(0, 255, 0);

const int NB_MAX_PIECE_BRICK = 9;
const int NMAX_WALL_KICKS = 6;
const int nbMaxCol = 40, nbMaxRow = 50;

enum rotationState{
    Initial = 0, Right = 1, Double = 2, Left = 3
};

struct wallKick{
    rotationState actaualState, desiredState;
    std::array<sf::Vector2i, NMAX_WALL_KICKS> offsets;
    int sizeOffsets;
};

struct PieceMold{
    std::string pattern;
    sf::Color color;
    sf::Vector2i spawnOffset;
    sf::Vector2f rotationCenter;
};

const PieceMold Imold = {"xxxx", CYAN, {2, 2}, sf::Vector2f(2, 0)};
const PieceMold Omold = {"xx/xx", YELLOW, {2, 2}, sf::Vector2f(1, 1)};
const PieceMold Zmold = {"xxo/oxx", RED, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};
const PieceMold Smold = {"oxx/xxo", GREEN, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};
const PieceMold Jmold = {"xoo/xxx", BLUE, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};
const PieceMold Lmold = {"xxx/xoo", ORANGE, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};
const PieceMold Tmold = {"oxo/xxx", PURPLE, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};

const std::array<PieceMold, 7> basisMolds = {Imold, Omold, Jmold, Lmold, Tmold, Zmold, Smold};

/**
* @brief Renvoie l'image d'un point après une rotation de 90°
* @param point point de départ de la rotation, @param center point central de la rotation, @param doClockwise si on effectue la rotation dans le sens horaire ou non
* @return sf::Vector2f
*/
sf::Vector2f getRotatedPoint(sf::Vector2f point, sf::Vector2f center, bool doClockwise);
ListVect2i getRotatedPositions(ListVect2i positions, sf::Vector2f center, bool doClockwise);

ListVect2i getMovedPositions(ListVect2i positions, sf::Vector2i offset);

bool isOutOfBounds(ListVect2i positions, sf::Vector2i gridSize);

bool isSpaceFree(ListVect2i positions,  std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy);

bool isValid(ListVect2i positions, sf::Vector2i gridSize, std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy);