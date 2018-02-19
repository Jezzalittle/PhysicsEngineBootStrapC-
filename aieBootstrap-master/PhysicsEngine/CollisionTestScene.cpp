#include "CollisionTestScene.h"
#include "Sphere.h"
#include "Plane.h"
#include "AABB.h"


void CollisionTestScene::Start()
{
	fallingBall = new Sphere({ -2,0 }, 3, 1, { 0,1,0,1 });
	ballInitalVel = new Sphere({ 2,-30 }, 3, 1, { 1,0,0,1 });
	staticPlane = new Plane({0,1}, 50.0f);
	box1 = new AABB(glm::vec2(5,0), glm::vec2(3,3), 1, {0, 0, 1, 1});

	ballInitalVel->SetVel({ 0,30 });

	this->addActor(box1);
	this->addActor(ballInitalVel);
	this->addActor(fallingBall);
	this->addActor(staticPlane);
}

void CollisionTestScene::CleanUp()
{
	this->removeActor(fallingBall);
	this->removeActor(staticPlane);
	this->removeActor(ballInitalVel);
	this->removeActor(box1);

	delete(box1);
	delete(ballInitalVel);
	delete(fallingBall);
	delete(staticPlane);

}



CollisionTestScene::~CollisionTestScene()
{
}
