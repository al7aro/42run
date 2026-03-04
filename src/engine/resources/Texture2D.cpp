#include "Texture2D.hpp"

#include <iostream>

namespace FT {
    Texture2D::Texture2D(unsigned int width, unsigned int height, unsigned int iformat, unsigned int format)
    {
        glGenTextures(1, &(m_id));
        glBindTexture(m_TARGET, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, iformat, width, height, 0, format, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(m_TARGET, 0);
    }
    Texture2D::Texture2D(unsigned char * data, int width, int height, int chn)
        : m_width(width), m_height(height), m_chn(chn)
    {
        if (!data)
            return ;

        glGenTextures(1, &(m_id));
        glBindTexture(m_TARGET, m_id);

        glTexParameteri(m_TARGET, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(m_TARGET, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(m_TARGET, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(m_TARGET, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        unsigned int format = GL_RGBA;
        if (chn == 3)
            format = GL_RGB;

        if (!((width * chn) % 4))
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        else
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        glTexImage2D(m_TARGET, 0, GL_RGBA, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
        glBindTexture(m_TARGET, 0);
    }

    // Delete texture from GPU
    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_id);
    }

    void Texture2D::Bind(unsigned int unit) const
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(m_TARGET, m_id);
    }

    void Texture2D::Unbind() const
    {
        glBindTexture(m_TARGET, 0);
    }
}