#pragma once

struct Vector2
{
	Vector2();
	Vector2(float x, float y);

	float Length();

	Vector2 GetNormal();

	void Normalize(); // 원본 자체를 정규화

	static float Dot(const Vector2& v1, const Vector2 v2);

	// 외적의 반환은 Vector but 2차원에서 쓰기 때문에 z값의 부호만 의미 있기 때문에 그냥 float 으로 return
	static float Cross(const Vector2& v1, const Vector2 v2);

	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	
	Vector2 operator*(const float& value);
	Vector2 operator/(const float& value);
	
	void operator+=(const Vector2& other);
	void operator-=(const Vector2& other);

	void operator*=(const float& value);
	void operator/=(const float& value);

	/// <summary> factor가 v1과 v2 사이에 있나 </summary>
	static bool IsBetween(const Vector2& factor, const Vector2& v1, const Vector2 v2);

	float x = 0.f;
	float y = 0.f;
};