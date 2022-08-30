#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
    stack<string> back_st, forward_st;
    string str, url = "http://www.acm.org/";

    while(cin >> str)
    {
        if(str == "BACK" || str == "b")
        {
            if(back_st.empty())
                cout << "Ignored" << endl ;
            else
            {
                forward_st.push(url);
                url = back_st.top();
                back_st.pop();
                cout << url << endl ;
            }
        }

        if(str == "FORWARD" || str == "f")
        {
            if(forward_st.empty())
                cout << "Ignored" << endl ;
            else
            {
                back_st.push(url);
                url = forward_st.top();
                forward_st.pop();
                cout << url << endl ;
            }
        }

        if(str == "VISIT" || str == "v")
        {
            back_st.push(url);
            cin >> url ;
            cout << url << endl ;
            while(!forward_st.empty())
                forward_st.pop();
        }

        if(str == "QUIT")
            break;
    }

    return 0;
}
