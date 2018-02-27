#pragma once
#include "PhysicsScene.h"

class ShapeMaker;
class Sphere;
class Plane;
class AABB;

class ConvexShapesScene : public PhysicsScene
{
public:

	ConvexShapesScene() = delete;
	ConvexShapesScene(std::shared_ptr<class SceneManager> sceneManager, float a_tiemStep, glm::vec2 a_gravity) : PhysicsScene(sceneManager, a_tiemStep, a_gravity) {  };

	void Start();

	void CleanUp();

	void Update(float dt);

	~ConvexShapesScene();

private:

	ShapeMaker * shapeMaker;

};

