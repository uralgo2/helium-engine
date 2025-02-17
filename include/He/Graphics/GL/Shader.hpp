#ifndef HELIUM_GRAPHICS_GL_SHADER_HPP
#define HELIUM_GRAPHICS_GL_SHADER_HPP
#include <He/Graphics/GL/VertexArrayObject.hpp>

#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

namespace He::Graphics::GL {
    class Mesh;
    class Shader {
    private:
        std::unordered_map<std::string, GLint> _uniformsLocations;
    public:GLuint _handler;
        GLint getUniformLocation(const std::string& name);
        public:
        Shader(const char* frag, const char* vert);
        ~Shader();
        void DrawArrays(const VertexArrayObject &vao, int first, int count);
        void DrawElements(const VertexArrayObject &vao, int count);
        void Draw(const Mesh& mesh);
        void Use();
        void SetUniform(const std::string& name, float value);
        void SetUniform(const std::string& name, float x, float y);
        void SetUniform(const std::string& name, float x, float y, float z);
        void SetUniform(const std::string& name, float x, float y, float z, float w);
        void SetUniform(const std::string &name, const glm::vec2& value);
        void SetUniform(const std::string& name, const glm::vec3& value);
        void SetUniform(const std::string& name, const glm::vec4& value);
        void SetUniform(const std::string& name, const glm::mat4& value);
    };
}

#endif