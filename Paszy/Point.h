#pragma once

struct Vector_2d;

class Point
{
public:
	int x, y;
	Point();
	Point(Vector_2d v);
	Point(int _x, int _y);
};

Point operator-(const Point& v);
Point operator+(const Point& v1, const Point& v2);
Point operator-(const Point& v1, const Point& v2);
Point operator*(int d, const Point& v);
Point operator*(const Point& v, int d);
Point operator/(const Point& v, int d);
Point operator+=(Point& v1, const Point& v2);
Point operator-=(Point& v1, const Point& v2);
Point operator*=(Point& v, const int d);
Point operator/=(Point& v, const int d);
bool operator==(const Point& v1, const Point& v2);
bool operator!=(const Point& v1, const Point& v2);

//int distanceSqr(int x1, int y1, int x2 = 0.0, int y2 = 0.0);
//int distanceSqr(Point v1, Point v2 = Point(0.0, 0.0));
//int distance(int x1, int y1, int x2 = 0.0, int y2 = 0.0);
//int distance(Point v1, Point v2 = Point(0.0, 0.0));
//int lengthSqr(int x, int y);
//int lengthSqr(Point v);
//int length(Point v);
//int length(int x, int y);
//int dot(int x1, int y1, int x2, int y2);
//int dot(Point v1, Point v2);
//int cross(int x1, int y1, int x2, int y2);
//int cross(Point v1, Point v2);
