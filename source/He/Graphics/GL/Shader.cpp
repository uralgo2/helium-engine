//
// Created by uralg on 13.02.2025.
//
#include <He/Graphics/GL/Shader.hpp>
#include <He/Graphics/GL/Mesh.hpp>
#include <stdexcept>
#include <fmt/core.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>

namespace He::Graphics::GL {
	GLint Shader::getUniformLocation(const std::string &name) {
		if (const auto it =this->_uniformsLocations.find(name); it != this->_uniformsLocations.end()) {
			return it->second;
		}
			GLint loc = glGetUniformLocation(this->_handler, name.c_str());

		if (loc == -1) {
			throw std::runtime_error("Could not find uniform location: " + name);
		}

		this->_uniformsLocations.emplace(name, loc);

		return loc;
	}

	Shader::Shader(const char *frag, const char *vert) {
		GLint success;
		GLchar infoLog[512];
		const GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		const GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertShader, 1, &vert, nullptr);
		glCompileShader(vertShader);

		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertShader, 512, nullptr, infoLog);
			throw std::runtime_error(fmt::format("VERTEX SHADER COMPILATION FAILED: {}", infoLog));
		}

		glShaderSource(fragShader, 1, &frag, nullptr);
		glCompileShader(fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
			throw std::runtime_error(fmt::format("FRAGMENT SHADER COMPILATION FAILED: {}", infoLog));
		}
		this->_handler = glCreateProgram();

		glAttachShader(this->_handler, vertShader);
		glAttachShader(this->_handler, fragShader);
		glLinkProgram(this->_handler);

		glGetProgramiv(this->_handler, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->_handler, 512, nullptr, infoLog);
			throw std::runtime_error(fmt::format("SHADER LINKAGE FAILED: {}", infoLog));
		}

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}
	Shader::~Shader() {
		glDeleteProgram(this->_handler);
	}
	void Shader::DrawArrays(const VertexArrayObject &vao, const int first, const int count) {
		glUseProgram(this->_handler);
		vao.Bind();
		glDrawArrays(GL_TRIANGLES, first, count);
	}

	void Shader::DrawElements(const VertexArrayObject &vao, const int count) {
		glUseProgram(this->_handler);
		vao.Bind();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
	void Shader::Draw(const Mesh &mesh) {
		glUseProgram(this->_handler);
		mesh._vao.Bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh._indices.size()), GL_UNSIGNED_INT, nullptr);
	}
	void Shader::Use() {
		glUseProgram(this->_handler);
	}
	void Shader::SetUniform(const std::string &name, const float value) {
		glProgramUniform1f(this->_handler, this->getUniformLocation(name), value);
	}
	void Shader::SetUniform(const std::string &name, const float x, const float y) {
		glProgramUniform2f(this->_handler, this->getUniformLocation(name), x, y);
	}
	void Shader::SetUniform(const std::string &name, const float x, const float y, const float z) {
		glProgramUniform3f(this->_handler, this->getUniformLocation(name), x, y, z);
	}
	void Shader::SetUniform(const std::string &name, const float x, const float y, const float z, const float w) {
		glProgramUniform4f(this->_handler, this->getUniformLocation(name), x, y, z, w);
	}

	void Shader::SetUniform(const std::string &name, const glm::vec2& value) {
		glProgramUniform2f(this->_handler, this->getUniformLocation(name), value.x, value.y);
	}

	void Shader::SetUniform(const std::string &name, const glm::vec3& value) {
		glProgramUniform3f(this->_handler, this->getUniformLocation(name), value.x, value.y, value.z);
	}

	void Shader::SetUniform(const std::string &name, const glm::vec4& value) {
		glProgramUniform4f(this->_handler, this->getUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void Shader::SetUniform(const std::string &name, const glm::mat4& value) {
		glProgramUniformMatrix4fv(this->_handler, this->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}
}
