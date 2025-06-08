#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>

#include "../math/Math.hpp"

namespace FT {
	class Shader
	{
	private:
		unsigned int m_id;

		Shader();
		Shader(const Shader &a);
		Shader & operator = (const Shader &a);
		void m_Compile(const std::string & vert_src, const std::string & frag_src);

	public:
		Shader(const std::string & vert_src, const std::string & frag_src);
		~Shader();

		void Enable() const;
		void Disable() const;

		void SetInt(const std::string & name, int value) const;
		void SetFloat(const std::string & name, float value) const;
		void SetVec2(const std::string & name, FT::vec2 value) const;
		void SetVec3(const std::string & name, FT::vec3 value) const;
		void SetVec4(const std::string & name, FT::vec4 value) const;
		void SetMat4(const std::string & name, FT::mat4 value) const;
		void SetMat3(const std::string & name, FT::mat3 value) const;

		unsigned int GetId();
	};
}