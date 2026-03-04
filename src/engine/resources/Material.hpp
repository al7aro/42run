#pragma once

#include <memory>

#include "Texture2D.hpp"
#include "Shader.hpp"

#include "../math/Math.hpp"

namespace FT {
    //TODO: change this to a struct??
    class Material
    {
    public:
		enum MaterialProperty
		{ // TODO: THIS COULD BE BIT FLAGS
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
        bool m_tex_enabled;
        std::shared_ptr<Texture2D> m_diff_map;
        bool m_diff_enabled;
        std::shared_ptr<Texture2D> m_spec_map;
        bool m_spec_enabled;
        std::shared_ptr<Texture2D> m_normal_map;
        bool m_normal_enabled;
        
        FT::vec3 m_col;
        FT::vec3 m_diffuse;
        FT::vec3 m_specular;
        FT::vec3 m_ambient;
        FT::vec3 m_emissive;
        FT::vec3 m_transparent;
        float m_opacity;
        float m_shininess;
        float m_shininess_strength;
        float m_refracti;

    public:
        Material();
        Material(const Material & o);
        Material & operator=(const Material & o);
        Material(FT::vec3 col);
        Material(const std::shared_ptr<Texture2D> & texture);
        ~Material();

        void                        SetColor(const FT::vec3 & col, MaterialProperty type = COLOR);
        FT::vec3                    GetColor(MaterialProperty type = COLOR);
        void                        SetValue(float value, MaterialProperty type);
        float                       GetValue(MaterialProperty type);

        void                        SetTexture(const std::shared_ptr<Texture2D> & texture, MaterialProperty type = TEXTURE, bool enable = true);
        std::shared_ptr<Texture2D>  GetTexture(MaterialProperty type);
        bool                        GetTextureEnabled(MaterialProperty type);

        void EnableTextures(MaterialProperty type, bool enable = true);
    };
}