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
}
std::vector<Point> SlowConvexHull::getConvexHullClockwise()
{
    return std::vector<Point>();
}