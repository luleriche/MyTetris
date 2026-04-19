#ifndef PIECE_HPP
#define PIECE_HPP
#endif

#include <SFML/Graphics.hpp>
#include <Piece.hpp>
#include <Grid.hpp>

class Game{

private:
    Grid m_grid;
    Piece m_piece;
public:
    sf::Vector2f m_size, m_pos;

    Game(sf::Vector2f pos, sf::Vector2f size);

    void game_loop();
};