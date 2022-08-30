#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

map <string, char> inv_morse;
map <char, string> morse;

void init()
{
    inv_morse[".-"] = 'A';  inv_morse["-..."] = 'B';
    inv_morse["-.-."] = 'C';  inv_morse["-.."] = 'D';  inv_morse["."] = 'E';
    inv_morse["..-."] = 'F';  inv_morse["--."] = 'G';  inv_morse["...."] = 'H';
    inv_morse[".."] = 'I';  inv_morse[".---"] = 'J';  inv_morse["-.-"] = 'K';
    inv_morse[".-.."] = 'L';  inv_morse["--"] = 'M';  inv_morse["-."] = 'N';
    inv_morse["---"] = 'O';  inv_morse[".--."] = 'P';  inv_morse["--.-"] = 'Q';
    inv_morse[".-."] = 'R';  inv_morse["..."] = 'S';  inv_morse["-"] = 'T';
    inv_morse["..-"] = 'U';  inv_morse["...-"] = 'V';  inv_morse[".--"] = 'W';
    inv_morse["-..-"] = 'X';  inv_morse["-.--"] = 'Y';  inv_morse["--.."] = 'Z';

    inv_morse["..--"] = '_';  inv_morse["---."] = '.';
    inv_morse[".-.-"] = ',';  inv_morse["----"] = '?';

    morse['A'] = ".-";  morse['B'] = "-...";
    morse['C'] = "-.-.";  morse['D'] = "-..";  morse['E'] = ".";
    morse['F'] = "..-.";  morse['G'] = "--.";  morse['H'] = "....";
    morse['I'] = "..";  morse['J'] = ".---";  morse['K'] = "-.-";
    morse['L'] = ".-..";  morse['M'] = "--";  morse['N'] = "-.";
    morse['O'] = "---";  morse['P'] = ".--.";  morse['Q'] = "--.-";
    morse['R'] = ".-.";  morse['S'] = "...";  morse['T'] = "-";
    morse['U'] = "..-";  morse['V'] = "...-";  morse['W'] = ".--";
    morse['X'] = "-..-";  morse['Y'] = "-.--";  morse['Z'] = "--..";

    morse['_'] = "..--";  morse['.'] = "---.";
    morse[','] = ".-.-";  morse['?'] = "----";
}

int main()
{
    int kase;
    cin >> kase;

    init();
    for(int i = 1; i <= kase; i++)
    {
        vector <int> len;
        string str, tmp, tmp2;
        cin >> str ;
        cout << i << ": " ;
        //cerr << str << endl ;

        for(int i = 0; i < str.length(); i++)
        {
            tmp += morse[str[i]];
            len.push_back(morse[str[i]].length());
        }

        reverse(len.begin(), len.end());

        int cur = 0;
        for(vector<int>::iterator itr = len.begin(); itr != len.end(); itr++)
        {
            cout << inv_morse[tmp.substr(cur, *itr)] ;
            cur += *itr;
        }
        cout << endl ;
    }
}
