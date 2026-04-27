#include <iostream>
#include <fstream>
#include "Utils.hpp"
#include "Log.hpp"

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
    return not isOutOfBounds(positions, gridSize) and isSpaceFree(positions, gridOccupancy);
}

rotationState getNextRotationState(rotationState actualState, bool doClockwise){
    if(doClockwise)
        return static_cast<rotationState>((static_cast<int>(actualState) + 1) % 4);
    else
        return static_cast<rotationState>((static_cast<int>(actualState) - 1) % 4);
}

int getSrsIndexFromRotationStates(rotationState firstState, rotationState secondState){
    if(firstState == Initial){
        if(secondState == Left)
            return 0;
        else
            return 1;
    }else if(firstState == Right){
        if(secondState == Initial)
            return 2;
        else 
            return 3;
    }else if(firstState == Double){
        if(secondState == Right)
            return 4;
        else
            return 5;
    }else if(firstState == Left){
        if(secondState == Double)
            return 6;
        else
            return 7;
    }else
        return 9;
}

int getSrsIndexFromString(std::string strStates){
    rotationState firstState = getRotationStateFromLetter(strStates[0]);
    rotationState secondState = getRotationStateFromLetter(strStates[1]);
    return getSrsIndexFromRotationStates(firstState, secondState);
}

rotationState getRotationStateFromLetter(char c){
    if(c=='I')
        return Initial;
    else if(c=='R')
        return Right;
    else if(c=='D')
        return Double;
    else if(c=='L')
        return Left;
    else{
        return Right;
    }
}

std::array<ListVect2i, 8> getSrsOffsetsFromFile(std::string fileName){
    std::array<ListVect2i, 8> srsOffsets;
    std::ifstream file;
    file.open(fileName);

    if(file.is_open())
    {
        Log::debug("Fichier SRS data ouvert correctement.");
        Log::debug("Les infos dans le fichier SRS doivent être dans l'ordre : IL - IR - RI - ... - LI. Aucune vérification ne sera faite.");
        
        std::string states; // inutile en fait (ex IR) c'est comme une poubelle
        int count; // nb de offset pour une rotation
        int index = 0; // index de la rotation dans la liste srs
        
        while(file.good())
        {
            file >> states >> count;
            srsOffsets[index].count = count;

            for(int i = 0; i < count; ++i)
            {
               file >> srsOffsets[index].points[i].x >> srsOffsets[index].points[i].y;
            }

            Log::debug("Liste suivante de offsets lu :");
            Log::debug(srsOffsets[index]);
            ++index;
        }
        if(index < 8){
            Log::error("Moins de 8 listes de offsets ont été lues. Seulement : ");Log::error(index);
        }   
        return srsOffsets;
    }else{
        Log::error("Le fichier où se trouves les offsets SRS n'a pas pu s'ouvrir.Nom fichier :");Log::error(fileName);
        return srsOffsets;
    }
}