#pragma once

#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

#include "Floor.hpp"

class Trail
{
public:
    std::map<Floor::Type, Floor> m_floor_types;
    std::vector<Floor *> m_trail;
    const int m_visible_trail_length;
    FT::Transform m_tr;
    glm::vec3 m_dir;

    FT::Feldespato & m_fdp;
public:
    Trail(FT::Feldespato & fdp)
        : m_fdp(fdp), m_visible_trail_length(5), m_tr(), m_dir(0.0, 0.0, -0.01)
    {
        std::srand(static_cast<unsigned>(1234));
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/front.dae"), Floor::FORWARD);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right.dae"), Floor::RIGHT);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/left.dae"), Floor::LEFT);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right_left.dae"), Floor::RIGHT_LEFT);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right_left_front.dae"), Floor::RIGHT_LEFT_FORWARD);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right_front.dae"), Floor::RIGHT_FORWARD);
        AddFloorType(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/left_front.dae"), Floor::LEFT_FORWARD);
    }
    void AddFloorType(FT::Model model, Floor::Type type)
    {
        m_floor_types[type] = Floor(model, type);
    }
    /* Randomly generates the initial floor path */
    void Init()
    {
        for (int i = 0; i < m_visible_trail_length; i++)
            PushRandom(false);
    }

    /* Push a random floor type and removes the first (now not visible) */
    /* TODO: This shouldn't be completely random, some floors have preference */
    void PushRandom(bool remove_front = true)
    {
        Floor::Type new_floor = static_cast<Floor::Type>(std::rand() % Floor::Type::MAX_FLOOR_ID);
        if (m_floor_types.find(new_floor) == m_floor_types.end())
            return ;
        // m_trail.push(&(m_floor_types[new_floor]));
        m_trail.push_back(&(m_floor_types[Floor::FORWARD]));
        if (remove_front)
            m_trail.erase(m_trail.begin());
    }

    void Update()
    {
        // TODO: SPEED
        m_tr.pos += m_dir;
        // if (m_tr.pos.length() >= 4.0)
        // {
        //     m_tr.pos = glm::vec3(0.0);
        //     PushRandom();
        // }
    }

    void Draw()
    {
        Update();
        // aux_front_floor_tr.pos = glm::vec3(0.0, 0.0, 4.0);
        // aux_front_floor_tr.parent = front_floor_tr.GetTransform();
        // aux_right_floor_tr.pos = glm::vec3(0.0, 0.0, 4.0);
        // aux_right_floor_tr.parent = front_floor_tr.GetTransform() * aux_front_floor_tr.GetTransform();
        FT::Transform tr;
        tr.pos = glm::vec3(0.0, 0.0, 4.0);
        m_fdp.PushMatrix();
        m_fdp.Translate(m_tr.pos);
        for (int i = 0; i < m_trail.size(); i++)
        {
            // TODO: do this using fdp.Translate
            m_fdp.Draw(m_trail[i]->model, tr);
            tr.parent = tr.GetTransform();
        }
        m_fdp.PopMatrix();
    }
};