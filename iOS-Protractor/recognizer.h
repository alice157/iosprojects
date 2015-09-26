#include <vector>
#include <cmath>
#include "point.h"
#ifndef RECOGNIZER_H
#define RECOGNIZER_H
#define NUM_POINTS 16
#define PI 3.14159265
typedef std::vector<Point> pointVector;
double pathLength(pointVector points);
double distance(Point p1, Point p2);
Point centroid(pointVector points);
pointVector resample(pointVector points);
pointVector translateToOrigin(pointVector points);
std::vector<int> vectorize(pointVector points, bool oSensitive);
double optimalCosineDistance(std::vector<int> vector1, std::vector<int> vector2);
double scoreTemplate(std::vector<int> gestureTemplate);
#endif
