#include <string>
#include <stdexcept>
#include "point.h"

class Segment
{
    public:
        Point start;
        Point end;

        Segment(Point startPoint, Point endPoint);
        float calculateCrossProduct(Segment other);
        std::string toString();
};