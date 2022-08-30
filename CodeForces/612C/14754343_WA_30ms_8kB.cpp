#include <iostream>
#include <string>
using namespace std;

int unmatched[300];
string str;

inline int abs(int x)
{
    if(x > 0)
        return x;
    return -x;
}

int main()
{
    cin >> str ;

    for(string::iterator itr = str.begin(); itr != str.end(); itr++)
    {
        switch(*itr)
        {
        case '<':
        case '{':
        case '[':
        case '(':
            unmatched[0]++;
            unmatched[*itr]++;
            break;
        case '>':
        case '}':
        case ']':
            unmatched[0]--;
            unmatched[(*itr) - 2]--;
            break;
        case ')':
            unmatched[0]--;
            unmatched[(*itr) - 1]--;
            break;
        }
    }

    cerr << unmatched[0] << endl ;
    cerr << unmatched['<'] << unmatched['{'] << unmatched['['] << unmatched['('] << endl ;
    if(unmatched[0])
        cout << "Impossible" << endl ;
    else
        cout << (abs(unmatched['<']) + abs(unmatched['{']) + abs(unmatched['[']) + abs(unmatched['('])) / 2 << endl ;

    return 0;
}
