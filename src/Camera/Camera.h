#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <memory>
#include <vector>
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
	auto matrixProjection(float fovDeg = 60.0f, float near = 0.1f, float far = 10000.0f) const -> glm::mat4;
	auto resize(int newWidth, int newHeight) -> void;
	auto addObserver(std::shared_ptr<Observer> observer) -> void;
	auto notify() -> void;
private:
	ShaderProgram* m_shaderProgram{ nullptr };
	glm::vec3 Position { 0.0f, 0.0f, 0.0f };
	glm::vec3 Orientation{ 0.0f, 0.0f, -1.0f };
	glm::vec3 up{ 0.0f, 1.0f, 0.0f };

	int width{ 0 };
	int height{ 0 };

	float speed{ 300.5f };
	float sensitivity{ 0.5f };
	bool firstClick{true};

	double lastX{ 0.0f };
	double lastY{ 0.0f };

	std::vector<std::weak_ptr<Observer>> observers;
};