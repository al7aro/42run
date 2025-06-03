#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>

int constexpr MAIN_BRANCH = 0;
int constexpr LEFT_BRANCH = 1;
int constexpr RIGHT_BRANCH = 2;
int constexpr MAX_BRANCH = 3;

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
    glm::ivec3 m_corner_cnt;
    glm::ivec3 m_prev_floor;
    bool m_active_branches;
    bool m_intersection;
    glm::ivec3 m_init_pos;
    int m_init_dir;
public:
    Grid(const Grid& grid)
        : m_y_size(grid.m_y_size), m_x_size(grid.m_x_size), m_z_size(grid.m_z_size), m_size(grid.m_size),
        m_x_loop(grid.m_x_loop), m_y_loop(grid.m_y_loop), m_z_loop(grid.m_z_loop),
        m_init_pos(grid.m_init_pos), m_init_dir(grid.m_init_dir), m_random(grid.m_random),
        m_active_branches(grid.m_active_branches), m_intersection(grid.m_intersection),
        m_corner_cnt(grid.m_corner_cnt), m_prev_floor(grid.m_prev_floor)
    {
        m_grid = new Floor[m_size];
        std::memcpy(m_grid, grid.m_grid, m_size * sizeof(Floor));
    }
    Grid(int x_size, int y_size, int z_size = 1, bool x_loop = true, bool y_loop = true, bool z_loop = true)
        : m_y_size(y_size), m_x_size(x_size), m_z_size(z_size), m_size(x_size* y_size* z_size),
        m_x_loop(x_loop), m_y_loop(y_loop), m_z_loop(z_loop), m_random(false),
        m_init_pos(0), m_init_dir(0), m_active_branches(0), m_intersection(0), m_corner_cnt(0),
        m_prev_floor(Floor::EMPTY)
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

    void PushToBranch(glm::ivec3 init_random_tile, int branch)
    {
        m_branches[branch].push_back(init_random_tile);
    }

    glm::ivec3 GetInitPos() const { return (m_init_pos); }
    int GetInitDir() const { return (m_init_dir); }

    glm::ivec3 GetNextTile(glm::ivec3 tile, Floor::Direction dir)
    {
        // pref_dir: PREFERED DIRECTION IN CASE THERE IS INTERESCTION
        Floor f = At(tile);
        glm::ivec3 new_tile;
        // The last element of the branch is the one we need to check
        glm::ivec3 front_tile = glm::ivec3(0);
        glm::ivec3 right_tile = glm::ivec3(0);
        glm::ivec3 left_tile = glm::ivec3(0);
        glm::ivec3 back_tile = glm::ivec3(0);
        switch (f.type)
        {
        case Floor::RIGHT:
            dir = Floor::EAST;
            break;
        case Floor::LEFT:
            dir = Floor::WEST;
            break;
        }
        switch (f.dir)
        {
        case Floor::NORTH:
            front_tile = glm::ivec3(0, 1, 0);
            right_tile = glm::ivec3(1, 0, 0);
            left_tile  = glm::ivec3(-1, 0, 0);
            back_tile  = glm::ivec3(0, -1, 0);
            break;
        case Floor::SOUTH:
            front_tile = -glm::ivec3(0, 1, 0);
            right_tile = -glm::ivec3(1, 0, 0);
            left_tile  = -glm::ivec3(-1, 0, 0);
            back_tile  = -glm::ivec3(0, -1, 0);
            break;
        case Floor::EAST:
            front_tile = glm::ivec3(1, 0, 0);
            right_tile = glm::ivec3(0, -1, 0);
            left_tile  = glm::ivec3(0, 1, 0);
            back_tile  = glm::ivec3(-1, 0, 0);
            break;
        case Floor::WEST:
            front_tile = -glm::ivec3(1, 0, 0);
            right_tile = -glm::ivec3(0, -1, 0);
            left_tile  = -glm::ivec3(0, 1, 0);
            back_tile  = -glm::ivec3(-1, 0, 0);
            break;
        }
        if (dir == Floor::NORTH)
            new_tile = tile + front_tile;
        else if (dir == Floor::SOUTH)
            new_tile = tile + back_tile;
        else if (dir == Floor::EAST)
            new_tile = tile + right_tile;
        else if (dir == Floor::WEST)
            new_tile = tile + left_tile;
        if (f.type == Floor::UP)
            new_tile = tile + glm::ivec3(0, 0, 1);
        if (f.type == Floor::DOWN)
            new_tile = tile + glm::ivec3(0, 0, -1);
        return (new_tile);
    }

    Floor::Direction GetNextDirection(glm::ivec3 tile, Floor::Direction dir)
    {
        Floor f = At(tile);
        Floor::Direction back_dir;
        Floor::Direction front_dir;
        Floor::Direction left_dir;
        Floor::Direction right_dir;
        front_dir = Floor::Direction((f.dir + 0) % Floor::Direction::NONE);
        right_dir = Floor::Direction((f.dir + 1) % Floor::Direction::NONE);
        back_dir =  Floor::Direction((f.dir + 2) % Floor::Direction::NONE);
        left_dir =  Floor::Direction((f.dir + 3) % Floor::Direction::NONE);
        if (f.type == Floor::RIGHT)
        {
            front_dir = Floor::Direction((f.dir + 1) % Floor::Direction::NONE);
            right_dir = Floor::Direction((f.dir + 2) % Floor::Direction::NONE);
            back_dir =  Floor::Direction((f.dir + 3) % Floor::Direction::NONE);
            left_dir =  Floor::Direction((f.dir + 0) % Floor::Direction::NONE);
        }
        if (f.type == Floor::LEFT)
        {
            front_dir = Floor::Direction((f.dir + 3) % Floor::Direction::NONE);
            right_dir = Floor::Direction((f.dir + 0) % Floor::Direction::NONE);
            back_dir =  Floor::Direction((f.dir + 1) % Floor::Direction::NONE);
            left_dir =  Floor::Direction((f.dir + 2) % Floor::Direction::NONE);
        }
        if (dir == Floor::NORTH)
            return (front_dir);
        else if (dir == Floor::SOUTH)
            return (back_dir);
        else if (dir == Floor::EAST)
            return (right_dir);
        else if (dir == Floor::WEST)
           return (left_dir);
    }

    void ClearBranches()
    {
        for (int i = 0; i < MAX_BRANCH; i++)
        {
            if (!m_branches[i].empty())
                m_branches[i].clear();
        }
    }

    Floor::Type RandomFloor(Floor::Type prev_type, int branch)
    {
        Floor::Type final_type = Floor::FORWARD;
        double r = double(std::rand()) / double(RAND_MAX);
        if (m_prev_floor[branch] != Floor::FORWARD)
            final_type = Floor::FORWARD;
        else if (!m_active_branches && prev_type == Floor::FORWARD)
        {
            // INTERESCTIONS
            if (r >= 0.75 && m_corner_cnt[branch] < 1 && m_corner_cnt[branch] > -1)
                final_type = Floor::RIGHT_FORWARD;
            else if (r >= 0.5 && m_corner_cnt[branch] > -2)
                final_type = Floor::LEFT_FORWARD;
            else if (r >= 0.25 && m_corner_cnt[branch] < 2)
                final_type = Floor::RIGHT_LEFT_FORWARD;
            else if (r >= 0.0 && m_corner_cnt[branch] < 2 && m_corner_cnt[branch] > -2)
                final_type = Floor::RIGHT_LEFT;
        }
        else
        {
            if (r <= 0.3 && m_corner_cnt[branch] < 1)
            {
                m_corner_cnt[branch] += 1;
                final_type = Floor::RIGHT;
            }
            else if (r <= 0.6 && m_corner_cnt[branch] > -1)
            {
                m_corner_cnt[branch] -= 1;
                final_type = Floor::LEFT;
            }
        }
        m_prev_floor[branch] = final_type;
        return (final_type);
    }

    void RandomizeNextTiles(glm::ivec3 player_tile)
    {
        if (!m_random) return;
        // MULTIPLE BRANCHES
        if (m_active_branches)
        {
            for (int i = 0; i < MAX_BRANCH; i++)
            {
                // THIS MEANS THE PLAYER REACHED AND CHOSE A POINT OF THE INTERESCTION
                if (m_branches[i].size() < 2) continue;
                if (player_tile == m_branches[i][1])
                {
                    for (int k = 0; k < MAX_BRANCH; k++)
                    {
                        if (k == i) continue;
                        for (glm::ivec3& pos : m_branches[k])
                            At(pos) = Floor(Floor::EMPTY, Floor::NONE);
                    }
                    //TODO UPDATE CORNER COUNTER ACCORDING TO
                    m_corner_cnt = glm::ivec3(0);
                    //m_corner_cnt[MAIN_BRANCH] = m_corner_cnt[i];
                    //m_corner_cnt[LEFT_BRANCH] = 0;
                    //m_corner_cnt[RIGHT_BRANCH] = 0;
                    m_prev_floor[MAIN_BRANCH] = m_prev_floor[i];
                    m_prev_floor[LEFT_BRANCH] = Floor::EMPTY;
                    m_prev_floor[RIGHT_BRANCH] = Floor::EMPTY;
                    m_active_branches = false;
                    glm::ivec3 sav = m_branches[i].back();
                    ClearBranches();
                    m_branches[MAIN_BRANCH].push_back(sav);
                    break;
                }
            }
            if (m_active_branches && !m_intersection)
            {
                for (int i = 0; i < MAX_BRANCH; i++)
                {
                    if (m_branches[i].size() < 2)
                        continue;
                    glm::ivec3 tile = m_branches[i].back();
                    Floor f = At(tile);
                    Floor::Direction new_dir = GetNextDirection(tile, Floor::NORTH);
                    glm::ivec3 new_tile = GetNextTile(tile, Floor::NORTH);
                    Floor::Type new_type = RandomFloor(f.type, i);
                    At(new_tile) = Floor(new_type, new_dir);
                    m_branches[i].push_back(new_tile);
                }
            }
            if (m_active_branches && m_intersection)
            {
                m_intersection = false;
                glm::ivec3 tile = m_branches[MAIN_BRANCH].back();
                Floor f = At(tile);
                Floor::Direction new_dir = GetNextDirection(tile, Floor::NORTH);
                if (f.type & Floor::FORWARD)
                {
                    glm::ivec3 new_tile = GetNextTile(tile, Floor::NORTH);
                    new_dir = GetNextDirection(tile, Floor::NORTH);
                    At(new_tile) = Floor(Floor::FORWARD, new_dir);
                    m_branches[MAIN_BRANCH].push_back(new_tile);
                }
                if (f.type & Floor::LEFT)
                {
                    glm::ivec3 new_tile = GetNextTile(tile, Floor::WEST);
                    new_dir = GetNextDirection(tile, Floor::WEST);
                    At(new_tile) = Floor(Floor::FORWARD, new_dir);
                    m_branches[LEFT_BRANCH].push_back(new_tile);
                }
                if (f.type & Floor::RIGHT)
                {
                    glm::ivec3 new_tile = GetNextTile(tile, Floor::EAST);
                    new_dir = GetNextDirection(tile, Floor::EAST);
                    At(new_tile) = Floor(Floor::FORWARD, new_dir);
                    m_branches[RIGHT_BRANCH].push_back(new_tile);
                }
            }
        }
        if (!m_active_branches)
        {
            // WE FIRST GET THE BACK TILE OF THE MAIN BRANCH
            glm::ivec3 tile = m_branches[MAIN_BRANCH].back();
            Floor f = At(tile);
            // A RANDOM FLOOR IS GENERATED
            Floor::Type new_type = RandomFloor(f.type, MAIN_BRANCH);
            Floor::Direction new_dir = GetNextDirection(tile, Floor::NORTH);
            // THIS MEANS AN INTERSECTION WAS GENERATED
            if (new_type != Floor::FORWARD && new_type != Floor::UP && new_type != Floor::DOWN
                && new_type != Floor::LEFT && new_type != Floor::RIGHT)
            {
                m_intersection = true;
                m_active_branches = true;
                tile = GetNextTile(tile, Floor::NORTH);
                At(tile) = Floor(new_type, new_dir);
                ClearBranches();
                m_branches[MAIN_BRANCH].push_back(tile);
                m_branches[LEFT_BRANCH].push_back(tile);
                m_branches[RIGHT_BRANCH].push_back(tile);
            }
            else
            {
                tile = GetNextTile(tile, Floor::NORTH);
                At(tile) = Floor(new_type, new_dir);
                m_branches[MAIN_BRANCH].push_back(tile);
            }
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
