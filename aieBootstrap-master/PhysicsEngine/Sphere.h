#pragma once
#include "RigidBody.h"

class Sphere : public RigidBody
{

public:
	Sphere() = delete;
	Sphere(const glm::vec2 pos, float radius, float  mass, const glm::vec4 a_colour);
	~Sphere();

	virtual void makeGizmo();
	

	float GetRadius() { return radius; }



protected:

	float radius;
	glm::vec4 colour;

};

