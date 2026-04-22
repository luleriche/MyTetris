#pragma once

#include <SFML/Graphics.hpp>

class Brick: public sf::Sprite
{
private:
    sf::Vector2i m_gridPos;

public:
Brick() = default;

/**
* @brief Créer une brique à partir de paramètres donnés.
* @param gridPos tosition initiale sur la grille, @param size taille en pixels, @param texture pointeur vers sa texture, @param color couleur de la brique
* @return sf::Vector2i
*/
Brick(sf::Vector2i gridPos, sf::Vector2f size, const sf::Texture &texture, sf::Color color);

/**
* @brief Déplace la brique selon un décalage donné.
* @param offset Le vecteur de déplacement (ex: {1, 0} pour la droite).
* @return void
*/
void moveBrick(sf::Vector2i offset);

/**
* @brief Retourne la position de la brique sur la grille.
* @return sf::Vector2i
*/
sf::Vector2i getGridPos();
};