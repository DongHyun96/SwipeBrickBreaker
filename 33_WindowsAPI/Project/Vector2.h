#pragma once

struct Vector2
{
	Vector2();
	Vector2(float x, float y);

	float Length();

	Vector2 GetNormal();

	void Normalize(); // ���� ��ü�� ����ȭ

	static float Dot(const Vector2& v1, const Vector2 v2);

	// ������ ��ȯ�� Vector but 2�������� ���� ������ z���� ��ȣ�� �ǹ� �ֱ� ������ �׳� float ���� return
	static float Cross(const Vector2& v1, const Vector2 v2);

	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	
	Vector2 operator*(const float& value);
	Vector2 operator/(const float& value);
	
	void operator+=(const Vector2& other);
	void operator-=(const Vector2& other);

	void operator*=(const float& value);
	void operator/=(const float& value);

	/// <summary> factor�� v1�� v2 ���̿� �ֳ� </summary>
	static bool IsBetween(const Vector2& factor, const Vector2& v1, const Vector2 v2);

	float x = 0.f;
	float y = 0.f;
};