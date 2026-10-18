#pragma once
#include <glad/gl.h>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Observers/Observer.h"

class Camera;
class ShaderProgram : public Observer
{
public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	ShaderProgram(Camera* camera);
	~ShaderProgram();

	auto use() const -> void;
	auto update(const glm::mat4& view) -> void override; // function so if camera annonces change -> update viewMatrix

	auto setUniform(const std::string& name, float value) -> void;
	auto setUniform(const std::string& name, float x, float y, float z) -> void;
	auto setUniform(const std::string& name, const glm::mat4& matrix) -> void;
private:
	GLuint id;
	auto createShaderFromFile(GLenum shaderType, const char* shaderFile) -> GLuint;

	Camera* m_camera;

};