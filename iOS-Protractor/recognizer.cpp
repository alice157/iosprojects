#include "recognizer.h"
using std::vector;
double distance(Point point1, Point point2) {
	double Distance = sqrt( pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2));	/* Distance formula */
	printf("Distance from (%d, %d) to (%d, %d) is %f\n", point1.x, point1.y, point2.x, point2.y, Distance);
	return Distance;
}

double pathLength(pointVector points) {
	double length = 0;
	for(int i = 1; i < points.size(); i++) { /* i = 1 intentional (need to start at second point) */
		length = length + distance(points.at(i), points.at(i - 1));
		printf("Length %f\n", length);
	}
	return length;
}

pointVector resample(pointVector points) {
	printf("Init constants\n");
	double I = pathLength(points) / (NUM_POINTS - 1); /* Var names from the pseudocode, not my fault */
	double D = 0;
	double d;
	Point q;
	pointVector newPoints;
	printf("Assigning newpoints to points");
	newPoints.push_back(points.at(0));
	printf("Newpoints[0].x = %d Newpoints[0].y = %d\n", newPoints.at(0).x, newPoints.at(0).y);
	for(int i = 1; i < NUM_POINTS + 1; i++) {
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
		newPoints.push_back(q);
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
		newVector.push_back(newX);
		newVector.push_back(newY);
		sum = sum + newX * newX + newY * newY;
	}
	magnitude = sqrt(sum);
	for(int i = 0; i < newVector.size(); i++) {
		newVector.at(i) = round(newVector.at(i) / magnitude);
	}
	return newVector;
}

double optimalCosineDistance(vector<int> vector1, vector<int> vector2) {
	double a, b, angle;
	a = 0;
	b = 0;
	for(int i = 0; i < vector1.size(); i += 2) {
		a += vector1.at(i) * vector2.at(i) + vector1.at(i + 1) * vector2.at(i + 1);
		b += vector1.at(i) * vector2.at(i + 1) - vector1.at(i + 1) * vector2.at(i);
	}
	printf("a: %f, b: %f\n", a, b);
	angle = atan(b / a);
	printf("angle: %f\n", angle);
	double odist = acos(a * cos(angle) + b * sin(angle));
	printf("Optimal Cosine Distance: %f\n", odist);
	return odist;
}

double scoreTemplate(vector<int> gesture, vector<int> gestureTemplate) {
	printf("Scoretemplate called\n");
	double score = 1 / optimalCosineDistance(gestureTemplate, gesture);
	return score;
}

void printPoints(pointVector points) {
	for(int i = 1; i < points.size(); i++ ) {
		printf("%d %d\n", points.at(i).x, points.at(i).y);
	}
}
int main(void) {
	pointVector points;
	points.push_back(Point(20, 40));
	points.push_back(Point(30, 50));
	points.push_back(Point(40, 60));
	points.push_back(Point(50, 70));
	pointVector resampledPoints;
	resampledPoints = resample(points);
	printPoints(resampledPoints);
	vector<int> vectorizedPoints = vectorize(resampledPoints, true);
	int template1[] = {32, 52, 28, 48, 32, 52, 28, 48, 32, 52, 28, 48, 32, 52, 28, 48, 32, 52, 28, 48, 32, 52, 28, 48, 32, 52, 28, 48, 32, 52, 28, 48};
	int template2[] = {31, 53, 29, 49, 31, 53, 29, 49, 31, 53, 29, 49, 31, 53, 29, 49, 31, 53, 29, 49, 31, 53, 29, 49, 31, 53, 29, 49, 31, 53, 29, 49};
  int template3[] = {11, -4, 53, 32, 32, 40, 11, 23, 51, 68, 12, 98, 41, 14, 67, 90, 20, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
	vector<int> template1v(template1, template1 + sizeof(template1) / sizeof(int));
	vector<int> template2v(template2, template2 + sizeof(template2) / sizeof(int));
	vector<int> template3v(template3, template3 + sizeof(template3) / sizeof(int));
	printf("Score for template 1 (exact match): %f\n", scoreTemplate(vectorizedPoints, template1v));
	printf("Score for template 2 (almost match): %f\n", scoreTemplate(vectorizedPoints, template2v));
	printf("Score for template 3 (no match): %f\n", scoreTemplate(vectorizedPoints, template3v));
}

