#include "Sphere.h"
#include <Gizmos.h>



Sphere::Sphere(const glm::vec2 pos, float a_radius, float  mass, const glm::vec4 a_colour)
	: RigidBody(SPHERE, pos, 0, mass)
{
	radius = a_radius;
	colour = a_colour;
}


Sphere::~Sphere()
{

}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(pos, radius, 32, colour);
}
