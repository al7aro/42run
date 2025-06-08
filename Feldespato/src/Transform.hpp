#pragma once

#include "math/Math.hpp"

namespace FT {
    struct Transform
    {
        FT::vec3 pos;
        FT::vec3 size;
        float rotX;
        float rotY;
        float rotZ;

        FT::mat4 parent;

		Transform()
            : pos(0.0), size(1.0), parent(1.0),
            rotX(0.0), rotY(0.0), rotZ(0.0)
		{
        }
        
        Transform(float s)
            : Transform()
        {
            size = FT::vec3(s);
        }

        Transform(FT::vec3 p)
            : pos(p), size(1.0), parent(1.0),
            rotX(0.0), rotY(0.0), rotZ(0.0)
        {
        }
        Transform(FT::vec3 p, FT::vec3 s)
            : pos(p), size(s), parent(1.0),
            rotX(0.0), rotY(0.0), rotZ(0.0)
        {
        }

        FT::mat4 GetTranslate() const
        {
            FT::mat4 translate = FT::translate(pos);
            return (translate);
        }

        FT::mat4 GetScale() const
        {
            FT::mat4 scale = FT::translate(pos);
            return (scale);
        }

        FT::mat4 GetRotation() const
        {
            FT::mat4 rotation = FT::rotateX(rotX);
            rotation *= FT::rotateY(rotY);
            rotation *= FT::rotateZ(rotZ);
            return (rotation);
        }

        FT::mat4 GetTransform() const
        {
            FT::mat4 total_tr = parent;
            total_tr *= FT::translate(pos);
            total_tr *= FT::scale(size);
            total_tr *= FT::rotateX(rotX);
            total_tr *= FT::rotateY(rotY);
            total_tr *= FT::rotateZ(rotZ);

            return (total_tr);
        }

        void Scale(const FT::vec3& offset)
        {
            this->size *= offset;
        }
        void Pitch(const float& angle)
        {
            FT::vec3 right = FT::vec3(1.0, 0.0, 0.0);
            rotX += angle;
        }
        void Roll(const float& angle)
        {
            FT::vec3 front = FT::vec3(0.0, 0.0, 1.0);
            rotZ += angle;
        }
        void Yaw(const float& angle)
        {
            FT::vec3 up = FT::vec3(0.0, 1.0, 0.0);
            rotY += angle;
        }
    };
}