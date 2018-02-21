#include "CollisionTestScene.h"
#include "Sphere.h"
#include "Plane.h"
#include "AABB.h"


void CollisionTestScene::Start()
{
	fallingBall = new Sphere({ 0,10 }, 3, 1, { 0,1,0,1 });
	ballInitalVel = new Sphere({0,-30 }, 3, 1, { 1,0,0,1 });
	staticPlane = new Plane({0,1}, 50.0f);
	staticPlane2 = new Plane({ 0,-1 }, 30);
	box1 = new AABB(glm::vec2(15,0), glm::vec2(3,3), 1, {0, 0, 1, 1});
	box2 = new AABB(glm::vec2(15, 15), glm::vec2(3, 3), 1, { 0, 0.5f, 0.5f, 1 });

	ballInitalVel->SetVel({ 0,30 });
	this->addActor(box2);
	this->addActor(box1);
	this->addActor(ballInitalVel);
	this->addActor(fallingBall);
	this->addActor(staticPlane);
	this->addActor(staticPlane2);
}

void CollisionTestScene::CleanUp()
{
	this->removeActor(box2);
	this->removeActor(fallingBall);
	this->removeActor(staticPlane);
	this->removeActor(ballInitalVel);
	this->removeActor(box1);
	this->removeActor(staticPlane2);

	delete(box2);
	delete(staticPlane2);
	delete(box1);
	delete(ballInitalVel);
	delete(fallingBall);
	delete(staticPlane);

}



CollisionTestScene::~CollisionTestScene()
{
}
