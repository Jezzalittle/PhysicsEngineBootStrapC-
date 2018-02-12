#pragma once
#include "PhysicsObject.h"
class Plane :	public PhysicsObject
{
public:
	Plane() = delete;
	Plane(const glm::vec2& a_normal, float a_distance);

	void fixedUpdate() {};
	void debug() {};
	void makeGizmo();

	glm::vec2 GetNormal() { return normal; }
	float GetDistanceToOrigin() { return distanceToOrigin; }

private:

	glm::vec2 normal;
	float distanceToOrigin;

};

