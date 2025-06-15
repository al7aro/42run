#pragma once

#include "FT.hpp"
#include <cstdlib>

constexpr float FLOOR_WIDTH = 4.0f;
constexpr float FLOOR_HEIGHT = 1.25f;
constexpr int OBSTACLES_SLOTS = 3;

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
        UP = 1 | 8, //9
        DOWN = 1 | 16, //17
        RIGHT_FORWARD = 1 | 2,
        LEFT_FORWARD = 1 | 4,
        RIGHT_LEFT = 2 | 4,
        RIGHT_LEFT_FORWARD = 1 | 2 | 4
    };

public:
    Type type;
    Direction dir;
    bool visible;
    int obstacles[OBSTACLES_SLOTS]; // TODO: 1 top obstacle | -1 bottom obstacle
    bool has_obstacles;
public:
    Floor() :type(EMPTY), dir(NONE), visible(true), has_obstacles(false) {}
    Floor(const Floor& o)
        : type(o.type), dir(o.dir), visible(o.visible), has_obstacles(o.has_obstacles)
    {
        for (int i = 0; i < OBSTACLES_SLOTS; i++)
            obstacles[i] = o.obstacles[i];
    }
    Floor(Type p_type, Direction p_dir, bool p_visible = true)
        : type(p_type), dir(p_dir), visible(p_visible)
    {
        RandomiceObstacles();
    }

    void RandomiceObstacles()
    {
        for (int i = 0; i < OBSTACLES_SLOTS; i++)
            obstacles[i] = 0;
        if (type & RIGHT || type & LEFT || type == UP || type == DOWN)
            return;
        double r = double(std::rand()) / double(RAND_MAX);
        // Let's check if this floor will have obstacles with a [floor_obstacle_density] density
        const float floor_obstacle_density = 0.2; // TODO: constexpr?
        // If it does not have obstacles -> stop
        if (r >= floor_obstacle_density)
            return;
        has_obstacles = true;
        // If it has obscatles fill them randomly
        int slot = FT::round(2.0 * (double(std::rand()) / double(RAND_MAX)));
        // It will always have at least one obstacle
        obstacles[slot] = 1;

        for (int i = 0; i < 3; i++)
        {
            if (i == slot) continue;
            // The rest 2 are filled randomly
            if ((double(std::rand()) / double(RAND_MAX)) <= 0.33)
                obstacles[i] = 1;
        }
    }
};