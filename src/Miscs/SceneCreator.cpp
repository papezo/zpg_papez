#include "SceneCreator.h"
#include "../Graphics/Scene.h"
#include "../Graphics/Model.h"
#include "../Graphics/DrawableObject.h"
#include "../Models/earth.h"
#include "../Graphics/CompositeTransform.h"
#include "../Graphics/StaticTransformations.h"
#include "../Graphics/DynamicRotate.h"


auto SceneCreator::createEarth() -> Scene
{
	Scene scene;
	auto earthModel = std::make_shared<Model>(earth, sizeof(earth) / sizeof(float), 9);
	auto earthShader = std::make_shared<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");
	auto earthObject = std::make_unique<DrawableObject>(earthModel, earthShader);

	auto composite = std::make_shared<CompositeTransform>();

	composite->add(std::make_shared<Translate>(0.0f, 0.0f, 0.0f));

	composite->add(std::make_shared<DynamicRotate>(0.0f, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f)));
	composite->add(std::make_shared<Scale>(0.5f));

	earthObject->setTransformation(composite);

	scene.addObject(std::move(earthObject));

	return scene;
}