#pragma once
#include "PhysicsScene.h"
class CollisionTestScene :	public PhysicsScene
{
public:

	CollisionTestScene() = delete;
	CollisionTestScene(std::shared_ptr<class SceneManager> sceneManager, float a_tiemStep, glm::vec2 a_gravity) : PhysicsScene(sceneManager, a_tiemStep, a_gravity) {  };

	void Start();

	void CleanUp();

	~CollisionTestScene();
};

