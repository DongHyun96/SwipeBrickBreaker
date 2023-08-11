#pragma once
class Rect
{
public:
	Rect();
	Rect(Point pos, Point size);
	Rect(float left, float top, float right, float bottom);
	~Rect();

	void SetRect(float left, float top, float right, float bottom);

	void Render(const HDC& hdc);

	float Left()	const { return pos.x - size.x * 0.5f; }
	float Right()	const { return pos.x + size.x * 0.5f; }
	float Top()		const { return pos.y - size.y * 0.5f; }
	float Bottom()	const { return pos.y + size.y * 0.5f; }

	Point& Pos() { return pos; }
	Point& Size() { return size; }

	template<class Archive>
	void serialize(Archive& ar, const UINT version);

private:
	Point pos	= {};
	Point size	= {}; // width height
};

template<class Archive>
inline void Rect::serialize(Archive& ar, const UINT version)
{
	ar& pos;
	ar& size;
}
