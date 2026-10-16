#pragma once
#include "ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>

class Transformation
{
public:
	virtual ~Transformation() = default;
	virtual auto getModelMatrix() -> glm::mat4 = 0; // returns actual matrix
};