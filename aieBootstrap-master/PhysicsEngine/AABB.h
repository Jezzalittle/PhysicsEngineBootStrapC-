#pragma once
#include "RigidBody.h"

class AABB : public RigidBody
{
public:

	AABB() = delete;
	AABB(const glm::vec2 pos, glm::vec2 a_extents , float  mass, const glm::vec4 a_colour);
	~AABB() {}

	glm::vec2 GetTL() { return tl; }
	glm::vec2 GetTR() { return tr; }
	glm::vec2 GetBL() { return bl; }
	glm::vec2 GetBR() { return br; }

	float getWidth() { return extents.x; }
	float getHeight() { return extents.y; }


	virtual void makeGizmo();


private:
	
	glm::vec2 tl;
	glm::vec2 tr;
	glm::vec2 bl;
	glm::vec2 br;

	glm::vec2 extents;
	glm::vec4 colour;

};

