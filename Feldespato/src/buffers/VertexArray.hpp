#pragma once

#include <glad/glad.h>
#include <memory>

#include "Buffer.hpp"
#include "IndexBuffer.hpp"

namespace FT {
    
    class VertexArray
    {
    private:
        unsigned int m_id;
        std::shared_ptr<Buffer> m_vbos;
        std::shared_ptr<IndexBuffer> m_ibo;

    public:
        VertexArray();
        ~VertexArray();

        void SetIBO(const std::shared_ptr<IndexBuffer> & ibo);
        void SetVBO(const std::shared_ptr<Buffer> & vbo);

        const std::shared_ptr<IndexBuffer> & GetIBO() const { return(m_ibo); }

        void Bind() const;
        void Unbind() const;
    };
}