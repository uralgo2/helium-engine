#ifndef HELIUM_GRAPHICS_GL_MESH_HPP
#define HELIUM_GRAPHICS_GL_MESH_HPP
#include <He/Graphics/GL/VertexArrayObject.hpp>
#include <He/Graphics/GL/VertexBufferObject.hpp>
#include <He/Graphics/GL/ElementBufferObject.hpp>
#include <He/Graphics/GL/Shader.hpp>
#include <He/Utils/Array.hpp>
#include <glm/glm.hpp>

namespace He::Graphics::GL {
    class Mesh {
    private:
        VertexArrayObject _vao;
        VertexBufferObject _vbo;
        ElementBufferObject _ebo;

        Utils::Array<glm::vec3> _vertices;
        Utils::Array<glm::vec3> _normals;
        Utils::Array<glm::vec2> _uvs;
        Utils::Array<unsigned int> _indices;
        friend class Shader;
        public:
        struct Vertex {
            glm::vec3 Position;
            glm::vec3 Normal;
            glm::vec2 UV;
        };
        Mesh();
        Mesh(const Utils::Array<glm::vec3>& vertices, const Utils::Array<glm::vec3>& normals, const Utils::Array<glm::vec2>& uvs, const Utils::Array<unsigned int>& indices);
        ~Mesh();
        Utils::Array<glm::vec3>& Vertices() ;
        Utils::Array<glm::vec3>& Normals() ;
        Utils::Array<glm::vec2>& UVs() ;
        Utils::Array<unsigned int>& Indices() ;

        void SetVertices(const Utils::Array<glm::vec3>& vertices);
        void SetNormals(const Utils::Array<glm::vec3>& normals);
        void SetUVs(const Utils::Array<glm::vec2>& uvs);
        void SetIndices(const Utils::Array<unsigned int>& indices);

        void Setup();

        void Draw();
    };
}

#endif