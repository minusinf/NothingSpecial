//
//  Camera.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 29/12/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "Camera.hpp"

#include "MathHelpers.h"

#include <eigen3/Eigen/Geometry>

using namespace Graphics;

Camera::Camera(float width, float height):
    Camera(width, height, 45.0f, 0.1f, 10000.0f)
{
    
}

Camera::Camera(float width, float height, float angle, float near, float far):
    m_angle(angle),
    m_aspect(width/height),
    m_near(near),
    m_far(far),
    m_speed(0.5),
    m_viewMatrix(mat4::Identity()),
    m_viewMatrixDirty(true),
    m_projMatrix(mat4::Identity()),
    m_projMatrixDirty(true),
    m_position(10,10,10),
    m_up(0,1,0),
    m_front(-m_position.normalized()), // Point at 0,0,0
    m_rotationCenter(0,0,0)
{
    resize(width, height);
}

const mat4&
Camera::view() const
{
    if (m_viewMatrixDirty)
    {
        m_viewMatrix = Camera::createLookAtMatrix(m_position, m_position+m_front, m_up);
        m_viewMatrixDirty = false;
    }
    return m_viewMatrix;
}

const mat4&
Camera::proj() const
{
    return m_projMatrix;
}

void
Camera::resize(float width, float height)
{
    m_aspect = width/height;
    m_projMatrix = createPerspectiveMatrix(m_aspect, m_angle, m_near, m_far);
    m_projMatrixDirty = false;
}

void
Camera::move(const vec3& dir)
{
    m_position += dir;
    m_viewMatrixDirty = true;
}

void
Camera::moveForward(float factor)
{
    move(m_front*m_speed*factor);
}

void
Camera::moveBackward()
{
    moveForward(-1.0f);
}

void
Camera::moveLeft(float factor)
{
    move(m_front.cross(m_up).normalized()*factor*m_speed);
}

void
Camera::moveRight()
{
    moveLeft(1.0f);
}

void
Camera::pan(const vec2 &offset, float sensitivity)
{
    using namespace Eigen;
    
    const vec3& xRotationAxis = m_up;
    vec3 yRotationAxis = m_up.cross(m_front);
    
    Quaternionf xRot(AngleAxisf(-offset.x()*sensitivity, xRotationAxis));
    Quaternionf yRot(AngleAxisf(offset.y()*sensitivity, yRotationAxis));

    Quaternionf rot = xRot*yRot;
    m_front = rot.matrix() * m_front;
    m_viewMatrixDirty = true;
}

void
Camera::rotate(const vec2 &offset, float sensitivity)
{
    using namespace Eigen;

    vec3 xRotationAxis = vec3(0,1,0);
    vec3 yRotationAxis = -m_front.cross(m_up).normalized();
    
    Quaternionf xRot(AngleAxisf(offset.x()*sensitivity, xRotationAxis));
    Quaternionf yRot(AngleAxisf(offset.y()*sensitivity, yRotationAxis));

    Quaternionf rot = xRot * yRot;

    Affine3f transform = Translation3f(-m_rotationCenter)
                       * rot
                       * Translation3f(m_rotationCenter);
    
    m_position = transform * m_position;
    m_front = rot.matrix() * m_front;
    m_up = rot.matrix() * m_up;
    
    m_viewMatrixDirty = true;
}

/*
 * creates a perspective matrix according to the C gluPerspectiveMatrix spec
 * https://www.opengl.org/sdk/docs/man2/xhtml/gluPerspective.xml
 */
mat4
Camera::createPerspectiveMatrix(float aspect, float angle, float near, float far)
{
    float finv = tan(Math::toRadians(angle)*0.5f);
    float wl = (far+near)/(near-far);
    float wr = (2*far*near)/(near-far);
    mat4 res;
    res << 1.0/(aspect*finv), 0.0,  0.0, 0.0,
           0.0, 1.0/finv         ,  0.0, 0.0,
           0.0, 0.0              ,  wl , wr,
           0.0, 0.0              , -1.0, 0.0;
    return res;
}

/*
 * creates a look at matrix.
 */
mat4
Camera::createLookAtMatrix(const vec3 &position, const vec3 &lookAt, const vec3 &up)
{
    vec3 f = (lookAt-position).normalized();
    vec3 u = up.normalized();
    vec3 s = f.cross(u).normalized();
    u = s.cross(f);
    mat4 res;
    res <<  s.x(),  s.y(),  s.z(), -s.dot(position),
            u.x(),  u.y(),  u.z(), -u.dot(position),
           -f.x(), -f.y(), -f.z(),  f.dot(position),
            0.0  ,  0.0  ,  0.0  ,  1.0;
    return res;
}