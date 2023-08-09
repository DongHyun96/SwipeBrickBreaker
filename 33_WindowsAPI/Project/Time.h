#pragma once
class Time
{
private:
	Time();
	~Time();

public:
	static Time* GetInstance();
	static void Delete();

public:
	void Update();
	void Render(); // backDC�� �׸� ���̰� ����
	void Render(HDC hdc);

	static float Delta() { return timeElapsed; }

private:
	static Time* instance;

private:
	static float timeElapsed; // �� ����� �ð�

	// Tick�� cpu�� ������
	INT64 curTick			= 0;
	INT64 lastTick			= 0;
	INT64 ticksPerSecond	= 0;

	UINT frameCount			= 0;
	UINT frameRate			= 0;

	float runningTime		= 0.f; // ���α׷� ���� ���ķ� �帥 �ð�
	float scanningRate		= 0.f; // �ֻ��� -> �ֻ����� �°� frameRate�� ���� -> vSync
	

	float oneSecCount		= 0.f;
	
};
