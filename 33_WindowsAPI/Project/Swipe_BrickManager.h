#pragma once
class Swipe_BrickManager : public Swipe_Pool<Swipe_Brick>
{
public:
	Swipe_BrickManager();
	Swipe_BrickManager(UINT poolCnt);
	~Swipe_BrickManager();

	virtual void Update() override;
	virtual void Render(const HDC& hdc) override;

	virtual void Spawn(Point spawnPos) override;

	AnimState GetAnimState() const { return animState; }
	
	vector<Swipe_Brick*>& GetBricks() { return pool; }

	bool IsGameOver();

	void DestroyAllBricks();

	template<class Archive>
	void serialize(Archive& ar, const UINT version);

private:
	AnimState animState = IDLE;

};

template<class Archive>
inline void Swipe_BrickManager::serialize(Archive& ar, const UINT version)
{
	ar& pool;
	ar& animState;
}
