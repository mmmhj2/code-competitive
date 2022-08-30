#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

struct POINT
{
    int x, y;
    POINT() {};
    POINT(int _x, int _y)
    {
        x = _x, y = _y;
    }
};

struct PIECE : public POINT
{
    enum TYPE
    {
        General = 1,
        Chariot,
        Horse,
        Cannon,
    };
    TYPE tp;

    PIECE() {};
    PIECE(int _x, int _y, TYPE _tp)
    {
        x = _x, y = _y;
        tp = _tp;
    }

    bool operator == (const POINT & pt) const
    {
        return x == pt.x && y == pt.y;
    }
    bool operator == (const PIECE & pt) const
    {
        return x == pt.x && y == pt.y;
    }

    bool inBoard()
    {
        return x >= 1 && x <= 10 && y >= 1 && y <= 9;
    }
    bool inPalace()
    {
        return x >= 1 && x <= 3 && y >= 4 && y <= 6;
    }
};

istream & operator >> (istream & _in, POINT & pt)
{
    return _in >> pt.x >> pt.y ;
}
ostream & operator << (ostream & _out, POINT pt)
{
    return _out << "(" << pt.x << ", " << pt.y << ")" ;
}
ostream & operator << (ostream & _out, PIECE pt)
{
    return _out << "(" << pt.x << ", " << pt.y << ", " << pt.tp << ")" ;
}
void Output(const PIECE & t)
{
    cerr << t << endl ;
}

///////////////////////////////////////////////////////////////////////////////////////

const int DIR[5][2] = {{0,0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int n;
POINT bG;
bool has_piece[50][50];

///////////////////////////////////////////////////////////////////////////////////////

int maxx, maxy, minx, miny;

bool sub_General(const PIECE & bG, const PIECE & rP)
{
    const int & y = bG.y;
    if(bG.y == rP.y)
    {
        for(int i = minx + 1; i < maxx; i++)
            if(has_piece[i][y])
                return false;
        return true;
    }
    return false;
}
bool sub_Chariot(const PIECE & bG, const PIECE & rP)
{
    if(sub_General(bG, rP))
        return true;
    const int & x = bG.x;
    if(bG.x == rP.x)
    {
        for(int i = miny + 1; i < maxy; i++)
            if(has_piece[x][i])
                return false;
        return true;
    }
    return false;
}
bool sub_Horse(const PIECE & bG, const PIECE & rP)
{
    for(int i = 1; i <= 4; i++)
    {
        PIECE newrP (rP.x + DIR[i][0], rP.y + DIR[i][1], rP.tp);
        if(!newrP.inBoard())
            continue;

        const int & tx = newrP.x, ty = newrP.y;

        if(has_piece[tx][ty])
        {
            //cerr << "Hobbled" << endl;
            continue;
        }


        switch(i)
        {
        case 1:
            if(tx+1 == bG.x && ty+1 == bG.y) return 1;
            if(tx-1 == bG.x && ty+1 == bG.y) return 1;
            break;
        case 2:
            if(tx+1 == bG.x && ty-1 == bG.y) return 1;
            if(tx-1 == bG.x && ty-1 == bG.y) return 1;
            break;
        case 3:
            if(tx+1 == bG.x && ty-1 == bG.y) return 1;
            if(tx+1 == bG.x && ty+1 == bG.y) return 1;
            break;
        case 4:
            if(tx-1 == bG.x && ty-1 == bG.y) return 1;
            if(tx-1 == bG.x && ty+1 == bG.y) return 1;

        }
    }
    return false;
}
bool sub_Cannon(const PIECE & bG, const PIECE & rP)
{
    int cnt = 0;

    if(bG.y == rP.y)
    {
        for(int i = minx + 1; i < maxx; i++)
            if(has_piece[i][bG.y])
                cnt++;
        if(cnt == 1)
            return true;
    }
    cnt = 0;
    if(bG.x == rP.x)
    {
        for(int i = miny + 1; i < maxy; i++)
            if(has_piece[bG.x][i])
                cnt++;
        if(cnt == 1)
            return true;
    }

    return false;
}

bool is_dangerous(const PIECE & bG, const PIECE & rP)
{
    minx = min(bG.x, rP.x);
    maxx = max(bG.x, rP.x);
    miny = min(bG.y, rP.y);
    maxy = max(bG.y, rP.y);
    switch(rP.tp)
    {
    case PIECE::General:
        return sub_General(bG, rP);
        break;
    case PIECE::Chariot:
        return sub_Chariot(bG, rP);
        break;
    case PIECE::Horse:
        return sub_Horse(bG, rP);
        break;
    case PIECE::Cannon:
        return sub_Cannon(bG, rP);
        break;
    default:
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
    while(cin >> n >> bG)
    {
        //cerr << bG << endl ;
        if(n == 0 && bG.x == 0 && bG.y == 0)
            break;

        vector <PIECE> pList;
        char type;
        bool checkmate = false;
        PIECE pt;
        memset(has_piece, 0x00, sizeof has_piece);

        for(int i = 0; i < n; i++)
        {
            cin >> type >> pt ;
            has_piece[pt.x][pt.y] = true;
            switch(type)
            {
            case 'G':
                pt.tp = PIECE::General;
                break;
            case 'R':
                pt.tp = PIECE::Chariot;
                break;
            case 'H':
                pt.tp = PIECE::Horse;
                break;
            case 'C':
                pt.tp = PIECE::Cannon;
                break;
            }
            pList.push_back(pt);
        }
        //for_each(pList.begin(), pList.end(), Output);

        for(int i = 1; i <= 4; i++)
        {
            PIECE newbG(bG.x + DIR[i][0], bG.y + DIR[i][1], PIECE::General);
            if(!newbG.inPalace())
                continue;

            checkmate = false;
            //cerr << "Trying : " << newbG << endl ;

            for(vector<PIECE>::iterator itr = pList.begin(); itr != pList.end(); itr++)
            {
                if(newbG == *itr)
                {
                    //cerr << "Piece eaten" << endl ;
                    continue;
                }
                if(is_dangerous(newbG, *itr))
                {
                    checkmate = true;
                    break;
                }
            }
            if(!checkmate)
                break;
        }
        cout << (checkmate ? "YES" : "NO") << endl ;
    }
}
