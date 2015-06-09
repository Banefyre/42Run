#include <Game.class.hpp>
#include <Graphic.class.hpp>
#include <TimeManager.class.hpp>
#include <42run.hpp>

Game::Game(void) {
    this->_gameLoop();
}

Game::~Game(void) {
    return ;
}

void Game::_gameLoop(void) {


    Graphic & g = Graphic::instance();
    eKey input;

    while ((input = g.processInput()) && input != ESC) {

        TimeManager::instance().calculateFrameRate(false);

        g.clear();
        g.display();
    }

}
