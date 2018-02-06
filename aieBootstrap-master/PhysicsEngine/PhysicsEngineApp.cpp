#include <math.h>
#define _USE_MATH_DEFINES
#include "PhysicsEngineApp.h"
#include "PhysicsScene.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include "Sphere.h"
#include "SceneManager.h"


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

	sceneManager = new SceneManager();

	ballDropScene = new PhysicsScene(*sceneManager, 0.5f, { 0,-9.8 });

	Sphere* ProjectileBall; 
	ProjectileBall = new Sphere(glm::vec2(-40, 0), 1.0f, 1, glm::vec4(1, 0, 0, 1));
	ProjectileBall->SetVel(glm::vec2(cos(0.785398f), sin(0.785398f)) * 30.0f);

	ballDropScene->addActor(ProjectileBall);
	drawprojectileMotionDemo();




	playerPos = glm::vec2(0, -40);



	return true;
}

void PhysicsEngineApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete ballDropScene;
}

void PhysicsEngineApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();



	sceneManager->UpdateScene(deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		sceneManager->NextScene();
	}
	
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
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
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}



void PhysicsEngineApp::drawprojectileMotionDemo()
{

	float t = 0;
	float tStep = 0.5f;
	float radius = 1.0f;
	glm::vec2 startPos = { -40,0 };
	int segments = 12;
	glm::vec4 colour = glm::vec4(1, 1, 0, 1);
	float speed = 20;
	float incline = 45;
	float gravity = -9.8f;

	while (t <= 5)
	{

		glm::vec2 currPos;

		currPos.x = startPos.x + (speed * t);
		currPos.y = startPos.y + (speed * t) + (0.5 * gravity * (t*t));

		aie::Gizmos::add2DCircle(glm::vec2(currPos.x, currPos.y), radius, segments, colour);
		t += tStep;
	}

}

void PhysicsEngineApp::drawBreakOut()
{
	aie::Input* input = aie::Input::getInstance();
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		playerPos.x--;
	}

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		playerPos.x++;
	}

	static const glm::vec4 blockColors[] = {
		glm::vec4(1,0,0,1), glm::vec4(0,1,0,1), glm::vec4(0,0,1,1), glm::vec4(0.8f,0,0.5f,1), glm::vec4(0,1,1,1)
	};

	static const int rows = 5;
	static const int columns = 10;
	static const int hSpace = 1;
	static const int vSpace = 1;

	static const glm::vec2 scrExtents(100, 50);
	static const glm::vec2 boxExtents(7, 3);
	static const glm::vec2 startPos(-(columns >> 1)*((boxExtents.x * 2) + vSpace) + boxExtents.x + (vSpace / 2.0f), scrExtents.y - ((boxExtents.y * 2) + hSpace));


	//draw the grid of blocks
	glm::vec2 pos;
	for (int y = 0; y < rows; y++)
	{
		pos = glm::vec2(startPos.x, startPos.y - (y* ((boxExtents.y * 2) + hSpace)));
		for (int x = 0; x < columns; x++)
		{
			aie::Gizmos::add2DAABBFilled(pos, boxExtents, blockColors[y]);
			pos.x += (boxExtents.x * 2) + vSpace;
		}
	}





	//ball
	aie::Gizmos::add2DCircle(glm::vec2(0, -35), 3, 12, glm::vec4(1, 1, 0, 1));

	//player
	aie::Gizmos::add2DAABBFilled(playerPos, glm::vec2(12, 2), glm::vec4(1, 0, 1, 1));

}
