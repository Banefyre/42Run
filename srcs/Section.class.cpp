#include <Section.class.hpp>
#include <TimeManager.class.hpp>

Section::Section(Model *model) : _m(model), _scale(1.0f), _rotation(0.0f)
{

    return;
}

Section::~Section(void)
{
    return;
}

void Section::setPosition(glm::vec3 pos)
{
    this->_position = pos;
}

void Section::move(void)
{
    this->_position.z += (11.35f * TimeManager::instance().deltaTime) / 5.0f;
}

void Section::draw(Camera *camera)
{
    this->_m->draw(camera, this->_position, this->_scale, this->_rotation);
}