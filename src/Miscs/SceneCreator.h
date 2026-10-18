#pragma once

#pragma once
#include <memory>
#include "Graphics/Scene.h"
#include "Graphics/DrawableObject.h"
#include "Graphics/Camera.h"

/*
	Helper class to create scenes and models for the application. 
	So it doesnt clutter the Application class with too many details.
*/
class SceneCreator
{
public:
	static auto createMoon(Camera& camera) -> std::unique_ptr<DrawableObject>;
	static auto createClock(float x, float z, Camera& camera)->std::unique_ptr<DrawableObject>;
	static auto createForest(Camera& camera) -> Scene;
};