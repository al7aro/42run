#pragma once

#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "Floor.hpp"
#include "Player.hpp"
#include "Grid.hpp"

class Trail
{
public:
    std::map<Floor::Type, FT::Model> m_floor_types;
    Grid<Floor> m_map;

    glm::vec3 m_pos;
    Floor::Direction m_dir;


    bool m_rotating;
    float m_rot_speed;
    float m_rot_offset;
    float m_total_rotation;

public:
    Trail(FT::Feldespato & fdp)
        : m_map(11, 11), m_pos(0.0), m_dir(Floor::NONE),
        m_rotating(false), m_rot_speed(0.1), m_rot_offset(0.0), m_total_rotation(0.0)
    {
        m_floor_types[Floor::FORWARD] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/front.dae");
        m_floor_types[Floor::RIGHT] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right.dae");
        m_floor_types[Floor::LEFT] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/left.dae");
        m_floor_types[Floor::RIGHT_LEFT] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right_left.dae");
        m_floor_types[Floor::RIGHT_LEFT_FORWARD] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right_left_front.dae");
        m_floor_types[Floor::RIGHT_FORWARD] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right_front.dae");
        m_floor_types[Floor::LEFT_FORWARD] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/left_front.dae");
        m_floor_types[Floor::UP] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/front_up.dae");
        m_floor_types[Floor::DOWN] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/front_down.dae");
    }

    void Init()
    {
        for (int y = 1; y < m_map.GetYSize() - 1; y++)
            m_map.At(1, y) = Floor(Floor::FORWARD, Floor::NORTH);
        for (int y = 1; y < m_map.GetYSize() - 1; y++)
            m_map.At(m_map.GetXSize() - 2, y) = Floor(Floor::FORWARD, Floor::SOUTH);
        for (int x = 1; x < m_map.GetXSize() - 1; x++)
            m_map.At(x, m_map.GetXSize() - 2) = Floor(Floor::FORWARD, Floor::EAST);
        for (int x = 1; x < m_map.GetXSize() - 1; x++)
            m_map.At(x, 1) = Floor(Floor::FORWARD, Floor::WEST);
        m_map.At(1, m_map.GetXSize() - 2) = Floor(Floor::RIGHT, Floor::NORTH);
        m_map.At(m_map.GetXSize() - 2, m_map.GetXSize() - 2) = Floor(Floor::RIGHT, Floor::WEST);
        m_map.At(m_map.GetXSize() - 2, 1) = Floor(Floor::RIGHT, Floor::SOUTH);
        m_map.At(1, 1) = Floor(Floor::RIGHT, Floor::EAST);
        std::cout << m_map;

        // FULL MAP - TEMPORAL TEST
        for (int y = 2; y < m_map.GetYSize() - 2; y++)
            for (int x = 2; x < m_map.GetXSize() - 2; x++)
                m_map.At(x, y) = Floor(Floor::FORWARD, Floor::NORTH);

        m_pos = glm::ivec3(1, 5, 0);
        m_dir = Floor::NORTH;
    }

    void Update(FT::Feldespato & fdp, Player & player)
    {
        
    }

    void Draw(FT::Feldespato & fdp)
    {
        DrawMapPortion(fdp, m_pos, 2);
    }

private:
    /* Draws a portion of map with size=DEPTH using draw_pos as center point */
    void DrawMapPortion(FT::Feldespato& fdp, glm::ivec3 draw_pos, int depth = 2)
    {
        // TEMPORAL TEST
        if (fdp.GetKey(GLFW_KEY_J) == GLFW_PRESS && !m_rotating)
            m_pos += glm::vec3(-0.01, 0.0, 0.0);
        else if (fdp.GetKey(GLFW_KEY_L) == GLFW_PRESS && !m_rotating)
            m_pos += glm::vec3(0.01, 0.0, 0.0);
        if (fdp.GetKey(GLFW_KEY_I) == GLFW_PRESS && !m_rotating)
            m_pos += glm::vec3(0.0, 0.01, 0.0);
        else if (fdp.GetKey(GLFW_KEY_K) == GLFW_PRESS && !m_rotating)
            m_pos += glm::vec3(0.0, -0.01, 0.0);
        if (fdp.GetKey(GLFW_KEY_R) == GLFW_PRESS && !m_rotating)
            m_rotating = true;

        /* MAP ROTATION: TODO: this should not be in DRAW */
        /*  - The m_rotating flag can be check to not allow any movement during rotation */
        if (m_rotating)
        {
            m_rot_offset = glm::clamp(m_rot_offset + m_rot_speed, 0.0f, glm::half_pi<float>());
            if (m_rot_offset >= glm::half_pi<float>())
            {
                m_rot_offset = 0.0;
                m_rotating = false;
                m_total_rotation = glm::mod(m_total_rotation + glm::half_pi<float>(), glm::two_pi<float>());
            }
        }

        fdp.PushMatrix();
        fdp.Rotate(m_total_rotation + m_rot_offset, glm::vec3(0.0, 1.0, 0.0));
        fdp.Translate(-FLOOR_WIDTH * glm::vec3(-m_pos.x, 0.0, m_pos.y)); // TODO: CHECK WHY X-AXIS IS INVERTED
        // BRUTE FORCE DRAW
        for (int y_it = draw_pos.y - depth; y_it <= draw_pos.y + depth; y_it++)
        {
            for (int x_it = draw_pos.x - depth; x_it <= draw_pos.x + depth; x_it++)
            {
                if (!m_map.Exists(x_it, y_it)) continue;
                Floor::Type type = m_map.At(x_it, y_it).type;
                if (type == Floor::EMPTY) continue;

                fdp.PushMatrix();
                fdp.Translate(FLOOR_WIDTH * glm::vec3(-x_it, 0.0, y_it)); // TODO: CHECK WHY X-AXIS IS INVERTED
                fdp.Rotate(glm::half_pi<float>() * m_map.At(x_it, y_it).dir, glm::vec3(0.0, 1.0, 0.0));
                fdp.Draw(m_floor_types[type]);
                fdp.PopMatrix();
            }
        }
        fdp.PopMatrix();
    }
};