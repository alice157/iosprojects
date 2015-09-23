#include "point.h"
#include <vector>
#include <cmath>
#ifndef RECOGNIZER_H
#define RECOGNIZER_H
#define NUM_POINTS 16
double pathLength(vector<point> points);
double distance(point p1, point p2);
vector<point> resample(vector<point> points);
#endif