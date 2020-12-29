#include <iostream>

using namespace std;

struct Point
{
    int x;
    int y;
};

// find orientation of ordered triplet(p, q, r)
// return 0: p, q and r are collinear
// return 1: clockwise
// return 2: counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0; // collinear

    return (val > 0) ? 1 : 2; // clockwise or counterclockwise
}

// given three collinear points p, q, r, the function checks
// if point q lies on line segment 'pr'
bool check_on_segment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
    {
        return true;
    }

    return false;
}

// return true if line segment 'p1-q1'
// and 'p2-q2' intersect
bool check_intersect(Point p1, Point q1, Point p2, Point q2)
{
    // find the four orientations needed for
    // general and special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // general case
    if (o1 != o2 && o3 != o4) return true;

    // special cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && check_on_segment(p1, p2, q1)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && check_on_segment(p1, q2, q1)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && check_on_segment(p2, p1, q2)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && check_on_segment(p2, p1, q2)) return true;

    return false;
}

int main() {
    struct Point p1 = {1, 1}, q1 = {10, 1};
    struct Point p2 = {1, 2}, q2 = {10, 2};

    check_intersect(p1, q1, p2, q2) ? cout << "Yes\n" : cout << "No\n";

    p1 = {10, 0}, q1 = {0, 10};
    p2 = {0, 0}, q2 = {10, 10};
    check_intersect(p1, q1, p2, q2) ? cout << "Yes\n" : cout << "No\n";

    p1 = {-5, -5}, q1 = {0, 0};
    p2 = {1, 1}, q2 = {10, 10};
    check_intersect(p1, q1, p2, q2) ? cout << "Yes\n" : cout << "No\n";

    return 0;
}
