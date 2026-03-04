#pragma once

#include <glad/glad.h>

#include "../Vertex.hpp"

namespace FT {
    class Buffer
    {
    public:
        static constexpr size_t DEFAULT_BUFFER_SIZE = 2048 * 2048 * sizeof(float);
    private:
        unsigned int m_id;
        VertexFormat m_format;

        const unsigned int _TARGET = GL_ARRAY_BUFFER;
        const unsigned int _USAGE = GL_STATIC_DRAW;
    public:
        Buffer(VertexFormat format = VertexFormat{3, 3, 3, 4, 4, 4});
        ~Buffer();

        void SetData(const float * data, size_t data_count);
        int GetStride() const;
        void * GetOffset(unsigned int  id) const;
        unsigned int GetCount(unsigned int id) const;
        unsigned int GetGLType(unsigned int id) const;

        const VertexFormat& GetFormat() const;

        void Bind() const;
        void Unbind() const;
    };
}