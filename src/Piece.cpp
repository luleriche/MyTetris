#include "Piece.hpp"

Piece::Piece(sf::Vector2i init_pos, sf::Vector2f init_size, sf::Color color, std::string pattern) {
    set_shape(pattern);
    set_position(init_pos);
    set_color(color);
    this->size = init_size;
}

void Piece::set_shape(std::string pattern) {
    int x = 0;
    int y = 0;
    nb_bricks = 0;
    for (unsigned int i = 0; i < pattern.length(); ++i) {
        if (pattern[i] == 'x') {
            shape[nb_bricks] = sf::Vector2f(x, y);
            ++nb_bricks;
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
}

void Piece::create_sprites(){
    this->brick_sprites = new sf::Sprite[nb_bricks];
    for(int i = 0; i < this->nb_bricks; ++i){
        brick_sprites[i].setTexture(this->brick_texture);
        brick_sprites[i].setPosition(sf::Vector2f((this->position.x + shape[i].x) * this->size.x, 
                                                  (this->position.y + shape[i].y) * this->size.y));
        
        brick_sprites[i].setScale(sf::Vector2f(this->size.x / 480, this->size.y /480));
        brick_sprites[i].setColor(this->color);
    }
}

void Piece::set_position(sf::Vector2i new_position) {
    position = new_position;
}

void Piece::set_color(sf::Color new_color) {
    color = new_color;
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

void Piece::set_texture(sf::Texture texture){
    this->brick_texture = texture;
}