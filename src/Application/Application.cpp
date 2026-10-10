#include "src/Application/Application.h"
#include "src/Miscs/SceneCreator.h"

#include <stdlib.h>
#include <stdio.h>

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

auto Application::error_callback(int error, const char* description) -> void { fputs(description, stderr); }

auto Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void
{
	auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		switch (key)
		{
		case GLFW_KEY_1:
			app->setActiveScene(0);
			break;
		case GLFW_KEY_2:
			app->setActiveScene(1);
			break;
		case GLFW_KEY_3:
			app->setActiveScene(2);
			break;
		case GLFW_KEY_4:
			app->setActiveScene(3);
			break;
		default:
			break;
		}
	}
}

auto Application::window_focus_callback(GLFWwindow* window, int focused) -> void { printf("window_focus_callback \n"); }

auto Application::window_iconify_callback(GLFWwindow* window, int iconified) -> void { printf("window_iconify_callback \n"); }

auto Application::window_size_callback(GLFWwindow* window, int width, int height) -> void {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

auto Application::cursor_callback(GLFWwindow* window, double x, double y) -> void { printf("cursor_callback \n"); }

auto Application::button_callback(GLFWwindow* window, int button, int action, int mode) -> void {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}


auto Application::initialization() -> void
{
	// Initialize GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//Initialization of a specific version
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);  //*/


	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// This is important to add bcs we need to access Application instance and without this 
	// we cant use keyboard callbacks
	glfwSetWindowUserPointer(window, this);

	// GLFW callbacks
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);

	// Initialize GLAD and load OpenGL function pointers
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		printf("GLAD initialization failed\n");
		//return -1;
	}

	// Get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	glEnable(GL_DEPTH_TEST);//Do depth comparisons and update the depth buffer.
}

auto Application::createShaders() -> void	
{
	shader = std::make_unique<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");
}


auto Application::createScenes() -> void
{
	scenes.push_back(SceneCreator::createEarth());
}

auto Application::setActiveScene(size_t index) -> void
{
	if (index >= 0 && index < scenes.size())
	{
		this->activeSceneIndex = index;
	}
	else {
		printf("This scene doesnt exist\n");
	}
}	


auto Application::run() -> void
{
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (shader && activeSceneIndex >= 0 && activeSceneIndex < scenes.size())
		{
			scenes[activeSceneIndex].render();
		}


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


Application::~Application()
{
	if (window)
	{
		glfwDestroyWindow(window);
	}
	
	glfwTerminate();
}