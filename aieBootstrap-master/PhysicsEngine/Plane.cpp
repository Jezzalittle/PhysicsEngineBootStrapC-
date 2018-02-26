#include "Plane.h"
#include <Gizmos.h>


Plane::Plane(glm::vec2 a_normal, float a_distance) : PhysicsObject(PLANE)
{
	normal = glm::normalize(a_normal);
	distanceToOrigin = a_distance;
}

void Plane::makeGizmo()
{
	const float lineSegLength = 300.0f;
	glm::vec2 center = normal * -distanceToOrigin;
	glm::vec4 colour = { 1,1,1,1 };

	glm::vec2 paralle{ normal.y, -normal.x };

	glm::vec2 start = center + (paralle * lineSegLength);
	glm::vec2 end = center - (paralle * lineSegLength);

	aie::Gizmos::add2DLine(start, end, colour);

}



