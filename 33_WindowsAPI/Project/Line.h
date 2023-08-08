#pragma once
class Line
{
public:
	Line();
	Line(Point start, Point end);
	~Line();

	void Render(const HDC& hdc);

	Point start;
	Point end;
	
	void SetStart(const Point& start) { this->start = start; }
	void SetEnd(const Point& end) { this->end = end; }
	const Point& GetStart() const { return start; }
	const Point& GetEnd() const { return end; }

private:
};
