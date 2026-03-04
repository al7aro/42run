#include <iostream>

#include "Layer.hpp"

namespace FT {
        Layer::Layer()
        {
            m_renderer = std::make_shared<StaticRenderer3D>();
        }


        Layer::~Layer() {}

        void Layer::Add(std::shared_ptr<Renderable> renderable)
        {
            if (!renderable) return ;
            m_renderables.push(renderable);
        }

        void Layer::SetCamera(const Camera & cam)
        {
            m_cam = cam;
        }
        void Layer::SetShader(std::shared_ptr<Shader> sh)
        {
            m_sh = sh;
        }

        const Camera & Layer::GetCamera()
        {
            return (m_cam);
        }
        std::shared_ptr<Shader> Layer::GetShader()
        {
            return (m_sh);
        }

        void Layer::Render()
        {
            std::shared_ptr<Shader> sh = m_sh;
            if (!sh) return;

            sh->SetMat4("view_mat", m_cam.GetViewMatrix());
            sh->SetMat4("proj_mat", m_cam.GetProjectionMatrix());

            while (!m_renderables.empty())
            {
				m_renderer->Submit(m_renderables.top());
				m_renderables.pop();
            }
            m_renderer->Flush(sh);
        }

        void Layer::Clear() {}
}