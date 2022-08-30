#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef string::iterator stritr;
string str;

int charCnt[30];
int changeCnt;
int changeLst[30];

int main()
{
    cin >> str;

    for(stritr i = str.begin(); i != str.end(); i++)
        charCnt[*i - 'a']++;
    for(int i = 0; i < 30; i++)
        if(charCnt[i] & 1)
            changeCnt++,
            changeLst[changeCnt] = i;

    //if(str.size() & 1)
    //    changeCnt--;
    //changeCnt /= 2;

    for(int i = 1; i <= changeCnt/2; i++)
    {
        charCnt[changeLst[i]]++;
        charCnt[changeLst[changeCnt-i+1]]--;
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
