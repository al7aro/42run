#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace FT {
    struct Transform
    {
        glm::vec3 pos;
        glm::vec3 size;
        float rotX;
        float rotY;
        float rotZ;

        glm::mat4 parent;

		Transform()
            : pos(0.0), size(1.0), parent(1.0),
            rotX(0.0), rotY(0.0), rotZ(0.0)
		{
        }
        
        Transform(float s)
            : Transform()
        {
            size = glm::vec3(s);
        }

        Transform(glm::vec3 p)
            : pos(p), size(1.0), parent(1.0),
            rotX(0.0), rotY(0.0), rotZ(0.0)
        {
        }
        Transform(glm::vec3 p, glm::vec3 s)
            : pos(p), size(s), parent(1.0),
            rotX(0.0), rotY(0.0), rotZ(0.0)
        {
        }

        glm::mat4 GetTranslate() const
        {
            glm::mat4 translate = glm::translate(glm::mat4(1.0), pos);
            return (translate);
        }

        glm::mat4 GetScale() const
        {
            glm::mat4 scale = glm::translate(glm::mat4(1.0), pos);
            return (scale);
        }

        glm::mat4 GetRotation() const
        {
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0), rotX, glm::vec3(1.0, 0.0, 0.0));
            rotation *= glm::rotate(glm::mat4(1.0), rotY, glm::vec3(0.0, 1.0, 0.0));
            rotation *= glm::rotate(glm::mat4(1.0), rotZ, glm::vec3(0.0, 0.0, 1.0));
            return (rotation);
        }

        glm::mat4 GetTransform() const
        {
            glm::mat4 translate = glm::translate(glm::mat4(1.0), pos);
            glm::mat4 scale = glm::scale(glm::mat4(1.0), size);
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0), rotX, glm::vec3(1.0, 0.0, 0.0));
            rotation *= glm::rotate(glm::mat4(1.0), rotY, glm::vec3(0.0, 1.0, 0.0));
            rotation *= glm::rotate(glm::mat4(1.0), rotZ, glm::vec3(0.0, 0.0, 1.0));

            return (parent * translate * scale * rotation);
        }

        void Scale(const glm::vec3& offset)
        {
            this->size *= offset;
        }
        void Pitch(const float& angle)
        {
            glm::vec3 right = glm::vec3(1.0, 0.0, 0.0);
            rotX += angle;
        }
        void Roll(const float& angle)
        {
            glm::vec3 front = glm::vec3(0.0, 0.0, 1.0);
            rotZ += angle;
        }
        void Yaw(const float& angle)
        {
            glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
            rotY += angle;
        }
    };
}