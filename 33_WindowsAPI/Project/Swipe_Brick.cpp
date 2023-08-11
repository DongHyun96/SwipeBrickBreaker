#include "Framework.h"
#include "Swipe_Brick.h"

Swipe_Brick::Swipe_Brick()
{
}

Swipe_Brick::Swipe_Brick(Point pos)
{
	body = new Rect(pos, BRICK_SIZE);

	pair<HPEN, HBRUSH> colors = Swipe_Palette::GetInst()->GetBrickColorPair();

	pen = colors.first;
	brush = colors.second;
}

Swipe_Brick::~Swipe_Brick()
{
	delete body;
}

void Swipe_Brick::Update()
{
	if (!isActive)
		return;

	switch (animState)
	{
	case IDLE:
		break;
	case SPAWNING:
	{
		// Lerp x scale
		if (body->Size().x < BRICK_SIZE_X * 0.99f)
			body->Size().x = Lerp(body->Size().x, BRICK_SIZE_X, Time::Delta() * spawnLerpSpeed);

		// Lerp y scale
		if (body->Size().y < BRICK_SIZE_Y * 0.99f)
			body->Size().y = Lerp(body->Size().y, BRICK_SIZE_Y, Time::Delta() * spawnLerpSpeed);

		if (body->Size().x >= BRICK_SIZE_X * 0.99f && body->Size().y >= BRICK_SIZE_Y * 0.99f)
		{
			body->Size() = BRICK_SIZE;
			nextPosY = body->Pos().y + BRICK_SIZE_Y + SWIPE_MARGIN;
			animState = IDLE;
		}
	}
		break;
	case POSITIONING: // Lerp to below
	{
		if (body->Pos().y < nextPosY * 0.99f)
			body->Pos().y = Lerp(body->Pos().y, nextPosY, Time::Delta() * positionLerpSpeed);
		else
		{
			body->Pos().y = nextPosY;
			nextPosY = body->Pos().y + BRICK_SIZE_Y + SWIPE_MARGIN;
			animState = IDLE;
		}
	}
		break;
	default:
		break;
	}
}

void Swipe_Brick::Render(HDC hdc)
{
	if (!isActive)
		return;

	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	body->Render(hdc);

	if (animState != SPAWNING)
		TextOut(hdc, body->Pos().x, body->Pos().y - 15, to_wstring(hp).c_str(), to_wstring(hp).size());
}

void Swipe_Brick::Spawn(Point spawnPos)
{
	isActive = true;

	body->Pos() = spawnPos;
	body->Size() = { 0, 0 };

	hp = Swipe_GameManager::GetInst()->GetLevel();

	animState = SPAWNING;

}

void Swipe_Brick::ApplyDamage()
{
	if (--hp <= 0)
	{
		isActive = false;
		Swipe_ParticleManager::GetInst()->Spawn(body->Pos(), PARTICLE_RED);
	}
	else
	{
		// Color 업데이트
		vector<pair<HPEN, HBRUSH>> colorVec = Swipe_Palette::GetInst()->GetBrickColorVec();

		UINT targetIdx = MappingtoNewRange((int)hp,
			1, (int)Swipe_GameManager::GetInst()->GetLevel(),
			0, (int)(colorVec.size() - 1));

		SetColor(colorVec[targetIdx]);
	}
}

void Swipe_Brick::SetColor(const pair<HPEN, HBRUSH>& colors)
{
	pen		= colors.first;
	brush	= colors.second;
}

