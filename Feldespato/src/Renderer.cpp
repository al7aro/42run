#include "Renderer.hpp"

namespace FT {
    StaticRenderer3D::StaticRenderer3D()
    {
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
            Model multi_mesh = renderable->GetMeshes();
            glm::mat4 model_mat = renderable->GetModelMatrix();

            /* BONES */
            for (auto& pair : multi_mesh.GetBones())
            {
                glm::mat4 b_tr = pair.second.final_transform;
                shader->SetMat4("bone_matrix["+std::to_string(pair.second.id)+"]", b_tr);
            }
            /*********/

            for (auto & mesh : multi_mesh.GetMeshes())
            {
                glm::mat4 tr = multi_mesh.GetNodeTransform(mesh.GetNodeName());
                std::shared_ptr<VertexArray> vao = Renderable::GetVAO(mesh);
                vao->Bind();
                /* SET SHADER UNIFORMS */
                shader->SetMat4("model_mat", model_mat * tr);
                std::shared_ptr<Texture2D> tex;
                Material mat = mesh.GetMaterial();
                for (int i = 0; i < Material::ALL; i++)
                {
                    tex = mat.GetTexture(static_cast<Material::MaterialProperty>(i));
                    if (tex)
                    {
                        tex->Bind(i);
                    }
                }
                shader->SetInt("texture_map", 0);
                shader->SetInt("texture_map_enabled", mat.GetTextureEnabled(Material::TEXTURE));
                shader->SetInt("diffuse_map", 1);
                shader->SetInt("diffuse_map_enabled", mat.GetTextureEnabled(Material::DIFFUSE_MAP));
                shader->SetInt("specular_map", 2);
                shader->SetInt("specular_map_enabled", mat.GetTextureEnabled(Material::SPECULAR_MAP));
                shader->SetInt("normal_map", 3);
                shader->SetInt("normal_map_enabled", mat.GetTextureEnabled(Material::NORMAL_MAP));

                /* Material Properties */
                shader->SetVec3("mat.col", mat.GetColor(Material::COLOR));
                shader->SetVec3("mat.diffuse", mat.GetColor(Material::DIFFUSE));
                shader->SetVec3("mat.specular", mat.GetColor(Material::SPECULAR));
                shader->SetVec3("mat.ambient", mat.GetColor(Material::AMBIENT));
                shader->SetVec3("mat.emissive", mat.GetColor(Material::EMISSIVE));
                shader->SetVec3("mat.transparent", mat.GetColor(Material::TRANSPARENT));
                shader->SetFloat("mat.opacity", mat.GetValue(Material::OPACITY));
                shader->SetFloat("mat.shininess", mat.GetValue(Material::SHININESS));
                shader->SetFloat("mat.shininess_strength", mat.GetValue(Material::SHININESS_STRENGTH));
                shader->SetFloat("mat.refracti", mat.GetValue(Material::REFRACTI));
                /* ------------------ */
                shader->Enable();
                glDrawElements(GL_TRIANGLES, vao->GetIBO()->GetCount(), GL_UNSIGNED_INT, (void*)0);
                vao->Unbind();
            }
            this->_render_queue.pop_front();
        }
    }
}