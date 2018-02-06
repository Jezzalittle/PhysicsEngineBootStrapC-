#pragma once
#include "RigidBody.h"

class Sphere : public RigidBody
{

private:

	//float speed;
	//float inclination;


public:
	Sphere() = delete;
	Sphere(const glm::vec2 pos, float radius, float  mass, const glm::vec4 a_colour);
	~Sphere();

	virtual void makeGizmo();
	

	//void SetSpeed(float a_speed) { speed = a_speed; };
	//void SetInclination(float a_inclination) { inclination = a_inclination; };



protected:

	float radius;
	glm::vec4 colour;


};

