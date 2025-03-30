#pragma once

#include <cstddef>

#include <glad/glad.h>

namespace FT {
    class IndexBuffer
    {
    private:
        unsigned int m_id;
        unsigned int m_count;

        const unsigned int m_TARGET = GL_ELEMENT_ARRAY_BUFFER;
        const unsigned int m_USAGE = GL_STATIC_DRAW;
    public:
        IndexBuffer(const unsigned int * data, unsigned int data_count);
        ~IndexBuffer();

        void Bind()  const;
        void Unbind()  const;

        unsigned int GetCount() const { return (this->m_count); }
        unsigned int GetId() const { return (this->m_id); }
    };
}