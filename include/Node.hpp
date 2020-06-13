/* Header file for basic node.
 * Mass, position, velocity, force passed in.
 * Private variables for mass, position, velocity,
 *  force, neighbour, vertex array object, buffer, and
 *  initial distance set
 */

#ifndef MODELLING_ASSIGNMENTS_ASSIGNMENT1_INCLUDE_B_SPLINE_HPP
#define MODELLING_ASSIGNMENTS_ASSIGNMENT1_INCLUDE_B_SPLINE_HPP

#pragma once

#include <atlas/utils/Geometry.hpp>
#include <atlas/utils/Mesh.hpp>
#include <atlas/gl/Buffer.hpp>
#include <atlas/gl/VertexArrayObject.hpp>

namespace assignment2
{
    class Node : public atlas::utils::Geometry
    {
    public:
        Node(atlas::math::Vector position);

        ~Node() = default;

        void renderGeometry(atlas::math::Matrix4 projection, atlas::math::Matrix4 view);
        void setPosition(atlas::math::Vector position);
        atlas::math::Vector getPosition();

    private:
        atlas::math::Vector mPosition;
        atlas::gl::VertexArrayObject mVAO;
        atlas::gl::Buffer mBuff;
    };
}


#endif
