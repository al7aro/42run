#pragma once

#include "FT.hpp"

constexpr float FLOOR_WIDTH = 4.0f;
constexpr float FLOOR_HEIGHT = 2.5f;

struct Floor
{
public:
    enum Type
    {
        FORWARD = 1,
        RIGHT = 2,
        LEFT = 4,
        UP = 8,
        DOWN = 16,
        RIGHT_FORWARD = 1 | 2,
        LEFT_FORWARD = 1 | 4,
        RIGHT_LEFT = 2 | 4,
        RIGHT_LEFT_FORWARD = 1 | 2 | 4,
        MAX_FLOOR_ID = 9
    };
    FT::Model model;
    Type type;
public:
    Floor() {}
    Floor(const Floor& o)
        : model(o.model), type(o.type)
    {
    }
    Floor(FT::Model p_model, Type p_type)
        : model(p_model), type(p_type)
    {
    }
};