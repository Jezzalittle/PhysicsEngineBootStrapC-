#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include <Gizmos.h>
#include <algorithm>
#include "SceneManager.h"
#include "Plane.h"
#include "Sphere.h"
#include <iostream>
#include "AABB.h"

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
	PhysicsScene::Sphere2Sphere,	PhysicsScene::Sphere2Plane,		PhysicsScene::Sphere2Box,
	PhysicsScene::Plane2Sphere,		nullptr,						PhysicsScene::Plane2Box,
	PhysicsScene::Box2Sphere,		PhysicsScene::Box2Plane,		PhysicsScene::Box2Box,

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
	Plane* plane = dynamic_cast<Plane*>(object1);
	Sphere* sphere = dynamic_cast<Sphere*>(object2);
	assert(plane && sphere);
	collData.normal = plane->GetNormal();
	float SphereToPlane = glm::dot(sphere->getPos(), plane->GetNormal()) + plane->GetDistanceToOrigin();

	if (SphereToPlane < 0)
	{
		collData.normal *= -1;
		SphereToPlane *= -1;
	}

	collData.overlap = SphereToPlane - sphere->GetRadius();
	collData.wasCollision = false;

	if (collData.overlap < 0)
	{
		collData.wasCollision = true;
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
		colldata.normal = glm::normalize(sphere1->getPos() - sphere2->getPos());
	}

	return colldata;
}

PhysicsScene::CollisionData PhysicsScene::Sphere2Box(PhysicsObject * object1, PhysicsObject * object2)
{
	CollisionData colldata;
	colldata.normal = { 0,0 };
	colldata.overlap = 0.0f;
	colldata.wasCollision = false;

	Sphere *sphere = dynamic_cast<Sphere*>(object1);
	AABB *box = dynamic_cast<AABB*>(object2);

	glm::vec2 vecBetween = sphere->getPos() - box->getPos();

	glm::vec2 offset;




	offset.x = glm::dot(vecBetween, { 1,0 });
	offset.y = glm::dot(vecBetween, { 0,1 });

	if (glm::abs(offset.x) > (box->getWidth() * 0.5f))
	{
		//(offset.x > 0) ? offset.x = box->getPos().x + (box->getWidth() / 2) : offset.x = box->getPos().x - (box->getWidth() / 2);

		offset.x = (box->getWidth()) * ((offset.x > 0) ? 1.0 : -1.0f);

	}
	if (glm::abs(offset.y) > box->getHeight() * 0.5f)
	{
		offset.y = (box->getHeight()) * ((offset.y > 0) ? 1.0 : -1.0f);
	}

	offset += box->getPos();

	glm::vec2 vecBetweenClamp = offset - sphere->getPos();

	if (glm::length(vecBetweenClamp) < sphere->GetRadius())
	{
		colldata.wasCollision = true;
		colldata.overlap = glm::length(vecBetweenClamp) - sphere->GetRadius();
		colldata.normal = glm::normalize(vecBetweenClamp);
	}

	return colldata;

}

PhysicsScene::CollisionData PhysicsScene::Box2Plane(PhysicsObject * object1, PhysicsObject * object2)
{
	CollisionData colldata;
	colldata.normal = { 0,0 };
	colldata.overlap = 0.0f;
	colldata.wasCollision = false;

	AABB *box = dynamic_cast<AABB*>(object1);
	Plane *plane = dynamic_cast<Plane*>(object2);

	glm::vec2 closestVec;



	//auto tlDistance = glm::dot(box->GetTL() + plane->GetNormal()   plane->GetDistanceToOrigin() , plane->GetNormal());
	//auto trDistance = glm::dot(box->GetTR() + plane->GetNormal()   plane->GetDistanceToOrigin(), plane->GetNormal());
	//auto blDistance = glm::dot(box->GetBL() + plane->GetNormal()   plane->GetDistanceToOrigin(), plane->GetNormal());
	//auto brDistance = glm::dot(box->GetBR() + plane->GetNormal()   plane->GetDistanceToOrigin(), plane->GetNormal());


	auto tlDistance = glm::dot(box->GetTL(), plane->GetNormal()) + plane->GetDistanceToOrigin();
	auto trDistance = glm::dot(box->GetTR(), plane->GetNormal()) + plane->GetDistanceToOrigin();
	auto blDistance = glm::dot(box->GetBL(), plane->GetNormal()) + plane->GetDistanceToOrigin();
	auto brDistance = glm::dot(box->GetBR(), plane->GetNormal()) + plane->GetDistanceToOrigin();


	if (tlDistance < 0 || trDistance < 0 || blDistance < 0 || brDistance < 0)
	{

		colldata.wasCollision = true;

		float closestDistance = tlDistance;
		float currentDistance = trDistance;



		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			closestVec = box->GetTR();
		}

		currentDistance = blDistance;


		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			closestVec = box->GetBL();
		}


		currentDistance = brDistance;


		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			closestVec = box->GetBR();
		}

		colldata.normal = plane->GetNormal();
		colldata.overlap = closestDistance;

	}

	return colldata;
}

