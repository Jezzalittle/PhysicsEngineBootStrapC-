#include "ConvexShapesScene.h"
#include "ShapeMaker.h"



void ConvexShapesScene::Start()
{
	shapeMaker = new ShapeMaker();
}

void ConvexShapesScene::CleanUp()
{
}

void ConvexShapesScene::Update(float dt)
{
	shapeMaker->Update(dt);
	shapeMaker->Draw();

}


ConvexShapesScene::~ConvexShapesScene()
{
}
