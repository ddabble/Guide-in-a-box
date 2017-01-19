#include "Game.h"

#include <iostream>

//// Must be included before the GLFW header
//#include <glload/gl_load.h>

// Must be included before the GLFW header
#include "gl/gl.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "event/EventHandler.h"


#include "game_object/hud/objects/Arrow.h"
Arrow* arrow1;
Arrow* arrow2;

Game::Game() : m_window("RS Daily Routine Helper"), m_eventHandler(this), m_gameObjectManager(this, m_eventHandler), m_input(this)
{
	//glGenerateMipmap(GL_TEXTURE_2D);

	// Magnification/minification mipmapping
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glEnable(GL_PROGRAM_POINT_SIZE);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);

	glClearColor(0.3f, 0.3f, 0.3f, 1);

	arrow1 = new Arrow(this, { 320, 192 }, { 960, 384 });
	arrow2 = new Arrow(this, { 120, 192 }, { 460, 384 });

	m_physicsThread = std::thread(physics, this);
}

Game::~Game()
{
	m_keepRunning = false;
	m_physicsThread.join();

	glfwTerminate();
}

void Game::physics(Game* game)
{
	game->runPhysics();
}

void Game::runPhysics()
{
	m_lastPhysicsTime = glfwGetTime() - PHYSICS_UPDATE_INTERVAL;
	while (m_keepRunning)
	{
		double currentTime = glfwGetTime();
		if (currentTime - m_lastPhysicsTime >= PHYSICS_UPDATE_INTERVAL)
		{
			physicsUpdate();
			m_lastPhysicsTime += PHYSICS_UPDATE_INTERVAL;
			m_hasSlept = false;
		} else if (!m_hasSlept)
		{
			double durationUntilNextPhysicsTime = (m_lastPhysicsTime + PHYSICS_UPDATE_INTERVAL - currentTime) * 0.90; // Leaves 10 % of the actual duration as a time buffer, just in case
			std::this_thread::sleep_for(std::chrono::microseconds(int(durationUntilNextPhysicsTime * 1e6)));
			m_hasSlept = true;
		}
	}
}

void Game::run()
{
	while (!glfwWindowShouldClose(m_window.m_window))
	{
		frameUpdate(m_window.m_window);

		glfwSwapBuffers(m_window.m_window);

		glfwPollEvents();
	}
}

// TODO: Put GL-code in own files

void Game::frameUpdate(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gameObjectManager.frameUpdate(this);

	arrow1->frameUpdate(this);
	arrow2->frameUpdate(this);

	// Setup
	//glEnable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);
	//glDrawArrays(GL_POINTS, 0, 1);

	glFlush();
}

void Game::physicsUpdate()
{
	m_gameObjectManager.physicsUpdate(this);
}