PhysicsScene::CollisionData PhysicsScene::Box2Sphere(PhysicsObject * object1, PhysicsObject * object2)
{
	return Sphere2Box(object2, object1);
}

PhysicsScene::CollisionData PhysicsScene::Box2Box(PhysicsObject * object1, PhysicsObject * object2)
{
	CollisionData colldata;
	colldata.wasCollision = false;
	colldata.normal = { 0,0 };
	AABB* box1 = dynamic_cast<AABB*>(object1);
	AABB* box2 = dynamic_cast<AABB*>(object2);

	float offsetFaceDis;


	//if both boxs are not null ptr
	if (box1 != nullptr && box2 != nullptr)
	{

		//checks to see the right and left side for both boxes
		if (abs(box1->getPos().x - box2->getPos().x) > box1->getWidth() + box2->getWidth())
		{
			return colldata;
		}

		//checks to see the top and bottom side for both boxes
		if (abs(box1->getPos().y - box2->getPos().y) > box1->getHeight()+ box2->getHeight())
		{
			return colldata;
		}

		colldata.wasCollision = true;
		offsetFaceDis = 0.0f;


		glm::vec2 xOverlap1 = { box1->GetTR().x - box2->GetBL().x, 0.0f };
		glm::vec2 xOverlap2 = { box1->GetBL().x - box2->GetTR().x, 0.0f };

		glm::vec2 yOverlap1 = { 0.0f , box1->GetTR().y - box2->GetBL().y };
		glm::vec2 yOverlap2 = { 0.0f ,box1->GetBL().y - box2->GetTR().y };
		

		float lowestDist = abs(xOverlap1.x);
		glm::vec2 lowestVec = xOverlap1;



		if (abs(xOverlap2.x) < lowestDist)
		{
			lowestDist = abs(xOverlap2.x);
			lowestVec = xOverlap2;
		}

		if (abs(yOverlap1.y) < lowestDist)
		{
			lowestDist = abs(yOverlap1.y);
			lowestVec = yOverlap1;
		}

		if (abs(yOverlap2.y) < lowestDist)
		{
			lowestDist = abs(yOverlap2.y);
			lowestVec = yOverlap2;
		}


		colldata.normal = glm::normalize(lowestVec);
		colldata.overlap = lowestDist;




		
		return colldata;





		//if (box1->GetBL().x > box2->GetTR().x)
		//{
		//	//left
		//	if ((box1->GetBL().x > box2->GetTR()) offsetFaceDis == 0.0f)

		//		colldata.normal = { -1,0 };
		//		offsetFaceDis = box2->GetBL().x - box1->GetTR().x;
		//	}
		//}
		//if (box1->GetTR().x < box2->GetBL().x)
		//{
		//	//right
		//	if (box1->GetTR().x - box2->GetBL().x < offsetFaceDis || offsetFaceDis == 0.0f)
		//	{
		//		colldata.normal = { 1,0 };
		//		offsetFaceDis = box1->GetBR().x - box2->GetTL().x;
		//	}
		//}
		//if (box1->GetBL().y > box2->GetTR().y)
		//{
		//	//down
		//	if (box1->GetBL().y - box2->GetTR().y < offsetFaceDis || offsetFaceDis == 0.0f)
		//	{
		//		colldata.normal = { 0,-1 };
		//		offsetFaceDis = box1->GetBL().y - box2->GetTR().y;
		//	}
		//}
		//if (box1->GetTR().y < box2->GetBL().y)
		//{
		//	//up
		//	if (box2->GetTR().y - box1->GetBL().y < offsetFaceDis || offsetFaceDis == 0.0f)
		//	{
		//		colldata.normal = { 0,1 };
		//		offsetFaceDis = box2->GetTR().y - box1->GetBL().y;
		//	}
		//}
		//colldata.overlap = offsetFaceDis;


	

	}
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
		glm::vec2 newVelocity = (j / rb1->getMass()) * collData.normal;
		rb1->applyForce(newVelocity, Physics::VelocityChange);
	}
	if (rb2)
	{
		glm::vec2 newVelocity = (j / rb2->getMass()) * collData.normal;
		rb2->applyForce(-newVelocity, Physics::VelocityChange);
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
	if (rb2)
	{
		rb2->SetPos(rb2->getPos() + (obj2MoveRatio * collData.overlap * collData.normal));
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




