#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>

class Grid
{
private:
    bool m_x_loop;
    bool m_y_loop;
    bool m_z_loop;

    int m_x_size;
    int m_y_size;
    int m_z_size;
    int m_size;
    Floor* m_grid;

    bool m_random;
    std::vector<glm::ivec3> m_branches[3];
    bool m_active_branches;
    glm::ivec3 m_init_pos;
    int m_init_dir;
public:
    Grid(const Grid& grid)
        : m_y_size(grid.m_y_size), m_x_size(grid.m_x_size), m_z_size(grid.m_z_size), m_size(grid.m_size),
        m_x_loop(grid.m_x_loop), m_y_loop(grid.m_y_loop), m_z_loop(grid.m_z_loop),
        m_init_pos(grid.m_init_pos), m_init_dir(grid.m_init_dir), m_random(grid.m_random), m_active_branches(grid.m_active_branches)
    {
        m_grid = new Floor[m_size];
        std::memcpy(m_grid, grid.m_grid, m_size * sizeof(Floor));
    }
    Grid(int x_size, int y_size, int z_size = 1, bool x_loop = true, bool y_loop = true, bool z_loop = true)
        : m_y_size(y_size), m_x_size(x_size), m_z_size(z_size), m_size(x_size* y_size* z_size),
        m_x_loop(x_loop), m_y_loop(y_loop), m_z_loop(z_loop), m_random(false),
        m_init_pos(0), m_init_dir(0), m_active_branches(0)
    {
        m_grid = new Floor[m_size];
        std::memset(m_grid, 0, m_size * sizeof(Floor));
    }
    ~Grid()
    {
        delete[] m_grid;
    }
    bool Exists(int x, int y, int z = 0)
    {
        if ((x < 0 || x >= m_x_size) && !m_x_loop)
            return (false);
        if ((y < 0 || y >= m_y_size) && !m_y_loop)
            return (false);
        if ((z < 0 || z >= m_z_size) && !m_z_loop)
            return (false);
        return (true);
    }
    bool Exists(glm::ivec3 v)
    {
        return (Exists(v.x, v.y, v.z));
    }
    Floor& At(int x, int y, int z)
    {
        if (!m_x_loop)
        {
            if (x < 0) x = 0;
            if (x > m_x_size) x = m_x_size - 1;
        }
        if (!m_y_loop)
        {
            if (y < 0) y = 0;
            if (y > m_y_size) y = m_y_size - 1;
        }
        if (!m_z_loop)
        {
            if (z < 0) z = 0;
            if (z > m_z_size) z = m_z_size - 1;
        }
        if (x < 0) x = m_size - (glm::abs(x) % m_size);
        if (y < 0) y = m_size - (glm::abs(y) % m_size);
        if (z < 0) z = m_size - (glm::abs(z) % m_size);
        x %= m_x_size;
        y %= m_y_size;
        z %= m_z_size;
        return (m_grid[z * (m_y_size * m_x_size) + y * m_x_size + x]);
    }
    const Floor& At(int x, int y, int z) const
    {
        if (!m_x_loop)
        {
            if (x < 0) x = 0;
            if (x > m_x_size) x = m_x_size - 1;
        }
        if (!m_y_loop)
        {
            if (y < 0) y = 0;
            if (y > m_y_size) y = m_y_size - 1;
        }
        if (!m_z_loop)
        {
            if (z < 0) z = 0;
            if (z > m_z_size) z = m_z_size - 1;
        }
        if (x < 0) x = m_size - (glm::abs(x) % m_size);
        if (y < 0) y = m_size - (glm::abs(y) % m_size);
        if (z < 0) z = m_size - (glm::abs(z) % m_size);
        x %= m_x_size;
        y %= m_y_size;
        z %= m_z_size;
        return (m_grid[z * m_size + y * m_x_size + x]);
    }
    Floor& At(int x, int y)
    {
        return (At(x, y, 0));
    }
    const Floor& At(int x, int y) const
    {
        return (At(x, y, 0));
    }
    Floor& At(glm::ivec3 v)
    {
        return (At(v.x, v.y, v.z));
    }
    const Floor& At(glm::ivec3 v) const
    {
        return (At(v.x, v.y, v.z));
    }
    int GetXSize() const { return (m_x_size); }
    int GetYSize() const { return (m_y_size); }
    int GetZSize() const { return (m_z_size); }

