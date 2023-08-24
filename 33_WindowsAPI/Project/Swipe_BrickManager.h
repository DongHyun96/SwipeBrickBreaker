#pragma once
class Swipe_BrickManager : public Swipe_Pool<Swipe_Brick>
{
public:
	Swipe_BrickManager(UINT poolCnt = 54);
	~Swipe_BrickManager();

	virtual void Update() override;
	virtual void Render(const HDC& hdc) override;

	virtual void Spawn(Point spawnPos) override;

	AnimState GetAnimState() const { return animState; }
	
	vector<Swipe_Brick*>& GetBricks() { return pool; }

	bool IsGameOver();

	void DestroyAllBricks();

private:
	AnimState animState = IDLE;

};
