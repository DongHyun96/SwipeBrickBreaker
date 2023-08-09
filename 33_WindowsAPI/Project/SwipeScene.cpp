#include "Framework.h"
#include "SwipeScene.h"


SwipeScene::SwipeScene()
{
	ceil = new Line(Point(0, SWIPE_CEIL), Point(WIN_WIDTH, SWIPE_CEIL));
	floor = new Line(Point(0, SWIPE_FLOOR), Point(WIN_WIDTH, SWIPE_FLOOR));

	background = new Rect(WIN_CENTER, Point(WIN_WIDTH, WIN_HEIGHT));

	ballManager = new Swipe_BallManager;

	brickManager = new Swipe_BrickManager;

	itemManager = new Swipe_ItemManager;

	font = Swipe_Palette::GetInst()->GetFont();
}

SwipeScene::~SwipeScene()
{
	delete ceil;
	delete floor;
	delete background;

	delete ballManager;

	delete brickManager;

	delete itemManager;
}

void SwipeScene::Update()
{
	Swipe_GameManager::GetInst()->Update();

	switch (Swipe_GameManager::GetInst()->GetGameState())
	{
	case INIT:
	{
		static bool initStarted = false;

		if (!initStarted)
		{
			Swipe_GameManager::GetInst()->AddLevel();

			Swipe_UIManager::GetInst()->SetLevel(Swipe_GameManager::GetInst()->GetLevel());
			
			ballManager->InitRound();

			InitBrickAndItem();

			Point ballStartPos = Swipe_GameManager::GetInst()->GetBallStartPos();

			Swipe_UIManager::GetInst()->SetPlayerDirStart(ballStartPos);
			Swipe_UIManager::GetInst()->SetBricks(brickManager->GetBricks());
			Swipe_UIManager::GetInst()->SetBallInfo(ballManager->GetBalls().size(), ballStartPos.x); // 볼 사이즈와 ballStartPos 한번에 넘김
			
			initStarted = true;
		}
		
		if (brickManager->GetAnimState() == IDLE && itemManager->GetAnimState() == IDLE && ballManager->GetAnimState() == IDLE)
		{

			// Check gameOver
			if (brickManager->IsGameOver())
			{
				Swipe_GameManager::GetInst()->SetGameState(GAMEOVER);
				initStarted = false;
				break;
			}

			Swipe_GameManager::GetInst()->SetGameState(PLAYING);

			Swipe_UIManager::GetInst()->SetIsDirPenActive(true);
			initStarted = false;
		}
	}
		break;
	case PLAYING:
		HandleFire();

		if (!ballManager->IsRoundOver())
			break;

		// 모든 ball이 바닥면에 다 닿았음

		Swipe_GameManager::GetInst()->SetGameState(INIT);

		break;
	case GAMEOVER:
	{
		static float timer = 0.f;
		static bool floorDestroyed = false;
		static bool brickDestroyed = false;

		timer += Time::Delta();

		if (!floorDestroyed)
		{
			for (float i = 0.25f; i < 1.f; i += 0.25f)
			{
				Swipe_ParticleManager::GetInst()->Spawn(Point(WIN_WIDTH * i, SWIPE_FLOOR), PARTICLE_BLACK);
				Swipe_ParticleManager::GetInst()->Spawn(Point(WIN_WIDTH * i, SWIPE_CEIL), PARTICLE_BLACK);
			}
			floorDestroyed = true;
		}

		if (timer >= 1.3f && !brickDestroyed)
		{
			timer -= 1.3f;
			brickManager->DestroyAllBricks();
			itemManager->DestroyAllItems();
			Swipe_UIManager::GetInst()->SetGameOverAnimFinished(true);

			UINT currentLv = Swipe_GameManager::GetInst()->GetLevel();
			UINT bestLv = Swipe_GameManager::GetInst()->GetBestLevelReached();

			if (currentLv > bestLv)
				Swipe_GameManager::GetInst()->SetBestLevelReached(currentLv);

			brickDestroyed = true;
		}

		if (brickDestroyed && timer >= 1.0f)
		{
			if (HandleRestartGame())
			{
				timer = 0.f;
				floorDestroyed = false;
				brickDestroyed = false;
			}

		}
	}
		break;
	default:
		break;
	}
	

	brickManager->Update();
	ballManager->Update();
	itemManager->Update();
	Swipe_ParticleManager::GetInst()->Update();
	Swipe_UIManager::GetInst()->Update();
	
	if (Swipe_GameManager::GetInst()->GetGameState() == PLAYING) // Playing 중일 때만 collision 검사
		HandleCollision();

}

