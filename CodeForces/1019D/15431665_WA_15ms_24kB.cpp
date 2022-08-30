#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

template<typename val = int32_t, typename ret = int64_t>
struct _tagPoint
{
    typedef val value_type;

    value_type x, y;

    _tagPoint() = default;
    _tagPoint(const _tagPoint &) = default;

    _tagPoint(value_type _x, value_type _y)
    {
        x = _x, y = _y;
    }

    _tagPoint operator + (const _tagPoint & rhs) const
    {
        return _tagPoint(x + rhs.x, y + rhs.y);
    }

    _tagPoint operator - (const _tagPoint & rhs) const
    {
        return _tagPoint(x - rhs.x, y - rhs.y);
    }

    bool operator < (const _tagPoint & rhs) const
    {
        return make_pair(y, x) > make_pair(rhs.y, rhs.x);
    }

    friend ostream & operator << (ostream & out, const _tagPoint & rhs)
    {
        return out << "(" << rhs.x << "," << rhs.y << ")" ;
    }

    /**
        Scalar Product
    **/
    ret operator * (const _tagPoint & rhs) const
    {
        return ((ret)x) * ((ret)rhs.x) + ((ret)y) * ((ret)rhs.y);
    }

    /**
        Cross Product
    **/
    ret operator ^ (const _tagPoint & rhs) const
    {
        return ((ret)x) * ((ret)rhs.y) - ((ret)y) * ((ret)rhs.x);
    }
};

typedef _tagPoint<> CVector, CPoint;

int64_t triangle_area(const CPoint & a, const CPoint & b, const CPoint & c)
{
    return abs((a ^ b) + (b ^ c) + (c ^ a));
}

struct segment
{
    CVector vec;
    int id1, id2;

    segment () = default;
    segment (const CVector & _vec, int _id1, int _id2)
    {
        vec = _vec, id1 = _id1, id2 = _id2;
    }

    static bool CmpAngle(const segment & lhs, const segment & rhs)
    {
        return 0 < (lhs.vec ^ rhs.vec) ;
    }
};

const int MAXN = 2000 + 10;

int N;
int64_t S;
CPoint points[MAXN];
int loc[MAXN];
vector <segment> segments;

void PrintAnswer(const CPoint & a, const CPoint & b, const CPoint & c)
{
    cout << "Yes" << endl ;
    cout << a << endl << b << endl << c << endl ;
}

int main()
{
    cin >> N >> S ;

    for(int i = 1; i <= N; i++)
        cin >> points[i].x >> points[i].y ;
    sort(&points[1], &points[N+1]);

    for(int i = 1; i <= N; i++)
        for(int j = 1; j < i; j++)
            segments.push_back(segment(points[i] - points[j], i, j));
    sort(segments.begin(), segments.end(), segment::CmpAngle);
    for(int i = 1; i <= N; i++)
        loc[i] = i;

    for(vector<segment>::iterator itr = segments.begin(); itr != segments.end(); ++itr)
    {
        int & loc1 = loc[itr->id1];
        int & loc2 = loc[itr->id2];
        int L, R;

        L = 1, R = loc2;
        while(L <= R)
        {
            int mid = (L + R) >> 1;
            int64_t area = triangle_area(points[mid], points[loc1], points[loc2]);

            if(area == 2 * S)
            {
                PrintAnswer(points[mid], points[loc1], points[loc2]);
                exit(0);
            }

            if(area > 2 * S)
                L = mid + 1;
            else
                R = mid - 1;
        }

        L = loc1 + 2, R = N;
        while(L <= R)
        {
            int mid = (L + R) >> 1;
            int64_t area = triangle_area(points[mid], points[loc1], points[loc2]);

            if(area == 2 * S)
            {
                PrintAnswer(points[mid], points[loc1], points[loc2]);
                exit(0);
            }

            if(area < 2 * S)
                L = mid + 1;
            else
                R = mid - 1;
        }

        swap(points[loc1], points[loc2]);
        swap(loc1, loc2);
    }

    cout << "No" << endl ;
    return 0;
}

