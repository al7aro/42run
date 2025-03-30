#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Transform.hpp"

namespace FT {
    struct Camera
    {
        enum Type
        {
			PERSPECTIVE,
			ORTHOGRAPHIC
        };
		Type  type;
        float fov;
        float aspect;
        float far;
        float near;
        float top;
		float bottom;
		float left;
        float right;
        float zoom;

        Transform tr;
        Camera(Type type = PERSPECTIVE)
            : type(type)
        {
            fov = glm::radians(60.0f);
            aspect = 1.0f;
            far = 1000.0f;
            near = 0.1f;
			top = 1.0f;
			bottom = -1.0f;
			left = -1.0f;
			right = 1.0f;
            zoom = 1.0f;
        }
        glm::mat4 GetProjectionMatrix() const
        {
            switch (type)
            {
			case PERSPECTIVE:
				return (glm::perspective(zoom * fov, aspect, near, far));
			case ORTHOGRAPHIC: //TODO: set near and far planes
                return (glm::ortho(left, right, bottom, top));
            }
            return (1.0f);
        }
        glm::mat4 GetViewMatrix() const
        {
            return (glm::inverse(glm::mat4_cast(tr.rot)) * glm::translate(glm::mat4(1.0), -tr.pos));
        }
    };
}