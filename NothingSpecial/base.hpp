//
//  base.h
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef base_h
#define base_h

// Used for development
#define BASE_PATH "/Users/pascal/Code/NothingSpecial/NothingSpecial/"
#include <stdint.h>
#include <memory> // unique_ptr
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cassert>
#include <sstream>
#include <unordered_map>

#include <exception>

// GLFW Setup
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h> // Includes OpenGL

#include <eigen3/Eigen/Dense>

typedef Eigen::Vector4f vec4;
typedef Eigen::Vector3f vec3;
typedef Eigen::Vector2f vec2;
typedef Eigen::Matrix4f mat4;
typedef Eigen::Matrix3f mat3;
typedef Eigen::Matrix<unsigned int, 3 , 1> face;

//#include <glm/glm.hpp>

#endif /* base_h */
