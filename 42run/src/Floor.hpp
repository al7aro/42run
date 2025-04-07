#pragma once

#include "FT.hpp"

struct Floor
{
public:
    enum Type
    {
        FORWARD = 0,
        RIGHT = 1,
        RIGHT_FORWARD = 2,
        LEFT = 3,
        LEFT_FORWARD = 4,
        RIGHT_LEFT = 5,
        RIGHT_LEFT_FORWARD = 6,
        UP = 7,
        DOWN = 8,
        MAX_FLOOR_ID = 9
    };
	FT::Model model;
    Type type;
public:
    Floor() {}
    Floor(const Floor & o)
        : model(o.model), type(o.type) {}
    Floor(FT::Model p_model, Type p_type)
        : model(p_model), type(p_type)
    {
    }
};