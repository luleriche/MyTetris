#include <SFML/Graphics.hpp>
#include <string>

#include "Game.hpp"

int main()
{
    Game my_game(sf::Vector2f(0, 0), sf::Vector2f(500, 900));
    my_game.game_loop();
    return 0;
}