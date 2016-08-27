#include "Game.h"

#include <iostream>

// Must be included before the GLFW header
#include <glload/gl_load.h>
// Must be included before the GLFW header
#include "gl/gl.h"
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "event/EventHandler.h"

Game::Game() : m_eventHandler(EventHandler(this)), m_gameObjectManager(GameObjectManager()), m_input(InputManager())
{
	m_windowWidth = 1280;
	m_windowHeight = 768;
}

void Game::run()
{
	GLFWwindow* window = windowInit();
	if (window == nullptr)
		return;

	init(window);

	glfwSwapInterval(1);

	m_physicsThread = std::thread(physics, this);

	while (!glfwWindowShouldClose(window))
	{
		frameUpdate(window);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	terminate();
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

GLFWwindow* Game::windowInit()
{
	GLFWwindow* window;

	glfwSetErrorCallback(EventHandler::errorCallback);

	if (!glfwInit())
		return nullptr;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(m_windowWidth, m_windowHeight, "RS Daily Routine Helper", NULL, NULL);
	if (!window)
	{
		std::cerr << "Unable to create a window with GLFW.\n" << "exiting..." << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwSetWindowSizeLimits(window, 100, 100, GLFW_DONT_CARE, GLFW_DONT_CARE);

	glfwMakeContextCurrent(window);

	int loadTest = ogl_LoadFunctions();
	if (loadTest == ogl_LOAD_FAILED)
	{
		std::cerr << "Unable to initialize GL Load.\n" << loadTest - ogl_LOAD_SUCCEEDED << " core functions failed to load.\n" << "exiting..." << std::endl;
		glfwTerminate();
		return nullptr;
	}

	return window;
}

void Game::init(GLFWwindow* window)
{
	m_gameObjectManager.init(this);

	m_gameObjectManager.addEventHooks(m_eventHandler);
	EventHandler::registerCallbacks(window);

	//glGenerateMipmap(GL_TEXTURE_2D);

	// Magnification/minification mipmapping
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glEnable(GL_PROGRAM_POINT_SIZE);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);

	glClearColor(0.3f, 0.3f, 0.3f, 1);

	m_input.getMouse().init(window, m_windowHeight);
}

// TODO: Put GL-code in own files

void Game::frameUpdate(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gameObjectManager.frameUpdate(this);

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

void Game::terminate()
{
	m_keepRunning = false;
	m_physicsThread.join();

	m_gameObjectManager.deallocateData();

	glfwTerminate();
}
