#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include <filesystem>

#include <stb_image.h>

#include "../resources/Shader.hpp"
#include "../resources/Texture2D.hpp"
#include "../resources/Material.hpp"
#include "../resources/Geometry.hpp"
#include "../resources/Mesh.hpp"
#include "../resources/Model.hpp"
#include "../Vertex.hpp"

namespace FT {
    class ResourceManager
    {
    private:
        std::map<std::string, std::shared_ptr<Texture2D> >  m_images;
        std::map<std::string, std::shared_ptr<Shader> >     m_shaders;
        
        std::shared_ptr<Shader>                       m_DEFAULT_SHADER;
        std::shared_ptr<Texture2D>                    m_DEFAULT_TEXTURE;

        ResourceManager();
        ResourceManager(const ResourceManager & o);

    public:
        ResourceManager(const std::string & default_shader, const std::string & default_texture)
            :m_DEFAULT_SHADER(read_shader(default_shader)), m_DEFAULT_TEXTURE(read_image(default_texture))
        {
        }
        ~ResourceManager()
        {
        }

        std::shared_ptr<Shader>     LoadShader(const std::string & path);
        std::shared_ptr<Texture2D>  LoadImage(const std::string & path);
        Model                       LoadModel(const std::string& path);
        Mesh                        LoadMesh(Mesh::MeshType type);

        std::shared_ptr<Shader>     GetDefaultShader() const { return this->m_DEFAULT_SHADER; }
        std::shared_ptr<Texture2D>  GetDefaultTexture() const { return this->m_DEFAULT_TEXTURE; }

        // Clean checks and destroy resources that are not being used anymore
        void Clean();

    private:
        std::vector<Mesh>               mesh_obj_reader(const std::string& path);
        std::map<std::string, Material> mesh_mtl_reader(const std::string& path);
	    std::shared_ptr<Texture2D>      read_image(const std::string & path, int desired_channels = 0);
        std::shared_ptr<Shader>         read_shader(const std::string & path);
        std::shared_ptr<Shader>         read_shader(const std::string & v_path, const std::string & f_path);
        Mesh                            load_rect();
        Mesh                            load_cube(bool face_normals = false);
    };
}