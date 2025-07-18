#pragma once

#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream>

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
    unsigned int m_distance;
    unsigned int m_score;
    bool m_collision;
    bool m_col_passed;
    float m_obstacle_width;
    float m_obstacle_height;

    /* MAP MOVEMENT */
    FT::vec3 m_pos;
    FT::ivec3 m_current_tile;
    FT::ivec3 m_prev_tile;
    FT::ivec3 m_prev2_tile;
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
    int m_climbed_tile;
    int m_climbing;
    float m_climb_perc;
    float m_climb_offset;

    /* Obstacles / Collectables */
    std::vector<FT::Model> m_obstacles;
    FT::Model m_collectable;
    float m_collectable_rot;

    /* PROPS */
    FT::Model m_cluster;

public:
    MapRunner(FT::Feldespato & fdp)
        : m_pos(0.0), m_current_tile(0), m_prev_tile(0), m_prev2_tile(0), m_tile_perc(0.5), m_dir(Floor::NONE),
        m_rotating(0), m_rotated_tile(false), m_rot_offset(0.0), m_total_rotation(0.0),
        m_climbing(0), m_climbed_tile(false), m_climb_perc(0.25),
        m_distance(0), m_collision(false), m_col_passed(false), m_obstacle_width(0.05), m_obstacle_height(0.75),
        m_mov_speed(2.0), m_rot_speed(30.0), m_collectable_rot(0.0)
    {
        m_floor_types[Floor::FORWARD] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/front.obj");
        m_floor_types[Floor::RIGHT] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right.obj");
        m_floor_types[Floor::RIGHT_LEFT] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right_left.obj");
        m_floor_types[Floor::RIGHT_LEFT_FORWARD] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/right_left_front.obj");
        m_floor_types[Floor::UP] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/front_up.obj");
        m_floor_types[Floor::DOWN] = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/floor/front_down.obj");

        m_collectable = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/coin/coin.obj");
        m_cluster = fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/cluster/cluster.obj");

        // TODO: make this a map or something
        m_obstacles.push_back(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/obstacles/low/fence/fence.obj"));
        m_obstacles.push_back(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/obstacles/low/fence2/fence2.obj"));
        m_obstacles.push_back(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/obstacles/low/fence3/fence3.obj"));
        m_obstacles.push_back(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/obstacles/high/column/column.obj"));
        m_obstacles.push_back(fdp.LoadModel(SANDBOX_ASSETS_DIRECTORY"/obstacles/high/column2/column2.obj"));
    }

    void Init(std::shared_ptr<Grid> map)
    {
        this->m_current_map = map;
        Reset();
    }

    void Reset()
    {
        m_pos = FT::vec3(m_current_map->GetInitPos());
        m_dir = Floor::Direction(m_current_map->GetInitDir());
        m_current_tile = m_pos;
        m_prev_tile = m_pos;
        m_prev2_tile = m_prev_tile;
        m_collision = false;
        m_distance = 0;
        m_score = 0;
        m_climbing = false;
        m_rotating = false;
        m_tile_perc = 0.5;
        m_rot_offset = 0.0;
        m_climb_offset = 0.0;
        m_total_rotation = 0.0;
        m_rotated_tile = 0.0;
        m_collectable_rot = 0.0;
        m_current_map->Reset();
    }

    void Update(FT::Feldespato & fdp, Player & player, float delta_time)
    {
        float final_mov_speed = m_mov_speed * delta_time;
        float final_rot_speed = m_rot_speed * delta_time;
        m_collectable_rot += 5.0 * delta_time;

        if (!m_current_map) return;

        /* Moves the map constantly */
        if (!m_rotating)
        {
            m_pos += final_mov_speed * FT::vec3((m_dir == Floor::EAST) - (m_dir == Floor::WEST),
                                             (m_dir == Floor::NORTH) - (m_dir == Floor::SOUTH), 0.0);
            m_tile_perc += final_mov_speed;
            if (FT::ivec3(FT::round(m_pos)) != m_current_tile && m_tile_perc >= 0.9)
            {
                m_tile_perc = 0.0;
                m_rotated_tile = false;
                m_climbed_tile = false;
                m_col_passed = false;
                m_prev2_tile = m_prev_tile;
                m_prev_tile = m_current_tile;
                m_current_map->RandomizeNextTiles(FT::ivec3(FT::round(m_pos.x), FT::round(m_pos.y), FT::round(m_pos.z)), m_prev2_tile);
            }
            m_current_tile.x = FT::round(m_pos.x);
            m_current_tile.y = FT::round(m_pos.y);
            m_current_tile.z = FT::round(m_pos.z);
        }

        /* Checks if the map needs to be climbed */
        if (!m_climbing && m_tile_perc >= (0.5 - m_climb_perc/2.0))
        {
            if ((m_current_map->At(m_current_tile.x, m_current_tile.y, m_current_tile.z).type == Floor::Type::UP))
                m_climbing = 1;
            else if ((m_current_map->At(m_current_tile.x, m_current_tile.y, m_current_tile.z).type == Floor::Type::DOWN))
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
            m_rot_offset = FT::clamp(m_rot_offset + FT::sign(m_rotating) * final_rot_speed, -FT::HALF_PI, FT::HALF_PI);
            if (FT::abs(m_rot_offset) >= FT::HALF_PI)
            {
                m_total_rotation = FT::mod(m_total_rotation + FT::sign(m_rotating) * FT::HALF_PI, FT::TWO_PI);
                int diff_aux = m_dir + m_rotating;
                if (diff_aux < 0)
                    diff_aux = 4 + diff_aux;
                m_dir = Floor::Direction(FT::mod(diff_aux, 4));
                m_rotated_tile = true;
                m_rot_offset = 0.0;
                m_rotating = 0.0;

                m_pos.x = FT::round(m_pos.x);
                m_pos.y = FT::round(m_pos.y);
            }
        }

        if (m_climbing && m_climbed_tile)
            m_climbing = 0;
        /* Climbs de map */
        if (m_climbing)
        {
            m_climb_offset += FT::sign(m_climbing) * (final_mov_speed / (m_climb_perc));
            m_pos.z = m_pos.z + FT::sign(m_climbing) * (final_mov_speed / (m_climb_perc));
            if (FT::abs(m_climb_offset) >= 1.0)
            {
                m_pos.z = FT::round(m_pos.z);
                m_climb_offset = 0.0;
                m_climbing = 0.0;
                m_climbed_tile = true;
            }
        }

        /* Updates Player Score */
        if (m_tile_perc == 0.0)
        {
            if (!m_current_map->Exists(m_current_tile) || m_current_map->At(m_current_tile).type == Floor::Type::EMPTY)
                m_collision = true;
            else if (!m_collision)
                m_distance++;
        }

        /* Checks player collision */
        Floor& floor = m_current_map->At(m_current_tile);
        int left = 0;
        int right = 2;
        int middle = 1;
        if (floor.dir == m_dir)
        {
            left = 2;
            right = 0;
        }
        if (m_tile_perc >= 0.5 && !m_col_passed)
        {
            switch (player.GetSide())
            {
            case Player::LEFT:
                if (floor.obstacles[left] == Floor::Obstacle::WALL ||
                    (floor.obstacles[left] == Floor::Obstacle::FENCE && !(player.GetJumpPerc() >= m_obstacle_height)))
                    m_collision = true;
                if (floor.collectables[left] && !(player.GetJumpPerc() >= m_obstacle_height))
                {
                    m_score++;
                    floor.collectables[left] = false;
                }
                break;
            case Player::RIGHT:
                if (floor.obstacles[right] == Floor::Obstacle::WALL ||
                    (floor.obstacles[right] == Floor::Obstacle::FENCE && !(player.GetJumpPerc() >= m_obstacle_height)))
                    m_collision = true;
                if (floor.collectables[right] && !(player.GetJumpPerc() >= m_obstacle_height))
                {
                    m_score++;
                    floor.collectables[right] = false;
                }
                break;
            case Player::MIDDLE:
                if (floor.obstacles[middle] == Floor::Obstacle::WALL ||
                    (floor.obstacles[middle] == Floor::Obstacle::FENCE && !(player.GetJumpPerc() >= m_obstacle_height)))
                    m_collision = true;
                if (floor.collectables[middle] && !(player.GetJumpPerc() >= m_obstacle_height))
                {
                    m_score++;
                    floor.collectables[middle] = false;
                }
                break;
            }
            if (m_tile_perc >= 0.5 + m_obstacle_width)
                m_col_passed = true;
        }
    }

    unsigned int GetDistance() const
    {
        return (m_distance);
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
        fdp.RotateY(-m_total_rotation - m_rot_offset);
        fdp.Translate(-FLOOR_DEPTH * FT::vec3(-m_pos.x, 0.0, m_pos.y)); // TODO: CHECK WHY X-AXIS IS INVERTED
        fdp.Translate(-FLOOR_HEIGHT * FT::vec3(0.0, m_pos.z, 0.0)); // TODO: CHECK WHY X-AXIS IS INVERTED
        DrawMapPortion(m_current_map, fdp, m_current_tile, FT::ivec3(5));
        fdp.PopMatrix();
    }

    /* Draws a portion of map with size=DEPTH using draw_pos as center point */
    void DrawMapPortion(std::shared_ptr<Grid> map, FT::Feldespato& fdp, FT::ivec3 draw_pos, FT::ivec3 depth = FT::ivec3(0))
    {
        FT::ivec3 depth_from(draw_pos - depth);
        FT::ivec3 depth_to(draw_pos + depth);
        if (depth == FT::ivec3(0))
        {
            depth_from = FT::ivec3(0);
            depth_to = FT::ivec3(map->GetXSize(), map->GetYSize(), map->GetZSize());
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
                    fdp.Translate(FLOOR_DEPTH * FT::vec3(-x_it, 0, y_it) + FLOOR_HEIGHT * FT::vec3(0, z_it, 0)); // TODO: CHECK WHY X-AXIS IS INVERTED
                    fdp.RotateY(FT::HALF_PI * map->At(x_it, y_it, z_it).dir);
                    DrawFloor(fdp, floor);
                    fdp.PopMatrix();
                }
            }
        }
    }

    void DrawFloor(FT::Feldespato& fdp, Floor floor)
    {
        Floor::Type type = floor.type;
        fdp.PushMatrix();
        switch (type)
        {
        case Floor::LEFT:
            type = Floor::RIGHT;
            fdp.RotateY(FT::HALF_PI);
            break;
        case Floor::RIGHT_FORWARD:
            type = Floor::RIGHT_LEFT;
            fdp.RotateY(-FT::HALF_PI);
            break;
        case Floor::LEFT_FORWARD:
            type = Floor::RIGHT_LEFT;
            fdp.RotateY(FT::HALF_PI);
            break;
        };
        if (type == Floor::FORWARD)
            fdp.Draw(m_cluster);
        fdp.Draw(m_floor_types[type]);
        fdp.PopMatrix();
        DrawObstacles(fdp, floor);
        DrawCollectables(fdp, floor);
    }

    void DrawObstacles(FT::Feldespato& fdp, Floor floor)
    {
        Floor::Obstacle obs = floor.obstacles[0];
        Floor::Obstacle obs1 = floor.obstacles[1];
        Floor::Obstacle obs2 = floor.obstacles[2];
        for (int slot = -1; slot <= 1; slot++)
        {
            if (obs == Floor::Obstacle::FENCE && obs == obs1 && obs == obs2)
            { // SIZE THREE FENCE
                fdp.Draw(m_obstacles[2]);
                return;
            }
            else if (obs == Floor::Obstacle::FENCE && obs == obs1)
            { // SIZE TWO FENCE
                fdp.PushMatrix();
                fdp.Translate(FT::vec3(double(slot) * WALK_FLOOR_WIDTH, 0.0, 0.0));
                fdp.Draw(m_obstacles[1]);
                fdp.PopMatrix();
                obs = obs1; obs1 = obs2; obs2 = Floor::Obstacle::FREE;
                slot += 1;

            }
            else if (obs == Floor::Obstacle::WALL && obs == obs1)
            { // SIZE TWO WALL
                fdp.PushMatrix();
                fdp.Translate(FT::vec3(double(slot) * WALK_FLOOR_WIDTH, 0.0, 0.0));
                fdp.Draw(m_obstacles[4]);
                fdp.PopMatrix();
                obs = obs1; obs1 = obs2; obs2 = Floor::Obstacle::FREE;
                slot += 1;
            }
            else if (obs == Floor::Obstacle::FENCE)
            { // NORMAL FENCE
                fdp.PushMatrix();
                fdp.Translate(FT::vec3(double(slot) * WALK_FLOOR_WIDTH, 0.0, 0.0));
                fdp.Draw(m_obstacles[0]);
                fdp.PopMatrix();
            }
            else if (obs == Floor::Obstacle::WALL)
            { // NORMAL WALL
                fdp.PushMatrix();
                fdp.Translate(FT::vec3(double(slot) * WALK_FLOOR_WIDTH, 0.0, 0.0));
                fdp.Draw(m_obstacles[3]);
                fdp.PopMatrix();
            }
            obs = obs1;
            obs1 = obs2;
            obs2 = Floor::Obstacle::FREE;
        }
    }

    void DrawCollectables(FT::Feldespato& fdp, Floor floor)
    {
        for (int slot = -1; slot <= 1; slot++)
        {
            if (floor.collectables[slot + 1])
            {
                float scale = 0.25;
                fdp.PushMatrix();
                fdp.Translate(FT::vec3(double(slot) * (WALK_FLOOR_WIDTH / scale) / 3.0, 0.0, 0.0));
                fdp.RotateY(m_collectable_rot);
                fdp.Draw(m_collectable, FT::Transform(scale));
                fdp.PopMatrix();
            }
        }
    }

    static std::shared_ptr<Grid> ReadMap(const std::string& path)
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
        FT::ivec3 pos;
        // READ MAP SIZE
        int x_size, y_size, z_size;
        int x_loop, y_loop, z_loop;
        std::getline(file, line);
        ss = std::istringstream(line);
        ss >> word; x_loop = (word[0] == 'T'); x_size = std::stoi(&word[1]);
        ss >> word; y_loop = (word[0] == 'T'); y_size = std::stoi(&word[1]);
        ss >> word; z_loop = (word[0] == 'T'); z_size = std::stoi(&word[1]);
        std::shared_ptr<Grid> map = std::make_shared<Grid>(x_size, y_size, z_size, x_loop, y_loop, z_loop);
        // READ INIT POS AND DIR
        std::getline(file, line);
        ss = std::istringstream(line);
        ss >> word;
        dir = aux_dirs[word[0]];
        ss >> word; pos.x = std::stoi(word);
        ss >> word; pos.y = std::stoi(word);
        ss >> word; pos.z = std::stoi(word);
        map->SetInitDir(dir);
        map->SetInitPos(pos);
        // EXTRACT RANDOM POINT
        std::getline(file, line);
        ss = std::istringstream(line);
        ss >> word;
        if (word[0] == 'R')
            map->SetRandomMap();

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
                        Floor floor(type, dir, true, visible);
                        if (x_it == pos.x && y_it == pos.y && z_it == pos.z)
                            floor.EnableObstacles(false);
                        map->At(x_it, y_it, z_it) = floor;
                        if (map->IsRandom())
                            map->PushToBranch(FT::ivec3(x_it, y_it, z_it), MAIN_BRANCH);
                    }
                    x_it++;
                }
                y_it++;
            }
            x_it = 0;
        }
        return map;
    }

    static std::shared_ptr<Grid> RandomMap()
    {
        std::shared_ptr<Grid> grid = std::make_shared<Grid>(11, 11, 11, true, true, true);
        grid->SetRandomMap();
        grid->SetInitDir(Floor::NORTH);
        grid->SetInitPos(FT::ivec3(5, 5, 5));
        for (int i = 0; i < 6; i++)
        {
            grid->At(5, 5 + i, 5) = Floor(Floor::FORWARD, Floor::NORTH, false, true);
            grid->PushToBranch(FT::ivec3(5, 5 + i, 5), MAIN_BRANCH);
        }
        return (grid);
    }
};