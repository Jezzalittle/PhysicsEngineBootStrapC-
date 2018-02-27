#pragma once
#include <vector>
#include <glm\ext.hpp>

class ShapeMaker
{
public:
	ShapeMaker();
	ShapeMaker(std::vector<glm::vec2> a_currentPoints);
	~ShapeMaker();

	void Update(float a_timeStep);

	void Draw();

	void CreateShape();

private:

	std::vector<glm::vec2> currentPoints;
};

