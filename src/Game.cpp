#include <Game.hpp>
#include <iostream>
#include "Utils.hpp"
#include <ctime>
#include <cstdlib>

Game::Game(sf::Vector2f gridSize) : m_grid(gridSize, 10, 18){
    srand(time(nullptr));
    if(!m_brickTexture.loadFromFile("assets/WhiteSquare.jpg"))
        std::cout << "Erreur au chargement de la texture !";
    m_piece = Piece(basisMolds[0], sf::Vector2f(35, 35), m_brickTexture);
    lastForceDownClock.restart();
}

void Game::game_loop(){
    sf::RenderWindow window(sf::VideoMode(350, 630), "My Tetris");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::Left) {
                    m_piece.tryMove(sf::Vector2i(-1, 0), m_grid.getGridSize(), m_grid.getGridOccupancy());
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Right) {
                    m_piece.tryMove(sf::Vector2i(1, 0), m_grid.getGridSize(), m_grid.getGridOccupancy());
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Up) {
                    m_piece.tryMove(sf::Vector2i(0, -1), m_grid.getGridSize(), m_grid.getGridOccupancy());
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Down) {
                    m_piece.tryMove(sf::Vector2i(0, 1), m_grid.getGridSize(), m_grid.getGridOccupancy());
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Space) {
                    m_piece.tryRotate(1, m_grid.getGridSize(), m_grid.getGridOccupancy());
                }
            }
        }
        if(lastForceDownClock.getElapsedTime().asMilliseconds() > 700){
            lastForceDownClock.restart();
            if(not m_piece.tryMove(sf::Vector2i(0, 1), m_grid.getGridSize(), m_grid.getGridOccupancy())){
                m_grid.addPieceToBricks(m_piece);
                m_piece = Piece(basisMolds[rand()%7], sf::Vector2f(35, 35), m_brickTexture);
            };
        }
        m_grid.draw(window);
        m_piece.draw(window);
        window.display();
    }
}