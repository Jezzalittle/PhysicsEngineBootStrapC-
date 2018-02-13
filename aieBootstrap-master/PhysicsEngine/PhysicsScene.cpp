#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include <Gizmos.h>
#include <algorithm>
#include "SceneManager.h"
#include "Plane.h"
#include "Sphere.h"
#include <iostream>

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

typedef PhysicsScene::CollisionData(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFuctionArray[] =
{
	PhysicsScene::Sphere2Sphere, PhysicsScene::Plane2Sphere, PhysicsScene::Plane2Box,
	PhysicsScene::Sphere2Plane, PhysicsScene::Sphere2Sphere, PhysicsScene::Sphere2Box, 
	PhysicsScene::Box2Plane, PhysicsScene::Box2Sphere, PhysicsScene::Box2Box,
};

void PhysicsScene::CheckForCollision()
{
	size_t  actorCount = actors.size();
	CollisionData collData;


	for (size_t outer = 0; outer < actorCount - 1; outer++)
	{
		for (size_t inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = actors[outer];
			PhysicsObject* object2 = actors[inner];
			int shapeId1 = (int)object1->GetShapeID();
			int shapeId2 = (int)object2->GetShapeID();
			int functionIdx = (shapeId1 * SHAPECOUNT) + shapeId2;

			fn collisionFunctionPtr = collisionFuctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				collData = collisionFunctionPtr(object1, object2);
				if (collData.wasCollision == true)
				{
					handleCollision(object1, object2, collData);
				}
			}

		}
	}
}

PhysicsScene::CollisionData PhysicsScene::Plane2Sphere(PhysicsObject *object1, PhysicsObject *object2)
{

	CollisionData collData;
	Plane* plane = dynamic_cast<Plane*>(object2);
	Sphere* sphere = dynamic_cast<Sphere*>(object1);
	assert(plane && sphere);
	collData.normal = plane->GetNormal();
	float SphereToPlane = glm::dot(sphere->getPos(), plane->GetNormal()) + plane->GetDistanceToOrigin();

	if (SphereToPlane < 0)
	{
		collData.normal *= -1;
		SphereToPlane *= -1;
	}

	collData.overlap = sphere->GetRadius() - SphereToPlane;
	collData.wasCollision = false;

	if (collData.overlap > 0)
	{
		sphere->SetVel({ 0,0 });
		collData.wasCollision = true;
		std::cout << "plane to sphere";
	}

	return collData;
}

PhysicsScene::CollisionData PhysicsScene::Sphere2Plane(PhysicsObject *object1, PhysicsObject *object2)
{
	return Plane2Sphere(object2, object1);

}

PhysicsScene::CollisionData PhysicsScene::Sphere2Sphere(PhysicsObject *object1, PhysicsObject *object2)
{
	CollisionData colldata;
	Sphere *sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere *sphere2 = dynamic_cast<Sphere*>(object2);
	assert(sphere1 && sphere2);

	float totalDistance = glm::distance(sphere2->getPos(), sphere1->getPos());
	float collDistance = sphere1->GetRadius() + sphere2->GetRadius();

	colldata.overlap = totalDistance - collDistance;

	if (colldata.overlap < 0)
	{
		colldata.wasCollision = true;
		sphere1->SetVel({ 0,0 });
		sphere2->SetVel({ 0,0 });
		colldata.normal = glm::normalize(sphere2->getPos() + sphere1->getPos());
		std::cout << "sphere Collision\n";
	}

	return colldata;
}

void PhysicsScene::handleCollision(PhysicsObject * object1, PhysicsObject * object2, const CollisionData & collData)
{
	auto rb1 = dynamic_cast<RigidBody*>(object1);
	auto rb2 = dynamic_cast<RigidBody*>(object2);
	SeperateCollisionObjects(rb1, rb2, collData);

	glm::vec2 relativeVelocity = { 0,0 };
	if (rb1) relativeVelocity = rb1->getVel();
	if (rb2) relativeVelocity -= rb2->getVel();

	float elasticity = 1;

	float invMass1 = (rb1) ? 1.0f / rb1->getMass() : 0.0f;
	float invMass2 = (rb2) ? 1.0f / rb2->getMass() : 0.0f;

	float jTop = -(1 + elasticity) * glm::dot(relativeVelocity, collData.normal);
	float jBottom = glm::dot(collData.normal, collData.normal) *  (invMass1 + invMass2);

	float j = jTop / jBottom;

	if (rb1)
	{
		glm::vec2 newVelocity = rb1->getVel() - (j / rb1->getMass()) * collData.normal;
		rb1->applyForce(newVelocity);
	}
	if (rb2)
	{
		glm::vec2 newVelocity = rb2->getVel() + (j / rb2->getMass()) * collData.normal;
	}


}

void PhysicsScene::SeperateCollisionObjects(RigidBody * rb1, RigidBody * rb2, const PhysicsScene::CollisionData & collData)
{


	if (rb1 == nullptr && rb2 == nullptr)
	{
		return;
	}

	float obj1MoveRatio = 0;
	float obj2MoveRatio = 0;

	if (rb1 && rb2)
	{
		float totalMass = rb1->getMass() + rb2->getMass();
		obj1MoveRatio = 1 - (rb1->getMass() / totalMass);
		obj2MoveRatio = 1 - (rb2->getMass() / totalMass);
	}
	else if (rb1)
	{
		obj1MoveRatio = 1.0f;
	}
	else
	{
		obj2MoveRatio = 1.0f;
	}

	if (rb1)
	{
		rb1->SetPos(rb1->getPos() - (obj1MoveRatio * collData.overlap * collData.normal));
	}
	if (rb1)
	{
		rb1->SetPos(rb2->getPos() - (obj2MoveRatio * collData.overlap * collData.normal));
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
	CheckForCollision();
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




