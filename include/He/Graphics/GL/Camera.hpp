//
// Created by uralg on 16.02.2025.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm/glm.hpp>
namespace He::Graphics::GL {
class Camera {
private:
	glm::vec3 _position;
	glm::vec3 _up, _front, _right;
	glm::vec3 _rotation;
	glm::mat4 _projection, _view;
	float _fov, _aspect, _near, _far;

public:
	static Camera* Active;

    Camera(
    	glm::vec3 position = glm::vec3(0.0f),
    	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
    	glm::vec3 front = glm::vec3(1.0f, 0.0f, 0.0f),
    	glm::vec3 right = glm::vec3(0.0f, 0.0f, 1.0f),
    	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
    	float fov = glm::radians(45.0f),
    	float aspect = 16.0f / 9.0f,
    	float near = 0.1f,
    	float far = 100.0f);
    ~Camera();

	void SetPosition(const glm::vec3& position);
	void SetPosition(float x, float y, float z);
	void SetRotation(const glm::vec3& rotation);

	const glm::vec3& Position() const;
	const glm::vec3& Rotation() const;
	glm::mat4 ProjectionMatrix() const;
	glm::mat4 ViewMatrix() const;
	void Select();
};
}

#endif //CAMERA_HPP
