#pragma once

#include <vector>
#include <string>

#include "../Vertex.hpp"

namespace FT {
    class Geometry
    {
    private:
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;

    public:
        Geometry()
        {
        }
        Geometry(const Geometry & o)
        {
            m_vertices = o.m_vertices;
            m_indices = o.m_indices;
        }
        Geometry & operator=(const Geometry & o)
        {
            m_vertices = o.m_vertices;
            m_indices = o.m_indices;
            return (*this);
        }
        Geometry(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
            : m_vertices(vertices), m_indices(indices)
        {
        }

        void SetVertices(std::vector<Vertex> vertices)
        {
            m_vertices = vertices;
        }
        void SetIndices(std::vector<unsigned int> indices)
        {
            m_indices = indices;
        }
        std::vector<Vertex>& GetVerticesRef()
        {
            return (m_vertices);
        }
        std::vector<unsigned int>& GetIndicesRef()
        {
            return (m_indices);
        }
        std::vector<Vertex> GetVertices() const
        {
            return (m_vertices);
        }
        const float * GetRawVertices() const
        {
            return (&(m_vertices[0].pos[0]));
        }
        std::vector<unsigned int> GetIndices() const
        {
            return (m_indices);
        }
        const unsigned int * GetRawIndices() const
        {
            return (&(m_indices[0]));
        }
        unsigned int GetIndexCount() const
        {
            return (static_cast<unsigned int>(m_indices.size()));
        }
        unsigned int GetVertexCount() const
        {
            return (static_cast<unsigned int>(m_vertices.size()));
        }
        unsigned int GetDataCount() const
        {
            return static_cast<unsigned int>(m_vertices.size() * sizeof(Vertex) / sizeof(float));
        }
    };
}