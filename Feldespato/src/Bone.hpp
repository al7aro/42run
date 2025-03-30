#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>

namespace FT {
	struct Bone
	{
		std::string name;
		std::string node_name;
		int 		id;
		glm::mat4 	offset;
		glm::mat4 	final_transform;

		Bone()
			:name(), node_name(), id(-1), offset(1.0f), final_transform(1.0f)
		{
		}
		Bone(std::string name_, std::string node_name_, int id_, glm::mat4 offset_)
			:name(name_), node_name(node_name_), id(id_), offset(offset_), final_transform(1.0f)
		{
		}
	};
}