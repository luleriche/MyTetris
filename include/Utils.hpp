#pragma once

#include <array>
#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

const sf::Color CYAN(0, 255, 255);
const sf::Color YELLOW(255, 255, 0);
const sf::Color PURPLE(255, 0, 255);
const sf::Color ORANGE(255, 127, 0);
const sf::Color BLUE(0, 0, 255);
const sf::Color RED(255, 0, 0);
const sf::Color GREEN(0, 255, 0);

const int NB_MAX_PIECE_BRICK = 9;
const int nbMaxCol = 40, nbMaxRow = 50;

struct ListVect2i{
    std::array<sf::Vector2i, 32> points;
    int count;
};

inline std::ostream& operator<<(std::ostream& os, const ListVect2i& l) {
    os << "Size : " << l.count << std::endl;
    for(int i = 0; i < l.count; ++i){
        os <<  "(" << l.points[i].x << " " << l.points[i].y << ")";
        if(i != l.count)
            os << ", ";
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sf::Vector2i& v) {
    os << "("<< v.x <<" " << v.y << ")";
    return os;
}

enum rotationState{
    Initial = 0, Right, Double, Left
};

struct PieceMold{
    std::string pattern;
    sf::Color color;
    sf::Vector2i spawnOffset;
    sf::Vector2f rotationCenter;
    ListVect2i wallKicks;
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
* @param point Point de départ de la rotation, @param center Point central de la rotation, @param doClockwise Si on effectue la rotation dans le sens horaire ou non
* @return sf::Vector2f
*/
sf::Vector2f getRotatedPoint(sf::Vector2f point, sf::Vector2f center, bool doClockwise);

/**
* @brief Renvoie l'image d'un ensemble de points après une rotation de 90°
* @param positions Points de départ, @param center Point central de la rotation, @param doClockwise Si on effectue la rotation dans le sens horaire ou non
* @return ListVect2i contenant les points après rotation, l'ordre de ceux-ci est inchangé.
*/
ListVect2i getRotatedPositions(ListVect2i positions, sf::Vector2f center, bool doClockwise);

/**
* @brief Renvoie l'image d'un ensemble de points une translation
* @param positions Points de départ, @param offset Vecteur de translation
* @return ListVect2i contenant les points après translation, l'ordre de ceux-ci est inchangé.
*/
ListVect2i getMovedPositions(ListVect2i positions, sf::Vector2i offset);

bool isOutOfBounds(ListVect2i positions, sf::Vector2i gridSize);

bool isSpaceFree(ListVect2i positions,  std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy);

bool isValid(ListVect2i positions, sf::Vector2i gridSize, std::array<std::array<bool, nbMaxRow>, nbMaxCol> gridOccupancy);

rotationState getNextRotationState(rotationState actualState, bool wasClockwise);

rotationState getRotationStateFromLetter(char c);

int getSrsIndexFromRotationStates(rotationState firstState, rotationState secondState);

int getSrsIndexFromString(std::string strStates);

void print(ListVect2i l);