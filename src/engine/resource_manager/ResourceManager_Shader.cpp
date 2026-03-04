#include "ResourceManager.hpp"

#include <iostream>

// https://stackoverflow.com/questions/9641960/c11-make-pair-with-specified-template-parameters-doesnt-compile

namespace FT {
    std::shared_ptr<Shader> ResourceManager::read_shader(const std::string & path)
    {
        enum ShaderIndex
		{
			VERTEX = 0,
			FRAGMENT = 1,
			NONE = -1
		};
		ShaderIndex current_shader = ShaderIndex::NONE;
		std::stringstream ss[2];

		std::fstream file(path);

		if (file.is_open() == false)
		{
			std::cout << "ERROR::RESOURCE_MANAGER::SHADER::FILE_NOT_FOUND: " << path << std::endl;
			return (std::shared_ptr<Shader>());
		}

		std::string line;
		while (std::getline(file, line))
		{
			if (line.find("#shader vertex") != std::string::npos)
				current_shader = ShaderIndex::VERTEX;
			else if (line.find("#shader fragment") != std::string::npos)
				current_shader = ShaderIndex::FRAGMENT;

			else if (current_shader != ShaderIndex::NONE)
				ss[current_shader] << line << "\n";
		}
		std::string vert_str = ss[ShaderIndex::VERTEX].str();
		std::string frag_str = ss[ShaderIndex::FRAGMENT].str();

		std::shared_ptr<Shader> sh = std::make_shared<Shader>(vert_str, frag_str);
		if (!sh->GetId())
			return (std::shared_ptr<Shader>());
		return (sh);
    }

    std::shared_ptr<Shader> ResourceManager::read_shader(const std::string & v_path, const std::string & f_path)
    {
		std::fstream v_file(v_path);
		std::fstream f_file(f_path);

		std::string vert_str;
		std::string frag_str;

		std::string line;
		while (std::getline(v_file, line))
			vert_str += (line + "\n");

		while (std::getline(f_file, line))
			frag_str += (line + "\n");

		std::shared_ptr<Shader> sh = std::make_shared<Shader>(vert_str, frag_str);
		if (!sh->GetId())
			return (std::shared_ptr<Shader>());
		return (sh);
    }

    /* SHADER utillites */
    std::shared_ptr<Shader> ResourceManager::LoadShader(const std::string & path)
    {
        std::map<std::string, std::shared_ptr<Shader>>::iterator it = this->m_shaders.find(path);

		if (it != this->m_shaders.end())
			return it->second;
        
        std::shared_ptr<Shader> sh = read_shader(path);
		if (!sh)
			return this->m_DEFAULT_SHADER;

        this->m_shaders.insert(std::make_pair(path, sh));
        return sh;
	}
}