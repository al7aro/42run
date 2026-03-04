#pragma once

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
            fov = FT::radians(60.0f);
            aspect = 1.0f;
            far = 1000.0f;
            near = 0.1f;
            if (type == ORTHOGRAPHIC)
            {
                far = 1.0f;
                near = -1.0f;
            }
			top = 1.0f;
			bottom = -1.0f;
			left = -1.0f;
			right = 1.0f;
            zoom = 1.0f;
        }
        FT::mat4 GetProjectionMatrix() const
        {
            switch (type)
            {
			case PERSPECTIVE:
				return (FT::perspective(zoom * fov, aspect, near, far));
			case ORTHOGRAPHIC:
                return (FT::ortho(left, right, bottom, top, near, far));
            }
            return (1.0f);
        }
        FT::mat4 GetViewMatrix() const
        {
            FT::mat4 translate = FT::translate(-tr.pos);
            FT::mat4 rotation = FT::inverse(tr.GetRotation());

            return (rotation * translate);
        }
    };
}