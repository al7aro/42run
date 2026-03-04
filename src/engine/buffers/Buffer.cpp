#include "Buffer.hpp"

#include <iostream>

namespace FT {
    Buffer::Buffer(const float * data, size_t data_count, FT::VertexFormat format)
    {
        for (int i = 0; i < VertexFormat::MAX_ATTRIBUTES; i++)
            this->m_format.attribute_count[i] = format.attribute_count[i];
        glGenBuffers(1, &(this->m_id));
        this->Bind();
        glBufferData(this->_TARGET, sizeof(float) * data_count, data, this->_USAGE);
        this->Unbind();
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &(this->m_id));
        this->m_id = 0;
    }

    int Buffer::GetStride() const
    {
        return (VertexFormat::GetVertexStride());
    }

    void * Buffer::GetOffset(unsigned int id) const
    {
        return (VertexFormat::GetAttOffset(id));
    }

    unsigned int Buffer::GetCount(unsigned int id) const
    {
        return (this->m_format.attribute_count[id]);
    }

    unsigned int Buffer::GetGLType(unsigned int id) const
    {
        return (VertexFormat::GetGLType(id));
    }

    void Buffer::Bind() const
    {
        glBindBuffer(this->_TARGET, this->m_id);
    }
    void Buffer::Unbind() const
    {
        glBindBuffer(this->_TARGET, 0);
    }
}