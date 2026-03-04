#pragma once

#include <glad/glad.h>

namespace FT {

    class Texture2D
    {
    private:        
        unsigned int m_id;
        int m_width;
        int m_height;
        int m_chn;

        const unsigned int m_TARGET = GL_TEXTURE_2D;

        Texture2D();
        Texture2D(const Texture2D & o);
        Texture2D & operator=(const Texture2D & o);
    public:
        Texture2D(unsigned int width, unsigned int height, unsigned int iformat, unsigned int format);
        Texture2D(unsigned char * data, int width, int height, int chn);
        ~Texture2D();

        void Bind(unsigned int unit) const;
        void Unbind() const;
        unsigned int GetId() const { return (m_id); };

    };
}