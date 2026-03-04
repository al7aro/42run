#include "Buffer.hpp"

#include <iostream>

namespace FT {
    Buffer::Buffer(FT::VertexFormat format)
        : m_format(format)
    {
        glGenBuffers(1, &(this->m_id));
        this->Bind();
        glBufferData(this->_TARGET, DEFAULT_BUFFER_SIZE, nullptr, this->_USAGE);
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &(this->m_id));
        this->m_id = 0;
    }

    void Buffer::SetData(const float * data, size_t data_count)
    {
        if (data_count * sizeof(float) > DEFAULT_BUFFER_SIZE)
            return ;
        this->Bind();
        glBufferSubData(this->_TARGET, 0, sizeof(float) * data_count, data);
        this->Unbind();
    }

    const VertexFormat& Buffer::GetFormat() const
    {
        return (m_format);
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