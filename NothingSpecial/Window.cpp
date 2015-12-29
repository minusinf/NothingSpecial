//
//  Window.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "Window.hpp"
#include "Scene.hpp"
#include <map>
#include <GLFW/glfw3.h>
#include <iostream>

std::map<GLFWwindow*, Window*> m_glfwWindowMap;

void
glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    m_glfwWindowMap[window]->keyCallback(key, scancode, action, mods);
}

void
glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    m_glfwWindowMap[window]->sizeCallback(width, height);
}

void
glfwWindowCloseCallback(GLFWwindow* window)
{
    m_glfwWindowMap[window]->close();
}

void
glfwWindowRefreshCallback(GLFWwindow* window)
{
    m_glfwWindowMap[window]->render();
}

void
glfwMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    m_glfwWindowMap[window]->mouseScrollCallback(xoffset, yoffset);
}

void
glfwMouseCursorCallback(GLFWwindow* window, double xpos, double ypos)
{
    m_glfwWindowMap[window]->mouseCursorCallback(xpos, ypos);
}

void
glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    m_glfwWindowMap[window]->mouseButtonCallback(button, action, mods);
}

Window::Window(int width, int height, const std::string& title):
    m_active(true),
    m_camera(width, height),
    m_scene(new Scene()) // empty default scene
{
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        std::cerr << "Failed to create glfw window. Aborting." << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(m_window);
    
    m_glfwWindowMap[m_window] = this;
    glfwSetKeyCallback(m_window, glfwKeyCallback);
    
    // Initialize framebuffer size
    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    glfwSetWindowRefreshCallback(m_window, glfwWindowRefreshCallback);
    glfwSetWindowCloseCallback(m_window, glfwWindowCloseCallback);
    glfwSetWindowSizeCallback(m_window, glfwFramebufferSizeCallback);
    
    glfwSetMouseButtonCallback(m_window, glfwMouseButtonCallback);
    glfwSetScrollCallback(m_window, glfwMouseScrollCallback);
    glfwSetCursorPosCallback(m_window, glfwMouseCursorCallback);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
}

bool
Window::isActive()
{
    return m_active;
}

void
Window::show()
{
    while (isActive())
    {
        render();
        glfwPollEvents();
    }

}

void
Window::render()
{
    double time = glfwGetTime();
    glViewport(0, 0, m_width, m_height);
    
    float ratio = m_width / (float) m_height;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_scene->render(m_camera);
    
    glfwSwapBuffers(m_window);
}

void
Window::keyCallback(int key, int scancode, int action, int mods)
{
    std::cout << "Received keycallback" << std::endl;
    if ((key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        || (key == GLFW_KEY_Q && (mods == GLFW_MOD_SUPER || mods == GLFW_MOD_CONTROL) && action == GLFW_PRESS)
        || (key == GLFW_KEY_W && (mods == GLFW_MOD_SUPER || mods == GLFW_MOD_CONTROL) && action == GLFW_PRESS))
    {
        close();
    }
    if (key == GLFW_KEY_UP)
    {
        m_camera.moveForward();
    }
    if (key == GLFW_KEY_DOWN)
    {
        m_camera.moveBackward();
    }
    if (key == GLFW_KEY_LEFT)
    {
        m_camera.moveLeft();
    }
    if (key == GLFW_KEY_RIGHT)
    {
        m_camera.moveRight();
    }
}

void
Window::mouseCursorCallback(double xpos, double ypos)
{
    if (!m_mouseLeftPressed)
    {
        m_mousePos.x() = xpos;
        m_mousePos.y() = ypos;
        return;
    }
    
    vec2 offset(m_mousePos.x()-xpos, ypos-m_mousePos.y());
    m_mousePos.x() = xpos;
    m_mousePos.y() = ypos;
    
    float sensitivty = 0.05;
    m_camera.mouse(offset, sensitivty);
}

void
Window::mouseButtonCallback(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            m_mouseLeftPressed = true;
        }
        else if (action == GLFW_RELEASE)
        {
            m_mouseLeftPressed = false;
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        if (action == GLFW_PRESS)
        {
            m_mouseRightPressed = true;
        }
        else if (action == GLFW_RELEASE)
        {
            m_mouseRightPressed = false;
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        if (action == GLFW_PRESS)
        {
            m_mouseMiddlePressed = true;
        }
        else if (action == GLFW_RELEASE)
        {
            m_mouseMiddlePressed = false;
        }
    }
}

void
Window::mouseScrollCallback(double xoffset, double yoffset)
{
    m_camera.moveForward(yoffset*0.1);
}

void
Window::sizeCallback(int width, int height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);
    m_camera.resize(width, height);
}

void
Window::loadScene(std::shared_ptr<Scene> scene)
{
    m_scene = scene;
}

void
Window::close()
{
    std::cout << "Closing window" << std::endl;
    m_active = false;
}
