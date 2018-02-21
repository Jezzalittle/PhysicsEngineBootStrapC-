#pragma once
#include "RigidBody.h"

class AABB : public RigidBody
{
public:

	AABB() = delete;
	AABB(const glm::vec2 pos, glm::vec2 a_extents, float  mass, const glm::vec4 a_colour);
	~AABB() {}

	glm::vec2 GetExtents()
	{
		return extents;
	}

	glm::vec2 GetTL() 
	{
		glm::vec2 tl;
		tl.x = pos.x - (0.5f * extents.x);
		tl.y = pos.y + (0.5f * extents.y);
		return tl;
	}

	glm::vec2 GetTR() 
	{
		glm::vec2 tr;
		tr.x = pos.x + (0.5f * extents.x);
		tr.y = pos.y + (0.5f * extents.y);
		return tr;
	}

	glm::vec2 GetBL() 
	{
		glm::vec2 bl;
		bl.x = pos.x - (0.5f * extents.x);
		bl.y = pos.y - (0.5f * extents.y);
		return bl;
	}

	glm::vec2 GetBR() 
	{
		glm::vec2 br;
		br.x = pos.x + (0.5f * extents.x);
		br.y = pos.y - (0.5f * extents.y);
		return br;
	}
	

	float getWidth() { return extents.x; }
	float getHeight() { return extents.y; }


	virtual void makeGizmo();


private:

	glm::vec2 extents;
	glm::vec4 colour;

};

