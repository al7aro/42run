#pragma once

#include <stack>

#include "Renderer.hpp"
#include "resources/Shader.hpp"
#include "Camera.hpp"
#include "buffers/FrameBuffer.hpp"

namespace FT {
    class Layer
    {
    private:
        std::shared_ptr<Renderer> m_renderer;
        std::stack<std::shared_ptr<Renderable> > m_renderables;
        Camera m_cam;
        std::shared_ptr<Shader> m_sh;

    public:
        Layer();
        ~Layer();

        void Add(std::shared_ptr<Renderable> renderable);
        void Render();

        void SetCamera(const Camera & cam);
        void SetShader(std::shared_ptr<Shader> sh);

        const Camera & GetCamera();
        std::shared_ptr<Shader> GetShader();

        void Clear();
    };
}