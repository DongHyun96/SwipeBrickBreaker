#pragma once
class Swipe_BallManager : public Swipe_Pool<Swipe_Ball>
{
public:
	Swipe_BallManager(UINT poolCnt = 500);
	~Swipe_BallManager();

	virtual void Update() override;
	virtual void Render(const HDC& hdc) override;
	void InitRound();

	void Fire(Vector2 direction);

	vector<Swipe_Ball*>& GetFieldBalls() { return fieldBalls; }

	AnimState GetAnimState() const { return animState; }

	vector<Swipe_Ball*>& GetBalls() { return fieldBalls; }

	bool IsRoundOver();

public:
	void InitGameStart(); // used for restarting game

private:
	virtual void Spawn(Point spawnPos) override; // 사용하지 않을 것임


private:
	vector<Swipe_Ball*> fieldBalls = {};

private:
	AnimState animState = IDLE;
};
