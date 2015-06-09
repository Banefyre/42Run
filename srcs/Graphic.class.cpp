#include <Graphic.class.hpp>
#include <stdio.h>
#include <cstdlib>

Graphic & Graphic::instance(void) {
    static Graphic inst;
    return inst;
}

Graphic::~Graphic(void) {
    glfwTerminate();
    return ;
}

Graphic::Graphic(void) {

    if ( !glfwInit() )
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        std::exit(-1);
    }

    //AA
    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    this->_window = glfwCreateWindow(WIDTH, HEIGHT, "42run", NULL, NULL);


    if ( this->_window == NULL )
    {
        fprintf(stderr, "Failed to create a GLFW window, you might need to download the latest drivers or change the OpenGL version to 3\n");
        delete this;

        std::exit(-1);
    }

    // Create the OpenGL context from the window and settings specified
    glfwMakeContextCurrent(this->_window);

    //set input mode
    glfwSetInputMode(this->_window, GLFW_STICKY_KEYS, GL_TRUE);


    //This turn off v sync
    //glfwSwapInterval(0);

    //hide mouse
    glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //set cursor position
    glfwSetCursorPos(this->_window, 0, 0);

    //needed to work
    glewExperimental = GL_TRUE;

    GLenum err = glewInit();

    if ( GLEW_OK != err )
    {
        fprintf(stderr, "Failed to initialize glew\n");
        std::exit(-1);
    }

}

void Graphic::clear(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphic::display(void) {
    glfwSwapBuffers(this->_window);
}

eKey Graphic::processInput(void) {

    glfwPollEvents();

    if ( glfwGetKey(this->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(this->_window) != 0 )
        return ESC;

    if ( glfwGetKey(this->_window, GLFW_KEY_UP) || glfwGetKey(this->_window, GLFW_KEY_W) )
        return UP;
    if ( glfwGetKey(this->_window, GLFW_KEY_DOWN) || glfwGetKey(this->_window, GLFW_KEY_S) )
        return DOWN;
    if ( glfwGetKey(this->_window, GLFW_KEY_LEFT) || glfwGetKey(this->_window, GLFW_KEY_A) )
        return LEFT;
    if ( glfwGetKey(this->_window, GLFW_KEY_RIGHT) || glfwGetKey(this->_window, GLFW_KEY_D) )
        return RIGHT;

    return NONE;
}
