#ifndef PLAYER_CLASS_HPP
#define PLAYER_CLASS_HPP

#include <Model.class.hpp>
#include <glm/glm.hpp>

class Player {
public:
    Player(Model * m);
    ~Player(void);

private:
    Model       *_m;
    glm::vec3   _position;
    glm::vec3   _scale;
    glm::vec3   _rotation;
};

#endif //PLAYER_CLASS_HPP
