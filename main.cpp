#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

#include <GL/gl.h>
#include <GLES3/gl3.h>
#else
#include <glad/glad.h>
#endif

// For example purpose we use global variables
#define SPEED 0.005f
GLFWwindow *window = nullptr;
float red = 0.0f;
bool increase = true;

/**
 * @brief This function just increases and decreases the red value.
 *
 * @return The red value.
 */
GLfloat getRed()
{
    if (increase)
    {
        red += SPEED;
        if (red > 1.0f)
        {
            red = 1.0f;
            increase = false;
        }
    }
    else
    {
        red -= SPEED;
        if (red < 0.0f)
        {
            red = 0.0f;
            increase = true;
        }
    }

    std::cout << "Red: " << red << std::endl;

    return red;
}

/**
 * @brief This function is called every frame.
 */
void mainLoop()
{
    std::cout << "Loop" << std::endl;

    // Clear the screen with a color
    auto red = getRed();
    glClearColor(red, 0.0f, 0.0f, 1.0f);
    // std::cout << "Clear color" << std::endl;

    glClear(GL_COLOR_BUFFER_BIT);
    // std::cout << "clear" << std::endl;

    // Swap the buffers of the window
    glfwSwapBuffers(window);

    // Poll for the events
    glfwPollEvents();
}

/**
 * @brief The normal main() function.
 *
 * @return Exit code.
 */
int main()
{
    std::cout << "Starting" << std::endl;

    // Initialize glfw
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // Create the window
    window = glfwCreateWindow(640, 480, "Emscripten webgl example", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Make this window the current context
    glfwMakeContextCurrent(window);

#ifndef __EMSCRIPTEN__
    int version = gladLoadGL();
    if (version == 0)
    {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }
#endif

    std::cout << "Going into loop" << std::endl;
#ifdef EMSCRIPTEN
    EM_ASM({ Module.wasmTable = wasmTable; });

    // Define a mail loop function, that will be called as fast as possible
    emscripten_set_main_loop(&mainLoop, 0, 1);
#else
    // This is the normal C/C++ main loop
    while (!glfwWindowShouldClose(window))
    {
        mainLoop();
    }
#endif

    // Tear down the system
    std::cout << "Loop ended" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}