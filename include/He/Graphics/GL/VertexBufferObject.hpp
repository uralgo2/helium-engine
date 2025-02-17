#ifndef HELIUM_GRAPHICS_GL_VERTEXBUFFEROBJECT_HPP
#define HELIUM_GRAPHICS_GL_VERTEXBUFFEROBJECT_HPP
#include <GL/glew.h>
#include <cstddef>
#include <He/Graphics/GL/VertexArrayObject.hpp>
namespace He::Graphics::GL
{
    class VertexBufferObject {
        private:      
        friend class VertexArrayObject;
        GLuint handler;  
        public:
        VertexBufferObject();
        ~VertexBufferObject();

        template<typename T> void SetData(std::size_t size, const T* dataPtr, GLenum usage){
            glNamedBufferData(this->handler, size, dataPtr, usage);
        };
    };
} // namespace He::Graphics::GL


#endif