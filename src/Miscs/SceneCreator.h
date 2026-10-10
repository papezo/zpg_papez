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
    static auto createEarth() -> Scene;

private:
    static auto createSignature() -> std::unique_ptr<DrawableObject>;
};