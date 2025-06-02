#pragma once

#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "FT.hpp"
#include "Floor.hpp"
#include "Player.hpp"
#include "Grid.hpp"

class MapRunner
{
public:
    std::map<Floor::Type, FT::Model> m_floor_types;
    std::shared_ptr<Grid> m_current_map;

    /* Player Score */
    unsigned int m_score;
    bool m_collision;
    bool m_col_passed;

    /* MAP MOVEMENT */
    glm::vec3 m_pos;
    glm::ivec3 m_current_tile;
    glm::ivec3 m_prev_tile;
    float m_tile_perc;
    float m_mov_speed;
    Floor::Direction m_dir;

    /* ROTATING ANIMATION */
    int m_rotating;
    bool m_rotated_tile;
    float m_rot_speed;
    float m_rot_offset;
    float m_total_rotation;

    /* UP/DOWN ANIMATION */
    int m_climbing;
    float m_climb_offset;

public:
    MapRunner(FT::Feldespato & fdp)
        : m_pos(0.0), m_current_tile(0), m_prev_tile(0), m_tile_perc(0.5), m_mov_speed(0.01), m_dir(Floor::NONE),
        m_rotating(0), m_rotated_tile(false), m_rot_speed(0.2), m_rot_offset(0.0), m_total_rotation(0.0),
        m_climbing(0),
        m_score(0), m_collision(false), m_col_passed(false)
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

    void Init(std::shared_ptr<Grid> map)
    {
        this->m_current_map = map;
        Reset();
    }

    void Reset()
    {
        m_pos = m_current_map->GetInitPos();
        m_dir = Floor::Direction(m_current_map->GetInitDir());
        m_current_tile = m_pos;
        m_prev_tile = m_pos;
        m_collision = false;
        m_score = 0;
        m_climbing = false;
        m_rotating = false;
        m_tile_perc = 0.5;
        m_rot_offset = 0.0;
        m_climb_offset = 0.0;
        m_total_rotation = 0.0;
        m_rotated_tile = 0.0;
    }

