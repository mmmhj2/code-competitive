#include <iostream>
#include <array>
using namespace std;

typedef char *pChar;
char square[10][10];

constexpr pChar area[4][4] =
{
    {
        &square[0][0], &square[0][1], &square[1][1], &square[1][0]
    },
    {
        &square[0][1], &square[0][2], &square[1][2], &square[1][1]
    },
    {
        &square[1][0], &square[1][1], &square[2][1], &square[2][0]
    },
    {
        &square[1][1], &square[1][2], &square[2][2], &square[2][1]
    }
};

void rotate(int a, int d)
{
    char tmp;
    if(d < 0)     // Counter-clockwise
    {
        tmp = *area[a][0];
        *area[a][0] = *area[a][1];
        *area[a][1] = *area[a][2];
        *area[a][2] = *area[a][3];
        *area[a][3] = tmp;
    }
    else        // Clockwise
    {
        tmp = *area[a][0];
        *area[a][0] = *area[a][3];
        *area[a][3] = *area[a][2];
        *area[a][2] = *area[a][1];
        *area[a][1] = tmp;
    }
}

int T, op;
int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin >> T;
    while(T--)
    {
        cin >> op ;
        for(int i = 0; i < 3; i++)
            cin >> square[i];
        while(op--)
        {
            int a;
            char d;
            cin >> a >> d ;
            rotate(a - 1, (d == 'C' ? 1 : -1));
        }
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
                cout << square[i][j] ;
            cout << endl ;
        }

    }

    return 0;
}
