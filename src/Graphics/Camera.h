#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <memory>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Observers/Observer.h"

class ShaderProgram;
class Camera
{
public:
	Camera(int width, int height, glm::vec3 position) : width{ width }, height{ height }, Position{ position } {}
	auto KeyInputs(GLFWwindow* window, float time) -> void;
	auto MouseInputs(GLFWwindow* window) -> void;
	auto matrixView() const -> glm::mat4;
	auto matrixProjection(float fovDeg = 60.0f, float nearPlane = 0.1f, float farPlane = 100.0f) const -> glm::mat4;
private:
	ShaderProgram* m_shaderProgram = nullptr;
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	int width;
	int height;

	float speed = 1.5f;
	float sensitivity = 0.1f;
	bool firstClick = true;

	double lastX = 0.0f;
	double lastY = 0.0f;

	std::vector<std::weak_ptr<Observer*>> observers;
};