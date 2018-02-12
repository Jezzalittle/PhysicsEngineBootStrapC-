#include "BallDropScene.h"
#include "Sphere.h"





void BallDropScene::Start()
{
	ball = new Sphere(glm::vec2(0,0), 1, 1, glm::vec4(0,1,0,1));
	this->addActor(ball);
}

void BallDropScene::CleanUp()
{
	if (ball != nullptr)
	{
		this->removeActor(ball);
		delete(ball);
	}

}


BallDropScene::~BallDropScene()
{

}
