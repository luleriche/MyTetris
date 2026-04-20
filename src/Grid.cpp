#include "Grid.hpp"

Grid::Grid(sf::Vector2f totalSize, int nb_col, int nb_row) 
    : m_totalSize(totalSize), m_gridSize(nb_col, nb_row)
{
    m_bgColor = sf::Color(10, 10, 10);
    m_lineColor = sf::Color(40, 40, 40);
    m_lineWidth = 2;
    m_tileSize = sf::Vector2f(m_totalSize.x / m_gridSize.x, m_totalSize.y / m_gridSize.y);
}

void Grid::draw(sf::RenderWindow& window) {
    sf::RectangleShape bg(m_totalSize);
    bg.setFillColor(m_bgColor);
    window.draw(bg);
    for (int i = 0; i < m_gridSize.x + 1; ++i) {
        sf::RectangleShape line(sf::Vector2f(m_lineWidth, m_totalSize.y));
        line.setPosition(sf::Vector2f(i * m_tileSize.x - m_lineWidth / 2, 0));
        line.setFillColor(m_lineColor);
        window.draw(line);
    }
    for (int i = 0; i < m_gridSize.y + 1; ++i) {
        sf::RectangleShape line(sf::Vector2f(m_totalSize.x, m_lineWidth));
        line.setPosition(sf::Vector2f(0, i * m_tileSize.y - m_lineWidth / 2));
        line.setFillColor(m_lineColor);
        window.draw(line);
    }
}

sf::Vector2f Grid::get_tileSize() {
    return m_tileSize;
};