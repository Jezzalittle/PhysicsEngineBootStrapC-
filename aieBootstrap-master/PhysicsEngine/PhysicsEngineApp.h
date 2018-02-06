#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <glm\ext.hpp>

class SceneManager;
class PhysicsScene;

class PhysicsEngineApp : public aie::Application {
public:

	PhysicsEngineApp();
	virtual ~PhysicsEngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	PhysicsScene*		ballDropScene;
	PhysicsScene*		projectileMotionScene;
	PhysicsScene*		currentScene;
	SceneManager*		sceneManager;


private:

	void drawprojectileMotionDemo();
	void drawBreakOut();
	glm::vec2 playerPos;
};