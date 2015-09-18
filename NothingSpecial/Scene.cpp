//
//  Scene.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene()
{
    
}

void
Scene::render() const
{
    for (const auto& pm: m_objects)
    {
        pm->render();
    }
}

void
Scene::addObject(std::shared_ptr<Graphics::RenderableObject> obj)
{
    m_objects.push_back(obj);
}