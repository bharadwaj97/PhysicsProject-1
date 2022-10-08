#include "ParticleSystem.h"

#include <random>

ParticleSystem::ParticleSystem()
	: ParticleSystem(Vector3()) {
}

ParticleSystem::ParticleSystem(const Vector3& position)
	: m_Position(position)
	, MinAgeMilliseconds(1000.f) 
	, MaxAgeMilliseconds(2000.f)
	, MinVelocity(Vector3(0.f))
	, MaxVelocity(Vector3(0.f, 1.f, 0.f))
{
	// m_Particles.reserve();
	// m_Particles.resize();
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::GenerateParticles(unsigned int count) {
	m_Particles.resize(count);
}

// Quick utility function for a random range of two floats
/*float RandFloat(float min, float max) {
	if (max == min)
		return 0.f;

	int diff = (max - min) * 1000;
	return min + (rand() % diff) / 1000.0f;
}*/

Particle* ParticleSystem::CreateParticle() { //initial:void ParticleSystem::CreateParticle(const Vector3& velocity)
	Particle* p = new Particle();
	m_Particles.push_back(p);
	return p;
}

void ParticleSystem::Integrate(
	float duration) {
	for (int i = 0; i < m_Particles.size(); i++) {
		Particle* p = m_Particles[i];
		p->ApplyForce(Vector3(0.f, -0.98f, 0.0f));
		p->Integrate(duration);
		p->KillAllForces();
	}
}

void ParticleSystem::PrintParticleInfo() {
	for (int i = 0; i < m_Particles.size(); i++) {
		Particle* p = m_Particles[i];
		p->PrintInfo();
	}
}
