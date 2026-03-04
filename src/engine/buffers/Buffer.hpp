#pragma once

#include <glad/glad.h>

#include "../Vertex.hpp"

namespace FT {
    class Buffer
    {
    private:
        unsigned int m_id;
        VertexFormat m_format;

        const unsigned int _TARGET = GL_ARRAY_BUFFER;
        const unsigned int _USAGE = GL_STATIC_DRAW;
    public:
        Buffer(const float * data, size_t data_count, VertexFormat format = VertexFormat{3, 3, 3, 4, 4, 4});
        ~Buffer();

        int GetStride() const;
        void * GetOffset(unsigned int  id) const;
        unsigned int GetCount(unsigned int id) const;
        unsigned int GetGLType(unsigned int id) const;

        void Bind() const;
        void Unbind() const;
    };
}