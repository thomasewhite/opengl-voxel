#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <chrono>

#include "../include/Camera.h"
#include "../include/Shader.h"
#include "../include/ChunkManager.h"
#include "../include/WindowManager.h"

// Shared camera instance
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Window manager with shared camera
WindowManager windowManager(camera);

void checkAllOpenGLErrors()
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error: " << err << " ";
        switch (err)
        {
        case GL_INVALID_ENUM:
            std::cerr << "(GL_INVALID_ENUM)";
            break;
        case GL_INVALID_VALUE:
            std::cerr << "(GL_INVALID_VALUE)";
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "(GL_INVALID_OPERATION)";
            break;
        case GL_STACK_OVERFLOW:
            std::cerr << "(GL_STACK_OVERFLOW)";
            break;
        case GL_STACK_UNDERFLOW:
            std::cerr << "(GL_STACK_UNDERFLOW)";
            break;
        case GL_OUT_OF_MEMORY:
            std::cerr << "(GL_OUT_OF_MEMORY)";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cerr << "(GL_INVALID_FRAMEBUFFER_OPERATION)";
            break;
        default:
            std::cerr << "(Unknown Error)";
        }
        std::cerr << std::endl;
    }
}

void displayFPS()
{
    static int frameCount = 0;
    static auto lastTime = std::chrono::high_resolution_clock::now();

    frameCount++;

    auto currentTime = std::chrono::high_resolution_clock::now();
    double elapsedTime = std::chrono::duration<double, std::milli>(currentTime - lastTime).count();

    if (elapsedTime >= 1000.0) // 1 second has passed
    {
        double fps = (frameCount / elapsedTime) * 1000.0;
        std::cout << "FPS: " << fps << std::endl;

        frameCount = 0;
        lastTime = currentTime;
    }
}

int main()
{
    if (windowManager.window == nullptr)
    {
        std::cerr << "Failed to initialize window manager!" << std::endl;
        return -1;
    }

    // Set camera pointer for callbacks
    glfwSetWindowUserPointer(windowManager.window, &camera);

    Shader shader("src/shader.vs", "src/shader.fs");

    ChunkManager chunkManager;
    glm::vec3 sunDirection(0.5f, 0.7f, 0.5f);

    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(windowManager.window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        windowManager.processInput(deltaTime);
        chunkManager.updateChunks(camera);

        // Clear screen
        glClearColor(0.1f, 0.7f, 0.88f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set shader properties
        shader.use();
        shader.setVec3("lightDir", sunDirection);
        shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1600.0f / 1200.0f, 0.1f, 10000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        shader.setMat4("model", model);

        chunkManager.renderChunks();

        checkAllOpenGLErrors();
        displayFPS();

        glfwSwapBuffers(windowManager.window);
    }

    return 0;
}
