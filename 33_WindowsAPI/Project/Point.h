#pragma once

struct Vector2;

struct Point
{
	//float a = 1 / 100.f;
	Point();
	Point(float x, float y);

	static float Distance(Point p1, Point p2);
	
	Point	operator+(const Vector2& other);
	Point	operator-(const Vector2& other);
					
	void	operator+=(const Vector2& other);
	void	operator-=(const Vector2& other);

	Vector2 operator-(const Point& other);
	
	// 내가 임의로 만든 operator overloadings

	bool operator<(const Point& other) const;
	bool operator<=(const Point& other) const;
	bool operator>(const Point& other) const;
	bool operator>=(const Point& other) const;

	//friend bool operator<(const Point& p1, const Point& p2);
	//friend bool operator<=(const Point& p1, const Point& p2);
	//friend bool operator>(const Point& p1, const Point& p2);
	//friend bool operator>=(const Point& p1, const Point& p2);
	//
	bool operator==(const Point& point);
	bool operator!=(const Point& point);

	friend bool operator==(const Point& p1, const Point& p2);
	friend bool operator!=(const Point& p1, const Point& p2);


	float x = 0.f;
	float y = 0.f;
};
