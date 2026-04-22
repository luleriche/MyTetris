#pragma once

#include <SFML/Graphics.hpp>
#include <Piece.hpp>
#include <Grid.hpp>

class Game
{
private:
    // Texture de brick utilisée par le jeu
    sf::Texture m_brickTexture;

    // Différents éléments enfants au jeu
    Grid m_grid;
    Piece m_piece;

public:
    // Constructeur
    Game(sf::Vector2f gridSize);

    // Boucle qui créee une fenetre et fait fonctionner le jeu
    void game_loop();
};