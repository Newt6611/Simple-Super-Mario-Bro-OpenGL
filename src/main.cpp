#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include <box2d/box2d.h>
#include "Input.h"

#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key >= 0 && key < 1024 && action == GLFW_PRESS)
    {
        Input::keys[key] = true;
    }

    if (key >= 0 && key < 1024 && action == GLFW_RELEASE)
    {
        Input::keys[key] = false;
        Input::keyUp[key] = false;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


int main(void)
{
    unsigned int width = 1920, height = 1080;

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, "Super Mario", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGL())
        std::cout << "error init glad !";
    
    Game game = Game(width, height);
    game.OnInit();

    float currentTime = 0.f;
    float lastTime = 0.f;
    float delta;


    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;

        glClearColor(0.363f, 0.914f, 0.937f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        game.OnUpdate(delta);
        game.OnRender();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}