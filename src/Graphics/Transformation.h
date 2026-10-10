#pragma once
#include "ShaderProgram.h"
#include "../../libs/glm/glm/glm.hpp"
#include "../../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../../libs/glm/glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>

class Transformation
{
public:
	virtual ~Transformation() = default;
	virtual auto getModelMatrix() -> glm::mat4 = 0; // returns actual matrix
};