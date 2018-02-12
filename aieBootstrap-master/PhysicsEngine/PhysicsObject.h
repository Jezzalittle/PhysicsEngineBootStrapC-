#pragma once

#include <glm\ext.hpp>

#include "PhysicsObject.h"

#include "PhysicsScene.h"

class PhysicsObject
{

public:

enum class ShapeType
{
	Sphere = 0,
	Plane,
	Box,
	num_Shape
};



	~PhysicsObject();
	PhysicsObject() = delete;

	ShapeType GetShapeID() { return shape; }

	virtual void fixedUpdate(glm::vec2 a_gravity, float a_timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPos() {};

protected:

	PhysicsObject(ShapeType a_Shape) : shape(a_Shape) {}
	ShapeType shape;

	

	
};

