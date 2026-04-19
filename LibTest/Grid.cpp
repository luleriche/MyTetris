#include "Grid.hpp"

Grid::Grid(sf::Vector2f size, int nb_col, int nb_row) {
    this->size = size;
    this->bg_color = sf::Color(10, 10, 10);
    this->l_color = sf::Color(40, 40, 40);
    this->l_width = 2;
    this->nb_col = nb_col;
    this->nb_row = nb_row;
    this->bricks_size = sf::Vector2f(size.x / nb_col, size.y / nb_row);
}

void Grid::draw(sf::RenderWindow& window) {
    sf::RectangleShape bg(this->size);
    bg.setFillColor(this->bg_color);
    window.draw(bg);
    for (int i = 0; i < this->nb_col + 1; ++i) {
        sf::RectangleShape line(sf::Vector2f(this->l_width, this->size.y));
        line.setPosition(sf::Vector2f(i * this->bricks_size.x - this->l_width / 2, 0));
        line.setFillColor(this->l_color);
        window.draw(line);
    }
    for (int i = 0; i < this->nb_row + 1; ++i) {
        sf::RectangleShape line(sf::Vector2f(this->size.x, this->l_width));
        line.setPosition(sf::Vector2f(0, i * this->bricks_size.y - this->l_width / 2));
        line.setFillColor(this->l_color);
        window.draw(line);
    }
}

sf::Vector2f Grid::get_bricks_size() {
    return this->bricks_size;
};