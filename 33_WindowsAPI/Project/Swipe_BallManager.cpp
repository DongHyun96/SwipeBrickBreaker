#include "Framework.h"
#include "Swipe_BallManager.h"


Swipe_BallManager::Swipe_BallManager(UINT poolCnt)
	:Swipe_Pool(poolCnt)
{
	// 부모 클래스에서 pool 생성

	// 공 하나 spawn
	pool[0]->SetActive(true);
	pool[0]->GetBody()->Pos() = Swipe_GameManager::GetInst()->GetBallStartPos();

	fieldBalls.push_back(pool[0]);

}

Swipe_BallManager::~Swipe_BallManager()
{
	// 부모 클래스에서 풀 삭제
}

void Swipe_BallManager::Update()
{
	for (Swipe_Ball* ball : fieldBalls)
		ball->Update();

	switch (animState)
	{
	case IDLE:
		break;
	case POSITIONING: // Check for anim state update
	{
		static bool repoStarted = false;

		if (!repoStarted)
		{
			for (Swipe_Ball* ball : fieldBalls)
				ball->SetAnimState(POSITIONING);

			repoStarted = true;
		}

		for (Swipe_Ball* ball : fieldBalls)
		{
			if (ball->GetAnimState() != IDLE) // 아직 positioning 하는 중
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

void Swipe_BallManager::Render(const HDC& hdc)
{
	if (Swipe_GameManager::GetInst()->GetGameState() == GAMEOVER)
		return;

	for (Swipe_Ball* ball : fieldBalls)
		ball->Render(hdc);
}

void Swipe_BallManager::Init()
{
	UINT end = fieldBalls.size() + Swipe_GameManager::GetInst()->GetItemEarned();

	for (UINT i = fieldBalls.size(); i < end; i++)
	{
		if (i >= pool.size()) // poolCnt reached, can't get more balls...
			break;

		pool[i]->SetActive(true);
		pool[i]->GetBody()->Pos() = Swipe_GameManager::GetInst()->GetBallStartPos();

		fieldBalls.push_back(pool[i]);
	}

	for (Swipe_Ball* ball : fieldBalls)
		ball->SetFired(false);

	Swipe_GameManager::GetInst()->SetItemEarned(0);

	animState = POSITIONING;
}

bool Swipe_BallManager::IsRoundOver()
{
	for (Swipe_Ball* ball : fieldBalls)
	{
		if (!ball->IsFired())
			return false;

		if (ball->IsMovable())
			return false;
	}
	return true;
}


void Swipe_BallManager::Spawn(Point spawnPos)
{
	Init();
}

void Swipe_BallManager::Fire(Vector2 direction)
{
	for (Swipe_Ball* ball : fieldBalls)
	{
		if (ball->IsFired())
			continue;

		ball->Fire(direction);
		break;
	}
}

