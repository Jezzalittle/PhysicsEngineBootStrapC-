#include <math.h>
#define _USE_MATH_DEFINES
#include "PhysicsEngineApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include "Sphere.h"
#include "SceneManager.h"
#include "BallDropScene.h"
#include "BallThrowScene.h"
#include "CollisionTestScene.h"
#include "ConvexShapesScene.h"

PhysicsEngineApp::PhysicsEngineApp() {

}

PhysicsEngineApp::~PhysicsEngineApp() {

}

bool PhysicsEngineApp::startup() {

	m_2dRenderer = new aie::Renderer2D();

	aie::Gizmos::create(225U, 225U, 65535U, 65535U);

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	sceneManager = std::make_shared<SceneManager>();

	ballDropScene = std::make_unique<BallDropScene>(sceneManager, 0.005f, glm::vec2{ 0, -9.8f });
	ballThrowScene = std::make_unique<BallThrowScene>(sceneManager, 0.005f, glm::vec2{ 0, -9.8f });
	collisionScene = std::make_unique<CollisionTestScene>(sceneManager, 0.005f, glm::vec2{ 0, -9.8f });
	convexScene = std::make_unique<ConvexShapesScene>(sceneManager, 0.005f, glm::vec2{ 0, -9.8f });

	return true;
}

void PhysicsEngineApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	//delete ballThrowScene;
}

void PhysicsEngineApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();



	sceneManager->UpdateScene(deltaTime);
	if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT))
	{
		sceneManager->NextScene();
	}
	
	if (input->wasKeyPressed(aie::INPUT_KEY_LEFT))
	{
		sceneManager->PreviousScene();
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsEngineApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = getWindowWidth() / (float)getWindowHeight();
	aie::Gizmos::draw2D(glm::ortho<float>(-100.0f, 100.0f, -100.0f / aspectRatio, 100.0f / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0.5f, 8.0f);

	// done drawing sprites
	m_2dRenderer->end();
}


