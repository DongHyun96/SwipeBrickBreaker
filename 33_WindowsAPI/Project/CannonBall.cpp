#include "Framework.h"
#include "CannonBall.h"


CannonBall::CannonBall()
{
	body = new Circle({ 0, 0 }, 10);
}

CannonBall::CannonBall(Point startPos)
{
	body = new Circle(startPos, 10);
}

CannonBall::~CannonBall()
{
	delete body;
}

void CannonBall::Update()
{
	if (!isActive)
		return;

	if (body->Top() > WIN_HEIGHT)
		isActive = false;

	Move();
	CollisionWall();
}

void CannonBall::Render(HDC hdc)
{
	if (!isActive)
		return;

	body->Render(hdc);
}

void CannonBall::Move()
{
	// �������� �̵�
	//body->Pos().x += speed * cosf(angle);

	//body->Pos().y -= speed * sinf(angle) - gravity; // y�� �ۿ�Ǵ� �ӵ� - 

	body->Pos() += direction * speed; // ������ ��ġ�� DirectionVector * speed

	//body->Pos() += Vector2(0, 1) * gravity; // �Ʒ��������� �߷¸�ŭ �ۿ�

	//gravity += gravityAccel;
}

void CannonBall::Fire(Point startPos, float angle, float power)
{
	body->Pos() = startPos;
	this->angle = angle;
	this->speed = power * 0.1f;

	isActive = true;

	gravity = 0.f;
}

void CannonBall::Fire(Point startPos, Vector2 dir, float power)
{
	body->Pos() = startPos;
	direction	= dir;
	this->speed = power * 0.1f;

	isActive = true;

	gravity = 0.f;
}

void CannonBall::CollisionWall()
{
	if (body->Left() < 0) // ���� ���� �浹���� ��
	{
		direction.x *= -1;
		body->Pos().x = body->Radius();
	}

	if (body->Right() > WIN_WIDTH)
	{
		direction.x *= -1;
		body->Pos().x = WIN_WIDTH - body->Radius();
	}

	if (body->Top() < 0)
	{
		direction.y *= -1;
		body->Pos().y = body->Radius();
	}

	if (body->Bottom() > WIN_HEIGHT)
	{
		direction.y *= -1;
		body->Pos().y = WIN_HEIGHT - body->Radius();
	}
}