void SwipeScene::Render(HDC hdc)
{
	HFONT oldFont = (HFONT)SelectObject(hdc, font);
	UINT prevAlign = SetTextAlign(hdc, TA_CENTER);
	int prevMode = SetBkMode(hdc, TRANSPARENT);

	RenderEnvironment(hdc);
	
	brickManager->Render(hdc);
	
	ballManager->Render(hdc);

	itemManager->Render(hdc);

	Swipe_UIManager::GetInst()->Render(hdc);

	Swipe_ParticleManager::GetInst()->Render(hdc);

	SelectObject(hdc, oldFont);
	SetTextAlign(hdc, prevAlign);
	SetBkMode(hdc, prevMode);

	DeleteObject(oldFont);

}

void SwipeScene::RenderEnvironment(HDC hdc)
{
	pair<HPEN, HBRUSH> bgColors = Swipe_Palette::GetInst()->GetBgColorPair();

	SelectObject(hdc, bgColors.first);
	SelectObject(hdc, bgColors.second);

	background->Render(hdc);

	if (Swipe_GameManager::GetInst()->GetGameState() == GAMEOVER)
		return;

	SelectObject(hdc, Swipe_Palette::GetInst()->GetFloorCeilPen());

	floor->Render(hdc);
	ceil->Render(hdc);
}

void SwipeScene::HandleFire()
{
	static bool fired = false;

	if (GetAsyncKeyState(VK_RBUTTON) && IsFireable() && GetForegroundWindow() == hWnd)
	{
		fireCnt = ballManager->GetFieldBalls().size();

		Point mouseP = (mousePos.y > FIRE_Y_LIMIT) ? Point(mousePos.x, FIRE_Y_LIMIT) : mousePos;

		fireDir = mouseP - Swipe_GameManager::GetInst()->GetBallStartPos();

		Swipe_UIManager::GetInst()->SetIsDirPenActive(false);
		fired = true;
	}

	if (fired)
	{
		fireTime += Time::Delta();

		if (fireTime >= fireTick)
		{
			fireTime -= fireTick;
			ballManager->Fire(fireDir);
			Swipe_UIManager::GetInst()->AddBallCnt(-1);
			
			if (--fireCnt <= 0)
				fired = false;
		}
	}
}

bool SwipeScene::IsFireable()
{
	for (Swipe_Ball* ball : ballManager->GetFieldBalls())
	{
		if (ball->IsMovable())
			return false;
	}
	return true;
}

void SwipeScene::InitBrickAndItem()
{
	UINT brickRandCnt = GetRandom(1, 5); // 1 ~ 5

	// 0 ~ 5 중 랜덤한 위치에 브릭을 뽑아야 함
	vector<UINT> picked = {};	// 브릭의 랜덤한 ids
	UINT itemIdx = 0;			// 아이템의 랜덤한 idx

	for (UINT i = 0; i < brickRandCnt; i++)
	{
		while (true)
		{
			UINT randomIdx = GetRandom(0, 5);

			auto it = find(picked.begin(), picked.end(), randomIdx);

			if (it == picked.end()) // 중복된 idx가 없을 때
			{
				picked.push_back(randomIdx);
				break;
			}
		}
	}

	while (true)
	{
		UINT randomIdx = GetRandom(0, 5);

		auto it = find(picked.begin(), picked.end(), randomIdx);

		if (it == picked.end())
		{
			itemIdx = randomIdx;
			break;
		}
	}

	for (UINT i : picked)
	{
		float xpos = SWIPE_MARGIN + BRICK_SIZE_X / 2 + (SWIPE_MARGIN + BRICK_SIZE_X) * i;
		float ypos = SWIPE_CEIL + SWIPE_MARGIN + BRICK_SIZE_Y / 2;

		brickManager->Spawn(Point(xpos, ypos));
	}

	float xpos = SWIPE_MARGIN + BRICK_SIZE_X / 2 + (SWIPE_MARGIN + BRICK_SIZE_X) * itemIdx;
	float ypos = SWIPE_CEIL + SWIPE_MARGIN + BRICK_SIZE_Y / 2;

	itemManager->Spawn(Point(xpos, ypos));

	if (Swipe_GameManager::GetInst()->GetLevel() == 1)
		return;

	// 브릭들 최대 HP에 따라 color 모두 업데이트
	for (Swipe_Brick* brick : brickManager->GetBricks())
	{
		if (!brick->IsActive())
			continue;

		vector<pair<HPEN, HBRUSH>> colorVec = Swipe_Palette::GetInst()->GetBrickColorVec();

		UINT targetIdx = MappingtoNewRange(	brick->GetHP(), 
											1, (int)Swipe_GameManager::GetInst()->GetLevel(),
											0, (int)(colorVec.size() - 1));

		brick->SetColor(colorVec[targetIdx]);
	}
	
}

