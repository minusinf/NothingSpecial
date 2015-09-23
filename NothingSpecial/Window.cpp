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

Window::Window(GLFWwindow* window):
    m_window(window),
    m_active(true),
    m_scene(new Scene()) // empty default scene
{
    m_glfwWindowMap[window] = this;
    glfwSetKeyCallback(window, glfwKeyCallback);
    
    // Initialize framebuffer size
    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    glfwSetWindowRefreshCallback(m_window, glfwWindowRefreshCallback);
    glfwSetWindowCloseCallback(m_window, glfwWindowCloseCallback);
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
Window::render()
{
    double time = glfwGetTime();
    glViewport(0, 0, m_width, m_height);
    
    float ratio = m_width / (float) m_height;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_scene->render();
    
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
//    glBegin(GL_TRIANGLES);
//    glColor3f(1.f, 0.f, 0.f);
//    glVertex3f(-0.6f, -0.4f, 0.f);
//    glColor3f(0.f, 1.f, 0.f);
//    glVertex3f(0.6f, -0.4f, 0.f);
//    glColor3f(0.f, 0.f, 1.f);
//    glVertex3f(0.f, 0.6f, 0.f);
//    glEnd();
    glfwPollEvents();
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
}

void
Window::sizeCallback(int width, int height)
{
    m_width = width;
    m_height = height;
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
