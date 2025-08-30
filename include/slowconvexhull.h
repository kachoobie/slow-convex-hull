#include <vector>
#include <string>
#include "point.h"
#include "segment.h"

#ifndef slowconvexhull
#define slowconvexhull

class SlowConvexHull
{
    public:
        std::vector<Segment> convexHull;
        std::vector<Point> pointSet;
        
        SlowConvexHull();
        void addPoint(float x, float y);
        void dump();
        void generateConvexHull();
        std::vector<Point> getConvexHullClockwise();
};

 #endif