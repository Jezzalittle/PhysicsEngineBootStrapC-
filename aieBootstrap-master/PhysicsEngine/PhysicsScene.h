#pragma once
#include <glm\ext.hpp>
#include <vector>
#include <memory>

class PhysicsObject;


class PhysicsScene
{


public:

	struct  CollisionData
	{
		bool wasCollision;
		glm::vec2 normal;
		float overlap;
	};

	PhysicsScene(std::shared_ptr<class SceneManager> sceneManager, float a_tiemStep, glm::vec2 a_gravity);
	PhysicsScene() = delete;
	~PhysicsScene();

	void CheckForCollision();

	static CollisionData Plane2Sphere(PhysicsObject* object1, PhysicsObject*object2);
	static CollisionData Sphere2Plane(PhysicsObject* object1, PhysicsObject* object2);
	static CollisionData Sphere2Sphere(PhysicsObject* object1, PhysicsObject* object2);
	static CollisionData Sphere2Box(PhysicsObject* object1, PhysicsObject* object2);
	static CollisionData Box2Plane(PhysicsObject* object1, PhysicsObject* object2);
	static CollisionData Box2Sphere(PhysicsObject* object1, PhysicsObject* object2);
	static CollisionData Box2Box(PhysicsObject* object1, PhysicsObject* object2);
	static CollisionData Plane2Box(PhysicsObject* object1, PhysicsObject* object2) { return CollisionData(); }
	


	void handleCollision(PhysicsObject* object1, PhysicsObject* object2, const CollisionData& data);

	void SeperateCollisionObjects(class RigidBody * object1, class RigidBody * object2, const PhysicsScene::CollisionData & collData);


	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	virtual void update(float dt);
	void updateGizmos();

	virtual void Start() = 0;
	virtual void CleanUp() = 0;

	void setGravity(const glm::vec2 a_gravity) { gravity = a_gravity; }
	glm::vec2 getGravity() const { return gravity;  }

	void setTimeStep(const float a_timeStep) { timeStep = a_timeStep; }
	float getTimeStep() const { return timeStep;  }

	void SetClearGizmos(bool a_clearGizmo) { clearGizmos = a_clearGizmo; }
	std::vector<PhysicsObject*> GetActors() { return actors;  }

protected:
	
	

	glm::vec2 gravity;
	float timeStep;
	std::vector<PhysicsObject*> actors;

	std::shared_ptr<class SceneManager> m_sceneManager;

private:

	bool clearGizmos;


};

