#include "Framework.h"
#include "Swipe_Ball.h"

bool Swipe_Ball::floorCollided = false;

Swipe_Ball::Swipe_Ball()
{
	pair<HPEN, HBRUSH> colorPair = Swipe_Palette::GetInst()->GetBallColorPair();
	pen		= colorPair.first;
	brush	= colorPair.second;

	body = new Circle(WIN_CENTER, 10.f);
}

Swipe_Ball::~Swipe_Ball()
{
	delete body;
}

void Swipe_Ball::Update()
{
	switch (animState)
	{
	case IDLE:
		break;
	case POSITIONING:
	{
		float xDst = Swipe_GameManager::GetInst()->GetBallStartPos().x;

		if (body->Pos().x < xDst * 0.99f)
			body->Pos().x = Lerp(body->Pos().x, xDst, Time::Delta() * positionLerpSpeed);
		else
		{
			body->Pos().x = xDst;
			fired = false;
			floorCollided = false;
			animState = IDLE;
		}
	}
		return;
	default:
		break;
	}

	if (!isMovable)
		return;
	
	Move();
	HandleCollisionWall();
}

void Swipe_Ball::Render(const HDC& hdc)
{
	auto pr = Swipe_GameManager::GetInst()->GetBallPosSet().insert(body->Pos());
	
	// 공이 엄청 많을 때의 frame drop 대비 처리, 만약 이미 해당 위치에 공이 존재한다면 그리지 않음
	if (!pr.second)
		return;

	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	body->Render(hdc);
}

void Swipe_Ball::Fire(Vector2 direction, float speed)
{
	this->direction = direction.GetNormal();
	this->speed = speed;
	
	isActive = true;
	isMovable = true;
	fired = true;
}

void Swipe_Ball::Move()
{
	body->Pos() += direction * speed * Time::Delta();
}

void Swipe_Ball::HandleCollisionWall()
{
	if (!isMovable)
		return;

	if (body->Left() < 0)
	{
		direction.x *= -1;
		body->Pos().x = body->Radius();
	}

	if (body->Right() > WIN_WIDTH)
	{
		direction.x *= -1;
		body->Pos().x = WIN_WIDTH - body->Radius();
	}

	if (body->Top() < SWIPE_CEIL)
	{
		direction.y *= -1;
		body->Pos().y = SWIPE_CEIL + body->Radius();
	}

	if (body->Bottom() > SWIPE_FLOOR)
	{
		isMovable = false;
		body->Pos().y = SWIPE_FLOOR - body->Radius() - 1.f; // 1픽셀 띄우고 시작해야 함

		// 처음 바닥면에 닿은 공인지 확인
		if (!floorCollided)
		{
			Swipe_GameManager::GetInst()->SetBallStartPos(body->Pos());
			floorCollided = true;
		}
	}
}
