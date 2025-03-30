#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace FT {
    struct Transform
    {
        glm::vec3 pos;
        glm::vec3 size;
        glm::quat rot;

        glm::mat4 parent;

		Transform()
            : pos(0.0), size(1.0), rot(glm::angleAxis(0.0f, glm::vec3(1.0))), parent(1.0)
		{
        }
        
        Transform(float s)
            : Transform()
        {
            size = glm::vec3(s);
        }

        Transform(glm::vec3 p)
            : pos(p), size(1.0), rot(glm::angleAxis(0.0f, glm::vec3(1.0))), parent(1.0)
        {
        }
        Transform(glm::vec3 p, glm::vec3 s)
            : pos(p), size(s), rot(glm::angleAxis(0.0f, glm::vec3(1.0))), parent(1.0)
        {
        }
        Transform(glm::vec3 p, glm::quat r)
            : pos(p), size(1.0), rot(r), parent(1.0)
        {
        }
        Transform(glm::vec3 p, glm::vec3 s, glm::quat r)
            : pos(p), size(s), rot(r), parent(1.0)
        {
        }

        glm::mat4 GetTransform() const
        {
            glm::mat4 translate = glm::translate(glm::mat4(1.0), pos);
            translate *= glm::scale(glm::mat4(1.0), size);
            translate *= glm::mat4_cast(rot);
            return (parent * translate);
        }

        void MoveLocal(const glm::vec3& offset)
        {
            this->pos += rot * offset;
        }
        void MoveWorld(const glm::vec3& offset)
        {
            this->pos += offset;
        }
        void Scale(const glm::vec3& offset)
        {
            this->size *= offset;
        }
        void RotateWorld(const float& angle, glm::vec3 axis)
        {
            axis = axis * rot;
            rot = glm::normalize(glm::rotate(rot, angle, axis));
        }
        void RotateLocal(const float& angle, glm::vec3 axis)
        {
            rot = glm::normalize(glm::rotate(rot, angle, axis));
        }
        void Pitch(const float& angle)
        {
            glm::vec3 right = glm::vec3(1.0, 0.0, 0.0);
            rot = glm::normalize(glm::rotate(rot, angle, right));
        }
        void Roll(const float& angle)
        {
            glm::vec3 front = glm::vec3(0.0, 0.0, 1.0);
            rot = glm::normalize(glm::rotate(rot, angle, front));
        }
        void Yaw(const float& angle)
        {
            glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
            rot = glm::normalize(glm::rotate(rot, angle, up));
        }
    };
}