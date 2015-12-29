//
//  Window.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "base.hpp"
#include "Camera.hpp"
typedef struct GLFWwindow GLFWwindow;
class Scene;
class Window
{
public:
    Window(int width, int height, const std::string& title);
    ~Window();
    
    bool isActive();
    
    void close();
    void render();
    void show();
    void loadScene(std::shared_ptr<Scene> scene);
    void keyCallback(int key, int scancode, int action, int mods);
    void sizeCallback(int width, int height);
    
    void mouseButtonCallback(int button, int action, int mods);
    void mouseScrollCallback(double xoffset, double yoffset);
    void mouseCursorCallback(double xpos, double ypos);
    
private:
    bool m_active;
    int m_width;
    int m_height;
    GLFWwindow* m_window;
    
    bool m_mouseLeftPressed;
    bool m_mouseRightPressed;
    bool m_mouseMiddlePressed;
    vec2 m_mousePos;
    Graphics::Camera m_camera;
    std::shared_ptr<Scene> m_scene;
};

#endif /* Window_hpp */
