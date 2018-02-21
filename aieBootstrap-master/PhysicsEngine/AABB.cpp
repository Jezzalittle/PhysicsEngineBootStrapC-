#include "AABB.h"
#include <Gizmos.h>





AABB::AABB(const glm::vec2 pos, glm::vec2 a_extents, float mass, const glm::vec4 a_colour) : RigidBody(BOX, pos, 0, mass), extents(a_extents), colour(a_colour) {}



void AABB::makeGizmo()
{
	aie::Gizmos::add2DAABBFilled(pos, extents, colour);
}
