#include "IndexBuffer.hpp"

#include <iostream>

namespace FT {
    IndexBuffer::IndexBuffer()
        :m_count(DEFAULT_INDEX_BUFFER_SIZE)
    {
        glGenBuffers(1, &(m_id));
        Bind();
        glBufferData(m_TARGET, DEFAULT_INDEX_BUFFER_SIZE, nullptr, m_USAGE);
    }
    IndexBuffer::IndexBuffer(const unsigned int * data, unsigned int data_count)
        :m_count(data_count)
    {
        glGenBuffers(1, &(m_id));
        Bind();
        glBufferData(m_TARGET, sizeof(unsigned int) * data_count, data, m_USAGE);
    }

    void IndexBuffer::SetData(const unsigned int * data, unsigned int data_count)
    {
        if (data_count * sizeof(unsigned int) > DEFAULT_INDEX_BUFFER_SIZE)
            return ;
        m_count = data_count;
        Bind();
        glBufferSubData(m_TARGET, 0, sizeof(unsigned int) * data_count, data);
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