#include "SceneManager.h"



SceneManager::SceneManager(PhysicsScene * a_startScene)
{
	currentScene = a_startScene;
	scenes.push_back(currentScene);
	sceneIndex = 0;
}

SceneManager::SceneManager()
{
	sceneIndex = 0;
	currentScene = nullptr;
}



SceneManager::~SceneManager()
{
}

void SceneManager::SetCurrentScene(PhysicsScene * a_scene)
{
	if (a_scene != nullptr)
	{
		currentScene = a_scene;
	}
}

void SceneManager::UpdateScene(float dt)
{
	currentScene->update(dt);
	currentScene->updateGizmos();
}

void SceneManager::AddScene(PhysicsScene * a_scene)
{
	if (a_scene != nullptr)
	{
		if (sceneIndex == 0)
		{
			currentScene = a_scene;
		}
		scenes.push_back(a_scene);
		sceneIndex++;
	}
}

void SceneManager::NextScene()
{
	if (sceneIndex + 1 < scenes.size())
	{
		sceneIndex++;
		currentScene = scenes[sceneIndex];
	}
}

void SceneManager::PreviousScene()
{
	if (sceneIndex - 1 >= 0)
	{
		sceneIndex--;
		currentScene = scenes[sceneIndex];
	}
}




