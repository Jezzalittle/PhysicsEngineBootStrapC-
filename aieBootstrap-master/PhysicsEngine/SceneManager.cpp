#include "SceneManager.h"
#include "RigidBody.h"
#include <Gizmos.h>


SceneManager::SceneManager(PhysicsScene * a_startScene)
{
	currentScene = a_startScene;
	scenes.push_back(currentScene);
	sceneIndex = 0;
	firstUpdate = true;
}

SceneManager::SceneManager()
{
	sceneIndex = 0;
	currentScene = nullptr;
	firstUpdate = true;
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
	if (firstUpdate == true && scenes.size() > 0)
	{
		scenes[0]->Start();
		firstUpdate = false;
	}
	currentScene->update(dt);
	currentScene->updateGizmos();
}

void SceneManager::AddScene(PhysicsScene * a_scene)
{
	if (a_scene != nullptr)
	{
		if (scenes.size() == 0)
		{
			currentScene = a_scene;
		}
		scenes.push_back(a_scene);

	}
}

void SceneManager::NextScene()
{
	if (sceneIndex + 1 < scenes.size())
	{
		for (auto i : scenes[sceneIndex]->GetActors())
		{
			i->resetPos();
		}

		scenes[sceneIndex]->CleanUp();

		sceneIndex++;
		currentScene = scenes[sceneIndex];

		currentScene->Start();
	}
}

void SceneManager::PreviousScene()
{
	if (sceneIndex - 1 >= 0)
	{
		
		for (auto i : scenes[sceneIndex]->GetActors())
		{
			i->resetPos();
		}

		scenes[sceneIndex]->CleanUp();
		sceneIndex--;
		currentScene = scenes[sceneIndex];

		currentScene->Start();
	}
}




void SceneManager::drawprojectileMotionDemo()
{

	float t = 0;
	float tStep = 0.5f;
	float radius = 1.0f;
	glm::vec2 startPos = { -40,0 };
	int segments = 12;
	glm::vec4 colour = glm::vec4(1, 1, 0, 1);
	float speed = 20;
	float incline = 45;
	float gravity = -9.8f;

	while (t <= 5)
	{

		glm::vec2 currPos;

		currPos.x = startPos.x + (speed * t);
		currPos.y = startPos.y + (speed * t) + (0.5f * gravity * (t*t));

		aie::Gizmos::add2DCircle(glm::vec2(currPos.x, currPos.y), radius, segments, colour);
		t += tStep;
	}

}


