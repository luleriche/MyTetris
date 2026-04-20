#pragma once

#include <SFML/Graphics.hpp>
#include <Piece.hpp>
#include <Grid.hpp>

class Game
{
private:
    sf::Texture m_brickTexture;
    Grid m_grid;
    Piece m_piece;

public:
    Game(sf::Vector2f gridSize);

    void game_loop();
};