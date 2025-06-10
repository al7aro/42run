#include "Mesh.hpp"

namespace FT {
    Mesh::Mesh() {}
    Mesh::Mesh(const Mesh & o)
        : m_geometry(o.m_geometry), m_material(o.m_material), m_node_name(o.m_node_name) {}
    Mesh & Mesh::operator=(const Mesh & o)
    {
        m_geometry = o.m_geometry;
        m_material = o.m_material;
        m_node_name = o.m_node_name;
        return (*this);
    }
    Mesh::Mesh(const Geometry & geom, const Material & mat)
    {
        m_geometry = geom;
        m_material = mat;
    }

    void Mesh::SetNodeName(const std::string& node_name)
    {
        m_node_name = node_name;
    }

    const std::string& Mesh::GetNodeName()
    {
        return (m_node_name);
    }

    void Mesh::SetGeometry(const Geometry & geom)
    {
        m_geometry = geom;
    }

    void Mesh::SetMaterial(const Material & mat)
    {
        m_material = mat;
    }


    const Geometry & Mesh::GetGeometry() const
    {
        return m_geometry;
    }
    const Material & Mesh::GetMaterial() const
    {
        return m_material;
    }

    void Mesh::SetColor(const FT::vec3 & col)
    {
        m_material.SetColor(col);
    }
    void Mesh::SetTexture(const std::shared_ptr<Texture2D> & tex, Material::MaterialProperty type)
    {
        m_material.SetTexture(tex, type);
    }
}