    void SetInitPos(glm::ivec3 pos)
    {
        m_init_pos = pos;
    }

    void SetInitDir(int dir)
    {
        m_init_dir = 0;
    }

    void SetRandomMap()
    {
        m_random = true;
    }

    bool IsRandom() const
    {
        return (m_random);
    }

    void PushToMainBranch(glm::ivec3 init_random_tile)
    {
        m_branches[0].push_back(init_random_tile);
    }

    glm::ivec3 GetInitPos() const { return (m_init_pos); }
    int GetInitDir() const { return (m_init_dir); }

    // TODO: REMOVE OLDER TILES NO LONGER NEEDED
    //       REMOVE ALL TILES M_BRANCHES HAS
    void RandomizeNextTiles(glm::ivec3 player_tile, glm::ivec3 prev_player_tile)
    {
        // Delete previous player tile (it is no longer visible)
        //At(prev_player_tile).dir = Floor::NONE;
        //At(prev_player_tile).type = Floor::EMPTY;
        // If player_tile equals the first element of one of the branchs, the other two are deleted
        if (!m_random) return;
        for (int i = 0; i < 3; i++)
        {
            if (m_branches[i].empty()) continue;
            if (player_tile == m_branches[i].front())
            {
                glm::ivec3 tmp_branch = m_branches[i].front();
                for (int j = 0; j < 3; j++)
                {
                    if (j != i)
                    {
                        for (glm::ivec3 & pos : m_branches[j])
                        {
                            At(pos).type = Floor::EMPTY;
                            At(pos).dir = Floor::NONE;
                        }
                    }
                    m_branches[j].clear();
                }
                m_branches[0].push_back(tmp_branch);
                m_active_branches = false;
                break;
            }
        }
        glm::ivec3 left_tile = glm::ivec3(0);
        glm::ivec3 front_tile = glm::ivec3(0);
        glm::ivec3 right_tile = glm::ivec3(0);
        // Check if the branch exists
        for (int i = 0; i < 3; i++)
        {
            if (m_branches[i].empty()) continue;
            glm::ivec3 tile = m_branches[i].back();
            Floor f = At(tile);
            // The last element of the branch is the one we need to check
            switch (f.dir)
            {
            case Floor::NORTH:
                left_tile = glm::ivec3(-1, 0, 0);
                front_tile = glm::ivec3(0, 1, 0);
                right_tile = glm::ivec3(1, 0, 0);
                break;
            case Floor::EAST:
                left_tile = glm::ivec3(0, 1, 0);
                front_tile = glm::ivec3(1, 0, 0);
                right_tile = glm::ivec3(0, -1, 0);
                break;
            case Floor::SOUTH:
                left_tile = glm::ivec3(1, 0, 0);
                front_tile = glm::ivec3(0, -1, 0);
                right_tile = glm::ivec3(-1, 0, 0);
                break;
            case Floor::WEST:
                left_tile = glm::ivec3(0, -1, 0);
                front_tile = glm::ivec3(-1, 0, 0);
                right_tile = glm::ivec3(0, 1, 0);
                break;
            }
            Floor::Type new_type;
            if (f.type & Floor::FORWARD)
            {
                tile += front_tile;
                if (f.type == Floor::UP)
                    tile += glm::ivec3(0, 0, 1);
                if (f.type == Floor::DOWN)
                    tile += glm::ivec3(0, 0, -1);
                if (m_active_branches)
                {
                    new_type = Floor::FORWARD; // ALWAYS FORWARD IF ACTIVE BRANCHES
                    m_branches[i].push_back(tile);
                    At(tile) = Floor(new_type, f.dir, true);
                }
                else
                {
                    RandomizeOneTile(tile, f.dir, left_tile, front_tile, right_tile);
                    m_active_branches = true;
                    break;
                }
            }
            if (f.type & Floor::RIGHT)
            {
                tile += right_tile;
                new_type = Floor::FORWARD; // ALWAYS FORWARD
                Floor::Direction right_dir = Floor::Direction((f.dir + 1) % Floor::Direction::NONE);
                m_branches[i].push_back(tile);
                At(tile) = Floor(new_type, right_dir, true);
            }
            if (f.type & Floor::LEFT)
            {
                tile += left_tile;
                
                new_type = Floor::FORWARD; // ALWAYS FORWARD
                m_branches[i].push_back(tile);
                Floor::Direction left_dir = Floor::Direction((f.dir - 1) % Floor::Direction::NONE);
                if (left_dir < Floor::NORTH) left_dir = Floor::Direction(left_dir + Floor::NONE);
                At(tile) = Floor(new_type, left_dir, true);
            }
        }
    }

