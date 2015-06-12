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
#include <Player.class.hpp>

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

    TextManager & tm = TextManager::instance();
    tm.print("Loading Models, Textures and Shaders...", 245.0f, 340.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    g.display();

    Shader s;
    s.initialize("shaders/Shader.vertex", "shaders/Shader.fragment");
    Model playerModel ("models/nanosuit/nanosuit.obj", &s);
    Model m ("models/cluster/cluster.obj", &s);


    Player player(&playerModel);

    glm::vec3 startPos(0.0f);
    for(int i = 0; i < SECTIONS; i++)
    {
        Section * s = new Section(&m);
        s->setPosition(startPos);
        startPos.z -= SECTIONSIZE;
        this->_sections.push_back(s);
    }


    double distance = 0;

    //									 FOV		    Aspect Ratio			   Near / Far Planes
    this->_camera.setPerspective(glm::radians(45.0f), WIDTH / (float)HEIGHT, 0.01f, 100.0f);
    //					        Position	         Yaw	 Pitch
    this->_camera.positionCamera(0, 0.9f, 3.0f,		0.0f,		0.2f);


    while (g.processInput(&this->_camera, &player)) {

        TimeManager::instance().calculateFrameRate(false);

        g.clear();

        std::list<Section *>::iterator it;
        for (it = this->_sections.begin() ; it != this->_sections.end() ; ++it) {
            (*it)->move();
            (*it)->draw(&this->_camera);
        }

        player.draw(&this->_camera);

        if (this->_sections.front()->getPosition().z >= SECTIONSIZE)
        {
            Section * front = this->_sections.front();
            this->_sections.pop_front();
            delete front;

            Section * s = new Section(&m);
            glm::vec3 pos = this->_sections.back()->getPosition();
            pos.z -= SECTIONSIZE;
            s->setPosition(pos);
            this->_sections.push_back(s);
        }

        distance += TimeManager::instance().deltaTime * 5.0f;

        tm.print(std::to_string((int)distance), 15.0f, 15.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

        g.display();
    }
}
