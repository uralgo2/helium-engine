#include <He/Graphics/GL/VertexArrayObject.hpp>
#include <He/Graphics/GL/VertexBufferObject.hpp>
#include <He/Graphics/GL/ElementBufferObject.hpp>

namespace He::Graphics::GL {
    VertexArrayObject::VertexArrayObject()
    {
        glCreateVertexArrays(1, &this->handler);
    }
    VertexArrayObject::~VertexArrayObject()
    {
        glDeleteVertexArrays(1, &this->handler);
    }

    void VertexArrayObject::BindElementBuffer(ElementBufferObject &ebo) {
        glVertexArrayElementBuffer(this->handler, ebo.handler);
    }

    void VertexArrayObject::BindVertexBuffer(VertexBufferObject& vbo, GLuint bindingIndex, GLintptr offset, std::size_t stride){
        glVertexArrayVertexBuffer(this->handler, bindingIndex, vbo.handler, offset, stride);
    }
    void VertexArrayObject::AttribFormat(GLuint attribIndex, GLint size, GLenum type, bool normalized, GLuint roffset)
    {
        glVertexArrayAttribFormat(this->handler, attribIndex, size, type, normalized, roffset);
    }
    void VertexArrayObject::AttribBinding(GLuint attribIndex, GLuint bindingIndex){
        glVertexArrayAttribBinding(this->handler, attribIndex, bindingIndex);
    }
    void VertexArrayObject::EnableAttrib(GLuint attribIndex) {
        glEnableVertexArrayAttrib(this->handler, attribIndex);
    }
    void VertexArrayObject::Bind() const{
        glBindVertexArray(this->handler);
    }
}

