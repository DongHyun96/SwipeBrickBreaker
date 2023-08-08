#include "Framework.h"
#include "Swipe_Item.h"


Swipe_Item::Swipe_Item()
{
	body = new Circle(WIN_CENTER, OUTER_RAD + 8.f); // 그리지 않고 충돌처리만 이용 -> 좀 더 후한 판정을 줘야 원할히 플레이 가능함

	middle = new Circle(WIN_CENTER, INNER_RAD); // Lerping 시킬 것임
	outer = new Circle(WIN_CENTER, 0); // Lerping 시킬 것임
	inner = new Circle(WIN_CENTER, 0);

	pair<HPEN, HBRUSH> colors = Swipe_Palette::GetInst()->GetItemColorPair();
	pair<HPEN, HBRUSH> whiteColors = Swipe_Palette::GetInst()->GetWhiteColorPair();

	pen = colors.first;
	brush = colors.second;

	whitePen = whiteColors.first;
	whiteBrush = whiteColors.second;
}

Swipe_Item::~Swipe_Item()
{
	delete body;
	delete inner;
	delete middle;
	delete outer;
}

void Swipe_Item::Update()
{
	if (!isActive)
		return;

	switch (animState)
	{
	case IDLE:
		break;
	case SPAWNING:

		if (inner->Radius() < INNER_RAD * 0.99f)
			inner->Radius() = Lerp(inner->Radius(), INNER_RAD, Time::Delta() * spawnLerpSpeed);
		else
			inner->Radius() = INNER_RAD;

		if (middle->Radius() < MID_RAD * 0.99f)
			middle->Radius() = Lerp(middle->Radius(), MID_RAD, Time::Delta() * spawnLerpSpeed);
		else
			middle->Radius() = MID_RAD;

		if (outer->Radius() < OUTER_RAD * 0.99f) // outer가 제일 lerp시간이 김 -> 여기서 animState 체크
			outer->Radius() = Lerp(outer->Radius(), OUTER_RAD, Time::Delta() * spawnLerpSpeed);
		else
		{
			outer->Radius() = OUTER_RAD;
			nextPosY = body->Pos().y + BRICK_SIZE_Y + SWIPE_MARGIN;
			animState = IDLE;
		}
		break;
	case POSITIONING:
		if (body->Pos().y < nextPosY * 0.99f)
		{
			float x = body->Pos().x;
			float y = Lerp(body->Pos().y, nextPosY, Time::Delta() * positionLerpSpeed);
			SetPosition(Point(x, y));

			// Check y limit
			if (body->Bottom() >= SWIPE_FLOOR)
			{
				isActive = false;
				Swipe_ParticleManager::GetInst()->Spawn(body->Pos(), PARTICLE_GREEN);
				animState = IDLE;
				break;
			}
		}
		else
		{
			SetPosition(Point(body->Pos().x, nextPosY));
			nextPosY = body->Pos().y + BRICK_SIZE_Y + SWIPE_MARGIN;

			animState = IDLE;
		}
		break;
	default:
		break;
	}
}

void Swipe_Item::Render(HDC hdc)
{
	if (!isActive)
		return;
	
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	outer->Render(hdc);

	SelectObject(hdc, whitePen);
	SelectObject(hdc, whiteBrush);

	middle->Render(hdc);

	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	inner->Render(hdc);

}

void Swipe_Item::Spawn(const Point& spawnPos)
{
	isActive = true;
	SetPosition(spawnPos);

	middle->Radius() = INNER_RAD;
	outer->Radius() = 0;
	inner->Radius() = 0;

	animState = SPAWNING;

}

void Swipe_Item::SetPosition(const Point& pos)
{
	body->Pos()		= pos;
	inner->Pos()	= pos;
	middle->Pos()	= pos;
	outer->Pos()	= pos;
}

