#pragma once

//#define OUTER_RAD	15.f
//#define MID_RAD		10.f
//#define INNER_RAD	5.f

#define OUTER_RAD	15.f
#define MID_RAD		10.f
#define INNER_RAD	5.f

class Swipe_Item
{
public:
	Swipe_Item();
	~Swipe_Item();

	void Update();
	void Render(HDC hdc);

	void Spawn(const Point& spawnPos);

	void SetPosition(const Point& pos);
	bool IsActive() const { return isActive; }
	void SetActive(const bool& isActive) { this->isActive = isActive; }

	Circle* GetBody() { return body; }

	AnimState GetAnimState() const { return animState; }
	void SetAnimState(const AnimState& state) { this->animState = state; }
private:
	Circle* body = nullptr;			// main body

	Circle* inner = nullptr;  // inner green circle
	Circle* middle = nullptr; // middle white circle
	Circle* outer = nullptr;  // outer green circle 

	bool isActive = false;

	HPEN	pen			= nullptr;
	HBRUSH	brush		= nullptr;
	HPEN	whitePen	= nullptr;
	HBRUSH	whiteBrush	= nullptr;
	
private:
	AnimState animState = IDLE;
	const float spawnLerpSpeed = 15.f;
	const float positionLerpSpeed = 15.f;
	float nextPosY = 0.f;

};
