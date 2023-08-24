#pragma once

class Swipe_Brick
{
public:

	Swipe_Brick(Point pos);

	~Swipe_Brick();

	void Update();
	void Render(HDC hdc);

	void Spawn(Point spawnPos);
	void ApplyDamage();

	bool IsActive() const { return isActive; }
	void SetActive(const bool& isActive) { this->isActive = isActive; }
	Rect* GetBody() { return body; }

	AnimState GetAnimState() const { return animState; }
	void SetAnimState(const AnimState state) { this->animState = state; }
	
	void SetColor(const pair<HPEN, HBRUSH>& colors);

	int GetHP() const { return hp; }

private:
	Rect* body = nullptr;
	bool isActive = false;

	HPEN pen = nullptr;
	HBRUSH brush = nullptr;

	UINT hp = 1;

private:
	AnimState animState = IDLE;

	const float spawnLerpSpeed = 15.f;
	const float positionLerpSpeed = 15.f;
	float nextPosY = 0.f;
};
