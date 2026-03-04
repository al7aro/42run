#include <iostream>

#include "VertexArray.hpp"

namespace FT {
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &(m_id));
    }
    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &(m_id));
        m_id = 0;
    }

    void VertexArray::SetIBO(const std::shared_ptr<IndexBuffer> & ibo)
    {
        m_ibo = ibo;
        this->Bind();
        ibo->Bind();
        this->Unbind();
        ibo->Unbind();
        // glVertexArrayElementBuffer(this->_id, this->_ibo->GetId()); // <- OpenGL >=4.3
    }

    void VertexArray::SetVBO(const std::shared_ptr<Buffer> & vbo)
    {
        this->Bind();
        vbo->Bind();
        for (int att_id = 0; att_id < FT::VertexFormat::MAX_ATTRIBUTES; att_id++)
        {
            if (!vbo->GetCount(att_id))
                continue;
            glEnableVertexAttribArray(att_id);
            if (vbo->GetGLType(att_id) != GL_INT)
                glVertexAttribPointer(att_id, vbo->GetCount(att_id), GL_FLOAT, GL_FALSE, vbo->GetStride(), vbo->GetOffset(att_id));
            else
                glVertexAttribIPointer(att_id, vbo->GetCount(att_id), GL_INT, vbo->GetStride(), vbo->GetOffset(att_id));
        }
        vbo->Unbind();
        this->Unbind();
        m_vbos = vbo;
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