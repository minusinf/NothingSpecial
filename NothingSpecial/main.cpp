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
#include "Shader.hpp"
#include "Mesh.hpp"
#include "MeshFactory.h"
#include "VolumeReader.hpp"
#include "Volume.hpp"
std::shared_ptr<Scene>
createScene()
{
    auto scene = std::make_shared<Scene>();
    auto volData = VolumeReader::readRaw("/users/pascal/golfball0_0-512x256x256.raw", vec3(512,256,256));
//    auto volData = VolumeReader::createBox(vec3(16,256,256));

    auto vol = std::make_shared<Graphics::Volume>(volData);
    scene->addObject(vol);
//    scene->addObject(std::make_shared<Graphics::Mesh>());
//    Graphics::MeshFactory::loadObj(*scene, "/Users/pascal/cube.obj", false);
//    Graphics::MeshFactory::addCube(*scene);
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
    
    // GLFW Init and Core Profile Setup
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW. Aborting." << std::endl;
        return EXIT_FAILURE;
    }
    glfwSetErrorCallback(glfw_error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
    // Create a window
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, PROJECT_NAME);
    window.loadScene(createScene());
    // Show the window
    window.show();
    
    // Terminate the window when the window has closed.
    glfwTerminate();
}
