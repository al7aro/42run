#include <iostream>

#include "VertexArray.hpp"

namespace FT {
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &(m_id));
        Bind();
    }
    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &(m_id));
        m_id = 0;
    }

    void VertexArray::SetFormat(const VertexFormat& format)
    {
        for (int att_id = 0; att_id < FT::VertexFormat::MAX_ATTRIBUTES; att_id++)
        {
            if (!format.attribute_count[att_id])
                continue;
            glEnableVertexAttribArray(att_id);
            if (VertexFormat::GetGLType(att_id) != GL_INT)
                glVertexAttribPointer(att_id, format.attribute_count[att_id],
                    GL_FLOAT, GL_FALSE,
                    VertexFormat::GetVertexStride(),
                    VertexFormat::GetAttOffset(att_id));
            else
                glVertexAttribIPointer(att_id, format.attribute_count[att_id], 
                    GL_INT,
                    VertexFormat::GetVertexStride(),
                    VertexFormat::GetAttOffset(att_id));
        }
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_id);
    }
    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
}