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
    std::vector<glm::ivec3> m_next_random_tiles;
    glm::ivec3 m_init_pos;
    int m_init_dir;
public:
    Grid(const Grid& grid)
        : m_y_size(grid.m_y_size), m_x_size(grid.m_x_size), m_z_size(grid.m_z_size), m_size(grid.m_size),
        m_x_loop(grid.m_x_loop), m_y_loop(grid.m_y_loop), m_z_loop(grid.m_z_loop),
        m_init_pos(grid.m_init_pos), m_init_dir(grid.m_init_dir), m_random(grid.m_random),
        m_next_random_tiles(grid.m_next_random_tiles)
    {
        m_grid = new Floor[m_size];
        std::memcpy(m_grid, grid.m_grid, m_size * sizeof(Floor));
    }
    Grid(int x_size, int y_size, int z_size = 1, bool x_loop = true, bool y_loop = true, bool z_loop = true)
        : m_y_size(y_size), m_x_size(x_size), m_z_size(z_size), m_size(x_size* y_size* z_size),
        m_x_loop(x_loop), m_y_loop(y_loop), m_z_loop(z_loop),
        m_init_pos(0), m_init_dir(0), m_next_random_tiles(0)
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

    void SetRandomMap(std::vector<glm::ivec3> next_random_tiles)
    {
        m_next_random_tiles = next_random_tiles;
        m_random = true;
    }

    void RandomizeNextTiles()
    {
        if (!m_random) return;
        //std::vector<glm::ivec3> new_tiles;
        for (int i = 0; i < m_next_random_tiles.size(); i++)
        {
            m_next_random_tiles[i] += glm::vec3(0, 1, 0);
            At(m_next_random_tiles[i]) = Floor(Floor::FORWARD, Floor::NORTH);
        }
    }

    glm::ivec3 GetInitPos() const { return (m_init_pos); }
    int GetInitDir() const { return (m_init_dir); }
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
