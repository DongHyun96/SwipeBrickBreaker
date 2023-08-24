#include "Framework.h"
#include "Swipe_BrickManager.h"


Swipe_BrickManager::Swipe_BrickManager(UINT poolCnt)
{
	for (UINT i = 0; i < SWIPE_COL_CNT * SWIPE_ROW_CNT; i++)
	{
		UINT x = i % SWIPE_COL_CNT;
		UINT y = i / SWIPE_COL_CNT;

		float xPos = SWIPE_MARGIN + BRICK_SIZE_X / 2 + (SWIPE_MARGIN + BRICK_SIZE_X) * x;
		float yPos = SWIPE_CEIL + SWIPE_MARGIN + BRICK_SIZE_Y / 2 + (SWIPE_MARGIN + BRICK_SIZE_Y) * y;

		pool.push_back(new Swipe_Brick(Point(xPos, yPos)));
	}
}

Swipe_BrickManager::~Swipe_BrickManager()
{
	// 부모 클래스에서 pool 삭제
}

void Swipe_BrickManager::Update()
{
	for (Swipe_Brick* brick : pool)
		brick->Update();

	switch (animState)
	{
	case IDLE:
		break;
	case SPAWNING:

		for (Swipe_Brick* brick : pool)
		{
			if (brick->IsActive() && brick->GetAnimState() != IDLE) // 아직 스폰하는 중
				return;
		}

		// 스포닝 끝, positioning 시작
		animState = POSITIONING;

		break;
	case POSITIONING: // Check for anim state update
	{

		static bool repoStarted = false;

		if (!repoStarted)
		{
			for (Swipe_Brick* brick : pool)
			{
				if (!brick->IsActive())
					continue;

				brick->SetAnimState(POSITIONING);
			}

			repoStarted = true;
		}

		for (Swipe_Brick* brick : pool)
		{
			if (brick->IsActive() && brick->GetAnimState() != IDLE) // 아직 positioning 하는 중
				return;
		}

		// positioning 끝
		repoStarted = false;
		animState = IDLE;
	}
		break;
	default:
		break;
	}
}

void Swipe_BrickManager::Render(const HDC& hdc)
{
	SetTextColor(hdc, RGB(255, 255, 255));

	for (Swipe_Brick* brick : pool)
		brick->Render(hdc);

	SetTextColor(hdc, RGB(0, 0, 0));

}

void Swipe_BrickManager::Spawn(Point spawnPos)
{
	animState = SPAWNING;

	for (Swipe_Brick* brick : pool)
	{
		if (brick->IsActive())
			continue;
		
		brick->Spawn(spawnPos);
		return;
	}
}

bool Swipe_BrickManager::IsGameOver()
{
	for (Swipe_Brick* brick : pool)
	{
		if (!brick->IsActive())
			continue;

		if (brick->GetBody()->Top() > SWIPE_GAME_OVER_Y)
			return true;
	}
	return false;
}

void Swipe_BrickManager::DestroyAllBricks()
{
	for (Swipe_Brick* brick : pool)
	{
		if (!brick->IsActive())
			continue;

		Swipe_ParticleManager::GetInst()->Spawn(brick->GetBody()->Pos(), PARTICLE_RED);
		brick->SetActive(false);
	}
}
