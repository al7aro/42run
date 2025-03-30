#include "Material.hpp"

namespace FT {
    
    Material::Material()
    {
    }
    Material::Material(const Material & o)
        : m_shader(o.m_shader),
            m_texture(o.m_texture), m_diff_map(o.m_diff_map), m_spec_map(o.m_spec_map), m_normal_map(o.m_normal_map),
            m_col(o.m_col), m_diffuse (o.m_diffuse), m_specular (o.m_specular), m_ambient (o.m_ambient), m_emissive (o.m_emissive),
            m_transparent (o.m_transparent), m_opacity (o.m_opacity), m_shininess (o.m_shininess),
            m_shininess_strength (o.m_shininess_strength), m_refracti (o.m_refracti)
    {
    }
    Material & Material::operator=(const Material & o)
    {
        m_shader = o.m_shader;
        m_texture = o.m_texture;
        m_diff_map = o.m_diff_map;
        m_spec_map = o.m_spec_map;
        m_normal_map = o.m_normal_map;
        m_col = o.m_col;
        m_diffuse = o.m_diffuse;
        m_specular = o.m_specular;
        m_ambient = o.m_ambient;
        m_emissive = o.m_emissive;
        m_transparent = o.m_transparent;
        m_opacity = o.m_opacity;
        m_shininess = o.m_shininess;
        m_shininess_strength = o.m_shininess_strength;
        m_refracti = o.m_refracti;
        return (*this);
    }
    Material::Material(glm::vec3 col)
        : m_col(col)
    {
    }
    Material::Material(const glm::vec3 & col, const std::shared_ptr<Texture2D> & texture)
        : m_col(col)
    {
        SetTexture(texture, MaterialProperty::ALL);
    }
    Material::Material(const std::shared_ptr<Texture2D> & texture)
        : Material()
    {
        SetTexture(texture, MaterialProperty::ALL);
    }
    Material::~Material() {}

    void Material::SetColor(const glm::vec3 & col, MaterialProperty type)
    {
        switch (type)
        {
        case MaterialProperty::COLOR:
            m_col = col;
            break;
        case MaterialProperty::DIFFUSE:
            m_diffuse = col;
            break;
        case MaterialProperty::SPECULAR:
            m_specular = col;
            break;
        case MaterialProperty::AMBIENT:
            m_ambient = col;
            break;
        case MaterialProperty::EMISSIVE:
            m_emissive = col;
            break;
        case MaterialProperty::TRANSPARENT:
            m_transparent = col;
            break;
        default:
            m_col = col;
            m_diffuse = col;
            m_specular = col;
            m_ambient = col;
            m_emissive = col;
            m_transparent = col;
        }
    }

    glm::vec3 Material::GetColor(MaterialProperty type)
    {
        switch (type)
        {
        case MaterialProperty::COLOR:
            return (m_col);
            break;
        case MaterialProperty::DIFFUSE:
            return (m_diffuse);
            break;
        case MaterialProperty::SPECULAR:
            return (m_specular);
            break;
        case MaterialProperty::AMBIENT:
            return (m_ambient);
            break;
        case MaterialProperty::EMISSIVE:
            return (m_emissive);
            break;
        case MaterialProperty::TRANSPARENT:
            return (m_transparent);
            break;
        default:
            return (m_col);
        }
    }

    void Material::SetValue(float value, MaterialProperty type)
    {
        switch (type)
        {
        case MaterialProperty::OPACITY:
            m_opacity = value;
            break;
        case MaterialProperty::SHININESS:
            m_shininess = value;
            break;
        case MaterialProperty::SHININESS_STRENGTH:
            m_shininess_strength = value;
            break;
        case MaterialProperty::REFRACTI:
            m_refracti = value;
            break;
        default:
            m_opacity = value;
            m_shininess = value;
            m_shininess_strength = value;
            m_refracti = value;
        }
    }

    float Material::GetValue(MaterialProperty type)
    {
        switch (type)
        {
        case MaterialProperty::OPACITY:
            return (m_opacity);
            break;
        case MaterialProperty::SHININESS:
            return (m_shininess);
            break;
        case MaterialProperty::SHININESS_STRENGTH:
            return (m_shininess_strength);
            break;
        case MaterialProperty::REFRACTI:
            return (m_refracti);
            break;
        default:
            return (0.0);
        }
    }

    void Material::SetTexture(const std::shared_ptr<Texture2D> & texture, MaterialProperty type)
    {
        switch (type)
        {
        case MaterialProperty::DIFFUSE_MAP:
            m_diff_map = texture;
            break;
        case MaterialProperty::SPECULAR_MAP:
            m_spec_map = texture;
            break;
        case MaterialProperty::NORMAL_MAP:
            m_normal_map = texture;
            break;
        case MaterialProperty::TEXTURE:
            m_texture = texture;
            break;
        default:
            m_diff_map = texture;
            m_spec_map = texture;
            m_normal_map = texture;
            m_texture = texture;
        }
    }
    std::shared_ptr<Texture2D> Material::GetTexture(MaterialProperty type)
    {
        switch (type)
        {
        case MaterialProperty::DIFFUSE_MAP:
            return (m_diff_map);
            break;
        case MaterialProperty::SPECULAR_MAP:
            return (m_spec_map);
            break;
        case MaterialProperty::NORMAL_MAP:
            return (m_normal_map);
            break;
        case MaterialProperty::TEXTURE:
        case MaterialProperty::ALL:
            return (m_texture);
            break;
        }
        return (std::shared_ptr<Texture2D>());
    }
}