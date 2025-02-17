#ifndef HELIUM_GRAPHICS_GL_VERTEXARRAYOBJECT_HPP
#define HELIUM_GRAPHICS_GL_VERTEXARRAYOBJECT_HPP
#include <GL/glew.h>
#include <cstddef>

namespace He::Graphics::GL
{
    class VertexBufferObject;
    class ElementBufferObject;

    class VertexArrayObject {
        private:      
        GLuint handler; 
        public: 
        VertexArrayObject();
        ~VertexArrayObject();
        void BindElementBuffer(ElementBufferObject& ebo);
        void BindVertexBuffer(VertexBufferObject& vbo, GLuint bindingIndex, GLintptr offset, std::size_t stride);
        void AttribFormat(GLuint attribIndex, GLint size, GLenum type, bool normalized, GLuint roffset);
        void AttribBinding(GLuint attribIndex, GLuint bindingIndex);
        void EnableAttrib(GLuint attribIndex);
        void Bind() const;
    };
} // namespace He::Graphics::GL


#endif