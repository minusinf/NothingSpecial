//
//  main.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include <iostream>
#include "base.hpp"
#include "Window.hpp"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define PROJECT_NAME "Nothing Special"

#include "Scene.hpp"
#include "ObjMesh.hpp"
std::shared_ptr<Scene>
createScene()
{
    std::shared_ptr<Scene> scene(new Scene());
    scene->addObject(std::make_shared<Graphics::ObjMesh>("/Users/pascal/Downloads/bunny.obj"));
    return scene;
}

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
    
    // Use OpenGL Core v4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* glfwwindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, PROJECT_NAME, NULL, NULL);
    if (!glfwwindow)
    {
        glfwTerminate();
        std::cerr << "Failed to create glfw window. Aborting." << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(glfwwindow);
    
    Window window(glfwwindow);
    window.loadScene(createScene());
    while (window.isActive())
    {
        window.render();
        glfwPollEvents();
    }    
    glfwTerminate();
    return EXIT_SUCCESS;
}
