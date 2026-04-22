#include <SFML/Graphics.hpp>
#include <string>

#include "Game.hpp"

int main()
{
    Game my_game(sf::Vector2f(350, 630));
    my_game.game_loop();
    return 0;
}