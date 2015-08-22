#include <bits/stdc++.h>
using namespace std;

#define linf                        (long long)1e18
#define inf                         (int)1e9
#define forall(i,a,b)               for(int i=a;i<b;i++)

// Useful container manipulation / traversal macros
#define forbac(i,a,b)               for(int i=a;i>=b;i--)
#define foreach(v, c)               for(typeof( (c).begin()) v = (c).begin();  v != (c).end(); ++v)
#define all(a)                      a.begin(), a.end()
#define in(a,b)                     ((b).find(a) != (b).end())
#define pb                          push_back
#define fill(a,v)                   memset(a, v, sizeof (a))
#define sz(a)                       ((int)(a.size()))
#define mp                          make_pair
#define ll long long

ll maxe(ll a,ll b)                  {if(a>b)return a;else return b;}
ll mine(ll a,ll b)                  {if(a<b)return a;else return b;}
ll abse(ll a)                       {if(a>0)return a;return   (-a);}

// comparision Guys 
#define DREP_sort(a)                 sort(all(a)); a.erase(unique(all(a)),a.end()) //deletes repeat sorted
#define DREP(a)                      a.erase(unique(all(a)),a.end()) //deletes repeat

// The bit standard guys
#define bit(x,i)                    (x&(1<<i))  //select the bit of position i of x
#define lowbit(x)                   ((x)&((x)^((x)-1))) //get the lowest bit of x
#define highbit(x)                  (1 << (int) log2(x) ) // the highest bit becareful
#define bitcount(x)                 __builtin_popcount(x)  // counts 1 eg- 1101 has value 3
#define zerotrail(x)                __builtin_ctz(x)  // returns number of trailing 0-bits of x 
// with bitcount be careful with data types

// The vectors and pairs
typedef vector<int>   vi;
typedef vector<vi>   vvi;
typedef pair<int,int> pi;
typedef map<int,int>hash;
#define ft                 first
#define sd                 second


// the data types
#define st string
#define ch char

/*
  This is the graham scan for the convex hull. 
  Step 1 Find the least point in plane in terms of y and then x in case of equality use 
 USE-the bool operator less than comparator that is use to compare the current element with
   element B
   
  Step 2 That above point is a pivot so sort all the angles wrt that point 
  you don't have to acutally find the angles you just compare which one of the angles is
  greater than the other one so we can compare between a and b to find which
  makes a greater tan with pivot 
 USE  Polar order  and conterclockwise checker 
 
  Step 3  REmove unnecessary vertices and make the hull


*/

class Point    {
public:
    int x, y;
    bool operator < (Point b) 
        {if (y != b.y)return y < b.y; else return x < b.x;}
};
Point pivot;

// returns -1 if a -> b -> c forms a counter-clockwise turn,
// +1 for a clockwise turn, 0 if they are collinear
// The comparision is simple compares point a with b and c angles 
// if angle by b,a is less than ca then you have counterclockwise
int ccw(Point a, Point b, Point c) {
    int area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area > 0)return -1;
    else if (area < 0)return 1;
    return 0;
}

// returns square of Euclidean distance between two points
int sqrDist(Point a, Point b)  {
    int dx = a.x - b.x, dy = a.y - b.y;return dx * dx + dy * dy;
}

// used for sorting points according to polar order w.r.t the pivot
bool POLAR_ORDER(Point a, Point b)  {
    int order = ccw(pivot, a, b);
    if (order == 0)return sqrDist(pivot, a) < sqrDist(pivot, b);
    return (order == -1);
}

stack<Point> grahamScan(Point *points, int N)    {
    stack<Point> hull; // this is a stack of struct of points

    if (N < 3)return hull;
    
    // find the point having the least y coordinate (pivot),
    // ties are broken in favor of lower x coordinate
    
    int leastY = 0;
    for (int i = 1; i < N; i++)if (points[i] < points[leastY])leastY = i;
    // swap the pivot with the first point
    Point temp = points[0];points[0] = points[leastY];points[leastY] = temp;
    // sort the remaining point according to polar order about the pivot
    pivot = points[0];
    sort(points + 1, points + N, POLAR_ORDER);
    
    forall(i,0,N)cout << points[i].x << " " << points[i].y <<"\n";

    hull.push(points[0]);
    hull.push(points[1]);
    hull.push(points[2]);

    for (int i = 3; i < N; i++) {
        Point top = hull.top();
        hull.pop();
        while (ccw(hull.top(), top, points[i]) != -1)   {
            top = hull.top();
            hull.pop();
        }
        hull.push(top);
        hull.push(points[i]);
    }
    return hull;
}


//their is however a special case of three points in a line 
int main()  {
    Point points[] = {{0, 10}, {10, 10}, {10, 0}, {0,0},{5,5},{6,6},{7,7}, {6,7}};
    int N = sizeof(points)/sizeof(points[0]);

    stack<Point> hull = grahamScan(points, N);
    while (!hull.empty())   {
        Point p = hull.top();
        hull.pop();

        printf("(%d, %d)\n", p.x, p.y);
    }

    return 0;
}