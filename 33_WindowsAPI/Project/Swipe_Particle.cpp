#include "Framework.h"
#include "Swipe_Particle.h"

const float Swipe_Particle::gravityAccel = 100.f;


Swipe_Particle::Swipe_Particle()
{
	for (UINT i = 0; i < PARTICLE_CNT; i++)
	{
		bodies.push_back(new Rect(WIN_CENTER, Point(10, 10)));
		
		Vector2 dir = Vector2( cosf((2 * PI / PARTICLE_CNT) * i), -sinf((2 * PI / PARTICLE_CNT) * i) );

		speeds.push_back(GetRandom(400.f, 700.f));

		dir.Normalize();

		directions.push_back(dir);
	}
	
}

Swipe_Particle::~Swipe_Particle()
{
	for (Rect* body : bodies)
		delete body;
}

void Swipe_Particle::Update()
{
	if (!isActive)
		return;

	Move();
	HandleCollisionFloor();
}

void Swipe_Particle::Render(HDC hdc)
{
	if (!isActive)
		return;

	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	for (Rect* body : bodies)
		body->Render(hdc);
}

void Swipe_Particle::Spawn(Point spawnPos, ParticleType type)
{
	isActive = true;

	for (Rect* body : bodies)
		body->Pos() = spawnPos;

	pair<HPEN, HBRUSH> targetColors;

	switch (type)
	{
	case PARTICLE_GREEN:
		targetColors = Swipe_Palette::GetInst()->GetParticleColorGreen();
		break;
	case PARTICLE_RED:
		targetColors = Swipe_Palette::GetInst()->GetParticleColorRed();
		break;
	case PARTICLE_BLACK:
		targetColors = Swipe_Palette::GetInst()->GetParticlColorBlack();
	default:
		break;
	}

	pen = targetColors.first;
	brush = targetColors.second;

	gravity = 0.f;
	
	speeds.clear();

	for (UINT i = 0; i < bodies.size(); i++)
		speeds.push_back(GetRandom(400.f, 700.f));

}

void Swipe_Particle::Move()
{
	for (UINT i = 0; i < bodies.size(); i++)
	{
		bodies[i]->Pos() += directions[i] * speeds[i] * Time::Delta();
		bodies[i]->Pos() += Vector2(0, 1) * gravity * Time::Delta();
		gravity += gravityAccel * Time::Delta();
	}
}

void Swipe_Particle::HandleCollisionFloor()
{
	for (Rect* body : bodies)
	{
		if (body->Bottom() < WIN_HEIGHT)
			return;
	}
	
	isActive = false;
	gravity = 0.f;
}
