#pragma once
#include "PhysicsObject.h"
class Plane : public PhysicsObject
{
public:
	Plane() = delete;
	Plane(glm::vec2 a_normal, float a_distance);
	~Plane() {};

	void fixedUpdate(glm::vec2 a_gravity, float a_timeStep) override {};
	virtual void debug() {};
	virtual void makeGizmo() override;

	glm::vec2 GetNormal() { return normal; }
	float GetDistanceToOrigin() { return distanceToOrigin; }

protected:

	glm::vec2 normal;
	float distanceToOrigin;

};

