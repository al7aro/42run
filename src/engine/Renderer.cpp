#include "Renderer.hpp"

namespace FT {
    StaticRenderer3D::StaticRenderer3D()
    {
        m_vao = std::make_shared<VertexArray>();
        m_vbo = std::make_shared<Buffer>();
        m_ibo = std::make_shared<IndexBuffer>();
        m_vao->SetFormat(m_vbo->GetFormat());
    }

    void StaticRenderer3D::Submit(std::shared_ptr<Renderable> renderable)
    {
        this->_render_queue.push_back(renderable);
    }
    void StaticRenderer3D::Flush(std::shared_ptr<Shader > shader)
    {
        if (!shader) return;
        while (!this->_render_queue.empty())
        {
            std::shared_ptr<Renderable> renderable = this->_render_queue.front();
            std::shared_ptr<Model> multi_mesh = renderable->GetMeshes();
            FT::mat4 model_mat = renderable->GetModelMatrix();

            for (auto & mesh : multi_mesh->GetMeshes())
            {
                FT::mat4 tr = multi_mesh->GetNodeTransform(mesh->GetNodeName());
                m_vbo->SetData(mesh->GetGeometry().GetRawVertices(), mesh->GetGeometry().GetDataCount());
                m_ibo->SetData(mesh->GetGeometry().GetRawIndices(), mesh->GetGeometry().GetIndexCount());
                
                m_vao->Bind();
                m_vbo->Bind();
                m_ibo->Bind();

                /* SET SHADER UNIFORMS */
                shader->SetMat4("model_mat", model_mat * tr);
                std::shared_ptr<Texture2D> tex;
                Material mat = mesh->GetMaterial();
                for (int i = 0; i < Material::ALL; i++)
                {
                    tex = mat.GetTexture(static_cast<Material::MaterialProperty>(i));
                    if (tex)
                        tex->Bind(i);
                }
                shader->SetInt("diffuse_map", 1);
                shader->SetInt("diffuse_map_enabled", mat.GetTextureEnabled(Material::DIFFUSE_MAP));

                /* Material Properties */
                shader->SetVec3("mat.diffuse", mat.GetColor(Material::DIFFUSE));
                /* ------------------ */
                shader->Enable();
                glDrawElements(GL_TRIANGLES, m_ibo->GetCount(), GL_UNSIGNED_INT, (void*)0);
            }
            this->_render_queue.pop_front();
        }
    }
}