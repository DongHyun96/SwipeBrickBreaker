#pragma once
class Swipe_ItemManager : public Swipe_Pool<Swipe_Item>
{
public:
	Swipe_ItemManager();
	Swipe_ItemManager(UINT poolCnt);
	~Swipe_ItemManager();

	virtual void Update() override;

	virtual void Render(const HDC& hdc) override;

	virtual void Spawn(Point spawnPos) override;

	AnimState GetAnimState() const { return animState; }

	vector<Swipe_Item*>& GetItems() { return pool; }

	void DestroyAllItems();

	template <class Archive>
	void serialize(Archive& ar, const UINT version);

private:

	AnimState animState = IDLE;

};

template<class Archive>
inline void Swipe_ItemManager::serialize(Archive& ar, const UINT version)
{
	ar& pool;
	ar& animState;
}
