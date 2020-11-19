#include <iostream>
#include <fstream>
#include <stack>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*
Convex hull :
        In geometry, the Convex Hull or convex envelope or convex closure of a shape is the smallest convex set that contains it.

Explanation :
        Actually the Convex Hull problem is how to draw a convex polygon with some given points such that the polygon wraps around all other given points.
    In computational geometry, we can solve it by divide and conquer approach or by Graham's Scan algorithm.
        Firstly, we have to choose a reference point p0 which should be the minimum point in term of x, y or any other dimension. Then we have to sort the
    points based on angle between p0pi and p0pi+1 where pi and pi+1 are two consecutive points from point array.
        Two make a convex polygon, we at least need 3 points who are not co-linear. So, we will check for co-linearity through the sorted points. If we gate
    at least three non co-linear points, we will proceed further.
        Now to get the polygon, we will initialize the process by pushing three points onto the stack. For each point pi, we will check the orientation for
    2 stack top elements and pi. We will repeat this process till we get a right(clockwise) orientation and keep popping elements from stack. Once we get the stack such that
    orientation is left(anti-clockwise) for 2 stack top elements and pi, we will push pi to the stack and pick up next element pi+1 from sorted points. Finally, we will print
    the stack.

Complexity :
        Time complexity of this algorithm is O(n * log n)

References :
        Wikipedia => https://en.wikipedia.org/wiki/Convex_hull#:~:text=In%20geometry%2C%20the%20convex%20hull,convex%20set%20that%20contains%20it.

Credit :
        Audity Ghosh
        CSE'17, RUET
*/

//Structure for points
struct Point
{
    int x, y;
};

Point p0;                           //Reference point identifier

//Function for getting element second from top of a stack
Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

//Function for swapping
int swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

//Squared distance between two points
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

//Check orientation for segments p0p1 and p0p2 where p0, p1 and p2 are three points
int orientation(Point p, Point q, Point r) {

    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) {             //If three points are co-linear
        return 0;
    }
    return (val > 0)? 1: 2;    //1 for anti-clockwise orientation and 2 for clockwise orientation
}

//Compare function for sorting the points
int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
    {
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;    //In case the points are co-linear
    }
    return (o == 2)? -1: 1;
}

void convexHull(Point points[], int numberOfPoints)
{
    //Setting minimum point as reference point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < numberOfPoints; i++) {

        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y, min = i;
        }
    }
    swap(points[0], points[min]);
    p0 = points[0];

    //Sorting the points
    qsort(&points[1], numberOfPoints-1, sizeof(Point), compare);

    //Check if here is at least 3 non co-linear points
    int m = 1;
    for (int i = 1; i < numberOfPoints; i++) {
        while (i < numberOfPoints - 1 && orientation(p0, points[i], points[i + 1]) == 0) {
            i++;
        }
        points[m] = points[i];
        m++;
    }
    if (m < 3)  {
        return;
    }

    //Stacking process for output
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);
    for (int i = 3; i < m; i++)
    {
        while (orientation(nextToTop(S), S.top(), points[i]) != 2)
        {
            S.pop();
        }
        S.push(points[i]);
    }

    cout << "Points for convex hull are :" << endl;
    while (!S.empty())
    {
        Point p = S.top();
        cout << "(" << p.x << "\t,\t" << p.y <<")" << endl;
        S.pop();
    }
}


//Driver function
int main()
{
    int a, n;
    ofstream filex,filey;
    Point points[7005];

    filex.open("inputX.txt");
    filey.open("inputY.txt");

    srand(time(0));
    for(int i = 1; i <= 7000; i++)
    {
        a = rand();
        filex << a << endl;
        points[i].x = a;
        a = rand();
        filey << a <<endl;
        points[i].y = a;
    }

    n = 7000;
    convexHull(points, n);

    return 0;
}

