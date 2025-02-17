//
// Created by uralg on 13.02.2025.
//
#include <He/Graphics/GL/ElementBufferObject.hpp>

namespace He::Graphics::GL {
	ElementBufferObject::ElementBufferObject() {
		glCreateBuffers(1, &this->handler);
	}

	ElementBufferObject::~ElementBufferObject() {
		glDeleteBuffers(1, &this->handler);
	}
}
