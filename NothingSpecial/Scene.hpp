//
//  Scene.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "base.hpp"
#include "Graphics/RenderableObject.hpp"

class Scene
{
public:
    Scene();
    void render() const;
    void addObject(std::shared_ptr<Graphics::RenderableObject> obj);
private:
    std::vector<std::shared_ptr<Graphics::RenderableObject>> m_objects;
};

#endif /* Scene_hpp */
