#include "Point.h"

#include "Vector.h"

Point::Point() : x(), y() {}
Point::Point(Vector_2d v) : x(v.x), y(v.y) {}
Point::Point(int _x, int _y) : x(_x), y(_y) {}

Point operator-(const Point& v)
{
	return Point{ -v.x, -v.y };
}
Point operator+(const Point& v1, const Point& v2)
{
	return Point{ v1.x + v2.x, v1.y + v2.y };
}
Point operator-(const Point& v1, const Point& v2)
{
	return Point{ v1.x - v2.x, v1.y - v2.y };
}
Point operator*(int d, const Point& v)
{
	return Point{ v.x * d, v.y * d };
}
Point operator*(const Point& v, int d)
{
	return d * v;
}
Point operator/(const Point& v, int d)
{
	return Point{ v.x / d, v.y / d };
}
Point operator+=(Point& v1, const Point& v2)
{
	v1 = v1 + v2;
	return v1;
}
Point operator-=(Point& v1, const Point& v2)
{
	v1 = v1 - v2;
	return v1;
}
Point operator*=(Point& v, const int d)
{
	v = v * d;
	return v;
}
Point operator/=(Point& v, const int d)
{
	v = v / d;
	return v;
}

bool operator==(const Point& v1, const Point& v2)
{
	return (v1.x == v2.x) && (v1.y == v2.y);
}

bool operator!=(const Point& v1, const Point& v2)
{
	return !(v1 == v2);
}

//
//int distanceSqr(int x1, int y1, int x2, int y2)
//{
//	return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
//}
//int distanceSqr(Point v1, Point v2)
//{
//	return distanceSqr(v1.x, v1.y, v2.x, v2.y);
//}
//int distance(int x1, int y1, int x2, int y2)
//{
//	return std::sqrt(distanceSqr(x1, y1, x2, y2));
//}
//int distance(Point v1, Point v2)
//{
//	return std::sqrt(distanceSqr(v1, v2));
//}
//int lengthSqr(int x, int y)
//{
//	return distanceSqr(x, y);
//}
//int lengthSqr(Point v)
//{
//	return distanceSqr(v);
//}
//int length(Point v)
//{
//	return std::sqrt(lengthSqr(v));
//}
//int length(int x, int y)
//{
//	return std::sqrt(lengthSqr(x, y));
//}
//int dot(int x1, int y1, int x2, int y2)
//{
//	return x1 * x2 + y1 * y2;
//}
//int dot(Point v1, Point v2)
//{
//	return dot(v1.x, v1.y, v2.x, v2.y);
//}
//int cross(int x1, int y1, int x2, int y2)
//{
//	return x1 * y2 - x2 * y1;
//}
//int cross(Point v1, Point v2)
//{
//	return cross(v1.x, v1.y, v2.x, v2.y);
//}
