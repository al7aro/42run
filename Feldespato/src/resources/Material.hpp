#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Texture2D.hpp"
#include "Shader.hpp"

namespace FT {
    //TODO: change this to a struct??
    class Material
    {
    public:
		enum MaterialProperty
		{
			TEXTURE = 0,
			DIFFUSE_MAP = 1,
			SPECULAR_MAP = 2,
			NORMAL_MAP = 3,

            COLOR,
            DIFFUSE,
            SPECULAR,
            AMBIENT,
            EMISSIVE,
            TRANSPARENT,

            OPACITY,
            SHININESS,
            SHININESS_STRENGTH,
            REFRACTI,
            ALL
		};
    private:
        std::shared_ptr<Shader> m_shader;
        std::shared_ptr<Texture2D> m_texture;
        std::shared_ptr<Texture2D> m_diff_map;
        std::shared_ptr<Texture2D> m_spec_map;
        std::shared_ptr<Texture2D> m_normal_map;
        
        glm::vec3 m_col;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;
        glm::vec3 m_ambient;
        glm::vec3 m_emissive;
        glm::vec3 m_transparent;
        float m_opacity;
        float m_shininess;
        float m_shininess_strength;
        float m_refracti;

    public:
        Material();
        Material(const Material & o);
        Material & operator=(const Material & o);
        Material(glm::vec3 col);
        Material(const glm::vec3 & col, const std::shared_ptr<Texture2D> & texture);
        Material(const std::shared_ptr<Texture2D> & texture);
        ~Material();

        void                        SetColor(const glm::vec3 & col, MaterialProperty type = COLOR);
        glm::vec3                   GetColor(MaterialProperty type = COLOR);
        void                        SetValue(float value, MaterialProperty type);
        float                       GetValue(MaterialProperty type);

        void                        SetTexture(const std::shared_ptr<Texture2D> & texture, MaterialProperty type = TEXTURE);
        std::shared_ptr<Texture2D>  GetTexture(MaterialProperty type);
    };
}