#include <vector>
#include <stdio.h>
#include <cmath>

#ifndef RECOGNIZER_H
#define RECOGNIZER_H
#define NUM_POINTS 16
class protractorPoint {
	public:
		int x, y;
		protractorPoint();
		protractorPoint(int a, int b);
};
#define PI 3.14159265
typedef std::vector<protractorPoint> pointVector;
double pathLength(pointVector points);
double distance(protractorPoint p1, protractorPoint p2);
protractorPoint centroid(pointVector points);
pointVector resample(pointVector points);
pointVector translateToOrigin(pointVector points);
std::vector<double> vectorize(pointVector points, bool oSensitive);
double optimalCosineDistance(std::vector<double> vector1, std::vector<double> vector2);
double scoreTemplate(std::vector<double> gestureTemplate);
void printVector(std::vector<double> vector1);
void printprotractorPoints(pointVector points);
void printsomething(void);
int qmain(void);
#endif
