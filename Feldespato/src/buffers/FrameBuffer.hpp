#pragma once

#include <iostream>
#include <memory>

#include "../resources/Texture2D.hpp"

namespace FT {
    class FrameBuffer
    {
    private:
        unsigned int m_id;
        unsigned int m_rbo;
		unsigned int m_width;
		unsigned int m_height;
        std::shared_ptr<Texture2D> m_color;
        bool m_enabled;
    public:
        FrameBuffer(unsigned int width, unsigned int  height)
            : m_width(width), m_height(height), m_enabled(false)
        {
            m_color = std::make_shared<Texture2D>(width, height, GL_RGBA, GL_RGBA);
            glGenFramebuffers(1, &m_id);
            glBindFramebuffer(GL_FRAMEBUFFER, m_id);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color->GetId(), 0);
            glGenRenderbuffers(1, &m_rbo);
            glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        ~FrameBuffer()
        {
            Disable();
            glDeleteRenderbuffers(1, &m_rbo);
            glDeleteFramebuffers(1, &m_id);
        }
        void Enable()
        {
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
			//glViewport(0, 0, m_width, m_height);
			m_enabled = true;
        }
        void Disable()
        {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			m_enabled = false;
        }
		std::shared_ptr<Texture2D> GetFrameColor() const
        {
            return m_color;
        }
		bool IsEnabled() const
		{
			return m_enabled;
		}
        int GetWidth() const
        {
            return m_width;
        }
        int GetHeight() const
        {
            return m_height;
        }
    };
}