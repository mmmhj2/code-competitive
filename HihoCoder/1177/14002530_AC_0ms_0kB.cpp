#include <algorithm>
#include <iostream>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

#define RANK_K 13
#define RANK_Q 12
#define RANK_J 11
#define RANK_A 1

string input[4];
vector <int> rnk;
vector <char> suit;
bool can_be_flushstraight = true;

bool judge_straight(vector <int> vec)
{
    sort(vec.begin(), vec.end());
    bool is_straight = true;
    for(int i = 0; i < 4; i++)
        if(vec[i]+1 != vec[i+1])
            is_straight = false;
    if(!is_straight)
        if(vec[0] == 1 && vec[1] == 10 && vec[2] == 11 && vec[3] == 12 && vec[4] == 13)
            is_straight = true;
    return is_straight;
}

int main()
{
    cin >> input[0] >> input[1] >> input[2] >> input[3];
    for(int i = 0; i < 4; i++)
    {
        const string & str = input[i];
        // 处理点数
        if(isdigit(str[0]))
        {
            if(str[0] == '1')
                rnk.push_back(10);
            else
                rnk.push_back(str[0]-'0');
        }
        else
        {
            switch(str[0])
            {
            case 'A':
                rnk.push_back(RANK_A);
                break;
            case 'J':
                rnk.push_back(RANK_J);
                break;
            case 'Q':
                rnk.push_back(RANK_Q);
                break;
            case 'K':
                rnk.push_back(RANK_K);
                break;
            }
        }
        // 处理花色
        suit.push_back(*str.rbegin());
    }
    // 处理同花顺
    for(int i = 0; i < 3; i++)
        if(suit[i] != suit[i+1])
        {
            can_be_flushstraight = false;
            break;
        }
    // 暴力模拟求解
    int poss = 0;
    for(int i = 1; i <= 13; i++)
    {
        rnk.push_back(i);
        poss += judge_straight(rnk);
        rnk.pop_back();
    }
    switch(poss)
    {
    case 0:
        cout << "0/1" ;
        break;
    case 1:
        if(can_be_flushstraight)
            cout << "1/16";     // 3/48
        else
            cout << "1/12";     // 4/48
        break;
    case 2:
        if(can_be_flushstraight)
            cout << "1/8";      // 6/48
        else
            cout << "1/6";      // 8/48
    }
    cout << endl ;
    return 0;
}
