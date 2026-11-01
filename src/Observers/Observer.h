#pragma once
#include <glm/glm.hpp>

class Observer 
{
public:
	virtual auto update(const glm::mat4& view, const glm::vec3& position) -> void = 0;
	virtual ~Observer() = default;
};