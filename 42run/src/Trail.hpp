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

class Trail
{
public:
    std::map<Floor::Type, Floor> m_floor_types;
    std::vector<Floor *> m_trail;
    int m_visible_trail_length;
    glm::vec3 m_pos;
    glm::vec3 m_dir;
    float m_speed;
    float m_rot;
    float m_rot_offset;

public:
    Trail(FT::Feldespato & fdp)
        : m_rot(0), m_rot_offset(0), m_pos(0.0), m_speed(0.05), m_dir(0.0, 0.0, -1.0)
    {
        std::srand(static_cast<unsigned>(1234));
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/front.dae"), Floor::FORWARD);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right.dae"), Floor::RIGHT);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/left.dae"), Floor::LEFT);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right_left.dae"), Floor::RIGHT_LEFT);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right_left_front.dae"), Floor::RIGHT_LEFT_FORWARD);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right_front.dae"), Floor::RIGHT_FORWARD);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/left_front.dae"), Floor::LEFT_FORWARD);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/front_up.dae"), Floor::UP);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/front_down.dae"), Floor::DOWN);
    }
    void AddFloorType(FT::Model model, Floor::Type type)
    {
        m_floor_types[type] = Floor(model, type);
    }
    /* Randomly generates the initial floor path */
    void Init()
    {
        //for (int i = 0; i < m_visible_trail_length; i++)
            //m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::RIGHT]));
        m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::RIGHT]));
        m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::RIGHT]));
        m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        m_trail.push_back(&(m_floor_types[Floor::Type::RIGHT]));
        m_visible_trail_length = 3;
    }

    /* Push a random floor type and removes the first (now not visible) */
    /* TODO: This shouldn't be completely random, some floors have preference */
    void PushRandom()
    {
        //std::vector<Floor::Type> tmp_test = { Floor::FORWARD, Floor::RIGHT, Floor::LEFT, Floor::UP, Floor::DOWN, Floor::RIGHT_FORWARD, Floor::LEFT_FORWARD, Floor::RIGHT_LEFT, Floor::RIGHT_LEFT_FORWARD, Floor::MAX_FLOOR_ID };

        //Floor::Type new_floor = tmp_test[std::rand() % (Floor::Type::MAX_FLOOR_ID - 1) + 1];
        //std::cout << "NF: " << new_floor << std::endl;
        //if (m_floor_types.find(new_floor) == m_floor_types.end())
        //    return ;
        //m_trail.push_back(&(m_floor_types[new_floor]));
        //for (int i = 0; i < m_new_floors - 1; i++)
        //    m_trail.push_back(&(m_floor_types[Floor::Type::FORWARD]));
        //m_trail.erase(m_trail.begin(), m_trail.begin() + m_new_floors);
    }

    void Update(PlayerPosition p)
    {
        float len = glm::length(m_pos);
        m_pos += (m_dir * m_speed);
        if (len >= FLOOR_WIDTH)
        {
            m_pos += glm::vec3(0.0, 0.0, FLOOR_WIDTH);
            std::rotate(m_trail.begin(), m_trail.begin() + 1, m_trail.end());
            //PushRandom();
        }
        if (m_trail[0]->type == Floor::RIGHT)
        {
            if (len < FLOOR_WIDTH / 2.0)
                m_rot = m_rot_offset + (len / FLOOR_WIDTH) * glm::pi<float>();
            else
                m_rot_offset = m_rot;
        }
    }

    void Draw(FT::Feldespato & fdp, PlayerPosition p)
    {
        Update(p);
        fdp.Rotate(m_rot, glm::vec3(0.0, 1.0, 0.0));
        fdp.PushMatrix();
        fdp.Translate(glm::vec3(0.0, 0.0, -FLOOR_WIDTH / 2.0));

        // At this point the Origin is under player at index [1]
        fdp.Translate(m_pos);
        fdp.PushMatrix();
        for (int i = 0; i < m_visible_trail_length; i++)
        {
            fdp.Translate(glm::vec3(0.0, 0.0, FLOOR_WIDTH));
            fdp.Draw(m_trail[i]->model);
        }
        fdp.PopMatrix();
        fdp.PopMatrix();
    }
};