#pragma once


#include "Particle.h"

#include <vector>

class ParticleSystem {
public:
	ParticleSystem();
	ParticleSystem(const Vector3& position);
	~ParticleSystem();

	// Typically done during loading of a level,
	// not performed during the gameplay, as it
	// could cause performance spikes.
	void GenerateParticles(unsigned int count);

	Particle* CreateParticle();//define function such that it returns p
														//initial :void CreateParticle(const Vector3& velocity)
	void Integrate(float duration);
	void PrintParticleInfo();

	Vector3 MinVelocity;
	Vector3 MaxVelocity;
	float MinAgeMilliseconds;
	float MaxAgeMilliseconds;

private:
	// unsigned int m_NumParticles;
	std::vector<Particle*> m_Particles;
	Vector3 m_Position;
};	