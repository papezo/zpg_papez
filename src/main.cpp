/*
 * Copyright (c) 2026 Ondřej Papež
 *
 * File: main.cpp
 * Description:  Fixed Function Pipeline.
 */

#include "src/Application/Application.h"

int main(void)
{
	Application app;
	app.initialization();

	//Loading scene
	app.createShaders();
	app.createScenes();
	app.run();

	return 0;

}