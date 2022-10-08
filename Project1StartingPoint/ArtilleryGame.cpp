#include "ArtilleryGame.h"
#include <iostream>			// cout
#include "AssetInfo.h"
#include <random>

#define DEBUG_LOG_ENABLED
#ifdef DEBUG_LOG_ENABLED
#define DEBUG_PRINT(x, ...) printf(x, __VA_ARGS__)
#else
#define DEBUG_PRINT(x)
#endif

// Ids preloaded in the main.cpp to be referenced when
// creating specific game objects for your game.
// - EnemyTank, PlayerTank, and Bullet
unsigned int TankModelId;
unsigned int ProjectileModelId;
unsigned int PlayerMaterialId;
unsigned int EnemyMaterialId;
unsigned int BulletMaterialId;


const float TANKRADIUS = 1;

// TODO:
// #include "YourPhysicsClass.h"

/// <summary>
/// Default constructor
/// Set all class variables to the desired default state
/// </summary>
ArtilleryGame::ArtilleryGame(): m_PlayerTank(nullptr) ,m_EnemyTank(nullptr), m_Bullet(nullptr) 
{
	DEBUG_PRINT("ArtilleryGame::ArtilleryGame\n");
	// DO NOTHING!!!!!!!!
}

float RandFloat(float min, float max) {
	if (max == min)
		return 0.f;

	int diff = (max - min) * 1000;
	return min + (rand() % diff) / 1000.f;
}

/// <summary>
/// Default destructor
/// </summary>
ArtilleryGame::~ArtilleryGame()
{
	DEBUG_PRINT("ArtilleryGame::~ArtilleryGame\n");
	// DO NOTHING!!!!!!!!
}
/// <summary>
/// Create everything needed for your game here
/// such as memory allocation calls
/// </summary>
void ArtilleryGame::Initialize()
{
	DEBUG_PRINT("ArtilleryGame::Initialize\n");
	// TODO:
	// - Create a Player Tank GameObject
	// - Create an Enemy Tank GameObject
	// - Create projectile(s)
	m_PlayerTank = CreateGameObjectByType("Player");
	m_EnemyTank = CreateGameObjectByType("Enemy");
	m_Bullet = CreateGameObjectByType("Bullet");

	p = particleSyst.CreateParticle();
	

	m_PlayerTank->Position = glm::vec3(-10, 0, -10);
	m_EnemyTank->Position = glm::vec3(10, 0, 10);
	m_Bullet->Position = glm::vec3(0, 0, 0);
	fireDirection = Vector3(0.f);

	StartNewGame();
}

/// <summary>
/// Handle everything that needs to be destroyed
/// such as memory de-allocation.
/// </summary>
void ArtilleryGame::Destroy()
{
	DEBUG_PRINT("ArtilleryGame::Destroy\n");
	// TODO:
}

/// <summary>
/// StartNewGame
/// 1. Randomly place the enemy tank at a random valid location 
///    on the map
/// 2. Randomly place the player tank at a random valid location
///    on the map
/// 3. Reset the bullet(s)
/// </summary>
void ArtilleryGame::StartNewGame()
{
	DEBUG_PRINT("ArtilleryGame::StartNewGame\n");
	// TODO:
	printf("New Game Started! ---------------------------------------------\n");

	m_PlayerTank->Position = glm::vec3(RandFloat(-20, 20), 0, RandFloat(-20, 20));
	m_EnemyTank->Position = glm::vec3(RandFloat(-20, 20), 0, RandFloat(-20, 20));
	

	
	
}


