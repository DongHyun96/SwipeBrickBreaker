#pragma once
class Swipe_Ball
{
public:
	Swipe_Ball();
	~Swipe_Ball();

	void Update();
	void Render(const HDC& hdc);

	void Fire(Vector2 direction, float speed = 2000.f);
	void Move();

public:
	void SetActive(const bool& isActive) { this->isActive = isActive; }
	bool IsActive() const { return isActive; }

	bool IsMovable() const { return isMovable; }

	Circle* GetBody() { return body; }
	Vector2& Dir() { return direction; }

	bool IsFired() const { return fired; }
	void SetFired(const bool& fired) { this->fired = fired; }

public:
	void SetAnimState(const AnimState& state) { this->animState = state; }
	const AnimState& GetAnimState() const { return animState; }

private:
	void HandleCollisionWall();

private:
	HPEN   pen		= nullptr;
	HBRUSH brush	= nullptr;

	bool isActive	= false;
	bool isMovable	= false; // 공을 쐈을 때 바닥면에 닿았는지 안닿았는지 체크(?)

	Circle* body	= nullptr;

	Vector2 direction = {};

	float speed = 0.f;

	bool fired = false;

	static bool floorCollided;

private:
	AnimState animState = IDLE;
	const float positionLerpSpeed = 15.f;
};
