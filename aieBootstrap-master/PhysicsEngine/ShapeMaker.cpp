#include "ShapeMaker.h"
#include <Input.h>
#include <Gizmos.h>


ShapeMaker::ShapeMaker()
{
}

ShapeMaker::ShapeMaker(std::vector<glm::vec2> a_currentPoints)
{
	currentPoints = a_currentPoints;
}


ShapeMaker::~ShapeMaker()
{
}

void ShapeMaker::Update(float a_timeStep)
{
	aie::Input* input = aie::Input::getInstance();
	if (input->isMouseButtonDown(0))
	{
		currentPoints.push_back({ input->getMouseX(), input->getMouseY() });
	}

	if (input->isMouseButtonDown(1))
	{
		if (currentPoints.size() >= 3)
		{
			CreateShape();
			currentPoints.clear();
		}
	}
}

void ShapeMaker::Draw()
{
	for (size_t i = 0; i < currentPoints.size() - 1; i++)
	{

		aie::Gizmos::add2DCircle(currentPoints[i], 1, 32, { 0,1,0,1 });
	}

}



void ShapeMaker::CreateShape()
{

}
