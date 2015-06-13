#ifndef SECTION_CLASS_HPP
# define SECTION_CLASS_HPP

#include <Model.class.hpp>
#include <glm/glm.hpp>
#include <42run.hpp>
#include <list>

class Section
{
    public:
        Section(Model *m, eSection type, Model * obstacle, Model * apple);
        ~Section(void);
        void setPosition(glm::vec3 pos);
        glm::vec3 & getPosition(void);
        glm::vec3 & getOPosition(void);
        void move(void);
        void draw(Camera *camera);
        bool collide(Model &player);

        bool takeApple(glm::vec3 & playerPos);

    private:
        Model       *_m;
        Model       *_obstacle;
        Model       *_apple;
        eSection    _type;
        glm::vec3   _position;
        glm::vec3   _scale;
        glm::vec3   _rotation;
        glm::vec3   _oPosition;
        glm::vec3   _oScale;
        glm::vec3   _oRotation;

        glm::vec3   _appleRot;
        glm::vec3   _appleScale;
        std::list<glm::vec3> _applesPos;


        void    _initNaboo(void);
        void    _initKrabbs(void);
        void    _initDragon(void);
        void    _initSonic(void);


        void    _posNaboo(glm::vec3 pos);
        void    _posKrabbs(glm::vec3 pos);
        void    _posDragon(glm::vec3 pos);
        void    _posSonic(glm::vec3 pos);

        bool    _posNaboo(Model &p);
        bool    _posKrabbs(Model &p);
        bool    _posDragon(Model &p);
        bool    _posSonic(Model &p);

};

#endif