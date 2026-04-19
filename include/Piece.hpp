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
    sf::Vector2i position;
    sf::Vector2f size;
    
    Piece(sf::Vector2i init_pos, sf::Vector2f init_size, sf::Color color, std::string pattern);

    void set_shape(std::string pattern);

    void create_sprites();

    void set_position(sf::Vector2i new_position);

    void set_color(sf::Color new_color);

    void move(sf::Vector2i vector);

    void draw(sf::RenderWindow& window);

    void set_texture(sf::Texture texture);

};
