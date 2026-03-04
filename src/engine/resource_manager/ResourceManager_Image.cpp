#include <iostream>

#include "ResourceManager.hpp"

namespace FT {
	std::shared_ptr<Texture2D> ResourceManager::read_image(const std::string & path, int desired_channels)
	{
        unsigned char * data;
        int width, height, chn;

		data = stbi_load(path.c_str(), &width, &height, &chn, desired_channels);
        if (!data)
            return std::shared_ptr<Texture2D>();
        std::shared_ptr<Texture2D> tex = std::make_shared<Texture2D>(data, width, height, chn);
        stbi_image_free(data);

		return (tex);
	}

    /* IMAGE utillites */
    std::shared_ptr<Texture2D> ResourceManager::LoadImage(const std::string & path)
    {
        std::map<std::string, std::shared_ptr<Texture2D>>::iterator it = this->m_images.find(path);

        if (it != this->m_images.end())
            return it->second;
        
        std::shared_ptr<Texture2D> tex = read_image(path, 0);
        if (!tex)
            return this->m_DEFAULT_TEXTURE;

        this->m_images.insert(std::make_pair(path, tex));
        return tex;
    }
}