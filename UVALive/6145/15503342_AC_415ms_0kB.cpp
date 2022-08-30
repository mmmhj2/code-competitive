#include <iostream>
#include <string>
#include <ext/rope>
using namespace std;

constexpr int MAXVERSION = 50000 + 10;
constexpr int MAXN = 200000;

__gnu_cxx::crope current, tmp, versions[MAXVERSION];
int versionCnt, disob;
int op1, op2, op3;
string str;
int N;

int main()
{
    cin >> N ;

    while(N--)
    {
        cin >> op1 ;

        switch(op1)
        {
        case 1:
            cin >> op2 >> str;
            op2 -= disob;
            current.insert(op2, str.c_str());
            versions[++versionCnt] = current;

            break;
        case 2:
            cin >> op2 >> op3;
            op2 -= disob, op3 -= disob;
            current.erase(op2-1, op3);
            versions[++versionCnt] = current;

            break;
        case 3:
            cin >> op1 >> op2 >> op3;
            op1 -= disob, op2 -= disob, op3 -= disob;
            tmp = versions[op1].substr(op2-1, op3);

            disob += count(tmp.begin(), tmp.end(), 'c');

            cout << tmp << endl ;

            break;
        }
    }

    return 0;
}
