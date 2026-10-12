#include "SceneCreator.h"

#include "../../Models/earth.h"
#include "../../Models/moon.h"
#include "../../Models/sun.h"
#include "../../Models/triangle.h"
#include "../../Models/bushes.h"
#include "../../Models/tree.h"

#include "../Graphics/Scene.h"
#include "../Graphics/Model.h"
#include "../Graphics/DrawableObject.h"

#include "../Graphics/CompositeTransform.h"
#include "../Graphics/StaticTransformations.h"
#include "../Graphics/DynamicRotate.h"

#include <corecrt_math_defines.h> // for pi
#include <random>
#include <numbers>

auto SceneCreator::createEarth() -> std::unique_ptr<DrawableObject>
{
	auto earthModel = std::make_shared<Model>(earth, sizeof(earth) / sizeof(float), 9);
	auto earthShader = std::make_shared<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");
	auto earthObject = std::make_unique<DrawableObject>(earthModel, earthShader);

	auto composite = std::make_shared<CompositeTransform>();

	composite->add(std::make_shared<DynamicRotate>(0.0f, 0.002f, glm::vec3(0.0f, 1.0f, 0.0f))); // Earth & Sun rotation
	composite->add(std::make_shared<Translate>(0.55f, 0.0f, 0.0f));
	composite->add(std::make_shared<Scale>(0.1f));

	earthObject->setTransformation(composite);

	return earthObject;
}

auto SceneCreator::createMoon() -> std::unique_ptr<DrawableObject>
{
	auto moonModel = std::make_shared<Model>(moon, sizeof(moon) / sizeof(float), 9);
	auto moonShader = std::make_shared<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");
	auto moonObject = std::make_unique<DrawableObject>(moonModel, moonShader);

	auto composite = std::make_shared<CompositeTransform>();

	// this has to be same as first rotation of earth!
	// its for moon to rotate same as earth by the sun
	composite->add(std::make_shared<DynamicRotate>(0.0f, 0.002f, glm::vec3(0.0f, 1.0f, 0.0f))); 
	composite->add(std::make_shared<Translate>(0.55f, 0.0f, 0.0f)); // earth & sun distance
	composite->add(std::make_shared<DynamicRotate>(0.0f, 0.005f, glm::vec3(0.0f, 1.0f, 0.0f)));  // Moon & Earth rotation
	composite->add(std::make_shared<Translate>(0.20f, 0.0f, 0.0f)); // Moon & sun distance
	composite->add(std::make_shared<Scale>(0.05f));

	moonObject->setTransformation(composite);

	return moonObject;
}

auto SceneCreator::createSun() -> std::unique_ptr<DrawableObject>
{
	Scene scene;
	auto sunModel = std::make_shared<Model>(sun, sizeof(sun) / sizeof(float), 9);
	auto sunShader = std::make_shared<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");
	auto sunObject = std::make_unique<DrawableObject>(sunModel, sunShader);

	auto composite = std::make_shared<CompositeTransform>();

	composite->add(std::make_shared<Translate>(0.0f, 0.0f, 0.0f));
	composite->add(std::make_shared<DynamicRotate>(0.0f, 0.02f, glm::vec3(0.0f, 1.0f, 0.0f)));
	composite->add(std::make_shared<Scale>(0.2f));

	sunObject->setTransformation(composite);

	return sunObject;
}


auto SceneCreator::createTriangle() -> Scene
{
	Scene scene;
	auto triangleModel = std::make_shared<Model>(triangle, sizeof(triangle) / sizeof(float), 6);
	auto triangleShader = std::make_shared<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");
	auto triangleObj = std::make_unique<DrawableObject>(triangleModel, triangleShader);

	auto composite = std::make_shared<CompositeTransform>();

	composite->add(std::make_shared<Translate>(0.2f, -0.2f, 0.0f));
	composite->add(std::make_shared<DynamicRotate>(0.0f, 0.05f, glm::vec3(0.0f, 0.0f, 1.0f)));

	triangleObj->setTransformation(composite);

	scene.addObject(std::move(triangleObj));

	return scene;

}
auto SceneCreator::createForest() -> Scene
{
	Scene scene;
	float radius = 4.0f;
	float angleStep = (2.0f * M_PI) / 12.0f;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(10, 29);

	int amountOfTrees = dist(gen);
	int amountOfBushes = dist(gen);

	float bushRadius = 1.25f;
	float angleStepBushes = (2.0f * M_PI) / amountOfBushes;

	auto treeModel = std::make_shared<Model>(tree, sizeof(tree) / sizeof(float), 6);
	auto treeShader = std::make_shared<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");

	auto bushModel = std::make_shared<Model>(bushes, sizeof(bushes) / sizeof(float), 6);
	auto bushShader = std::make_shared<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");

	for (auto i = 0; i < amountOfTrees; i++)
	{
		auto treeObj = std::make_unique<DrawableObject>(treeModel, treeShader);

		auto composite = std::make_shared<CompositeTransform>();
		float angle = i * angleStep;
		float posX = std::cos(angle) * radius;
		float posY = std::sin(angle) * radius;

		composite->add(std::make_shared<Scale>(0.08f));
		composite->add(std::make_shared<Translate>(posX, posY, 0.0f));

		treeObj->setTransformation(composite);
		scene.addObject(std::move(treeObj));

	}

	for (auto i = 0; i < amountOfBushes; i++)
	{
		auto bushObj = std::make_unique<DrawableObject>(bushModel, bushShader);

		auto composite = std::make_shared<CompositeTransform>();

		float angle = i * angleStepBushes;
		float posX = std::cos(angle) * bushRadius;
		float posY = std::sin(angle) * bushRadius;

		composite->add(std::make_shared<Scale>(0.5f));
		composite->add(std::make_shared<Translate>(posX, posY, 0.0f));
		


		bushObj->setTransformation(composite);
		scene.addObject(std::move(bushObj));
	}

	return scene;
}
auto SceneCreator::createSolarSystem() -> Scene
{
	Scene scene;
	scene.addObject(createSun());
	scene.addObject(createMoon());
	scene.addObject(createEarth());


	return scene;
}