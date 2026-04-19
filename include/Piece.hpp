#ifndef PIECE_HPP
#define PIECE_HPP
#endif

#include <SFML/Graphics.hpp>
#include <array>

const int NMax = 50;
using tab_vec2f = std::array<sf::Vector2f, NMax>;

class Piece {

public:
    tab_vec2f shape;
    int nb_bricks;
    sf::Sprite* brick_sprites;
    sf::Texture brick_texture;
    sf::Color color;
    sf::Vector2f size;

    Piece() = default;

    Piece(sf::Color color, std::string pattern, sf::Vector2f brick_sizes, sf::Texture brick_texture);

    void create_sprites();

    void move(sf::Vector2i vector);

    void draw(sf::RenderWindow& window);

};
