#pragma once
#include "PhysicsScene.h"

class Sphere;
class Plane;
class AABB;

class CollisionTestScene :	public PhysicsScene
{
public:

	CollisionTestScene() = delete;
	CollisionTestScene(std::shared_ptr<class SceneManager> sceneManager, float a_tiemStep, glm::vec2 a_gravity) : PhysicsScene(sceneManager, a_tiemStep, a_gravity) {  };

	void Start();

	void CleanUp();

	~CollisionTestScene();

private:

	Sphere* ball1;
	Sphere* ball2;
	Sphere* ball3;
	Sphere* ball4;

	Plane* plane1;
	Plane* plane2;
	Plane* plane3;
	Plane* plane4;
	Plane* plane5;

	AABB* box1;
	AABB* box2;
	AABB* box3;

};

