#include "Shader.hpp"

namespace FT {
	Shader::Shader(const std::string & vert_src, const std::string & frag_src)
	{
		m_Compile(vert_src, frag_src);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_id);
		m_id = 0;
	}

	void Shader::m_Compile(const std::string & vert_src, const std::string & frag_src)
	{
		m_id = glCreateProgram();

		const char * v_buff = vert_src.c_str();
		const char * f_buff = frag_src.c_str();

		unsigned int v_id = glCreateShader(GL_VERTEX_SHADER);
		unsigned int f_id = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(v_id, 1, &v_buff, NULL);
		glShaderSource(f_id, 1, &f_buff, NULL);

		glCompileShader(v_id);
		glCompileShader(f_id);

		int v_status, f_status;
		char buff[512];
		glGetShaderiv(f_id, GL_COMPILE_STATUS, &v_status);
		glGetShaderInfoLog(f_id, sizeof(buff), 0, buff);
		if (v_status != GL_TRUE)
			std::cout << "ERROR::SHADER::FRAGMENT:\n" << buff << std::endl;
		glGetShaderiv(v_id, GL_COMPILE_STATUS, &f_status);
		glGetShaderInfoLog(v_id, sizeof(buff), 0, buff);
		if (f_status != GL_TRUE)
			std::cout << "ERROR::SHADER::VERTEX:\n" << buff << std::endl;
		if (v_status != GL_TRUE || f_status != GL_TRUE)
		{
			glDeleteShader(v_id);
			glDeleteShader(f_id);
			glDeleteProgram(m_id);
			m_id = 0;
			return ;
		}

		glAttachShader(m_id, v_id);
		glAttachShader(m_id, f_id);

		glLinkProgram(m_id);

		glDetachShader(m_id, v_id);
		glDeleteShader(v_id);
		glDetachShader(m_id, f_id);
		glDeleteShader(f_id);
	}

	void Shader::Enable() const
	{
		glUseProgram(m_id);
	}

	void Shader::Disable() const
	{
		glUseProgram(0);
	}

	void Shader::SetInt(const std::string & name, int value) const
	{
		glProgramUniform1i(m_id, glGetUniformLocation(m_id, name.c_str()), value);
	}
	void Shader::SetFloat(const std::string & name, float value) const
	{
		glProgramUniform1f(m_id, glGetUniformLocation(m_id, name.c_str()), value);
	}
	void Shader::SetVec2(const std::string & name, FT::vec2 value) const
	{
		glProgramUniform2fv(m_id, glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
	}
	void Shader::SetVec3(const std::string & name, FT::vec3 value) const
	{
		glProgramUniform3fv(m_id, glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
	}
	void Shader::SetVec4(const std::string & name, FT::vec4 value) const
	{
		glProgramUniform4fv(m_id, glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
	}
	void Shader::SetMat4(const std::string & name, FT::mat4 value) const
	{
		glProgramUniformMatrix4fv(m_id, glGetUniformLocation(m_id, name.c_str()), 1, false, &value[0]);
	}
	void Shader::SetMat3(const std::string & name, FT::mat3 value) const
	{
		glProgramUniformMatrix3fv(m_id, glGetUniformLocation(m_id, name.c_str()), 1, false, &value[0]);
	}
	
	unsigned int Shader::GetId()
	{
		return (m_id);
	}
}