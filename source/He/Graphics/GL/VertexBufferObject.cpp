#include <He/Graphics/GL/VertexBufferObject.hpp>

namespace He::Graphics::GL {
    VertexBufferObject::VertexBufferObject()
    {
        glCreateBuffers(1, &this->handler);
    }
    VertexBufferObject::~VertexBufferObject()
    {
        glDeleteBuffers(1, &this->handler);
    }
}