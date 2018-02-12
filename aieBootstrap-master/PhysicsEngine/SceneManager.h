#pragma once

#include "PhysicsScene.h"
#include <vector>



class SceneManager
{
private:

	PhysicsScene * currentScene;
	std::vector<PhysicsScene*> scenes;
	int sceneIndex;
	bool firstUpdate;
	
public:
	SceneManager(PhysicsScene* startScene);
	SceneManager();
	~SceneManager();

	void SetCurrentScene(PhysicsScene* a_scene);

	void UpdateScene(float dt);

	void AddScene(PhysicsScene* a_scene);
	
	void NextScene();

	void PreviousScene();

	
	int getSceneIndex() { return sceneIndex; };


	void drawprojectileMotionDemo();



};

