#ifndef SECTION_CLASS_HPP
# define SECTION_CLASS_HPP

#include <Model.class.hpp>
#include <glm/glm.hpp>

class Section
{
    public:
        Section(Model *m);
        ~Section(void);
        void setPosition(glm::vec3 pos);
        glm::vec3 getPosition(void);
        void move(void);
        void draw(Camera *camera);

    private:
        Model       *_m;
        glm::vec3   _position;
        glm::vec3   _scale;
        glm::vec3   _rotation;

};

#endif