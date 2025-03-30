#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <string>
#include <iostream>

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
		void SetVec2(const std::string & name, glm::vec2 value) const;
		void SetVec3(const std::string & name, glm::vec3 value) const;
		void SetVec4(const std::string & name, glm::vec4 value) const;
		void SetMat4(const std::string & name, glm::mat4 value) const;
		void SetMat3(const std::string & name, glm::mat3 value) const;

		unsigned int GetId();
	};
}