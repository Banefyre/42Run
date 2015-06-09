#ifndef _42RUN_GAME_CLASS_HPP_
#define _42RUN_GAME_CLASS_HPP_

#include <Camera.class.hpp>

class Game {

public:
    Game(void);
    ~Game(void);


private:
    void _gameLoop(void);
    Camera      _camera;

};

#endif //42RUN_GAME_CLASS_HPP
