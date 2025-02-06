#include "../include/WindowManager.h"

WindowManager::WindowManager(Camera &cam) : camera(cam)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Voxel", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBufferCallback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    const char *renderer = (const char *)glGetString(GL_RENDERER);
    std::cout << "OpenGL renderer: " << renderer << std::endl;

    glEnable(GL_DEPTH_TEST);
}

WindowManager::~WindowManager()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void WindowManager::processInput(float deltaTime) // Accept deltaTime
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Callbacks (unchanged)
void WindowManager::frameBufferCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void WindowManager::mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    static bool firstMouse = true;
    static float lastX = 800.0f, lastY = 600.0f;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    Camera *cam = reinterpret_cast<Camera *>(glfwGetWindowUserPointer(window));
    if (cam)
    {
        cam->ProcessMouseMovement(xoffset, yoffset);
    }
}

void WindowManager::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    Camera *cam = reinterpret_cast<Camera *>(glfwGetWindowUserPointer(window));
    if (cam)
    {
        cam->ProcessMouseScroll(static_cast<float>(yoffset));
    }
}
