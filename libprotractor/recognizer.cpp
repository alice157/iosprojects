#include "recognizer.h"
using namespace std;
protractorPoint::protractorPoint(int a, int b) {
	x = a;
	y = b;
}
protractorPoint::protractorPoint() {
	x = 0;
	y = 0;
}
double distanceBetweenprotractorPoints(protractorPoint point1, protractorPoint point2) {
	double Distance = sqrt( pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2));	/* Distance formula */
	return Distance;
}

double pathLength(pointVector points) {
	double length = 0;
	for(int i = 1; i < (int)points.size(); i++) { /* i = 1 intentional (need to start at second point) */
		length = length + distanceBetweenprotractorPoints(points.at(i), points.at(i - 1));
	}
	return length;
}

pointVector resample(pointVector points) {
	double I = pathLength(points) / (NUM_POINTS - 1); /* Var names from the pseudocode, not my fault */
	double D = 0;
	double d;
	protractorPoint q;
	pointVector newprotractorPoints;
	newprotractorPoints.push_back(points.at(0));
	for(int i = 1; i < NUM_POINTS - 1; i++) {
		d = distanceBetweenprotractorPoints(points.at(i), points.at(i - 1)); /* once again, awful var names from pseudocode */
		if((D + d) >= I) {
			q.x = points.at(i - 1).x + ((I - D) / d) * (points.at(i).x - points.at(i - 1).x);
			q.y = points.at(i - 1).y + ((I - D) / d) * (points.at(i).y - points.at(i - 1).y);
			newprotractorPoints.push_back(q);
			points.insert(points.begin() + i + 1, q);
			D = 0;
		} else {
			D = std::abs(D) + d;
		}
	}
	printprotractorPoints(newprotractorPoints);
	return newprotractorPoints;
}

protractorPoint centroid(pointVector points) {
	protractorPoint newprotractorPoint;
	int averageX, averageY;
	averageX = averageY = 0;
	for(int i = 0; i < (int)points.size(); i++) {
		averageX += points.at(i).x;
		averageY += points.at(i).y;
	}
	averageX = round((double) averageX / points.size());
	averageY = round((double) averageY / points.size());
	newprotractorPoint.x = averageX;
	newprotractorPoint.y = averageY;
	return newprotractorPoint;
}

pointVector translateToOrigin(pointVector points) {
	protractorPoint c = centroid(points);
	pointVector newprotractorPoints;
	protractorPoint q;
	for(int i = 0; i < (int)points.size(); i++) {
		q.x = points.at(i).x - c.x;
		q.y = points.at(i).y - c.y;
		newprotractorPoints.push_back(q);
	}
	return newprotractorPoints;
}

vector<double> vectorize(pointVector points, bool oSensitive) {
	double indicativeAngle, baseOrientation, delta, magnitude;
	int sum = 0, newX, newY;
	vector<double> newVector;
	points = translateToOrigin(points);
	indicativeAngle = atan2(points.at(0).y, points.at(0).x);
	if(oSensitive) {
		baseOrientation = (PI / 4) * floor((indicativeAngle + (PI / 8)) / (PI / 4));
		delta = baseOrientation - indicativeAngle;
	} else {
		delta = -indicativeAngle;
	}
	for(int i = 0; i < (int)points.size(); i++) {
		newX = points.at(i).x * cos(delta) - points.at(i).y * sin(delta);
	 	newY = points.at(i).y * cos(delta) + points.at(i).x * sin(delta);
		newVector.push_back(newX);
		newVector.push_back(newY);
		printVector(newVector);
		sum = sum + newX * newX + newY * newY;
	}
	magnitude = sqrt(sum);
	for(int i = 0; i < (int)newVector.size(); i++) {
		newVector.at(i) = newVector.at(i) / magnitude;
	}
	printVector(newVector);
	return newVector;
}

double optimalCosineDistance(vector<double> vector1, vector<double> vector2) {
	double a, b, angle;
	a = 0;
	b = 0;
	for(int i = 0; i < (int)vector2.size(); i += 2) {
		a += vector1.at(i) * vector2.at(i) + vector1.at(i + 1) * vector2.at(i + 1);
		b += vector1.at(i) * vector2.at(i + 1) - vector1.at(i + 1) * vector2.at(i);
	}
	angle = atan(b / a);
	double odist = acos(a * cos(angle) + b * sin(angle));
	return odist;
}

double scoreTemplate(vector<double> gesture, vector<double> gestureTemplate) {
	double score = 1 / optimalCosineDistance(gestureTemplate, gesture);
	return score;
}

void printprotractorPoints(pointVector points) {
	for(int i = 1; i < (int)points.size(); i++) {
	}
}
void printVector(vector<double> vector1) {
	for(int i = 0; i < (int)vector1.size(); i++) {
	}
}
void printsomething(void) {
	printf("1\n");
}

int qmain(void) {
	pointVector points;
	pointVector points2;
	pointVector points3;

	points.push_back(protractorPoint(20, 40));
	points.push_back(protractorPoint(30, 50));
	points.push_back(protractorPoint(40, 60));
	points.push_back(protractorPoint(50, 70));

	points2.push_back(protractorPoint(21, 41));
	points2.push_back(protractorPoint(31, 51));
	points2.push_back(protractorPoint(41, 61));
	points2.push_back(protractorPoint(51, 71));

	points3.push_back(protractorPoint(82, -32));
	points3.push_back(protractorPoint(44, 87));
	points3.push_back(protractorPoint(12, 133));
	points3.push_back(protractorPoint(-3, 53));

	pointVector resampledprotractorPoints;
	pointVector resampledprotractorPoints2;
	pointVector resampledprotractorPoints3;

	resampledprotractorPoints = resample(points);
	resampledprotractorPoints2 = resample(points2);
	resampledprotractorPoints3 = resample(points3);

	printprotractorPoints(resampledprotractorPoints);
	vector<double> vectorizedprotractorPoints = vectorize(resampledprotractorPoints, true);
	vector<double> vectorizedprotractorPoints2 = vectorize(resampledprotractorPoints2, true);
	vector<double> vectorizedprotractorPoints3 = vectorize(resampledprotractorPoints3, true);
	printsomething();
	printVector(vectorizedprotractorPoints);
	return 1;
}
