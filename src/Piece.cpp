#include "Piece.hpp"

Piece::Piece(sf::Color color, std::string pattern, sf::Vector2f brick_sizes, sf::Texture brick_texture) {
    int x = 0;
    int y = 0;
    this->nb_bricks = 0;
    for (unsigned int i = 0; i < pattern.length(); ++i) {
        if (pattern[i] == 'x') {
            shape[nb_bricks] = sf::Vector2f(3+x, 1+y);
            ++this->nb_bricks;
            ++x;
        }
        else if (pattern[i] == '/') {
            ++y;
            x = 0;
        }
        else {
            ++x;
        }
    }
    this->color = color;
    this->size = brick_sizes;
    this->brick_texture = brick_texture;
}

void Piece::create_sprites(){
    this->brick_sprites = new sf::Sprite[nb_bricks];
    for(int i = 0; i < this->nb_bricks; ++i){
        brick_sprites[i].setTexture(this->brick_texture);
        brick_sprites[i].setPosition(sf::Vector2f(shape[i].x * this->size.x, shape[i].y * this->size.y));
        
        brick_sprites[i].setScale(sf::Vector2f(this->size.x / 480, this->size.y /480));
        brick_sprites[i].setColor(this->color);
    }
}


void Piece::move(sf::Vector2i vector) {
    for(int i = 0; i < this->nb_bricks; ++i){
        brick_sprites[i].move(sf::Vector2f(vector.x*this->size.x, vector.y*this->size.y));
    }
}

void Piece::draw(sf::RenderWindow& window) {
    for (int i = 0; i < nb_bricks; ++i) {
        window.draw(this->brick_sprites[i]);
    }
}