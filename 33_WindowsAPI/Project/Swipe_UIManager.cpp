#include "Framework.h"
#include "Swipe_UIManager.h"


Swipe_UIManager::Swipe_UIManager()
{
	dirLine = new Line(Swipe_GameManager::GetInst()->GetBallStartPos(), mousePos);
	sampleBall = new Circle(WIN_CENTER, 10.f);
}

Swipe_UIManager::~Swipe_UIManager()
{
	delete dirLine;
	delete sampleBall;
}

void Swipe_UIManager::Update()
{
	if (isDirPenActive)
	{
		Point endPos = mousePos;
		Vector2 dir = endPos - dirLine->GetStart();

		dir.Normalize();

		while (true)
		{
			if (endPos.y <= SWIPE_CEIL || endPos.x <= 0 || endPos.x >= WIN_WIDTH)
			{
				if (endPos.y <= SWIPE_CEIL)
					endPos.y = SWIPE_CEIL;

				break;
			}

			endPos += dir;
		}
		
		if (endPos.y > FIRE_Y_LIMIT)
			endPos.y = FIRE_Y_LIMIT;
		
		// 공의 위치 조정
		sampleBall->Pos() = dirLine->GetStart();

		while (!HandleSampleBallCollision())
			sampleBall->Pos() += dir;

		if (sampleBall->Pos().y > FIRE_Y_LIMIT)
			sampleBall->Pos().y = FIRE_Y_LIMIT;

		dirLine->SetEnd(endPos);
	}
}

void Swipe_UIManager::Render(HDC hdc)
{
	wstring lv = L"Level   " + to_wstring(level);
	TextOut(hdc, LEVEL_POS.x, LEVEL_POS.y, lv.c_str(), lv.size());

	if (Swipe_GameManager::GetInst()->GetGameState() == GAMEOVER)
	{
		RenderGameOver(hdc);
		return;
	}

	COLORREF prevBlack = SetTextColor(hdc, BALL_CNT_COLOR);

	wstring ballCntText = L"X" + to_wstring(ballCnt);
	TextOut(hdc, ballCntPos.x, ballCntPos.y, ballCntText.c_str(), ballCntText.size());

	SetTextColor(hdc, prevBlack);

	RenderPlayerDir(hdc);
}

void Swipe_UIManager::RenderPlayerDir(HDC hdc)
{
	if (!isDirPenActive)
		return;

	SelectObject(hdc, dirPen);
	dirLine->Render(hdc);

	SelectObject(hdc, sampleBallColors.first);
	SelectObject(hdc, sampleBallColors.second);

	sampleBall->Render(hdc);
}

void Swipe_UIManager::SetBallInfo(const UINT& cnt, const float& xPos)
{
	ballCnt = cnt;
	ballCntPos.x = xPos;
}

void Swipe_UIManager::InitUI()
{
	isGameOverAnimFin = false;
}

bool Swipe_UIManager::HandleSampleBallCollision()
{
	if (HandleCollisionBricks())
		return true;

	if (HandleCollisionWall())
		return true;

	return false;
}

bool Swipe_UIManager::HandleCollisionBricks()
{
	Point point;

	for (Swipe_Brick* brick : bricks)
	{
		if (!brick->IsActive())
			continue;

		if (Collision::Collision(brick->GetBody(), sampleBall, &point))
		{

			Vector2 dir = sampleBall->Pos() - brick->GetBody()->Pos();

			Point size = brick->GetBody()->Size();

			Vector2 LU = Vector2(-size.x, -size.y); // Left UP
			Vector2 RU = Vector2(+size.x, -size.y); // Right Up
			Vector2 LD = Vector2(-size.x, +size.y);
			Vector2 RD = Vector2(+size.x, +size.y);

			if (Vector2::IsBetween(dir, LU, LD) && sampleBall->Pos().x < brick->GetBody()->Pos().x)
			{
				// Left
				sampleBall->Pos().x = brick->GetBody()->Left() - sampleBall->Radius();
				return true;
			}
			else if (Vector2::IsBetween(dir, RU, RD) && sampleBall->Pos().x > brick->GetBody()->Pos().x)
			{
				// Right
				sampleBall->Pos().x = brick->GetBody()->Right() + sampleBall->Radius();
				return true;

			}
			else if (Vector2::IsBetween(dir, LU, RU) && sampleBall->Pos().y < brick->GetBody()->Pos().y)
			{
				// Up
				sampleBall->Pos().y = brick->GetBody()->Top() - sampleBall->Radius();
				return true;

			}
			else if (Vector2::IsBetween(dir, LD, RD) && sampleBall->Pos().y > brick->GetBody()->Pos().y)
			{
				// Down
				sampleBall->Pos().y = brick->GetBody()->Bottom() + sampleBall->Radius();
				return true;

			}
		}
	}
	return false;
}

bool Swipe_UIManager::HandleCollisionWall()
{
	if (sampleBall->Left() < 0)
	{
		sampleBall->Pos().x = sampleBall->Radius();
		return true;
	}
	else if (sampleBall->Right() > WIN_WIDTH)
	{
		sampleBall->Pos().x = WIN_WIDTH - sampleBall->Radius();
		return true;
	}
	else if (sampleBall->Top() < SWIPE_CEIL)
	{
		sampleBall->Pos().y = SWIPE_CEIL + sampleBall->Radius();
		return true;
	}

	return false;
}

void Swipe_UIManager::RenderGameOver(HDC hdc)
{
	if (isGameOverAnimFin)
	{
		wstring gameOverPhrase = L"GAME OVER!";
		TextOut(hdc, WIN_CENTER.x, WIN_CENTER.y * 0.8f, gameOverPhrase.c_str(), gameOverPhrase.size());

		COLORREF prevColor = SetTextColor(hdc, RGB(197, 22, 5));
		
		wstring bestLevelStr = L"BEST LV : " + to_wstring(Swipe_GameManager::GetInst()->GetBestLevelReached());
		TextOut(hdc, WIN_CENTER.x, WIN_CENTER.y, bestLevelStr.c_str(), bestLevelStr.size());

		SetTextColor(hdc, prevColor);

		wstring restartPhrase = L"PRESS R TO RESTART";
		TextOut(hdc, WIN_CENTER.x, WIN_CENTER.y * 1.2f, restartPhrase.c_str(), restartPhrase.size());

	}
}
