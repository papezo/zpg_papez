#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <vector>
#include <memory>

#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Scene.h"

class Application
{
public:
	auto createShaders() -> void;
	auto initialization() -> void;
	auto createScenes() -> void;
	auto setActiveScene(size_t index) -> void;
	auto run() -> void;

	~Application();
	Application() = default;

private:
	GLFWwindow* window = nullptr;
	std::unique_ptr<ShaderProgram> shader;
	std::vector<Scene> scenes;
	int activeSceneIndex = 0;


	static auto error_callback(int error, const char* description) -> void;
	static auto key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void;
	static auto window_focus_callback(GLFWwindow* window, int focused) -> void;
	static auto window_iconify_callback(GLFWwindow* window, int iconified) -> void;
	static auto window_size_callback(GLFWwindow* window, int width, int height) -> void;
	static auto cursor_callback(GLFWwindow* window, double x, double y) -> void;
	static auto button_callback(GLFWwindow* window, int button, int action, int mode) -> void;

};
