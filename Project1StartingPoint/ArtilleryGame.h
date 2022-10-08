#pragma once

#include <gdp/Engine.h>
#include <string>
#include "ParticleSystem.h"

using namespace gdp; 

class ArtilleryGame {
public:
	ArtilleryGame();
	~ArtilleryGame();

	void Initialize();
	void Destroy();

	void StartNewGame();
	void GameUpdate();
	void DisplayTextToUser(const std::string& text);

	ParticleSystem particleSyst;
	Vector3 fireDirection;
	Particle* p;

	float distanceVectors(glm::vec3 vec1, glm::vec3 vec2);

private:
	GameObject* CreateGameObjectByType(const std::string& type);

	GameObject* m_PlayerTank;
	GameObject* m_EnemyTank;
	GameObject* m_Bullet;
};