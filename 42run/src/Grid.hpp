#pragma once

#include <cstring>
#include <iostream>
#include <string>

#include <glm/glm.hpp>

template <typename T>
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
    T* m_grid;
public:
    Grid(const Grid& grid)
        : m_y_size(grid.m_y_size), m_x_size(grid.m_x_size), m_z_size(grid.m_z_size), m_size(grid.m_size),
        m_x_loop(grid.m_x_loop), m_y_loop(grid.m_y_loop), m_z_loop(grid.m_z_loop)
    {
        m_grid = new T[m_size];
        std::memcpy(m_grid, grid.m_grid, m_size * sizeof(T));
    }
    Grid(int x_size, int y_size, int z_size = 1, bool x_loop = true, bool y_loop = true, bool z_loop = true)
        : m_y_size(y_size), m_x_size(x_size), m_z_size(z_size), m_size(x_size* y_size* z_size),
        m_x_loop(x_loop), m_y_loop(y_loop), m_z_loop(z_loop)
    {
        m_grid = new T[m_size];
        std::memset(m_grid, 0, m_size * sizeof(T));
    }
    ~Grid()
    {
        delete[] m_grid;
    }
    bool Exists(int x, int y, int z = 0)
    {
        if (x < 0 || x >= m_x_size)
            return (false);
        if (y < 0 || y >= m_y_size)
            return (false);
        if (z < 0 || z >= m_z_size)
            return (false);
        return (true);
    }
    bool Exists(glm::ivec3 v)
    {
        return (Exists(v.x, v.y, v.z));
    }
    T& At(int x, int y, int z)
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
    const T& At(int x, int y, int z) const
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
    T& At(int x, int y)
    {
        return (At(x, y, 0));
    }
    const T& At(int x, int y) const
    {
        return (At(x, y, 0));
    }
    T& At(glm::ivec3 v)
    {
        return (At(v.x, v.y, v.z));
    }
    const T& At(glm::ivec3 v) const
    {
        return (At(v.x, v.y, v.z));
    }
    int GetXSize() const { return (m_x_size); }
    int GetYSize() const { return (m_y_size); }
    int GetZSize() const { return (m_z_size); }

    bool operator==(const Grid& o) const
    {
        for (int z = 0; z < m_z_size; z++)
            for (int y = 0; y < m_y_size; y++)
                for (int x = 0; x < m_x_size; x++)
                    if (o.At(x, y, z) != At(x, y, z))
                        return (false);
        return (true);
    }
};

std::ostream& operator<<(std::ostream& os, Grid<Floor>& grid)
{
    os << "#Frame " << grid.GetXSize() << " " << grid.GetYSize() << " " << grid.GetZSize() << std::endl;
    for (int z = 0; z < grid.GetZSize(); z++)
    {
        for (int y = 0; y < grid.GetYSize(); y++)
        {
            for (int x = 0; x < grid.GetXSize(); x++)
            {
                os << (grid.At(x, y, z).type != Floor::EMPTY) << " ";
            }
            os << "\n";
        }
        os << "\n";
    }
    return (os);
}
