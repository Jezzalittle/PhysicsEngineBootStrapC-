#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include <Gizmos.h>
#include <algorithm>
#include "SceneManager.h"


PhysicsScene::PhysicsScene(std::shared_ptr<class SceneManager> sceneManager, float a_tiemStep, glm::vec2 a_gravity)
{
	m_sceneManager = sceneManager;

	m_sceneManager->AddScene(this);
	timeStep = a_tiemStep;
	gravity = a_gravity;
}

PhysicsScene::~PhysicsScene()
{
	//m_sceneManager->
	for (auto& actor : actors)
	{
		delete actor;
	}
}

void PhysicsScene::addActor(PhysicsObject * actor)
{
	assert(actor != nullptr);
	assert(std::find(std::begin(actors), std::end(actors), actor) == actors.end());

	actors.push_back(actor);

}

void PhysicsScene::removeActor(PhysicsObject * actor)
{
	std::remove(std::begin(actors), std::end(actors), actor);
}

void PhysicsScene::update(float dt)
{
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= timeStep)
	{
		for (auto pActor : actors)
		{
			pActor->fixedUpdate(gravity, timeStep);
		}

		accumulatedTime -= timeStep;
	}
}

void PhysicsScene::updateGizmos()
{
	if (clearGizmos)
	{
		aie::Gizmos::clear();
	}
	for (auto pActor : actors)
	{
		pActor->makeGizmo();
	}
}


