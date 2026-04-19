#include <SFML/Graphics.hpp>
#include <string>
#include "Piece.hpp"
#include "Grid.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 900), "My Tetris");

    Grid my_grid(sf::Vector2f(500.f, 900.f), 10, 18);
    Piece my_piece(sf::Vector2i(0, 0), my_grid.get_bricks_size(), sf::Color::Red, "xxo/oxx");
    sf::Texture brick_texture;
    brick_texture.loadFromFile("assets/WhiteSquare.jpg");
    my_piece.set_texture(brick_texture);
    my_piece.create_sprites();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Left) {
                    my_piece.move(sf::Vector2i(-1, 0));
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Right) {
                    my_piece.move(sf::Vector2i(1, 0));
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Up) {
                    my_piece.move(sf::Vector2i(0, -1));
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Down) {
                    my_piece.move(sf::Vector2i(0, 1));
                }
            }
        }

        window.clear();
        my_grid.draw(window);
        my_piece.draw(window);
        window.display();
    }
}