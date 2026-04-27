#pragma once

#include <SFML/Graphics.hpp>
#include <Piece.hpp>
#include <Grid.hpp>
#include "Utils.hpp"

class Game
{
private:
    // Texture de brick utilisée par le jeu
    sf::Texture m_brickTexture;

    // Différents éléments enfants au jeu
    Grid m_grid;
    Piece m_piece;
    sf::Clock lastForceDownClock;

    PieceMold Imold = {"xxxx", CYAN, {2, 2}, sf::Vector2f(2, 0)};
    PieceMold Omold = {"xx/xx", YELLOW, {2, 2}, sf::Vector2f(1, 1)};
    PieceMold Zmold = {"xxo/oxx", RED, {2, 2}, sf::Vector2f(1.5, 1.5)};
    PieceMold Smold = {"oxx/xxo", GREEN, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};
    PieceMold Jmold = {"xoo/xxx", BLUE, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};
    PieceMold Lmold = {"xxx/xoo", ORANGE, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};
    PieceMold Tmold = {"oxo/xxx", PURPLE, sf::Vector2i(2, 2), sf::Vector2f(1.5, 1.5)};

    std::array<PieceMold, 7> basisMolds = {Imold, Omold, Jmold, Lmold, Tmold, Zmold, Smold};
    
public:
    // Constructeur
    Game(sf::Vector2f gridSize);

    // Boucle qui créee une fenetre et fait fonctionner le jeu
    void game_loop();
};