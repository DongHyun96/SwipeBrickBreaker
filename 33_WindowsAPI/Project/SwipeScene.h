#pragma once
class SwipeScene : public Scene
{
public:
	SwipeScene();
	~SwipeScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:

	void RenderEnvironment(HDC hdc);
	
	void HandleFire();
	bool IsFireable();

	void InitBrickAndItem();

private:
	void HandleCollision();
	
	// ���� �긯�� �浹
	void HandleCollision(vector<Swipe_Ball*>& balls, vector<Swipe_Brick*>& bricks);

	// ���� �������� �浹
	void HandleCollision(const vector<Swipe_Ball*>& balls, vector<Swipe_Item*>& items);

private:

	Line* ceil = nullptr;
	Line* floor = nullptr;
	Rect* background = nullptr;

private:
	Swipe_BallManager* ballManager = nullptr;
	float fireTime = 0.f;
	float fireTick = 0.05f;
	//float fireTick = 0.025f;

	UINT fireCnt = 0;
	Vector2 fireDir = {};

private:
	Swipe_BrickManager* brickManager = nullptr;
	Swipe_ItemManager* itemManager = nullptr;

	HFONT font = nullptr;
};
