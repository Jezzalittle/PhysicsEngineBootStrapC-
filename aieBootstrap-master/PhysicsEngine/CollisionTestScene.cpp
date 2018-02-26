#include "CollisionTestScene.h"
#include "Sphere.h"
#include "Plane.h"
#include "AABB.h"


void CollisionTestScene::Start()
{
	box1 = new AABB(glm::vec2(15,-15.0f), glm::vec2(3,3), 1.0f, {0, 0, 1, 1});
	box2 = new AABB(glm::vec2(15.0f, 20), glm::vec2(3, 3), 1.0f, { 0, 0.5f, 0.5f, 1 });
	box3 = new AABB(glm::vec2(-15, 20), glm::vec2(3, 3), 1.0f, { 0.5f, 0, 0.5f, 1 });
	
	ball1 = new Sphere({ 0,20 }, 3, 1, { 0,1,0,1 });
	ball2 = new Sphere({0, -15}, 3, 1, { 1,0,0,1 });
	ball3 = new Sphere({ -15.0f, -15.0f }, 3, 1, { 0.5f,0.5f,0,1 });
	ball4 = new Sphere({ -50.0f, -15.0f }, 3, 1, { 1,1.1,1,1 });

	plane1 = new Plane({0,1}, 50.0f);
	plane2 = new Plane({ 0,-1 }, 20);
	plane3 = new Plane({ 1, 0 }, 50.0f);
	plane4 = new Plane({ -1,0 }, 50.0f);
	plane5 = new Plane({ -0.5f, 0.5f }, 50);

	
	ball4->SetVel({ 3, 0 });

	this->addActor(box1);
	this->addActor(box2);
	this->addActor(box3);

	this->addActor(ball1);
	this->addActor(ball2);
	this->addActor(ball3);
	this->addActor(ball4);

	this->addActor(plane1);
	this->addActor(plane2);
	this->addActor(plane3);
	this->addActor(plane4);
	this->addActor(plane5);



}

void CollisionTestScene::CleanUp()
{

	this->removeActor(box1);
	this->removeActor(box2);
	this->removeActor(box3);

	this->removeActor(ball1);
	this->removeActor(ball2);
	this->removeActor(ball3);
	this->removeActor(ball4);

	this->removeActor(plane1);
	this->removeActor(plane2);
	this->removeActor(plane3);
	this->removeActor(plane4);
	this->removeActor(plane5);

	delete(box1);
	delete(box2);
	delete(box3);

	delete(ball1);
	delete(ball2);
	delete(ball3);
	delete(ball4);

	delete(plane1);
	delete(plane2);
	delete(plane3);
	delete(plane4);
	delete(plane5);


}



CollisionTestScene::~CollisionTestScene()
{
}
