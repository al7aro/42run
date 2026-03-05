#pragma once

#include <glad/glad.h>
#include <memory>

#include "Buffer.hpp"

namespace FT {
    
    class VertexArray
    {
    private:
        unsigned int m_id;

    public:
        VertexArray();
        ~VertexArray();

        void SetFormat(const VertexFormat& format);

        void Bind() const;
        void Unbind() const;
    };
}