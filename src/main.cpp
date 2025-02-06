#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>
#include <vector>
#include <map>

#include "../include/Camera.h"
#include "../include/Shader.h"
#include "../include/ChunkManager.h"
#include "../include/WindowManager.h"

// Shared camera instance
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Window manager with shared camera
WindowManager windowManager(camera);

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

        glfwSwapBuffers(windowManager.window);
    }

    return 0;
}
