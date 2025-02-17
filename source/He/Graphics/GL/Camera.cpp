//
// Created by uralg on 16.02.2025.
//
#include <He/Graphics/GL/Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace He::Graphics::GL {
	Camera* Camera::Active = nullptr;

	Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front, glm::vec3 right, glm::vec3 rotation, float fov,
		float aspect, float near, float far):   _position(position),
												_up(up),
												_front(front),
												_right(right),
												_rotation(rotation),
												_fov(fov),
												_aspect(aspect),
												_near(near),
												_far(far) {
		this->_projection = glm::perspective(fov, aspect, near, far);
		this->_view = glm::lookAt(_position, front, up);
	}

	void Camera::SetPosition(const glm::vec3& position) {
		this->_position = position;
	}

	void Camera::SetPosition(float x, float y, float z) {
		this->_position = glm::vec3(x, y, z);
	}

	void Camera::SetRotation(const glm::vec3 &rotation) {
		this->_rotation = rotation;
		float pitch = glm::radians(rotation.x); // Вращение вокруг X
		float yaw   = glm::radians(rotation.y); // Вращение вокруг Y
		float roll  = glm::radians(rotation.z); // Вращение вокруг Z

		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, pitch, glm::vec3(1.0f, 0.0f, 0.0f)); // X
		rotationMatrix = glm::rotate(rotationMatrix, yaw,   glm::vec3(0.0f, 1.0f, 0.0f)); // Y
		rotationMatrix = glm::rotate(rotationMatrix, roll,  glm::vec3(0.0f, 0.0f, 1.0f)); // Z

	}

	const glm::vec3 & Camera::Position() const {
		return this->_position;
	}

	const glm::vec3 & Camera::Rotation() const {
		return this->_rotation;
	}

	glm::mat4 Camera::ProjectionMatrix() const {
		return _projection;
	}

	glm::mat4 Camera::ViewMatrix() const {
		return _view;
	}

	void Camera::Select() {
		Camera::Active = this;
	}
}
