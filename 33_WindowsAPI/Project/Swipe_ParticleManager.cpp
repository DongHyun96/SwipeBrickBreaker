#include "Framework.h"
#include "Swipe_ParticleManager.h"


Swipe_ParticleManager::Swipe_ParticleManager()
{
	for (UINT i = 0; i < 60; i++)
		pool.push_back(new Swipe_Particle);
}

Swipe_ParticleManager::~Swipe_ParticleManager()
{
}

void Swipe_ParticleManager::Update()
{
	for (Swipe_Particle* particle : pool)
		particle->Update();
}

void Swipe_ParticleManager::Render(const HDC& hdc)
{
	for (Swipe_Particle* particle : pool)
		particle->Render(hdc);
}

void Swipe_ParticleManager::Spawn(Point spawnPos, ParticleType type)
{
	for (Swipe_Particle* particle : pool)
	{
		if (particle->IsActive())
			continue;

		particle->Spawn(spawnPos, type); // temp
		return;
	}
}

void Swipe_ParticleManager::Spawn(Point spawnPos)
{
}
