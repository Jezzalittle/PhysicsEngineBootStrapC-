#pragma once
#include <glm\ext.hpp>
#include "PhysicsObject.h"

namespace Physics
{
	enum ForceMode
	{
		Force,			//Add a continuous force to the rigidbody, using its mass.
		Acceleration,	//Add a continuous acceleration to the rigidbody, ignoring its mass.
		Impulse,		//Add an instant force impulse to the rigidbody, using its mass.
		VelocityChange	//Add an instant velocity change to the rigidbody, ignoring its mass.
	};
}

class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType a_shape, glm::vec2 a_pos, float a_rot, float a_mass);
	~RigidBody();


	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug() {};

	virtual void resetPos() override;

	void applyForce(glm::vec2 a_force, Physics::ForceMode a_forceMode);
	void applyForceToActor(RigidBody* other, glm::vec2 force);

	//virtual bool checkCollision(PhysicsObject * pOther) = 0;

	glm::vec2 getPos() { return pos; }
	float getRot() { return rot; }
	glm::vec2 getVel() { return vel; }
	float getMass() { return mass; }

	void SetVel(glm::vec2 a_vel) { vel = a_vel; }
	void SetPos(glm::vec2 a_pos) { pos = a_pos; }

protected:

	glm::vec2 pos;
	glm::vec2 vel;
	glm::vec2 acc;
	float rot;
	float mass;
	glm::vec2 ogPos;
	glm::vec2 initialVel;
	bool firstFixedUpdate;

};

