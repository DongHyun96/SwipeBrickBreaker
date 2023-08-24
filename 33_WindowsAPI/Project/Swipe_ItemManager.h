#pragma once
class Swipe_ItemManager : public Swipe_Pool<Swipe_Item>
{
public:
	Swipe_ItemManager(UINT poolCnt = 54);
	~Swipe_ItemManager();

	virtual void Update() override;

	virtual void Render(const HDC& hdc) override;

	virtual void Spawn(Point spawnPos) override;

	AnimState GetAnimState() const { return animState; }

	vector<Swipe_Item*>& GetItems() { return pool; }

	void DestroyAllItems();

private:

	AnimState animState = IDLE;


};
