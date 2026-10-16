#include "SceneCreator.h"

#include "Models/moon.h"
#include "Models/sun.h"
#include "Models/bushes.h"
#include "Models/tree.h"
#include "Models/grass.h"
#include "Models/clock.h"

#include "Graphics/Scene.h"
#include "Graphics/Model.h"
#include "Graphics/DrawableObject.h"

#include "Graphics/CompositeTransform.h"
#include "Graphics/StaticTransformations.h"
#include "Graphics/DynamicRotate.h"

#include <corecrt_math_defines.h> // for pi
#include <random>
#include <numbers>


auto SceneCreator::createMoon() -> std::unique_ptr<DrawableObject>
{
	auto moonModel = std::make_shared<Model>(moon, sizeof(moon) / sizeof(float), 9);
	auto moonShader = std::make_shared<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");
	auto moonObject = std::make_unique<DrawableObject>(moonModel, moonShader);

	auto composite = std::make_shared<CompositeTransform>();

	// this has to be same as first rotation of earth!
	// its for moon to rotate same as earth by the sun
	composite->add(std::make_shared<DynamicRotate>(0.0f, 0.05f, glm::vec3(0.0f, 1.0f, 0.0f))); 
	composite->add(std::make_shared<Translate>(10.0f, 5.0f, 0.0f)); // earth & sun distance
	composite->add(std::make_shared<DynamicRotate>(0.0f, 0.05f, glm::vec3(0.0f, 1.0f, 0.0f)));  // Moon & Earth rotation
	composite->add(std::make_shared<Translate>(0.20f, 0.0f, 0.0f)); // Moon & sun distance
	composite->add(std::make_shared<Scale>(0.5f));

	moonObject->setTransformation(composite);

	return moonObject;
}

auto SceneCreator::createClock(float x, float z) -> std::unique_ptr<DrawableObject>
{
	Scene scene;
	auto clockMod = std::make_shared<Model>(clockModel, sizeof(clockModel) / sizeof(float), 9);
	auto clockShader = std::make_shared<ShaderProgram>("Shaders/clock.vert", "Shaders/clock.frag");
	auto clockObj = std::make_unique<DrawableObject>(clockMod, clockShader);

	auto composite = std::make_shared<CompositeTransform>();

	composite->add(std::make_shared<Translate>(x, 0.25f, z));
	composite->add(std::make_shared<Scale>(glm::vec3(-0.1f, 0.1f, 0.1f)));

	clockObj->setTransformation(composite);

	return clockObj;
}

auto SceneCreator::createForest() -> Scene
{
	Scene scene;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distTrees(74, 80);
	std::uniform_int_distribution<int> distBushes(74, 80);

	std::uniform_real_distribution<float> posDist(-35.0f, 35.0f);
	std::uniform_real_distribution<float> bushDist(-6.0f, 6.0f);

	std::uniform_real_distribution<float> treesScale(0.03f, 0.15f);

	int amountOfTrees = distTrees(gen);
	int amountOfBushes = distBushes(gen);

	auto treeModel = std::make_shared<Model>(tree, sizeof(tree) / sizeof(float), 6);
	auto treeShader = std::make_shared<ShaderProgram>("Shaders/tree.vert", "Shaders/tree.frag");

	auto bushModel = std::make_shared<Model>(bushes, sizeof(bushes) / sizeof(float), 6);
	auto bushShader = std::make_shared<ShaderProgram>("Shaders/bush.vert", "Shaders/bush.frag");

	auto grassModel = std::make_shared<Model>(grass, sizeof(grass) / sizeof(float), 6);
	auto grassShader = std::make_shared<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");

	auto groundObj = std::make_unique<DrawableObject>(grassModel, grassShader);

	scene.addObject(std::move(groundObj));
	scene.addObject(std::move(createClock(0.50f, 0.0f)));
	scene.addObject(std::move(createClock(-1.0f, -1.0f)));
	scene.addObject(std::move(createMoon()));



	for (auto i = 0; i < amountOfTrees; i++)
	{
		auto treeObj = std::make_unique<DrawableObject>(treeModel, treeShader);

		auto composite = std::make_shared<CompositeTransform>();

		composite->add(std::make_shared<Scale>(treesScale(gen)));
		composite->add(std::make_shared<Translate>(posDist(gen), 0.0f, posDist(gen)));

		treeObj->setTransformation(composite);
		scene.addObject(std::move(treeObj));

	}

	for (auto i = 0; i < amountOfBushes; i++)
	{
		auto bushObj = std::make_unique<DrawableObject>(bushModel, bushShader);

		auto composite = std::make_shared<CompositeTransform>();

		composite->add(std::make_shared<Scale>(0.5f));
		composite->add(std::make_shared<Translate>(bushDist(gen), 0.0f, bushDist(gen)));
		
		bushObj->setTransformation(composite);
		scene.addObject(std::move(bushObj));
	}

	return scene;
}