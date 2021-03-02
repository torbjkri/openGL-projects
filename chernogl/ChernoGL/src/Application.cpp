#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    int flags;

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (GLEW_OK != glewInit()) {
        std::cout << "Error: Unable to initialize GLEW!" << std::endl;
        return 1;
    }
    glfwSwapInterval(1);
    std::cout << glGetString(GL_VERSION) << std::endl;

    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_OTHER, 0, GL_DEBUG_SEVERITY_NOTIFICATION, -1, "GL debug output enabled!");
    }
    else {
        std::cout << "No debug context!" << std::endl;
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader("res/shaders/Basic.shader");

    const float positions[] = {
        -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f,   0.0f, 1.0f
    };

    const unsigned int indices[]{
        0, 1, 2,
        2, 3, 0
    };
    { // Scope gl objects
        VertexArray va;

        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 2 * 3);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();


        float r = 0.0f;
        float increment = 0.04f;
        /* Loop until the user closes the window */

        Texture texture("res/textures/tree.jpg");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        Renderer renderer;

        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();


            renderer.Draw(va, ib, shader);

            r += increment;
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}