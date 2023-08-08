#pragma once

#define MAX_POWER 650.f

class Tank
{
public:
	Tank();
	~Tank();

	void Update();
	void Render(HDC hdc);

	void RotateBarrel();
	void Move();
	void Fire();

	CannonBallManager* GetBalls() { return balls; }

private:
	Rect* body			= nullptr;
	Line* barrel		= nullptr;

	float barrelLength	= 200.f;
	float barrelAngle	= 0.f;	// ������ ȸ������

	float speed			= 5.f; // ��ũ�� ������ �ӵ�

	//CannonBall* ball	= nullptr;
	CannonBallManager* balls = nullptr;

	bool isCharging = false; // power�� ������ ���ΰ�

	float power = 0.f; // ��ź�� power

	Rect* frontBar = nullptr;
	Rect* backBar = nullptr;

	HBRUSH redBrush;

	Vector2 direction; // ������ direction
};
