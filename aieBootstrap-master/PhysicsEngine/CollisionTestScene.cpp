#include "CollisionTestScene.h"
#include "Sphere.h"
#include "Plane.h"


void CollisionTestScene::Start()
{
	fallingBall = new Sphere({ 0,0 }, 3, 5, { 0,1,0,1 });
	staticPlane = new Plane({0,1}, 50.0f);
	
	ballInitalVel = new Sphere({ 0,-30 }, 3, 5, { 1,0,0,1 });

	ballInitalVel->SetVel({ 0,30 });

	this->addActor(ballInitalVel);
	this->addActor(fallingBall);
	this->addActor(staticPlane);
}

void CollisionTestScene::CleanUp()
{
	this->removeActor(fallingBall);
	this->removeActor(staticPlane);
	this->removeActor(ballInitalVel);

	delete(ballInitalVel);
	delete(fallingBall);
	delete(staticPlane);

}



CollisionTestScene::~CollisionTestScene()
{
}
