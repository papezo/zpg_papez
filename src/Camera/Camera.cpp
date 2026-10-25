#include "Camera.h"
#include "../Graphics/ShaderProgram.h"


auto Camera::KeyInputs(GLFWwindow* window, float time) -> void
{
	float velocity = speed * time; // so its independent on pc hardware. using just speed var acts differently on each device...
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += velocity * Orientation;
		notify();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += velocity * -Orientation;
		notify();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += velocity * -glm::normalize(glm::cross(Orientation, up));
		notify();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += velocity * glm::normalize(glm::cross(Orientation, up));
		notify();
	}

}
auto Camera::MouseInputs(GLFWwindow* window) -> void
{
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		if (firstClick)
		{
			lastX = mouseX;
			lastY = mouseY;
			firstClick = false;
		}

		float rotX = sensitivity * static_cast<float>(mouseY - lastY);
		float rotY = sensitivity * static_cast<float>(mouseX - lastX);

		lastX = mouseX;
		lastY = mouseY;

		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, up)));

		if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		Orientation = glm::rotate(Orientation, glm::radians(-rotY), up);
		notify();
	}
	else {
		firstClick = true;
	}

}

auto Camera::resize(int newWidth, int newHeight) -> void {
	if (newWidth <= 0 || newHeight <= 0) {
		return;
	}

	width = newWidth;
	height = newHeight;

}

auto Camera::addObserver(std::shared_ptr<Observer> observer) -> void
{
	observers.push_back(observer);
}

auto Camera::notify() -> void
{
	for (auto& obs : observers)
	{
		if (auto observer = obs.lock())
		{
			observer->update(matrixView());
		}
	}
}




auto Camera::matrixView() const -> glm::mat4 
{
	return glm::lookAt(Position, Position + Orientation, up);
}

auto Camera::matrixProjection(float fovDeg, float near, float far) const -> glm::mat4
{
	return glm::perspective(glm::radians(fovDeg), (float)(width) / (float)(height), near, far);
}