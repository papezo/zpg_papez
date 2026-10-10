#include "SceneCreator.h"
#include "../Graphics/Scene.h"
#include "../Graphics/Model.h"
#include "../Graphics/DrawableObject.h"
#include "../Models/earth.h"



auto SceneCreator::createEarth() -> Scene
{
	Scene scene;
	auto earthModel = std::make_shared<Model>(earth, sizeof(earth) / sizeof(float), 9);
	auto earthShader = std::make_shared<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");
	auto earthObject = std::make_unique<DrawableObject>(earthModel, earthShader);
	earthObject->transformation.setScale(0.35f);
	scene.addObject(std::move(earthObject));
	return scene;
}