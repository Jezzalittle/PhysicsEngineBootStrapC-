#pragma once
#include <glm\ext.hpp>
#include "PhysicsObject.h"


class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType a_shape, glm::vec2 a_pos, float a_rot, float a_mass);
	~RigidBody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug() {};

	void applyForce(glm::vec2 a_force);
	void applyForceToActor(RigidBody* other, glm::vec2 force);

	//virtual bool checkCollision(PhysicsObject * pOther) = 0;

	glm::vec2 getPos() { return pos; }
	float getRot() { return rot; }
	glm::vec2 getVel() { return vel; }
	float getMass() { return mass; }

	void SetVel(glm::vec2 a_vel) { vel = a_vel; }

protected:

	ShapeType shape;
	glm::vec2 pos;
	glm::vec2 vel;
	glm::vec2 acc;
	float rot;
	float mass;
	glm::vec2 ogPos;

};

