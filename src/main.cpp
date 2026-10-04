/*
 * Copyright (c) 2026 Martin Němec
 *
 * File: main.cpp
 * Description:  Fixed Function Pipeline.
 */

#include "src/Application/Application.h"

int main(void)
{
	Application* app = new Application();
	app->initialization();

	//Loading scene
	app->createShaders();
	app->createModels();
	app->run();

}