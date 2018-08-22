#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate
{
    Coordinate(unsigned x, unsigned y;) : x(x), y(y) {};
    bool operator==(const Coordinate &a, const Coordinate &b){return a.x == b.x && a.y == b.y;};
    unsigned x;
    unsigned y;
}

inline unsigned dist(const Coordinate &a, const Coordinate &b)
{
    return abs((int)a.x - (int)b.x) + abs((int)a.y - (int)b.y);
}

#endif
