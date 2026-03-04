#pragma once

#include <memory>
#include <map>

#include "resources/Model.hpp"
#include "resources/Shader.hpp"
#include "buffers/VertexArray.hpp"
#include "buffers/Buffer.hpp"
#include "buffers/IndexBuffer.hpp"
#include "Transform.hpp"

namespace FT {
    class Renderable
    {
    protected:
        std::shared_ptr<Model> m_meshes;
        Transform m_transform;

    public:
        Renderable() {}
        Renderable(std::shared_ptr<Mesh> & mesh, Transform transform)
            : m_transform(transform)
        {
            m_meshes = std::make_shared<Model>();
            m_meshes->AddMesh(mesh);
        }
        Renderable(std::shared_ptr<Model>& model, Transform transform)
            : m_meshes(model), m_transform(transform)
        {
        }
        virtual ~Renderable()
        {
        }
        virtual FT::mat4 GetModelMatrix()
        {
            return (m_transform.GetTransform());
        }
        const std::shared_ptr<Model>& GetMeshes()
        {
            return (m_meshes);
        }
        void SetModel(const std::shared_ptr<Model>& model)
        {
            m_meshes = model;
        }
        void SetTransform(const Transform& transform)
        {
            m_transform = transform;
        }
    };
}