#include "SceneCreator.h"
#include "../Graphics/Scene.h"
#include "../Graphics/Model.h"

#include "../../Models/sphere.h"
#include "../../Models/tree.h"
#include "../../Models/triangle.h"
#include "../../Models/bushes.h"
#include "../../Models/PAP0123.h"

auto SceneCreator::createSignature() -> std::unique_ptr<Model>
{
	auto sign = std::make_unique<Model>(login, sizeof(login) / sizeof(float));
	sign->setPosition(0.75f, -0.75f, 0.0f);
	sign->setScale(0.2f);
	sign->setColor(0.2f, 0.8f, 1.0f);
	return sign;
}

auto SceneCreator::createTriangleScene() -> std::unique_ptr<Scene>
{
	auto scene = std::make_unique<Scene>();

	auto triangleModel = std::make_unique<Model>(triangle, sizeof(triangle) / sizeof(float));
	triangleModel->setScale(0.5f);
	triangleModel->setColor(0.0f, 0.0f, 1.0f);

	scene->addModel(std::move(triangleModel));
	scene->addModel(createSignature());
	return scene;
}

auto SceneCreator::createSphereScene() -> std::unique_ptr<Scene>
{
	auto scene = std::make_unique<Scene>();

	auto sphereModel = std::make_unique<Model>(sphere, sizeof(sphere) / sizeof(float));
	sphereModel->setScale(0.5f);
	sphereModel->setColor(1.0f, 0.0f, 0.0f);
	scene->addModel(std::move(sphereModel));
	scene->addModel(createSignature());
	return scene;
}

auto SceneCreator::createForestScene() -> std::unique_ptr<Scene>
{
	auto scene = std::make_unique<Scene>();

	// Trees
	for (int i = 0; i < 14; i++)
	{
		auto treeModel = std::make_unique<Model>(tree, sizeof(tree) / sizeof(float));
		treeModel->setScale(0.08f);

		float posX = -0.85f + i * (1.7f / 13.0f);
		float posY = -0.2f + (i % 3) * 0.1f;
		treeModel->setPosition(posX, posY, 0.0f);
		treeModel->setColor(0.15f, 0.6f, 0.2f);

		scene->addModel(std::move(treeModel));
	}

	// Bushes
	for (int i = 0; i < 12; i++)
	{
		auto bushModel = std::make_unique<Model>(bushes, sizeof(bushes) / sizeof(float));
		bushModel->setScale(0.5f);

		float posX = -0.8f + i * (1.6f / 11.0f);
		float posY = -0.6f + (i % 2) * 0.15f;
		bushModel->setPosition(posX, posY, 0.0f);
		bushModel->setColor(0.15f, 0.6f, 0.2f);

		scene->addModel(std::move(bushModel));
	}

	// Sun
	auto sun = std::make_unique<Model>(sphere, sizeof(sphere) / sizeof(float));
	sun->setPosition(0.7f, 0.7f, 0.0f);
	sun->setScale(0.15f);
	sun->setColor(1.0f, 1.0f, 0.0f); 

	scene->addModel(std::move(sun));
	scene->addModel(createSignature());

	return scene;
}

auto SceneCreator::createLoginScene() -> std::unique_ptr<Scene>
{
	auto scene = std::make_unique<Scene>();
	auto loginModel = std::make_unique<Model>(login, sizeof(login) / sizeof(float));

	loginModel->setPosition(0.0f, 0.0f, 0.0f);
	loginModel->setScale(1.0f);

	scene->addModel(std::move(loginModel));
	return scene;
}


