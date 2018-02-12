#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include <Gizmos.h>
#include <algorithm>
#include "SceneManager.h"


PhysicsScene::PhysicsScene(std::shared_ptr<class SceneManager> sceneManager, float a_tiemStep, glm::vec2 a_gravity)
{
	m_sceneManager = sceneManager;

	timeStep = a_tiemStep;
	gravity = a_gravity;
	m_sceneManager->AddScene(this);
}

PhysicsScene::~PhysicsScene()
{
	//m_sceneManager->
	for (auto& actor : actors)
	{
		delete actor;
	}
}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFuctionArray[] =
{
	nullptr, PhysicsScene::Plane2Sphere, PhysicsScene::Sphere2Plane, PhysicsScene::Sphere2Sphere,
};

void PhysicsScene::CheckForCollision()
{
	size_t  actorCount = actors.size();

	for (size_t outer = 0; outer < actorCount - 1; outer++)
	{
		for (size_t inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = actors[outer];
			PhysicsObject* object2 = actors[inner];
			int shapeId1 = (int)object1->GetShapeID();
			int shapeId2 = (int)object2->GetShapeID();
			int functionIdx = (shapeId1 * (int)PhysicsObject::ShapeType::num_Shape) + shapeId2;

			fn collisionFunctionPtr = collisionFuctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				collisionFunctionPtr(object1, object2);
			}

		}
	}
}

bool PhysicsScene::Plane2Sphere(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::Sphere2Plane(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::Sphere2Sphere(PhysicsObject *, PhysicsObject *)
{
	return false;
}


void PhysicsScene::addActor(PhysicsObject * actor)
{
	assert(actor != nullptr);
	assert(std::find(std::begin(actors), std::end(actors), actor) == actors.end());

	actors.push_back(actor);

}

void PhysicsScene::removeActor(PhysicsObject * actor)
{
	assert(actor != nullptr);
	actors.erase(std::find(std::begin(actors), std::end(actors), actor));
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




