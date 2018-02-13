#include "RigidBody.h"
#include <Gizmos.h>




RigidBody::RigidBody(ShapeType a_shape, glm::vec2 a_pos, float a_rot, float a_mass) : PhysicsObject(a_shape)
{
	shape = a_shape;
	pos = a_pos;
	ogPos = pos;
	vel = { 0,0 };
	rot = a_rot;
	mass = a_mass;
	acc = { 0, 0 };
	initialVel = vel;
	firstFixedUpdate = true;
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	applyForce(gravity * mass, Physics::Impulse);
	vel += acc * timeStep;
	pos += vel * timeStep;

	if (firstFixedUpdate)
	{
		initialVel = vel;
		firstFixedUpdate = false;
	}

	acc = { 0,0 };
}

void RigidBody::resetPos()
{
	pos = ogPos;
	vel = initialVel;
	aie::Gizmos::clear();
}

void RigidBody::applyForce(glm::vec2 a_force, Physics::ForceMode a_forceMode)
{
	switch (a_forceMode)
	{
	case Physics::Force:
		acc += (a_force / mass);
	case Physics::Acceleration:
		acc += a_force;
	case Physics::Impulse:
		vel += (a_force / mass);
		break;
	case Physics::VelocityChange:
		vel += a_force;
		break;
	default:
		assert(false);
		break;
	}



}

void RigidBody::applyForceToActor(RigidBody * other, glm::vec2 force)
{
	other->applyForce(force);
	applyForce(-force);
}
