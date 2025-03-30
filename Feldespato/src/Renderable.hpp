#pragma once

#include <memory>
#include <map>

#include <glm/glm.hpp>

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
        Model m_meshes;
        Transform m_transform;

    public:
        Renderable() {}
        Renderable(const Mesh & mesh, Transform transform)
            : m_transform(transform)
        {
            m_meshes = Model();
            m_meshes.AddMesh(mesh);
        }
        Renderable(Model model, Transform transform)
            : m_meshes(model), m_transform(transform)
        {
        }
        virtual ~Renderable()
        {
        }
        virtual glm::mat4 GetModelMatrix()
        {
            return (m_transform.GetTransform());
        }
        Model GetMeshes()
        {
            return (m_meshes);
        }

        static std::shared_ptr<VertexArray>    GetVAO(Mesh mesh)
        {
            std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>();
            vao->SetVBO(std::make_shared<Buffer>(mesh.GetGeometry().GetRawVertices(), mesh.GetGeometry().GetDataCount()));
            vao->SetIBO(std::make_shared<IndexBuffer>(mesh.GetGeometry().GetRawIndices(), mesh.GetGeometry().GetIndexCount()));
            return (vao);
        }
    };
}