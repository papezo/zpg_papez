#pragma once

#pragma once
#include <memory>
#include "../Graphics/Scene.h"
#include "../Graphics/DrawableObject.h"

/*
	Helper class to create scenes and models for the application. 
	So it doesnt clutter the Application class with too many details.
*/
class SceneCreator
{
public:
    static auto createEarth() -> std::unique_ptr<DrawableObject>;
	static auto createSun() -> std::unique_ptr<DrawableObject>;
	static auto createMoon() -> std::unique_ptr<DrawableObject>;
	static auto createTriangle() -> Scene;
	static auto createForest() -> Scene;
	static auto createSolarSystem() -> Scene;
};