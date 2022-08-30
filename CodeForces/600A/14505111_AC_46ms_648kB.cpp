#include <iostream>
#include <string>

using namespace std;
typedef string::iterator stritr;
string orgStr;
string numStr, othStr;

void ProcessString(string tmpStr)
{
    //cerr << tmpStr << endl ;
    bool isNumber = true;

    if(tmpStr.size() <= 0)
    {
        isNumber = false;
        goto END;
    }

    if(tmpStr.size() > 1)
        if(tmpStr[0] == '0')
        {
            isNumber = false;
            goto END;
        }

    for(stritr itr = tmpStr.begin(); itr != tmpStr.end(); itr++)
        if(!isdigit(*itr))
        {
            isNumber = false;
            goto END;
        }

END:
    if(isNumber)
        numStr.append(tmpStr),
        numStr.push_back(',');
    else
        othStr.append(tmpStr),
        othStr.push_back(',');
}

int main()
{
    cin >> orgStr;

    orgStr.push_back(';');

    stritr last = orgStr.begin();
    for(stritr itr = orgStr.begin(); itr != orgStr.end(); itr++)
    {
        if(*itr != ',' && *itr != ';')
            continue;
        string tmpStr(last, itr);
        ProcessString(tmpStr);
        last = itr + 1;
    }

    if(numStr.size() <= 0)
        cout << "-" << endl ;
    else
    {
        numStr.pop_back();
        cout << "\"" << numStr << "\"" << endl ;
    }

    if(othStr.size() <= 0)
        cout << "-" << endl ;
    else
    {
        othStr.pop_back();
        cout << "\"" << othStr << "\"" << endl ;
    }


    return 0;
}
