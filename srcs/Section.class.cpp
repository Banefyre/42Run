#include <Section.class.hpp>
#include <TimeManager.class.hpp>
#include <map>
#include <iostream>

Section::Section(Model *model, eSection type, Model * obstacle) : _m(model), _obstacle(obstacle), _type(type), _scale(1.0f), _rotation(0.0f)
{
    typedef void (Section::*INIT)(void);
    static std::map<eSection, INIT> map = {
            { NABOO, &Section::_initNaboo },
            { DRAGON, &Section::_initDragon },
            { KRABBS, &Section::_initKrabbs },
            { SONIC, &Section::_initSonic }
    };

    INIT ft = map[type];
    (this->*ft)();

    return;
}

Section::~Section(void)
{
    return;
}

void Section::setPosition(glm::vec3 pos)
{
    this->_position = pos;

    typedef void (Section::*POS)(glm::vec3);
    static std::map<eSection, POS> map = {
            { NABOO, &Section::_posNaboo },
            { DRAGON, &Section::_posDragon },
            { KRABBS, &Section::_posKrabbs },
            { SONIC, &Section::_posSonic }
    };

    POS ft = map[_type];
    (this->*ft)(pos);

}

glm::vec3 & Section::getPosition(void)
{
    return this->_position;
}

glm::vec3 & Section::getOPosition(void)
{
    return this->_oPosition;
}

void Section::move(void)
{
    this->_position.z += (11.35f * TimeManager::instance().deltaTime) / 2.5f;
    this->_oPosition.z += (11.35f * TimeManager::instance().deltaTime) / 2.5f;
}

void Section::draw(Camera *camera)
{
    this->_m->draw(camera, this->_position, this->_scale, this->_rotation);
    this->_obstacle->draw(camera, this->_oPosition, this->_oScale, this->_oRotation);
}

void Section::_initNaboo(void) {
    this->_oScale = glm::vec3(0.4f);
    this->_oRotation = glm::vec3(0.0f, glm::radians(85.0f), 0.0f);
}

void Section::_initKrabbs(void) {
    this->_oScale = glm::vec3(0.5f);
    this->_oRotation = glm::vec3(0.0f);
}

void Section::_initDragon(void) {
    this->_oScale = glm::vec3(1.0f);
    this->_oRotation = glm::vec3(0.0f);
}

void Section::_initSonic(void) {
    this->_oScale = glm::vec3(0.5f);
    this->_oRotation = glm::vec3(0.0f);
}

void Section::_posDragon(glm::vec3 pos) {

    this->_oPosition = pos;
    //this->_oPosition.x -= 1.0f;

}

void Section::_posNaboo(glm::vec3 pos) {

    this->_oPosition = pos;
    this->_oPosition.y -= 0.45f;
}

void Section::_posKrabbs(glm::vec3 pos) {

    this->_oPosition = pos;
    this->_oPosition.y -= 0.55f;
    this->_oPosition.x -= 0.5f;

}

void Section::_posSonic(glm::vec3 pos) {

    this->_oPosition = pos;
    this->_oPosition.y -= 0.55f;

}
