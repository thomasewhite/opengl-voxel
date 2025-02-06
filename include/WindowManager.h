#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/Camera.h"

class WindowManager
{
public:
    WindowManager(Camera& camera);
    ~WindowManager();

    GLFWwindow *window;
    void processInput(float deltaTime); // Accept deltaTime

private:
    Camera &camera; // Shared camera reference

    // Window size
    const unsigned int width = 1600;
    const unsigned int height = 1200;

    // Mouse input
    float lastX = width / 2.0f;
    float lastY = height / 2.0f;
    bool firstMouse = true;

    // Callbacks
    static void frameBufferCallback(GLFWwindow *window, int width, int height);
    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
};

#endif
