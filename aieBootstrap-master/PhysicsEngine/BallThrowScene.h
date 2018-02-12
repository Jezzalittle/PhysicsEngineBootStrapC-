#pragma once
#include "PhysicsScene.h"
#include <memory>

class Sphere;

class BallThrowScene : public PhysicsScene
{
public:


	BallThrowScene() = delete; 
	BallThrowScene(std::shared_ptr<class SceneManager> sceneManager, float a_tiemStep, glm::vec2 a_gravity) : PhysicsScene(sceneManager, a_tiemStep, a_gravity) {  ball = nullptr; };

	void Start();

	void CleanUp();

	~BallThrowScene();

private:
	
	Sphere* ball;

};

