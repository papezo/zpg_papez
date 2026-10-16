#include "Camera.h"
#include "ShaderProgram.h"


auto Camera::KeyInputs(GLFWwindow* window, float time) -> void
{
	float velocity = speed * time; // so its independent on pc hardware. using just speed var acts differently on each device...
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += velocity * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += velocity * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += velocity * -glm::normalize(glm::cross(Orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += velocity * glm::normalize(glm::cross(Orientation, up));
	}

}
auto Camera::MouseInputs(GLFWwindow* window) -> void
{
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double mouseX, mouseY; // cant use float for glfwGetCursorPos
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
	}
	else {
		firstClick = true;
	}

}




auto Camera::matrixView() const -> glm::mat4 
{
	return glm::lookAt(Position, Position + Orientation, up);
}

auto Camera::matrixProjection(float fovDeg, float nearPlane, float farPlane) const -> glm::mat4
{
	return glm::perspective(glm::radians(fovDeg), (float)(width) / (float)(height), nearPlane, farPlane);
}