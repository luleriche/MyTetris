#include <Game.hpp>
#include <iostream>

Game::Game(sf::Vector2f gridSize) : m_grid(gridSize, 10, 18){
    if(!m_brickTexture.loadFromFile("assets/WhiteSquare.jpg"))
        std::cout << "Erreur au chargement de la texture !";
    m_piece = Piece("oxo/xxx", sf::Color::Green, sf::Vector2f(50, 50), m_brickTexture);
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
                else if (event.key.scancode == sf::Keyboard::Scan::Space){
                    m_grid.addPieceToBricks(m_piece);
                }
            }
        }
        m_grid.draw(window);
        m_piece.draw(window);
        window.display();
    }
}