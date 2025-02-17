#ifndef HELIUM_GRAPHICS_GL_ELEMENTBUFFEROBJECT_HPP
#define HELIUM_GRAPHICS_GL_ELEMENTBUFFEROBJECT_HPP
#include <GL/glew.h>
#include <cstddef>
#include <He/Graphics/GL/VertexArrayObject.hpp>
namespace He::Graphics::GL
{
    class ElementBufferObject {
        private:      
        friend class VertexArrayObject;
        GLuint handler;  
        public:
        ElementBufferObject();
        ~ElementBufferObject();

        template<typename T> void SetData(std::size_t size, const T* dataPtr, GLenum usage){
            glNamedBufferData(this->handler, size, dataPtr, usage);
        };
    };
} // namespace He::Graphics::GL


#endif