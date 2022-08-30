#include <iostream>
#include <cstring>
using namespace std;

typedef int64_t i64;
typedef uint64_t u64;

bool reversed;
int H, W;
char matrix[300][300];


int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T;
    cin >> T ;
    while(T--)
    {
        reversed = false;
        cin >> H >> W ;
        memset(matrix, 0x00, sizeof matrix);

        if(H & 1)
        {
            for(int i = 0; i < H; i++)
                for(int j = 0; j < W; j++)
                    matrix[i][j] = (j < W/2 ? '(' : ')');
        }
        else if(W & 1)
        {
            for(int i = 0; i < H; i++)
                for(int j = 0; j < W; j++)
                    matrix[i][j] = (i < H/2 ? '(' : ')');
        }
        else
        {
            if(H > W)
                swap(H, W), reversed = true;
            switch(H)
            {
            case 2:
                for(int i = 0; i < W; i++)
                    matrix[0][i] = '(', matrix[1][i] = ')';
                break;
            case 4:
                for(int i = 0; i < W; i++)
                    matrix[0][i] = '(', matrix[3][i] = ')',
                    matrix[1][i] = (i >= W/2 ? '(' : ')'),
                    matrix[2][i] = (i < W/2 ? '(' : ')');
                break;
            default:
                for(int i = 0; i < H; i++)
                    for(int j = 0; j < W; j++)
                        if(i == 0 || j == 0)
                            matrix[i][j] = '(';
                        else if(i == H-1 || j == W-1)
                            matrix[i][j] = ')';
                        else if(!((i ^ j) & 1))
                            matrix[i][j] = '(';
                        else
                            matrix[i][j] = ')';
            }
        }

        if(reversed)
            swap(H, W);

        for(int i = 0; i < H; i++)
        {
            for(int j = 0; j < W; j++)
                cout << matrix[i][j] ;
            cout << endl ;
        }
    }
    return 0;
}
