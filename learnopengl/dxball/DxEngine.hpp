#ifndef DXGAME_H
#define DXGAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class DxEngine
{
public:
    // Game state
    GameState State;
    GLboolean Keys[1024];
    GLuint Width, Height;
    // Constructor/destructor
    DxEngine(GLuint width, GLuint height);
    ~DxEngine();
    // Initializer function
    void Init();
    // Game Loop
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
};

#endif