void SwipeScene::HandleCollision()
{
	HandleCollision(ballManager->GetBalls(), brickManager->GetBricks());
	HandleCollision(ballManager->GetBalls(), itemManager->GetItems());
}

void SwipeScene::HandleCollision(vector<Swipe_Ball*>& balls, vector<Swipe_Brick*>& bricks)
{
	Point point;

	for (Swipe_Ball* ball : balls)
	{
		for (Swipe_Brick* brick : bricks)
		{
			if (!brick->IsActive())
				continue;

			if (Collision::Collision(brick->GetBody(), ball->GetBody(), &point))
			{

				Vector2 dir = ball->GetBody()->Pos() - brick->GetBody()->Pos();

				Point size = brick->GetBody()->Size();

				Vector2 LU = Vector2(-size.x, -size.y); // Left UP
				Vector2 RU = Vector2(+size.x, -size.y); // Right Up
				Vector2 LD = Vector2(-size.x, +size.y);
				Vector2 RD = Vector2(+size.x, +size.y);

				if (Vector2::IsBetween(dir, LU, LD) && ball->GetBody()->Pos().x < brick->GetBody()->Pos().x)
				{
					// Left
					ball->Dir().x *= -1;
					ball->GetBody()->Pos().x = brick->GetBody()->Left() - ball->GetBody()->Radius();
				}
				else if (Vector2::IsBetween(dir, RU, RD) && ball->GetBody()->Pos().x > brick->GetBody()->Pos().x)
				{
					// Right
					ball->Dir().x *= -1;
					ball->GetBody()->Pos().x = brick->GetBody()->Right() + ball->GetBody()->Radius();
				}
				else if (Vector2::IsBetween(dir, LU, RU) && ball->GetBody()->Pos().y < brick->GetBody()->Pos().y)
				{
					// Up
					ball->Dir().y *= -1;
					ball->GetBody()->Pos().y = brick->GetBody()->Top() - ball->GetBody()->Radius();
				}
				else if (Vector2::IsBetween(dir, LD, RD) && ball->GetBody()->Pos().y > brick->GetBody()->Pos().y)
				{
					// Down
					ball->Dir().y *= -1;
					ball->GetBody()->Pos().y = brick->GetBody()->Bottom() + ball->GetBody()->Radius();
				}

				brick->ApplyDamage();
			}
		}
	}
}

void SwipeScene::HandleCollision(const vector<Swipe_Ball*>& balls, vector<Swipe_Item*>& items)
{
	for (Swipe_Ball* ball : balls)
	{
		for (Swipe_Item* item : items)
		{
			if (!item->IsActive())
				continue;

			if (Collision::Collision(ball->GetBody(), item->GetBody()))
			{
				item->SetActive(false);
				Swipe_GameManager::GetInst()->AddItemEarned();
				Swipe_ParticleManager::GetInst()->Spawn(item->GetBody()->Pos(), PARTICLE_GREEN);
			}
		}
	}
}

bool SwipeScene::HandleRestartGame()
{
	if (GetAsyncKeyState('R'))
	{
		Swipe_GameManager::GetInst()->InitGame();
		Swipe_UIManager::GetInst()->InitUI();
		ballManager->InitGameStart();

		return true;
	}

	return false;
}
