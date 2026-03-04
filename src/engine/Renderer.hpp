#pragma once

#include <memory>
#include <queue>

#include "Renderable.hpp"
#include "buffers/VertexArray.hpp"

namespace FT {
    class Renderer
    {
    public:
        Renderer() {}
        virtual ~Renderer() = default;

        virtual void Submit(std::shared_ptr<Renderable> renderable) = 0;
        virtual void Flush(std::shared_ptr<Shader> shader) = 0;
    };

    class StaticRenderer3D : public FT::Renderer
    {
    private:
        std::deque<std::shared_ptr<Renderable> > _render_queue;

    public:
        StaticRenderer3D();

        void Submit(std::shared_ptr<Renderable> renderable) override;
        void Flush(std::shared_ptr<Shader > shader) override;
    };
}