    void Update(FT::Feldespato & fdp, Player & player)
    {
        if (!m_current_map) return;
        //if (fdp.GetKey(GLFW_KEY_V) == GLFW_PRESS)
        //    m_climbing = 1;

        /* Moves the map constantly */
        if (!m_rotating)
        {
            m_pos += m_mov_speed * glm::vec3((m_dir == Floor::EAST) - (m_dir == Floor::WEST),
                                             (m_dir == Floor::NORTH) - (m_dir == Floor::SOUTH), 0.0);
            m_tile_perc += m_mov_speed;
            if (glm::ivec3(glm::round(m_pos)) != m_current_tile && m_tile_perc >= 0.9)
            {
                m_tile_perc = 0.0;
                m_rotated_tile = false;
                m_col_passed = false;
                m_current_map->RandomizeNextTiles();
            }
            m_current_tile.x = glm::round(m_pos.x);
            m_current_tile.y = glm::round(m_pos.y);
            m_current_tile.z = glm::round(m_pos.z);
        }

        /* Checks if the map needs to be climbed */
        if (!m_climbing)
        {
            if ((m_current_map->At(m_current_tile.x, m_current_tile.y, m_current_tile.z).type & Floor::Type::UP))
                m_climbing = 1;
            else if ((m_current_map->At(m_current_tile.x, m_current_tile.y, m_current_tile.z).type & Floor::Type::DOWN))
                m_climbing = -1;
            if (m_current_map->At(m_current_tile.x, m_current_tile.y, m_current_tile.z).dir != m_dir)
                m_climbing *= -1;
        }
        
        /* Checks if the map needs to be rotated */
        if ((m_current_map->At(m_current_tile).type & Floor::Type::RIGHT ||
            m_current_map->At(m_current_tile).type & Floor::Type::LEFT) && m_tile_perc >= 0.5)
        {
            switch (player.GetSide())
            {
            case Player::PlayerPosition::LEFT:
                m_rotating = -1;
                break;
            case Player::PlayerPosition::RIGHT:
                m_rotating = 1;
                break;
            }
        }

        /* Rotates de map */
        if (m_rotating && m_rotated_tile)
            m_rotating = 0;
        if (m_rotating)
        {
            m_rot_offset = glm::clamp(m_rot_offset + glm::sign(m_rotating) * m_rot_speed, -glm::half_pi<float>(), glm::half_pi<float>());
            if (glm::abs(m_rot_offset) >= glm::half_pi<float>())
            {
                m_total_rotation = glm::mod(m_total_rotation + glm::sign(m_rotating) * glm::half_pi<float>(), glm::two_pi<float>());
                double diff_aux = double(m_dir) + double(m_rotating);
                if (diff_aux < 0)
                    diff_aux = 4.0 + diff_aux;
                m_dir = Floor::Direction(glm::mod(diff_aux, 4.0));
                m_rotated_tile = true;
                m_rot_offset = 0.0;
                m_rotating = 0.0;

                m_pos.x = glm::round(m_pos.x);
                m_pos.y = glm::round(m_pos.y);
            }
        }

        /* Climbs de map */
        if (m_climbing)
        {
            m_climb_offset += glm::sign(m_climbing) * m_mov_speed;
            m_pos.z = m_pos.z + glm::sign(m_climbing) * m_mov_speed;
            if (glm::abs(m_climb_offset) >= 1.0)
            {
                m_pos.z = glm::round(m_pos.z);
                m_climb_offset = 0.0;
                m_climbing = 0.0;
            }
        }

        /* Updates Player Score */
        if (m_tile_perc == 0.0)
        {
            if (!m_current_map->Exists(m_current_tile) || m_current_map->At(m_current_tile).type == Floor::Type::EMPTY)
                m_collision = true;
            else if (!m_collision)
                m_score++;
        }

        // TODO: ADD HIGH OBSTACLES AND THE PLAYER CAN CROUCH
        /* Checks player collision */
        Floor floor = m_current_map->At(m_current_tile);
        int left_obstacle = 0;
        int right_obstacle = 2;
        int middle_obstacle = 1;
        if (floor.dir == m_dir)
        {
            left_obstacle = 2;
            right_obstacle = 0;
        }
        if (m_tile_perc >= 0.5 && !m_col_passed)
        {
            if (player.IsJumping())
                m_col_passed = true;
            else
            {
                switch (player.GetSide())
                {
                case Player::LEFT:
                    if (floor.obstacles[left_obstacle] != 0)
                        m_collision = true;
                    break;
                case Player::RIGHT:
                    if (floor.obstacles[right_obstacle] != 0)
                        m_collision = true;
                    break;
                case Player::MIDDLE:
                    if (floor.obstacles[middle_obstacle] != 0)
                        m_collision = true;
                    break;
                }
                m_col_passed = true;
            }
        }
        //if (m_tile_perc == 0.0)
        //    std::cout << "Score: " << m_score << std::endl;
        //if (m_collision)
        //    Reset();
    }

    unsigned int GetScore() const
    {
        return (m_score);
    }

    bool GetCollision() const
    {
        return (m_collision);
    }

    void Draw(FT::Feldespato& fdp)
    {
        if (!m_current_map) return;
        fdp.PushMatrix();
        fdp.Rotate(m_total_rotation + m_rot_offset, glm::vec3(0.0, 1.0, 0.0));
        fdp.Translate(-FLOOR_WIDTH * glm::vec3(-m_pos.x, 0.0, m_pos.y)); // TODO: CHECK WHY X-AXIS IS INVERTED
        fdp.Translate(-FLOOR_HEIGHT * glm::vec3(0.0, m_pos.z, 0.0)); // TODO: CHECK WHY X-AXIS IS INVERTED
        DrawMapPortion(m_current_map, fdp, m_current_tile, glm::ivec3(2));
        fdp.PopMatrix();
    }

