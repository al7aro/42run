#pragma once

#include "FT.hpp"

constexpr float FLOOR_WIDTH = 4.0f;
constexpr float FLOOR_HEIGHT = 2.5f;

struct Floor
{
public:
    enum Direction
    {
        NORTH = 0,
        EAST = 1,
        SOUTH = 2,
        WEST = 3,
        NONE
    };
    enum Type
    {
        EMPTY = 0,
        FORWARD = 1,
        RIGHT = 2,
        LEFT = 4,
        UP = 8,
        DOWN = 16,
        RIGHT_FORWARD = 1 | 2,
        LEFT_FORWARD = 1 | 4,
        RIGHT_LEFT = 2 | 4,
        RIGHT_LEFT_FORWARD = 1 | 2 | 4
    };

public:
    Type type;
    Direction dir;
public:
    Floor() :type(EMPTY), dir(NONE) {}
    Floor(const Floor& o)
        : type(o.type), dir(o.dir)
    {
    }
    Floor(Type p_type, Direction p_dir)
        : type(p_type), dir(p_dir)
    {
    }
};