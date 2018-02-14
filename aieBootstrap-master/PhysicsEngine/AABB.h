#pragma once
#include "RigidBody.h"

class AABB : public RigidBody
{
public:

	AABB() = delete;
	AABB(const glm::vec2 pos, glm::vec2 a_extents , float  mass, const glm::vec4 a_colour);
	~AABB();

	virtual void makeGizmo();


private:
	
	glm::vec2 extents;
	glm::vec4 colour;

};