    /* Draws a portion of map with size=DEPTH using draw_pos as center point */
    void DrawMapPortion(std::shared_ptr<Grid> map, FT::Feldespato& fdp, glm::ivec3 draw_pos, glm::ivec3 depth = glm::ivec3(0))
    {
        glm::ivec3 depth_from(draw_pos - depth);
        glm::ivec3 depth_to(draw_pos + depth);
        if (depth == glm::ivec3(0))
        {
            depth_from = glm::ivec3(0);
            depth_to = glm::ivec3(map->GetXSize(), map->GetYSize(), map->GetZSize());
        }
        for (int z_it = depth_from[2]; z_it < depth_to[2]; z_it++)
        {
            for (int y_it = depth_from[1]; y_it < depth_to[1]; y_it++)
            {
                for (int x_it = depth_from[0]; x_it < depth_to[0]; x_it++)
                {
                    if (!map->Exists(x_it, y_it, z_it)) continue;
                    Floor floor = map->At(x_it, y_it, z_it);
                    if (floor.type == Floor::EMPTY) continue;
                    if (!floor.visible) continue;

                    fdp.PushMatrix();
                    fdp.Translate(FLOOR_WIDTH * glm::vec3(-x_it, 0, y_it) + FLOOR_HEIGHT * glm::vec3(0, z_it, 0)); // TODO: CHECK WHY X-AXIS IS INVERTED
                    fdp.Rotate(glm::half_pi<float>() * map->At(x_it, y_it, z_it).dir, -glm::vec3(0.0, 1.0, 0.0));
                    fdp.Draw(m_floor_types[floor.type]);
                    for (int slot = -1; slot <= 1; slot++)
                    {
                        if (floor.obstacles[slot + 1])
                        {
                            fdp.PushMatrix();
                            fdp.Translate(glm::vec3(double(slot) * FLOOR_WIDTH / 3.0, 0.0, 0.0));
                            fdp.Cube(FT::Transform{ 0.5 });
                            fdp.PopMatrix();
                        }
                    }
                    fdp.PopMatrix();
                }
            }
        }
    }

    std::shared_ptr<Grid> ReadMap(const std::string& path)
    {
        std::fstream file(path);
        std::istringstream ss;
        std::string word;
        std::string line;
        std::map<char, Floor::Direction> aux_dirs;
        aux_dirs['N'] = Floor::Direction::NORTH;
        aux_dirs['E'] = Floor::Direction::EAST;
        aux_dirs['S'] = Floor::Direction::SOUTH;
        aux_dirs['W'] = Floor::Direction::WEST;

        // THE FIRST LINE SPECIFY THE SIZE
        bool visible = 1;
        Floor::Direction dir = Floor::Direction::NORTH;
        Floor::Type type = Floor::Type::FORWARD;
        glm::ivec3 pos;
        // READ MAP SIZE
        int x_size, y_size, z_size;
        int x_loop, y_loop, z_loop;
        std::getline(file, line);
        ss = std::istringstream(line);
        ss >> word; x_loop = (word[0] == 'T'); x_size = std::stoi(&word[1]);
        ss >> word; y_loop = (word[0] == 'T'); y_size = std::stoi(&word[1]);
        ss >> word; z_loop = (word[0] == 'T'); z_size = std::stoi(&word[1]);
        std::shared_ptr<Grid> map = std::make_shared<Grid>(x_size, y_size, z_size, x_loop, y_loop, z_loop);
        std::vector<glm::ivec3> random_pos;
        std::getline(file, line);
        ss = std::istringstream(line);
        ss >> word;
        // EXTRACT RANDOM POINT
        bool random = false;
        while (word[0] == 'R')
        {
            random = true;
            glm::ivec3 ran;
            ss >> word; ran.x = std::stoi(&word[0]);
            ss >> word; ran.y = std::stoi(&word[0]);
            ss >> word; ran.z = std::stoi(&word[0]);
            random_pos.push_back(ran);
            std::getline(file, line);
            ss = std::istringstream(line);
            ss >> word;
        }
        if (random)
            map->SetRandomMap({ glm::ivec3(2, 4, 2) });
        // READ INIT POS AND DIR
        dir = aux_dirs[word[0]];
        ss >> word; pos.x = std::stoi(word);
        ss >> word; pos.y = std::stoi(word);
        ss >> word; pos.z = std::stoi(word);
        map->SetInitDir(dir);
        map->SetInitPos(pos);

        int x_it = 0, y_it = 0, z_it = 0;
        while (std::getline(file, line))
        {
            if (line.empty())
            {
                z_it++;
                y_it = 0;
            }
            else
            {
                ss = std::istringstream(line);
                while (ss >> word)
                {
                    map->At(x_it, y_it, z_it) = Floor(Floor::EMPTY, Floor::NONE);
                    if (word[0] != '0')
                    {
                        dir = aux_dirs[word[0]];
                        visible = (word[1] == 'T');
                        type = Floor::Type(std::atoi(&word[2]));
                        Floor floor(type, dir, visible);
                        map->At(x_it, y_it, z_it) = floor;
                    }
                    x_it++;
                }
                y_it++;
            }
            x_it = 0;
        }
        return map;
    }
};