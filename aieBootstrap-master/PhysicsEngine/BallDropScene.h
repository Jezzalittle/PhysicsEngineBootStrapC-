#pragma once
#include "PhysicsScene.h"
#include <memory>

class Sphere;

class BallDropScene : public PhysicsScene
{
public:


	BallDropScene() = delete;
	BallDropScene(std::shared_ptr<class SceneManager> sceneManager, float a_tiemStep, glm::vec2 a_gravity) : PhysicsScene(sceneManager, a_tiemStep, a_gravity) { ball = nullptr; };


	void Start();

	void CleanUp();

	~BallDropScene();

private:

	Sphere* ball;


};

