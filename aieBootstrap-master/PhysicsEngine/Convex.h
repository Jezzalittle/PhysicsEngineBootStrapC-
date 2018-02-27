#include "PhysicsObject.h"

#pragma once
class Convex : public PhysicsObject
{
public:
	Convex() = delete;
	~Convex();

private :

	std::vector<glm::vec2> verts;


};

