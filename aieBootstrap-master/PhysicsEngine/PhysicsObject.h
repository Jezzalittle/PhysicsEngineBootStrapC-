#pragma once

#include <glm\ext.hpp>

#include "PhysicsObject.h"

#include "PhysicsScene.h"

enum ShapeType
{
	SPHERE = 0,
	PLANE,
	BOX,
	SHAPECOUNT
};


class PhysicsObject
{

public:





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

