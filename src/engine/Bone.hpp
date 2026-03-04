#pragma once

#include <string>

#include <glad/glad.h>

namespace FT {
	struct Bone
	{
		std::string name;
		std::string node_name;
		int 		id;
		FT::mat4 	offset;
		FT::mat4 	final_transform;

		Bone()
			:name(), node_name(), id(-1), offset(1.0f), final_transform(1.0f)
		{
		}
		Bone(std::string name_, std::string node_name_, int id_, FT::mat4 offset_)
			:name(name_), node_name(node_name_), id(id_), offset(offset_), final_transform(1.0f)
		{
		}
	};
}