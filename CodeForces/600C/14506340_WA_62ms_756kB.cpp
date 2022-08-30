#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef string::iterator stritr;
string str;

int charCnt[30];
int changeCnt;

int main()
{
    cin >> str;

    for(stritr i = str.begin(); i != str.end(); i++)
        charCnt[*i - 'a']++;
    for(int i = 0; i < 30; i++)
        if(charCnt[i] & 1)
            changeCnt++;
    if(str.size() & 1)
        changeCnt--;
    changeCnt /= 2;
    int changeFrom = 26, changeTo = -1;
    while(1)
    {
        if(changeCnt <= 0)
            break;
        for(int i = changeTo+1; i < 30; i++)
            if(charCnt[i] & 1)
            {
                changeTo = i;
                break;
            }
        for(int i = changeFrom-1; i >= 0; i--)
            if(charCnt[i] & 1)
            {
                changeFrom = i;
                break;
            }
        charCnt[changeFrom]--;
        charCnt[changeTo]++;
        changeCnt--;
    }

    string tmpStr, ansStr;
    int centre = -1;

    for(int i = 0; i < 26; i++)
        if(charCnt[i] & 1)
            centre = i;
        else
            for(int j = 0; j < charCnt[i] / 2; j++)
                tmpStr.push_back('a' + i);
    ansStr.append(tmpStr);

    if(centre >= 0)
        for(int i = 0; i < charCnt[centre]; i++)
            ansStr.push_back('a' + centre);

    reverse(tmpStr.begin(), tmpStr.end());
    ansStr.append(tmpStr);

    cout << ansStr << endl;
    return 0;
}
