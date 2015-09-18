//
//  Window.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

class GLFWwindow;

class Window
{
public:
    Window(GLFWwindow* window);
    ~Window();
    
    bool isActive();
    
    void close();
    void render();
    void keyCallback(int key, int scancode, int action, int mods);
    void sizeCallback(int width, int height);
private:
    bool m_active;
    int m_width;
    int m_height;
    GLFWwindow* m_window;
};

#endif /* Window_hpp */
