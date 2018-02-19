#include "AABB.h"
#include <Gizmos.h>





AABB::AABB(const glm::vec2 pos, glm::vec2 a_extents, float mass, const glm::vec4 a_colour) : RigidBody(BOX, pos, 0, mass), extents(a_extents), colour(a_colour) 
{
	tl.x = pos.x - (0.5f * a_extents.x);
	tl.y = pos.y + (0.5f * a_extents.y);

	tr.x = pos.x + (0.5f * a_extents.x);
	tr.y = pos.y + (0.5f * a_extents.y);

	bl.x = pos.x - (0.5f * a_extents.x);
	bl.y = pos.y - (0.5f * a_extents.y);

	br.x = pos.x + (0.5f * a_extents.x);
	br.y = pos.y - (0.5f * a_extents.y);

}


void AABB::makeGizmo()
{
	aie::Gizmos::add2DAABBFilled(pos, extents, colour);
}
