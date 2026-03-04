#pragma once

#include <memory>

#include "Geometry.hpp"
#include "Material.hpp"

namespace FT {
    class Mesh
    {
    public:
        enum MeshType
        {
            RECT,
            CUBE
        };
    private:
        Geometry m_geometry;
        Material m_material;
        std::string m_node_name;

    public:
        Mesh();
        Mesh(const Mesh & o);
        Mesh & operator=(const Mesh & o);
        Mesh(const Geometry & geom, const Material & mat);

        void                SetNodeName(const std::string& node_name);
        void                SetGeometry(const Geometry & geom);
		void                SetMaterial(const Material & mat);
        void                SetColor(const FT::vec3 & col);
        void                SetTexture(const std::shared_ptr<Texture2D> & tex, Material::MaterialProperty type);
        const std::string & GetNodeName();
        const Geometry    & GetGeometry() const;
        const Material    & GetMaterial() const;
    };
}