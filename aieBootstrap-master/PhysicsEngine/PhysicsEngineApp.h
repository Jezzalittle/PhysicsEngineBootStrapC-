#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <glm\ext.hpp>
#include <memory>

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
	std::unique_ptr<PhysicsScene>		ballThrowScene;
	std::unique_ptr<PhysicsScene>		ballDropScene;
	std::unique_ptr<PhysicsScene>		collisionScene;
	std::shared_ptr<SceneManager>		sceneManager;


private:

	glm::vec2 playerPos;
};