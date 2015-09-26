#include "recognizer.h"
using std::vector;
double distance(Point point1, Point point2) {
	return sqrt(pow((point1.x - point2.x), 2) + pow((point1.y - point2.y), 2)); /* Distance formula */
}

double pathLength(pointVector points) {
	double length = 0;
	for(int i = 1; i < (points.size() + 1); i++) { /* i = 1 intentional (need to start at second point) */
		length += distance(points.at(i), points.at(i - 1));
	}
	return length;
}

pointVector resample(pointVector points) {
	double I = pathLength(points) / (NUM_POINTS - 1); /* Var names from the pseudocode, not my fault */
	double D = 0;
	double d;
	Point q;
	pointVector newPoints;
	newPoints.at(0) = points.at(0);
	for(int i = 1; i < points.size(); i++) {
		d = distance(points.at(i), points.at(i - 1)); /* once again, awful var names from pseudocode */
		if((D + d) >= I) {
			q.x = points.at(i).x + ((I - D) / d) * (points.at(i).x - points.at(i - 1).x);
			q.y = points.at(i).y + ((I - D) / d) * (points.at(i).y - points.at(i - 1).y);
			newPoints.push_back(q);
			points.insert(points.begin() + i, q);
			D = 0;
		} else {
			D = D + d;
		}
	}
	return newPoints;
}

Point centroid(pointVector points) {
	Point newPoint;
	int averageX, averageY;
	averageX = averageY = 0;
	for(int i = 0; i < points.size(); i++) {
		averageX += points.at(i).x;
		averageY += points.at(i).y;
	}
	averageX = round((double) averageX / points.size());
	averageY = round((double) averageY / points.size());
	newPoint.x = averageX;
	newPoint.y = averageY;
}

pointVector translateToOrigin(pointVector points) {
	Point c = centroid(points);
	pointVector newPoints;
	Point q;
	for(int i = 0; i < points.size(); i++) {
		q.x = points.at(i).x - c.x;
		q.y = points.at(i).y - c.y;
		newPoints.push_back(points.begin() + i, q);
	}
	return newPoints;
}

vector<int> vectorize(pointVector points, bool oSensitive) {
	double indicativeAngle, baseOrientation, delta, magnitude;
	int sum = 0, newX, newY;
	vector<int> newVector;
	points = translateToOrigin(points);
	indicativeAngle = atan2(points.at(0).y, points.at(0).x);
	if(oSensitive) {
		baseOrientation = (PI / 4) * floor((indicativeAngle + (PI / 8)) / (PI / 4));
		delta = baseOrientation - indicativeAngle;
	} else {
		delta = -indicativeAngle;
	}
	for(int i = 0; i < points.size(); i++) {
		newX = points.at(0).x * cos(delta) - points.at(0).y * sin(delta);
	 	newY = points.at(0).y * cos(delta) + points.at(0).x * sin(delta);
		newVector.push_back(newVector.begin() + i, newX);
		newVector.push_back(newVector.begin() + i + 1, newY);
		sum = sum + newX * newX + newY * newY;
	}
	magnitude = sqrt(sum);
	for(i = 0; i < newVector.size(); i++) {
		newVector.at(i) = round(newVector.at(i) / magnitude);
	}
	return newVector;
}

double optimalCosineDistance(vector<int> vector1, vector<int> vector2) {
	double a, b, angle;
	a = b = 0;
	for(int i = 1; i < vector1.size(); i += 2) {
		a += vector1.at(i) * vector2.at(i) + vector1.at(i + 1) * vector2.at(i + 1);
		b += vector1.at(i) * vector2.at(i + 1) - vector1.at(i + 1) * vector2.at(i);
	}
	angle = atan(b / a);
	return acos(a * cos(angle) + b * sin(angle));
}

double scoreTemplate(vector<int> gesture, vector<int> gestureTemplate) {
	double score = 1 / optimalCosineDistance(gestureTemplate, gesture);
	return score;
}
