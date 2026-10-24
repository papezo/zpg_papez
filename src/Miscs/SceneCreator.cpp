#include "SceneCreator.h"

#include "Models/bushes.h"
#include "Models/tree.h"
#include "Models/grass.h"
#include "Models/clock.h"
#include "Models/sphere.h"

#include "Graphics/Scene.h"
#include "Graphics/Model.h"
#include "Graphics/DrawableObject.h"

#include "Transformations/CompositeTransform.h"
#include "Transformations/StaticTransformations.h"

#include "SolarSystemCreator.h"

#include <random>


auto SceneCreator::createClock(float x, float z, Camera& camera) -> std::unique_ptr<DrawableObject>
{
	auto clockMod = std::make_shared<Model>(clockModel, sizeof(clockModel) / sizeof(float), 9);
	auto clockShader = std::make_shared<ShaderProgram>("Shaders/clock.vert", "Shaders/clock.frag");

	camera.addObserver(clockShader);

	auto clockObj = std::make_unique<DrawableObject>(clockMod, clockShader);
	auto composite = std::make_shared<CompositeTransform>();

	composite->add(std::make_shared<Translate>(x, 0.25f, z));
	composite->add(std::make_shared<Scale>(glm::vec3(-0.1f, 0.1f, 0.1f)));

	clockObj->setTransformation(composite);

	return clockObj;
}

auto SceneCreator::createForest(Camera& camera) -> Scene
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

	camera.addObserver(treeShader);
	camera.addObserver(bushShader);
	camera.addObserver(grassShader);

	auto groundObj = std::make_unique<DrawableObject>(grassModel, grassShader);

	scene.addObject(std::move(groundObj));
	scene.addObject(std::move(createClock(0.50f, 0.0f, camera)));
	scene.addObject(std::move(createClock(-1.0f, -1.0f, camera)));

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


auto SceneCreator::createBallScene(Camera& camera) -> Scene
{
	Scene scene;
	// positions for the balls
	const glm::vec3 positions[] = {
		{ 0.0f,  1.0f, 0.0f },
		{-1.0f,  0.0f, 0.0f },
		{ 1.0f,  0.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f }
	};

	auto ballMod = std::make_shared<Model>(sphere, sizeof(sphere) / sizeof(float), 6);
	auto ballShader = std::make_shared<ShaderProgram>("Shaders/Lighting/lighting.vert", "Shaders/Lighting/blinn_phong.frag");

	ballShader->use();
	ballShader->setUniform("lightColor", 1.0f, 1.0f, 1.0f);
	ballShader->setUniform("objectColor", 0.3f, 0.7f, 0.9f);

	camera.addObserver(ballShader);

	auto ballObj = std::make_unique<DrawableObject>(ballMod, ballShader);
	auto composite = std::make_shared<CompositeTransform>();

	for (const auto& position : positions)
	{
		auto ballObj = std::make_unique<DrawableObject>(
			ballMod, ballShader);

		auto composite = std::make_shared<CompositeTransform>();
		composite->add(std::make_shared<Translate>(position));
		composite->add(std::make_shared<Scale>(0.4f));

		ballObj->setTransformation(composite);
		scene.addObject(std::move(ballObj));
	}

	return scene;


}

auto SceneCreator::createSolarSystem(Camera& camera) -> Scene
{
	Scene scene;
	SolarSystemCreator solarSystem;

	scene.addObject(solarSystem.createBlackHole(camera));
	scene.addObject(solarSystem.createEarth(camera));
	scene.addObject(solarSystem.createSun(camera));
	scene.addObject(solarSystem.createMars(camera));
	scene.addObject(solarSystem.createMercury(camera));
	scene.addObject(solarSystem.createMoon(camera));
	scene.addObject(solarSystem.createVenus(camera));

	scene.addObject(solarSystem.createSignature(camera));

	return scene;
}
