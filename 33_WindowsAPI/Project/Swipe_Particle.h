#pragma once

#define PARTICLE_CNT 30

enum ParticleType
{
	PARTICLE_GREEN,
	PARTICLE_RED,
	PARTICLE_BLACK
};

class Swipe_Particle
{
public:
	Swipe_Particle();
	~Swipe_Particle();

	void Update();
	void Render(HDC hdc);

	void Spawn(Point spawnPos, ParticleType type);

	bool IsActive() const { return isActive; }

private:
	void Move();

	/// <summary>
	/// 마지막 입자까지 바닥과 충돌했으면 isActive -> false
	/// </summary>
	void HandleCollisionFloor();

private:
	vector<Rect*> bodies = {};
	
	//float speed = 400.f;

	vector<Vector2> directions = {};
	vector<float> speeds = {};

	bool isActive = false;

	HPEN pen		= nullptr;
	HBRUSH brush	= nullptr;

	static const float gravityAccel;
	float gravity = 0.f;

};
