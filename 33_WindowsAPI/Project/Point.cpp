#include "Framework.h"
#include "Point.h"

Point::Point()
{
}

Point::Point(float x, float y)
	:x(x), y(y)
{
}

float Point::Distance(Point p1, Point p2)
{
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;

	float distance = sqrtf(x * x + y * y); // sqrtf floatÀ» ¹ÝÈ¯
	
	return distance;
}

Point Point::operator+(const Vector2& other)
{
	return Point(this->x + other.x, this->y + other.y);
}

Point Point::operator-(const Vector2& other)
{
	return Point(this->x - other.x, this->y - other.y);

}

void Point::operator+=(const Vector2& other)
{
	this->x += other.x;
	this->y += other.y;
}

void Point::operator-=(const Vector2& other)
{
	this->x -= other.x;
	this->y -= other.y;
}

Vector2 Point::operator-(const Point& other)
{
	return Vector2(this->x - other.x, this->y - other.y);
}

bool Point::operator<(const Point& other) const 
{
	return this->x < other.x;
}

bool Point::operator<=(const Point& other) const
{
	return this->x <= other.x;
}

bool Point::operator>(const Point& other) const
{
	return this->x > other.x;
}

bool Point::operator>=(const Point& other) const
{
	return this->x >= other.x;
}

bool Point::operator==(const Point& point)
{
	if (this->x == point.x && this->y == point.y)
		return true;
	return false;
}

bool Point::operator!=(const Point& point)
{
	return !operator==(point);
}

//bool operator<(const Point& p1, const Point& p2)
//{
//	return p1 < p2;
//}
//
//bool operator<=(const Point& p1, const Point& p2)
//{
//	return p1 <= p2;
//}
//
//bool operator>(const Point& p1, const Point& p2)
//{
//	return p1 > p2;
//}
//
//bool operator>=(const Point& p1, const Point& p2)
//{
//	return p1 >= p2;
//}

bool operator==(const Point& p1, const Point& p2)
{
	if (p1.x != p2.x) return false;
	if (p1.y != p2.y) return false;
	return true;
}

bool operator!=(const Point& p1, const Point& p2)
{
	return !operator==(p1, p2);
}


