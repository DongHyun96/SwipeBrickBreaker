#include "Framework.h"
#include "Time.h"

Time* Time::instance = nullptr;

float Time::timeElapsed = 0.f;

Time::Time()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond); // CPU�� �ʴ� �������� ������ִ� �Լ�

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTick); // CPU�� ����(Tick) ���� ��
}

Time::~Time()
{
}

Time* Time::GetInstance()
{
	if (instance == nullptr)
		instance = new Time();

	return instance;
}

void Time::Delete()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void Time::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&curTick);

	timeElapsed = (float)(curTick - lastTick) / (float)ticksPerSecond;

	runningTime += timeElapsed;

	oneSecCount += timeElapsed; // oneSecCount - 1�ʸ� üũ�ϱ� ���� ����

	if (oneSecCount >= 1.0f) // 1�ʰ� �귶�� ��
	{
		frameRate = frameCount;
		frameCount = 0;

		oneSecCount -= 1.0f;	// ��Ȯ�� �� 1�ʿ��� �� ���� �� �ֱ� ������ 0���� �ʱ�ȭ�� ��Ű�� ����
								// ��¦ ���� �ð��� ���� ��꿡 �־��־�� ������ ������ ����
	}

	frameCount++;

	lastTick = curTick;
}

void Time::Render()
{
	wstring str;

	str = L"RunningTime : " + to_wstring((int)runningTime);
	TextOut(backDC, 0, 0, str.c_str(), str.size());

	str = L"FPS : " + to_wstring((int)frameRate);
	TextOut(backDC, 0, 20, str.c_str(), str.size());
}

