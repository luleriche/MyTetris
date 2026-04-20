#ifndef PIECE_HPP
#define PIECE_HPP
#endif

#include <SFML/Graphics.hpp>
#include <array>

const int NMax = 9;
using tab_vec2f = std::array<sf::Vector2f, NMax>;

class Piece
{
private:
    int m_nbBricks;
    std::array<sf::Sprite, NMax> m_bricks;
    sf::Texture m_bricksTexture;
    sf::Color m_bricksColor;
    sf::Vector2f m_bricksSize;
public:
    
    Piece() = default;

    Piece(std::string pattern, sf::Color color, sf::Vector2f brick_sizes, sf::Texture brick_texture);

    void move(sf::Vector2i vector);

    void draw(sf::RenderWindow& window);

};
