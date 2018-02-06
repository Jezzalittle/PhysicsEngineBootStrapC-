#pragma once
#include <glm\ext.hpp>
#include <vector>

class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene(class SceneManager& sceneManager, float a_tiemStep, glm::vec2 a_gravity);
	PhysicsScene() = delete;
	~PhysicsScene();


	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float dt);
	void updateGizmos();

	void setGravity(const glm::vec2 a_gravity) { gravity = a_gravity; }
	glm::vec2 getGravity() const { return gravity;  }

	void setTimeStep(const float a_timeStep) { timeStep = a_timeStep; }
	float getTimeStep() const { return timeStep;  }

protected:
	
	glm::vec2 gravity;
	float timeStep;
	std::vector<PhysicsObject*> actors;

};

