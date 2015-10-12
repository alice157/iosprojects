#include <vector>
#include <stdio.h>
#include <cmath>

#ifndef RECOGNIZER_H
#define RECOGNIZER_H
#define NUM_POINTS 16
class Point {
	public:
		int x, y;
		Point();
		Point(int a, int b);
};
#define PI 3.14159265
typedef std::vector<Point> pointVector;
double pathLength(pointVector points);
double distance(Point p1, Point p2);
Point centroid(pointVector points);
pointVector resample(pointVector points);
pointVector translateToOrigin(pointVector points);
std::vector<double> vectorize(pointVector points, bool oSensitive);
double optimalCosineDistance(std::vector<double> vector1, std::vector<double> vector2);
double scoreTemplate(std::vector<double> gestureTemplate);
void printVector(std::vector<double> vector1);
void printPoints(pointVector points);
void printsomething(void);
int qmain(void);
#endif
