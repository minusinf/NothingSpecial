//
//  main.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include <iostream>
#include <GLFW/glfw3.h>
#include "Window.hpp"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define PROJECT_NAME "Nothing Special"

void glfw_error_callback(int error, const char* desc)
{
    std::cerr << "GLFW ERROR(" << std::to_string(error) << ")" << desc << std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Welcome to Project Nothing Special" << std::endl;
    std::cout << "Initializing OpenGL" << std::endl;
    
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW. Aborting." << std::endl;
        return EXIT_FAILURE;
    }
    glfwSetErrorCallback(glfw_error_callback);
    
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, PROJECT_NAME, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cerr << "Failed to create window. Aborting." << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    
    std::unique_ptr<Window> pWindow(new Window(window));
    while (pWindow->isActive())
    {
        pWindow->render();
        glfwPollEvents();
    }
    pWindow->close();
    
    glfwTerminate();
    return EXIT_SUCCESS;
}