/// <summary>
/// Update all bullets here
/// - Call your Physics class to update all projectiles
/// Check for bullet collision (position.y <= 0, hit ground)
/// Check for User input:
/// >>> GDP_IsKeyPressed, GDP_IsKeyHeldDown <-- Case Sensitive
/// >>> example: if (GDP_IsKeyPressed('n') || GDP_IsKeyPressed('N'))
/// - Input for changing the bullet direction	(wasd, etc)
/// - Input to change the projectile type		(1,2,3,4,5)
/// - Input to fire a projectile				(space)
/// - Input to start a new game					(n)
/// </summary>
void ArtilleryGame::GameUpdate()
{
	// DEBUG_PRINT("ArtilleryGame::GameUpdate\n");
	// TODO:

	//Add GDP_IsKeyPressed
	
	if (GDP_IsKeyPressed('D') || GDP_IsKeyPressed('d')) {
		// To fire the bullet Right
		
		fireDirection.x -= 1.0f;
		printf("fireDirection(%.2f, %.2f, %.2f\n", fireDirection.x, fireDirection.y, fireDirection.z);
	}
	if (GDP_IsKeyPressed('A') || GDP_IsKeyPressed('a')) {
		//To fire the bullet Left

		fireDirection.x += 1.0f;
		printf("fireDirection(%.2f, %.2f, %.2f\n", fireDirection.x, fireDirection.y, fireDirection.z);
	}
	
	if (GDP_IsKeyPressed('S') || GDP_IsKeyPressed('s')) {
		// To change the direction of the bullet
		
		fireDirection.z += 1.0f;
		printf("fireDirection(%.2f, %.2f, %.2f\n", fireDirection.x, fireDirection.y, fireDirection.z);
	}
	if (GDP_IsKeyPressed('W') || GDP_IsKeyPressed('w')) {
		//To change the Direction of the Bullet

		fireDirection.z += 1.0f;
		printf("fireDirection(%.2f, %.2f, %.2f\n", fireDirection.x, fireDirection.y, fireDirection.z);
	}
	
	if (GDP_IsKeyPressed('E') || GDP_IsKeyPressed('e')) {
		// To Fire the bullet in Downward Direction 
		
		fireDirection.y-= 1.0f;
		printf("fireDirection(%.2f, %.2f, %.2f\n", fireDirection.x, fireDirection.y, fireDirection.z);
	}
	if (GDP_IsKeyPressed('Q') || GDP_IsKeyPressed('q')) {
		// To Fire the bullet in Upward Direction

		fireDirection.y += 1.0f;
		printf("fireDirection(%.2f, %.2f, %.2f\n", fireDirection.x, fireDirection.y, fireDirection.z);
	}
	if (GDP_IsKeyPressed(' ')) {
		// Fire!
		p->ApplyForce(fireDirection);
		printf("Force: (%.3f, %.3f, %.3f) Applied!\n", fireDirection.x, fireDirection.y, fireDirection.z);
	}

	//To Start a new game
	if (GDP_IsKeyPressed('N') || GDP_IsKeyPressed('n')) {
	
			StartNewGame();
	}


	//If the bullet hits the Enemy Tank
	float distance = distanceVectors(m_EnemyTank->Position, m_Bullet->Position);
	if (distance <= TANKRADIUS) {
		printf("Bullet hit Tank\n");
	}
	else
	{
		printf("Bullet Missed\n");
	}
	m_Bullet->Position.x = p->position.x;
	m_Bullet->Position.y = p->position.y;
	m_Bullet->Position.z = p->position.z;


	particleSyst.Integrate(1.0f);

}

float ArtilleryGame::distanceVectors(glm::vec3 vec1, glm::vec3 vec2) {
		float distance = sqrt((vec1.x - vec2.x) * (vec1.x - vec2.x) +
		(vec1.y - vec2.y) * (vec1.y - vec2.y) +
		(vec1.z - vec2.z) * (vec1.z - vec2.z));
		return distance;
}

/// <summary>
/// Print provided text to the console for the user
/// </summary>
/// <param name="text"></param>
void ArtilleryGame::DisplayTextToUser(const std::string& text)
{
	std::cout << text << "\n";
}

GameObject* ArtilleryGame::CreateGameObjectByType(const std::string& type)
{
	DEBUG_PRINT("ArtilleryGame::CreateGameObjectByType(%s)\n", type.c_str());

	if (type.compare("Player") == 0) {
		DEBUG_PRINT("Create player!\n");
		GameObject* go = GDP_CreateGameObject();
		go->Renderer.ShaderId = 1;
		go->Renderer.MeshId = TankModelId;
		go->Renderer.MaterialId = PlayerMaterialId;
		return go;
	}
	if (type.compare("Enemy") == 0) {
		DEBUG_PRINT("Create Enemy!\n");
		GameObject* go = GDP_CreateGameObject();
		go->Renderer.ShaderId = 1;
		go->Renderer.MeshId = TankModelId;
		go->Renderer.MaterialId = EnemyMaterialId;
		return go;
	}
	if (type.compare("Bullet") == 0) {
		DEBUG_PRINT("Create Bullet!\n");
		GameObject* go = GDP_CreateGameObject();
		go->Renderer.ShaderId = 1;
		go->Renderer.MeshId = ProjectileModelId;
		go->Renderer.MaterialId = BulletMaterialId;
		go->Position = glm::vec3(0, 0, 0);
		return go;
	}

	// Invalid game object type, return nullptr
	return nullptr;
}