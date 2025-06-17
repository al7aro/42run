#pragma once

#include "FT.hpp"
#include <cstdlib>

constexpr float FLOOR_WIDTH = 4.0f;
constexpr float FLOOR_HEIGHT = 1.25f;
constexpr int OBSTACLES_SLOTS = 3;
constexpr int COLLECTABLE_SLOTS = 3;

constexpr float OBSTACLE_DENSITY = 0.2; // TODO: constexpr?
constexpr float COLLECTABLE_DENSITY = 0.2; // TODO: constexpr?


struct Floor
{
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
    enum Obstacle
    {
        FREE = 0,
        FENCE,  // JUMPABLE
        WALL    // NON JUMPABLE
    };
    Type type;
    Direction dir;
    bool visible;
    Obstacle obstacles[OBSTACLES_SLOTS]; // TODO: 1 top obstacle | -1 bottom obstacle
    bool collectables[COLLECTABLE_SLOTS];
    bool has_obstacles;
    bool enabled_obstacles;

    Floor() : type(EMPTY), dir(NONE), visible(true), has_obstacles(false) {}
    Floor(const Floor& o)
        : type(o.type), dir(o.dir), visible(o.visible), has_obstacles(o.has_obstacles), enabled_obstacles(o.enabled_obstacles)
    {
        for (int i = 0; i < OBSTACLES_SLOTS; i++)
            obstacles[i] = o.obstacles[i];
        for (int i = 0; i < COLLECTABLE_SLOTS; i++)
            collectables[i] = o.collectables[i];
    }
    Floor(Type p_type, Direction p_dir, bool enabled_obstacles = true, bool p_visible = true)
        : type(p_type), dir(p_dir), visible(p_visible), enabled_obstacles(enabled_obstacles)
    {
        Reset();
    }

    void Reset()
    {
        RandomiceObstacles();
        RandomiceCollectables();
    }

    void RandomiceObstacles()
    {
        for (int i = 0; i < OBSTACLES_SLOTS; i++)
            obstacles[i] = Obstacle::FREE;
        if (!enabled_obstacles)
            return;
        if (type & RIGHT || type & LEFT || type == UP || type == DOWN)
            return;
        double r = double(std::rand()) / double(RAND_MAX);
        // Let's check if this floor will have obstacles with a [floor_obstacle_density] density
        // If it does not have obstacles -> stop
        if (r >= OBSTACLE_DENSITY)
            return;
        has_obstacles = true;
        // If it has obscatles fill them randomly
        int slot = FT::round(2.0 * (double(std::rand()) / double(RAND_MAX)));
        // It will always have at least one obstacle
        obstacles[slot] = Obstacle::WALL;
        if ((double(std::rand()) / double(RAND_MAX)) <= 0.5)
            obstacles[slot] = Obstacle::FENCE;

        for (int i = 0; i < 3; i++)
        {
            if (i == slot) continue;
            // The rest 2 are filled randomly
            if ((double(std::rand()) / double(RAND_MAX)) <= 0.33)
            {
                obstacles[slot] = Obstacle::WALL;
                if ((double(std::rand()) / double(RAND_MAX)) <= 0.75)
                    obstacles[slot] = Obstacle::FENCE;
            }
        }
    }

    void RandomiceCollectables()
    {
        for (int i = 0; i < COLLECTABLE_SLOTS; i++)
            collectables[i] = false;
        if (type & RIGHT || type & LEFT || type == UP || type == DOWN)
            return;
        double r = double(std::rand()) / double(RAND_MAX);
        // Let's check if this floor will have obstacles with a [floor_obstacle_density] density
        // If it does not have obstacles -> stop
        if (r >= COLLECTABLE_DENSITY)
            return;
        // If it has obscatles fill them randomly
        int slot = FT::round(2.0 * (double(std::rand()) / double(RAND_MAX)));
        // It will always have at least one obstacle
        if (obstacles[slot] != Obstacle::FREE)
            return;
        collectables[slot] = true;
    }

    void EnableObstacles(bool enable = true)
    {
        enabled_obstacles = enable;
    }
};