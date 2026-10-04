#pragma once

#include <memory>
#include <vector>
#include <Graphics/Scene.h>

/*
	Helper class to create scenes and models for the application. 
	So it doesnt clutter the Application class with too many details.
*/
class SceneCreator
{
public:
	static auto createTriangleScene() -> std::unique_ptr<Scene>;
	static auto createSphereScene() -> std::unique_ptr<Scene>;
	static auto createForestScene() -> std::unique_ptr<Scene>;
	static auto createLoginScene() -> std::unique_ptr<Scene>;
private:
	static auto createSignature() -> std::unique_ptr<Model>;
};