    void RandomizeOneTile(glm::ivec3 tile, Floor::Direction dir, glm::ivec3 left_tile, glm::ivec3 front_tile, glm::ivec3 right_tile)
    {
        Floor::Direction front_dir = dir;
        Floor::Direction right_dir = Floor::Direction((dir + 1) % Floor::Direction::NONE);
        Floor::Direction left_dir = Floor::Direction((dir - 1) % Floor::Direction::NONE);
        if (left_dir < Floor::NORTH)
            left_dir = Floor::Direction(left_dir + Floor::NONE);
        Floor::Type new_type;

        // CLEAR ALL BRANCHES
        m_branches[0].clear();
        m_branches[1].clear();
        m_branches[2].clear();

        // GENERATE A RANDOM FLOOR AND PLACE IT
        new_type = Floor::RIGHT_LEFT_FORWARD;
        At(tile) = Floor(new_type, front_dir, true);
        
        // GENERATE FORWARDS AT THE INTERESECTIONS OF THAT RANDOM FLOOR
        At(tile + front_tile) = Floor(Floor::EMPTY, Floor::NONE, true);
        At(tile + left_tile) = Floor(Floor::EMPTY, Floor::NONE, true);
        At(tile + right_tile) = Floor(Floor::EMPTY, Floor::NONE, true);
        if (new_type & Floor::FORWARD)
        {
            m_branches[0].push_back(tile + front_tile);
            At(tile + front_tile) = Floor(Floor::FORWARD, front_dir, true);
        }
        if (new_type & Floor::LEFT)
        {
            m_branches[1].push_back(tile + left_tile);
            At(tile + left_tile) = Floor(Floor::FORWARD, left_dir, true);
        }
        if (new_type & Floor::RIGHT)
        {
            m_branches[2].push_back(tile + right_tile);
            At(tile + right_tile) = Floor(Floor::FORWARD, right_dir, true);
        }
    }
};

std::ostream& operator<<(std::ostream& os, Grid& grid)
{
    std::string aux_dirs = "NESW";
    os << grid.GetXSize() << " " << grid.GetYSize() << " " << grid.GetZSize() << std::endl;
    os << aux_dirs[grid.GetInitDir()] << " " << grid.GetInitPos().x << " ";
    os << grid.GetInitPos().y << " " << grid.GetInitPos().z << "\n";
    for (int z = 0; z < grid.GetZSize(); z++)
    {
        for (int y = 0; y < grid.GetYSize(); y++)
        {
            for (int x = 0; x < grid.GetXSize(); x++)
            {
                if (grid.At(x, y, z).type == Floor::EMPTY)
                    os << "0";
                else
                {
                    Floor::Direction dir = grid.At(x, y, z).dir;
                    Floor::Type type = grid.At(x, y, z).type;
                    bool visible = grid.At(x, y, z).visible;
                    os << aux_dirs[dir] << visible << type;
                }
                os << "\t";
            }
            os << "\n";
        }
        os << "\n";
    }
    return (os);
}
