#include <Game.class.hpp>
#include <Graphic.class.hpp>
#include <TimeManager.class.hpp>
#include <42run.hpp>
#include <Model.class.hpp>
#include <Camera.class.hpp>
#include <TextManager.class.hpp>
#include <TextManager.class.hpp>
#include <glm/glm.hpp>
#include <iostream>

Game::Game(void) {
}

Game::~Game(void) {

    std::list<Section *>::iterator it;
    for (it = this->_sections.begin() ; it != this->_sections.end() ; it ++) {
        delete (*it);
    }
    Graphic::instance().terminate();

    return ;
}

void Game::startGame(void) {

    Graphic & g = Graphic::instance();
    eKey input;

    Shader s;
    s.initialize("shaders/Shader.vertex", "shaders/Shader.fragment");
    //Model m ("models/nanosuit/nanosuit.obj", &s);

    Model m ("models/cluster/cluster.obj", &s);
    //TextManager & tm = TextManager::instance();


    glm::vec3 startPos(0.0f);
    for(int i = 0; i < SECTIONS; i++)
    {
        Section * s = new Section(&m);
        s->setPosition(startPos);
        startPos.z -= 11.35f;
        this->_sections.push_back(s);
    }

    //									 FOV		    Aspect Ratio			   Near / Far Planes
    this->_camera.setPerspective(glm::radians(45.0f), WIDTH / (float)HEIGHT, 0.01f, 100.0f);
    //					        Position	         Yaw	 Pitch
    this->_camera.positionCamera(0, 0, 3,		0,		0);


    while ((input = g.processInput(&this->_camera)) && input != KEYESC) {

        TimeManager::instance().calculateFrameRate(false);

        g.clear();

        switch ( input )
        {
            case KEYUP:
                this->_camera.moveCamera(this->_camera.getSpeed() * TimeManager::instance().deltaTime);
                break;
            case KEYDOWN:
                this->_camera.moveCamera(-1 * this->_camera.getSpeed() * TimeManager::instance().deltaTime);
                break;
            case KEYLEFT:
                this->_camera.strafe(-1 * this->_camera.getSpeed() * TimeManager::instance().deltaTime);
                break;
            case KEYRIGHT:
                this->_camera.strafe(this->_camera.getSpeed() * TimeManager::instance().deltaTime);
                break;
            default:
                break;
        }

        std::list<Section *>::iterator it;
        for (it = this->_sections.begin() ; it != this->_sections.end() ; it ++) {
            (*it)->move();
            (*it)->draw(&this->_camera);
        }

        //tm.print("Hello world", 25.0f, 25.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        g.display();
    }
}
