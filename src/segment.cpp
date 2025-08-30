#include "../include/segment.h"

Segment::Segment(Point startPoint, Point endPoint) : start(startPoint), end(endPoint) {}

float Segment::calculateCrossProduct(Segment other)
{

    if (!this->start.isEqual(other.start)) {
        throw std::invalid_argument("Parameter segment must have equal start Point as this segment.");
    }

    Point point1 = this->start;
    Point point2 = this->end;
    Point point3 = other.end;

    float crossProduct = ((point2.x - point1.x)*(point3.y - point1.y)) - ((point2.y - point1.y)*(point3.x - point1.x));

    return crossProduct;
}

std::string Segment::toString()
{
    std::string out = std::format("Segment: {} ---> {}", this->start.toString(), this->end.toString());
    return out;
}