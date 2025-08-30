#include "../include/slowconvexhull.h"

SlowConvexHull::SlowConvexHull(){};

void SlowConvexHull::addPoint(float x, float y)
{
    Point newPoint(x, y);
    pointSet.push_back(newPoint);
}

void SlowConvexHull::dump()
{
    pointSet.clear();
    convexHull.clear();
}

void SlowConvexHull::orderConvexHullClockwise()
{
    Segment added = this->convexHull.at(0);
    std::vector<Segment> clockwiseConvexHull;
    clockwiseConvexHull.push_back(added);
    while (clockwiseConvexHull.size() < this->convexHull.size()) {
        for (int i = 0; i < this->convexHull.size(); ++i) {
            Segment current = this->convexHull.at(i);
            if (current.start.isEqual(added.end)) {
                added = current;
                clockwiseConvexHull.push_back(added);
                break;
            }
        }
    }
    this->convexHull = clockwiseConvexHull;
}

void SlowConvexHull::generateConvexHull()
{
    if (this->convexHull.size() > 0) {
        this->convexHull.clear();
    }
    float epsilon = 0.000000001;
    for (int i = 0; i < this->pointSet.size(); ++i) {
        for (int j = 0; j < this->pointSet.size(); ++j) {
            Point point1 = this->pointSet.at(i);            // Vector 1:  point1 -------------> point2
            Point point2 = this->pointSet.at(j);

            if (point1.isEqual(point2)) {
                continue;
            }

            Segment segment12(point1, point2);

            bool allPointsRight = true;
            for (int k = 0; k < this->pointSet.size(); ++k) {
                Point point3 = this->pointSet.at(k);

                if (!(point3.isEqual(point1) || point3.isEqual(point2))) {  // Vector 2: point1 -------------> point3
                    Segment segment13(point1, point3);
                    float crossProduct = segment12.calculateCrossProduct(segment13);
                    
                    if (crossProduct > epsilon) {   // Point is to the left
                        allPointsRight = false;
                        break;
                    }
                }
            }

            if (allPointsRight) {
                this->convexHull.push_back(segment12);
            }
        }
    }
    this->orderConvexHullClockwise();
}

std::vector<Point> SlowConvexHull::getConvexHullClockwise()
{
    std::vector<Point> convexHullPoints;
    std::vector<Segment>::iterator it;
    for (it = this->convexHull.begin(); it < this->convexHull.end(); ++it) {
        Segment current = *it;
        convexHullPoints.push_back(current.start);
    }
    return convexHullPoints;
}