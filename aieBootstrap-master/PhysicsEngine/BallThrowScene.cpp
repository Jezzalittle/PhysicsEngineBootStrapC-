#include "BallThrowScene.h"
#include <memory>
#include "Sphere.h"
#include "SceneManager.h"



void BallThrowScene::Start()
{
	ball = new Sphere(glm::vec2(-40, 0), 1.0f, 1, glm::vec4(1, 0, 0, 1));
	ball->SetVel(glm::vec2(cos(0.785398f), sin(0.785398f)) * 30.0f);

	this->addActor(ball);

	this->SetClearGizmos(false);

	m_sceneManager->drawprojectileMotionDemo();

}

void BallThrowScene::CleanUp()
{
	if (ball != nullptr)
	{
		this->removeActor(ball);
		delete(ball);
	}
}

BallThrowScene::~BallThrowScene()
{
}
