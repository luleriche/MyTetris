#include <Game.hpp>

Game::Game(sf::Vector2f pos, sf::Vector2f size) : m_grid(size, 10, 18), m_size(size), m_pos(pos){
    sf::Texture brick_texture;
    brick_texture.loadFromFile("assets/WhiteSquare.jpg");
    m_piece = Piece(sf::Color::Green, "oxo/xxx", sf::Vector2f(50, 50), brick_texture);
    m_piece.create_sprites();
}

void Game::game_loop(){
    sf::RenderWindow window(sf::VideoMode(500, 900), "My Tetris");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Left) {
                    m_piece.move(sf::Vector2i(-1, 0));
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Right) {
                    m_piece.move(sf::Vector2i(1, 0));
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Up) {
                    m_piece.move(sf::Vector2i(0, -1));
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Down) {
                    m_piece.move(sf::Vector2i(0, 1));
                }
            }
        }
        m_grid.draw(window);
        m_piece.draw(window);
        window.display();
    }
}