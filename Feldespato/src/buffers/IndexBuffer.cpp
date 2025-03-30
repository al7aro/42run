#include "IndexBuffer.hpp"

#include <iostream>

namespace FT {
    IndexBuffer::IndexBuffer(const unsigned int * data, unsigned int data_count)
        :m_count(data_count)
    {
        glGenBuffers(1, &(m_id));
        Bind();
        glBufferData(m_TARGET, sizeof(unsigned int) * data_count, data, m_USAGE);
        Unbind();
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &(m_id));
        m_id = 0;
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(m_TARGET, m_id);
    }
    void IndexBuffer::Unbind() const
    {
        glBindBuffer(m_TARGET, 0);
    }
}